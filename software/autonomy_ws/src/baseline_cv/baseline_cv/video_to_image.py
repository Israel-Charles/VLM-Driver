#!/usr/bin/env python3
"""Read frames from a video file and publish them as ROS Image messages."""

import cv2
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge


class VideoToImagePublisher(Node):
    """Turn a saved video into a camera-like image stream."""

    def __init__(self):
        """Open the video file and publish frames at the video's FPS."""
        super().__init__("video_to_image_publisher")

        self.declare_parameter("video_path", "")
        self.declare_parameter("image_topic", "/camera/camera/color/image_raw")
        self.declare_parameter("frame_id", "camera_color_optical_frame")
        self.declare_parameter("loop", True)

        self.video_path = self.get_parameter("video_path").value
        self.image_topic = self.get_parameter("image_topic").value
        self.frame_id = self.get_parameter("frame_id").value
        self.loop = self.get_parameter("loop").value

        if self.video_path == "":
            raise RuntimeError("Please provide video_path:=/path/to/video.mp4")

        self.cap = cv2.VideoCapture(self.video_path)

        if not self.cap.isOpened():
            raise RuntimeError(f"Could not open video: {self.video_path}")

        self.bridge = CvBridge()
        self.publisher = self.create_publisher(Image, self.image_topic, 10)

        fps = self.cap.get(cv2.CAP_PROP_FPS)
        if fps <= 0:
            fps = 30.0

        self.timer = self.create_timer(1.0 / fps, self.publish_frame)

        self.get_logger().info(f"Publishing video frames on: {self.image_topic}")
        self.get_logger().info(f"Video FPS: {fps}")

    def publish_frame(self):
        """Publish one video frame, looping back if requested."""
        ret, frame = self.cap.read()

        if not ret:
            if self.loop:
                self.get_logger().info("Restarting video from beginning")
                self.cap.set(cv2.CAP_PROP_POS_FRAMES, 0)
                return
            else:
                self.get_logger().info("Video finished")
                return

        msg = self.bridge.cv2_to_imgmsg(frame, encoding="bgr8")
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = self.frame_id

        self.publisher.publish(msg)


def main(args=None):
    """Start the video-to-image publisher."""
    rclpy.init(args=args)
    node = VideoToImagePublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()