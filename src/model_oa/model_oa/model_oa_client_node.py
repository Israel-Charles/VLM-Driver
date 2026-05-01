"""ROS client node that asks a remote vision-language model for driving decisions."""

import base64
import json
import os
import time

import cv2
import requests
from typing import Dict

import rclpy
from cv_bridge import CvBridge
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import String
from vlm_driver_msgs.msg import DrivingDecisions, PipelineMetrics


class ModelOAClient(Node):
    """Send camera frames to the remote model and publish its driving decision."""

    def __init__(self) -> None:
        """Set up model settings, ROS topics, and debug overlay publishing."""
        super().__init__('model_oa_client')

        # CvBridge handles conversion between ROS Image messages and OpenCV arrays.
        self.bridge = CvBridge() #library to conver ros msgs to opencv 

        # The model endpoint is kept in the environment so it is not hard-coded into launch files.
        self.model_url=os.environ.get('MODEL_OA_URL', "")
        if not self.model_url:
            self.get_logger().error(
                "MODEL_OA_URL is not set. Example: "
                "export MODEL_OA_URL=https://samaviajaffery--example-sglang-low-latency-sglang-dev.us-east.modal.direct/v1/chat/completions"
            )
         
        self.model_name = "Qwen/Qwen2.5-VL-7B-Instruct"

        # Parameters keep the camera topic and model request settings easy to tune.
        self.declare_parameter('image_topic', '/camera/camera/color/image_raw')
        
        self.decision_topic = self.declare_parameter(
            "decision_topic",
            "/model_oa/decision"
        ).value

        self.request_period = float(
            self.declare_parameter("request_period", 0.5).value
        )

        self.resize_width = int(
            self.declare_parameter("resize_width", 640).value
        )

        self.jpeg_quality = int(
            self.declare_parameter("jpeg_quality", 70).value
        )

        self.last_request_time = 0.0

        image_topic = self.get_parameter('image_topic').value #subscribes to the camera image topic

        
        #driving decision map
        # Convert model steering labels into numeric angles for downstream nodes.
        self.steering_map_deg: Dict[str, float] = {
            'hard_left': 40.0,
            'left': 25.0,
            'slight_left': 10.0,
            'straight': 0.0,
            'slight_right': -10.0,
            'right': -25.0,
            'hard_right': -40.0,
        }

        # Convert model speed labels into meters per second.
        self.speed_map_mps: Dict[str, float] = {
            'stop': 0.0,
            'slow': 2.0,
            'medium': 3.0,
            'fast': 5.0,
        }

        # Subscribe to the camera stream that will be sampled for model requests.
        self.image_sub = self.create_subscription(
            Image,
            image_topic,
            self.image_callback,
            10
        )

        # Publish the structured decision that the mapper node can consume.
        self.decision_pub = self.create_publisher(
            DrivingDecisions,
            self.decision_topic,
            10
        )
        
        self.overlay_topic = self.declare_parameter(
            "overlay_topic",
            "/model_oa/overlay_image"
        ).value

        # Overlay images are useful for seeing what the model decided on each request.
        self.overlay_pub = self.create_publisher(
            Image,
            self.overlay_topic,
            10
        )

        self.get_logger().info(f"Publishing model overlay image to {self.overlay_topic}")
        self.get_logger().info(f"Model OA client subscribing to {image_topic}")
        self.get_logger().info(f"Publishing model decisions to {self.decision_topic}")

  
    def image_callback(self, msg: Image) -> None:
        """Throttle camera frames, call the model, and publish the model decision."""
        now = time.time()

        # Do not call the remote VLM at camera FPS.
        if now - self.last_request_time < self.request_period:
            return

        self.last_request_time = now

        try:
            # Convert the ROS image into a small JPEG payload for the HTTP request.
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding="bgr8")
            jpeg_b64 = self.cv_image_to_base64_jpeg(cv_image)

            # Ask the model for a driving decision in JSON form.
            decision = self.call_model(jpeg_b64)

            steering_label= decision.get('steering_label')
            speed_label=decision.get('speed_label')
            emergency_stop=decision.get('emergency_stop')
            confidence=decision.get('confidence')

            # Fall back to safe labels if the model returns something outside the expected set.
            if steering_label not in self.steering_map_deg:
                self.get_logger().warn(f'Invalid steering label from model {steering_label}')
                steering_label='straight'
            
            if speed_label not in self.speed_map_mps:
                self.get_logger().warn(f'Invalid speed label from model {speed_label}')
                speed_label='stop'

            if (emergency_stop):
                speed_label='stop'

            # Package the model output into the same decision message used by the baseline.
            decision_msg = DrivingDecisions()
            decision_msg.header = msg.header
            decision_msg.source = "model_oa"
            decision_msg.steering_label = steering_label
            decision_msg.speed_label = speed_label
            decision_msg.steering_deg = float(self.steering_map_deg[steering_label])
            decision_msg.speed_mps = float(self.speed_map_mps[speed_label])
            decision_msg.confidence = float(confidence)
            decision_msg.emergency_stop = bool(emergency_stop)

            self.decision_pub.publish(decision_msg)
            reason = decision.get("reason", "")

            # Draw a debug image so the model choice can be checked visually.
            overlay_image = self.draw_decision_overlay(
                cv_image,
                steering_label,
                speed_label,
                confidence,
                emergency_stop,
                reason
            )

            overlay_msg = self.bridge.cv2_to_imgmsg(overlay_image, encoding="bgr8")
            overlay_msg.header = msg.header
            self.overlay_pub.publish(overlay_msg)

            self.get_logger().info(f"Model OA decision: {decision}")
            self.get_logger().info(f"Model OA Decision msg: {decision_msg}")

        except Exception as e:
            self.get_logger().error(f"Model OA request failed: {e}")
    
    def draw_decision_overlay(
        self,
        cv_image,
        steering_label,
        speed_label,
        confidence,
        emergency_stop,
        reason=""
    ):
        """Draw the model's selected command and steering direction on the frame."""
        overlay = cv_image.copy()
        h, w = overlay.shape[:2]

        # Draw left / center / right visual regions, similar to baseline CV
        cv2.line(overlay, (w // 3, 0), (w // 3, h), (255, 255, 0), 2)
        cv2.line(overlay, (2 * w // 3, 0), (2 * w // 3, h), (255, 255, 0), 2)

        cv2.putText(
            overlay,
            "LEFT",
            (30, 40),
            cv2.FONT_HERSHEY_SIMPLEX,
            1.0,
            (255, 255, 0),
            2
        )

        cv2.putText(
            overlay,
            "CENTER",
            (w // 3 + 30, 40),
            cv2.FONT_HERSHEY_SIMPLEX,
            1.0,
            (255, 255, 0),
            2
        )

        cv2.putText(
            overlay,
            "RIGHT",
            (2 * w // 3 + 30, 40),
            cv2.FONT_HERSHEY_SIMPLEX,
            1.0,
            (255, 255, 0),
            2
        )

        # Decision panel
        panel_h = 150
        cv2.rectangle(overlay, (0, 0), (w, panel_h), (0, 0, 0), -1)

        # Red means stop condition, green means the model thinks it can keep moving.
        status_color = (0, 0, 255) if emergency_stop else (0, 255, 0)

        cv2.putText(
            overlay,
            f"MODEL OA",
            (20, 35),
            cv2.FONT_HERSHEY_SIMPLEX,
            1.0,
            status_color,
            2
        )

        cv2.putText(
            overlay,
            f"Steering: {steering_label}",
            (20, 75),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.8,
            (255, 255, 255),
            2
        )

        cv2.putText(
            overlay,
            f"Speed: {speed_label} | Conf: {confidence:.2f}",
            (20, 110),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.8,
            (255, 255, 255),
            2
        )

        cv2.putText(
            overlay,
            f"Emergency Stop: {emergency_stop}",
            (20, 145),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.75,
            status_color,
            2
        )

        # Steering arrow
        steering_deg = self.steering_map_deg.get(steering_label, 0.0)

        # Start near the bottom middle so the arrow looks like the vehicle's next motion.
        start_point = (w // 2, h - 40)

        # Positive steering means left in your map, so x moves left
        dx = int(-(steering_deg / 40.0) * (w * 0.35))
        end_point = (w // 2 + dx, int(h * 0.55))

        cv2.arrowedLine(
            overlay,
            start_point,
            end_point,
            status_color,
            6,
            tipLength=0.25
        )

        if reason:
            # Keep the reason short enough that it stays on one visible line.
            cv2.putText(
                overlay,
                f"Reason: {reason[:70]}",
                (20, h - 15),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.65,
                (255, 255, 255),
                2
            )

        return overlay

    def cv_image_to_base64_jpeg(self, cv_image):
        """Resize and JPEG-encode an OpenCV image for the model request."""
        h, w = cv_image.shape[:2]

        # Shrinking wide frames keeps the remote request lighter and faster.
        if self.resize_width > 0 and w > self.resize_width:
            scale = self.resize_width / float(w)
            new_h = int(h * scale)
            cv_image = cv2.resize(cv_image, (self.resize_width, new_h))

        encode_params = [
            int(cv2.IMWRITE_JPEG_QUALITY),
            self.jpeg_quality
        ]

        success, buffer = cv2.imencode(".jpg", cv_image, encode_params)

        if not success:
            raise RuntimeError("Failed to JPEG-encode image")

        return base64.b64encode(buffer).decode("utf-8")
    
    def clean_model_json(self, content: str) -> str:
        """Remove markdown fences if the model wraps the JSON anyway."""
        content = content.strip()

        # The prompt asks for raw JSON, but this protects against common markdown output.
        if content.startswith("```json"):
            content = content.replace("```json", "", 1).strip()

        if content.startswith("```"):
            content = content.replace("```", "", 1).strip()

        if content.endswith("```"):
            content = content[:-3].strip()

        return content

    def call_model(self, jpeg_b64):
        """Send one image to the model endpoint and parse the JSON decision."""
        image_data_url = f"data:image/jpeg;base64,{jpeg_b64}"

        # The prompt keeps the output small and easy for this node to parse.
        prompt = """
    You are the obstacle avoidance model for a small autonomous vehicle.

    Look at the front camera image and choose a safe driving action.

    Return raw JSON only.
    Do not use markdown.
    Do not use ```json.
    Do not add explanation outside the JSON.

    Allowed steering_label values:
    hard_left, left, slight_left, straight, slight_right, right, hard_right

    Allowed speed_label values:
    stop, slow, medium, fast

    Rules:
    - Use emergency_stop=true if there is an immediate collision risk.
    - If emergency_stop=true, speed_label must be "stop".
    - confidence must be a number between 0.0 and 1.0.

    JSON format:
    {
    "steering_label": "...",
    "speed_label": "...",
    "confidence": 0.0,
    "emergency_stop": false,
    "reason": "short reason"
    }
        }
    """
        payload = {
                "model": self.model_name,
                "messages": [
                    {
                        "role": "user",
                        "content": [
                            {
                                "type": "text",
                                "text": prompt
                            },
                            {
                                "type": "image_url",
                                "image_url": {
                                "url": image_data_url
                            }
                        }
                    ]
                }
            ],
            "temperature": 0,
            "max_tokens": 128
        }

        # This endpoint is OpenAI-compatible, so the request uses chat completions format.
        response = requests.post(
            self.model_url,
            json=payload,
            timeout=20
        )

        response.raise_for_status()
        data = response.json()

        content = data["choices"][0]["message"]["content"]
        cleaned = self.clean_model_json(content)

      
        try:
            # Return a dict when the model followed the JSON instruction.
            parsed = json.loads(cleaned)
            return parsed
        except json.JSONDecodeError:
            self.get_logger().warn(f"Could not parse model JSON. Raw output: {content}")
            return content

def main(args=None) -> None:
    """Start the model OA client node."""
    rclpy.init(args=args)
    node = ModelOAClient()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()