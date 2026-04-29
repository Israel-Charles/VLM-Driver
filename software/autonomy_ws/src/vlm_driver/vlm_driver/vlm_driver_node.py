"""ROS 2 node: VLM-driven steering and speed controller."""

from __future__ import annotations

import json
import threading
from typing import Optional

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy

from sensor_msgs.msg import Image
from ackermann_msgs.msg import AckermannDriveStamped
from std_srvs.srv import Trigger
from std_msgs.msg import String  # used only for switch_model service-like topic

from cv_bridge import CvBridge
from PIL import Image as PILImage
import numpy as np

from .model_registry import (
    enable_hf_transfer_if_available,
    load_registry,
    resolve_hf_token,
)
from .inference_engine import InferenceEngine


def parse_json_loose(text: str):
    try:
        return json.loads(text)
    except json.JSONDecodeError:
        s = text.find("{")
        e = text.rfind("}")
        if s != -1 and e > s:
            try:
                return json.loads(text[s:e + 1])
            except json.JSONDecodeError:
                return None
    return None


class VlmDriverNode(Node):
    def __init__(self):
        super().__init__(
            "vlm_driver_node",
            allow_undeclared_parameters=True,
            automatically_declare_parameters_from_overrides=True,
        )

        # ---- read params (auto-declared from YAML + launch overrides) ----
        def _get_or(name, default):
            if self.has_parameter(name):
                return self.get_parameter(name).value
            return default

        self.models_config = _get_or("models_config", "")
        self.model_root_override = _get_or("model_root", "")
        self.selected_model = _get_or("selected_model", "llama_3_2_vision_11b")
        self.lazy_load = bool(_get_or("lazy_load", False))
        self.image_topic = _get_or("image_topic", "/camera/color/image_raw")
        self.drive_topic = _get_or("drive_topic", "/drive")
        self.rate_hz = float(_get_or("inference_rate_hz", 5.0))
        self.drop_stale = bool(_get_or("drop_stale_frames", True))
        self.max_new_tokens = int(_get_or("max_new_tokens", 128))
        self.hf_token_param = _get_or("hf_token", "")
        self.min_conf = float(_get_or("min_confidence_for_motion", 0.2))
        self.fallback_steer = _get_or("fallback_steering_label", "straight")
        self.fallback_speed = _get_or("fallback_speed_label", "stop")
        self.prompt = _get_or("prompt", "")

        self.steering_map_deg = self._read_float_map("steering_map_deg")
        self.speed_map_mps = self._read_float_map("speed_map_mps")

        if not self.steering_map_deg or not self.speed_map_mps:
            raise RuntimeError(
                "steering_map_deg and speed_map_mps must be set in the YAML "
                "(as nested keys, e.g. 'steering_map_deg.hard_left: 30.0')."
            )

        if not self.models_config:
            raise RuntimeError("Parameter 'models_config' is required.")

        # ---- registry + engine ----
        enable_hf_transfer_if_available()
        # Token: param wins, then env, then stored login
        self._hf_token = resolve_hf_token(self.hf_token_param)
        self.registry = load_registry(self.models_config, self.model_root_override)
        self.engine = InferenceEngine()

        # ---- ROS interfaces ----
        self.bridge = CvBridge()
        sensor_qos = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=1,
        )
        self.image_sub = self.create_subscription(
            Image, self.image_topic, self._on_image, sensor_qos
        )
        self.drive_pub = self.create_publisher(AckermannDriveStamped, self.drive_topic, 10)

        # Services
        self.create_service(Trigger, "~/load_model", self._srv_load)
        self.create_service(Trigger, "~/unload_model", self._srv_unload)
        # Switch model: write the desired key to /vlm_driver_node/selected_model param,
        # then call this service; or set the param on a running node.
        self.create_service(Trigger, "~/switch_model", self._srv_switch)
        self.add_on_set_parameters_callback(self._on_param_change)

        # State for inference loop
        self._latest_msg: Optional[Image] = None
        self._latest_lock = threading.Lock()
        self._infer_lock = threading.Lock()
        period = 1.0 / max(self.rate_hz, 0.1)
        self.timer = self.create_timer(period, self._tick)

        # Load now unless lazy
        if not self.lazy_load:
            self._load_selected()

        self.get_logger().info(
            f"vlm_driver_node ready. selected_model={self.selected_model}, "
            f"image={self.image_topic}, drive={self.drive_topic}, rate={self.rate_hz} Hz"
        )

    # ---------- helpers ----------

    def _read_float_map(self, prefix: str) -> dict:
        """Read a YAML map declared as <prefix>.<key>: <float> into a dict."""
        out = {}
        for sub_name, param in self.get_parameters_by_prefix(prefix).items():
            try:
                out[sub_name] = float(param.value)
            except (TypeError, ValueError):
                self.get_logger().warn(
                    f"param {prefix}.{sub_name} is not numeric; skipping"
                )
        return out

    def _load_selected(self):
        entry = self.registry.get(self.selected_model)
        local = entry.local_dir(self.registry.model_root)
        # Auto-download if the user forgot to run download_models first.
        if not (local / "config.json").is_file():
            self.get_logger().warn(
                f"Model not on disk at {local}. Downloading {entry.repo_id} ..."
            )
            from huggingface_hub import snapshot_download
            local.mkdir(parents=True, exist_ok=True)
            snapshot_download(
                repo_id=entry.repo_id, local_dir=str(local), token=self._hf_token,
            )
        self.get_logger().info(f"Loading {entry.repo_id} ({entry.family}) ...")
        self.engine.load(entry.family, local)
        self.get_logger().info("Model loaded.")

    # ---------- ROS callbacks ----------

    def _on_image(self, msg: Image):
        if self.drop_stale:
            with self._latest_lock:
                self._latest_msg = msg
        else:
            # Queue-of-1 still, but signaled by lock
            with self._latest_lock:
                if self._latest_msg is None:
                    self._latest_msg = msg

    def _tick(self):
        # Skip if a previous inference is still running
        if not self._infer_lock.acquire(blocking=False):
            return
        try:
            with self._latest_lock:
                msg = self._latest_msg
                self._latest_msg = None
            if msg is None:
                return
            if not self.engine.is_loaded():
                if self.lazy_load:
                    self._load_selected()
                else:
                    self._publish_fallback("model not loaded")
                    return

            try:
                cv_img = self.bridge.imgmsg_to_cv2(msg, desired_encoding="rgb8")
                pil_img = PILImage.fromarray(cv_img)
            except Exception as e:
                self.get_logger().warn(f"image convert failed: {e}")
                return

            try:
                raw, latency = self.engine.infer_pil(
                    pil_img, self.prompt, self.max_new_tokens
                )
            except Exception as e:
                self.get_logger().error(f"inference failed: {e}")
                self._publish_fallback("inference exception")
                return

            self.get_logger().info(f"latency={latency*1000:.1f} ms raw={raw[:400]}")
            parsed = parse_json_loose(raw)
            self._publish_from_parsed(parsed, msg.header)
        finally:
            self._infer_lock.release()

    # ---------- publishing ----------

    def _publish_from_parsed(self, parsed, header):
        if not isinstance(parsed, dict):
            self._publish_fallback("unparsable output", header)
            return
        steer_label = str(parsed.get("steering_label", self.fallback_steer))
        speed_label = str(parsed.get("speed_label", self.fallback_speed))

        emergency = self._coerce_bool(parsed.get("emergency_stop", False))
        confidence = self._coerce_float(parsed.get("confidence"), default=0.5)

        # Treat exact 0.0 as "model didn't fill it in" rather than zero confidence
        if confidence == 0.0:
            confidence = 0.9999

        if emergency:
            speed_label = "stop"

        if steer_label not in self.steering_map_deg:
            self.get_logger().warn(f"unknown steering_label '{steer_label}', using fallback")
            steer_label = self.fallback_steer
        if speed_label not in self.speed_map_mps:
            self.get_logger().warn(f"unknown speed_label '{speed_label}', using fallback")
            speed_label = self.fallback_speed

        steering_deg = self.steering_map_deg[steer_label]
        speed_mps = self.speed_map_mps[speed_label]

        if confidence < self.min_conf and not emergency:
            speed_mps = 0.0  # do not move if uncertain

        self._publish(steering_deg, speed_mps, header)

    def _publish_fallback(self, reason, header=None):
        self.get_logger().warn(f"publishing fallback: {reason}")
        steer_deg = self.steering_map_deg.get(self.fallback_steer, 0.0)
        speed_mps = self.speed_map_mps.get(self.fallback_speed, 0.0)
        self._publish(steer_deg, speed_mps, header)

    def _publish(self, steering_deg, speed_mps, header):
        out = AckermannDriveStamped()
        if header is not None:
            out.header = header
        else:
            out.header.stamp = self.get_clock().now().to_msg()
        out.header.frame_id = "base_link"
        out.drive.steering_angle = float(np.deg2rad(steering_deg))
        out.drive.speed = float(speed_mps)
        self.drive_pub.publish(out)

    # ---------- services ----------

    def _srv_load(self, _req, resp):
        try:
            self._load_selected()
            resp.success = True
            resp.message = f"loaded {self.selected_model}"
        except Exception as e:
            resp.success = False
            resp.message = str(e)
        return resp

    def _srv_unload(self, _req, resp):
        try:
            self.engine.unload()
            resp.success = True
            resp.message = "unloaded"
        except Exception as e:
            resp.success = False
            resp.message = str(e)
        return resp

    def _srv_switch(self, _req, resp):
        # Reads current selected_model param and (re)loads it.
        self.selected_model = self.get_parameter("selected_model") \
            .get_parameter_value().string_value
        try:
            self._load_selected()
            resp.success = True
            resp.message = f"switched to {self.selected_model}"
        except Exception as e:
            resp.success = False
            resp.message = str(e)
        return resp

    def _on_param_change(self, params):
        from rcl_interfaces.msg import SetParametersResult
        for p in params:
            if p.name == "selected_model" and p.value != self.selected_model:
                self.get_logger().info(
                    f"selected_model param changed to {p.value} (call switch_model to apply)"
                )
        return SetParametersResult(successful=True)

    @staticmethod
    def _coerce_bool(val) -> bool:
        """Handle real bools and string-typed bools that small VLMs love to emit."""
        if isinstance(val, bool):
            return val
        if isinstance(val, (int, float)):
            return val != 0
        if isinstance(val, str):
            return val.strip().lower() in ("true", "1", "yes", "y")
        return False

    @staticmethod
    def _coerce_float(val, default: float) -> float:
        if val is None:
            return default
        try:
            return float(val)  # works for numbers and numeric strings like "0.7"
        except (TypeError, ValueError):
            return default


def main(args=None):
    rclpy.init(args=args)
    node = VlmDriverNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        try:
            node.engine.unload()
        except Exception:
            pass
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()