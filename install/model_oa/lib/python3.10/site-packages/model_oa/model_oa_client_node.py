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
    def __init__(self) -> None:
        super().__init__('model_oa_client')

        self.bridge = CvBridge() #library to conver ros msgs to opencv 

        self.model_url=os.environ.get('MODEL_OA_URL', "")
        if not self.model_url:
            self.get_logger().error(
                "MODEL_OA_URL is not set. Example: "
                "export MODEL_OA_URL=https://samaviajaffery--example-sglang-low-latency-sglang-dev.us-east.modal.direct/v1/chat/completions"
            )
         
        self.model_name = "Qwen/Qwen2.5-VL-7B-Instruct"

        self.declare_parameter('image_topic', '/camera/camera/color/image_raw')
        
        self.decision_topic = self.declare_parameter(
            "decision_topic",
            "/model_oa/decision"
        ).value

        self.request_period = float(
            self.declare_parameter("request_period", 1.0).value
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
        self.steering_map_deg: Dict[str, float] = {
            'hard_left': 40.0,
            'left': 25.0,
            'slight_left': 10.0,
            'straight': 0.0,
            'slight_right': -10.0,
            'right': -25.0,
            'hard_right': -40.0,
        }

        self.speed_map_mps: Dict[str, float] = {
            'stop': 0.0,
            'slow': 2.0,
            'medium': 3.0,
            'fast': 5.0,
        }

        self.image_sub = self.create_subscription(
            Image,
            image_topic,
            self.image_callback,
            10
        )

        self.decision_pub = self.create_publisher(
            DrivingDecisions,
            self.decision_topic,
            10
        )

        self.get_logger().info(f"Model OA client subscribing to {image_topic}")
        self.get_logger().info(f"Publishing model decisions to {self.decision_topic}")

  
    def image_callback(self, msg: Image) -> None:
        now = time.time()

        # Do not call the remote VLM at camera FPS.
        if now - self.last_request_time < self.request_period:
            return

        self.last_request_time = now

        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding="bgr8")
            jpeg_b64 = self.cv_image_to_base64_jpeg(cv_image)

            decision = self.call_model(jpeg_b64)

            steering_label= decision.get('steering_label')
            speed_label=decision.get('speed_label')
            emergency_stop=decision.get('emergency_stop')
            confidence=decision.get('confidence')

            if steering_label not in self.steering_map_deg:
                self.get_logger().warn(f'Invalid steering label from model {steering_label}')
                steering_label='straight'
            
            if speed_label not in self.speed_map_mps:
                self.get_logger().warn(f'Invalid speed label from model {speed_label}')
                speed_label='stop'

            if (emergency_stop):
                speed_label='stop'

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

            self.get_logger().info(f"Model OA decision: {decision}")
            self.get_logger().info(f"Model OA Decision msg: {decision_msg}")

        except Exception as e:
            self.get_logger().error(f"Model OA request failed: {e}")

    def cv_image_to_base64_jpeg(self, cv_image):
        h, w = cv_image.shape[:2]

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
        content = content.strip()

        if content.startswith("```json"):
            content = content.replace("```json", "", 1).strip()

        if content.startswith("```"):
            content = content.replace("```", "", 1).strip()

        if content.endswith("```"):
            content = content[:-3].strip()

        return content

    def call_model(self, jpeg_b64):
        image_data_url = f"data:image/jpeg;base64,{jpeg_b64}"

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
            parsed = json.loads(cleaned)
            return parsed
        except json.JSONDecodeError:
            self.get_logger().warn(f"Could not parse model JSON. Raw output: {content}")
            return content

def main(args=None) -> None:
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