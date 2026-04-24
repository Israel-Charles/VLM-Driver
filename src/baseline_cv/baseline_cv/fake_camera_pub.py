#!/usr/bin/env python3

import rclpy
import cv2
import numpy as np

from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge


class FakeCameraPublisher(Node):
    def __init__(self):
        super().__init__('fake_camera_publisher')

        self.pub = self.create_publisher(Image, '/camera/image_raw', 10)
        self.bridge = CvBridge()

        self.timer = self.create_timer(1.0, self.publish_test_frame)
        self.step = 0

        self.width = 640
        self.height = 480

        self.get_logger().info('Fake camera publisher started.')

    def make_base_frame(self):
        # Dark background so synthetic obstacles stand out
        frame = np.zeros((self.height, self.width, 3), dtype=np.uint8)

        # Draw a simple floor-like guide so image isn't totally empty
        cv2.line(frame, (0, self.height - 1), (self.width - 1, self.height - 1), (50, 50, 50), 2)
        return frame

    def add_obstacle(self, frame, x1, y1, x2, y2):
        # White rectangle = strong edges for Canny
        cv2.rectangle(frame, (x1, y1), (x2, y2), (255, 255, 255), -1)

    def publish_test_frame(self):
        frame = self.make_base_frame()
        label = ""

        # IMPORTANT:
        # Baseline node uses roi_top_ratio=0.55, so only bottom 45% matters.
        # For a 480px image, ROI starts near y=264.
        # Put synthetic obstacles BELOW that.
        if self.step == 0:
            label = "clear"
            # no obstacle

        elif self.step == 1:
            label = "center obstacle"
            self.add_obstacle(frame, 260, 320, 380, 460)

        elif self.step == 2:
            label = "left obstacle"
            self.add_obstacle(frame, 40, 320, 180, 460)

        elif self.step == 3:
            label = "right obstacle"
            self.add_obstacle(frame, 460, 320, 600, 460)

        elif self.step == 4:
            label = "all blocked"
            self.add_obstacle(frame, 20, 320, 200, 460)
            self.add_obstacle(frame, 230, 320, 410, 460)
            self.add_obstacle(frame, 440, 320, 620, 460)

        elif self.step == 5:
            label = "center+right blocked"
            self.add_obstacle(frame, 240, 320, 390, 460)
            self.add_obstacle(frame, 430, 320, 610, 460)

        msg = self.bridge.cv2_to_imgmsg(frame, encoding='bgr8')
        self.pub.publish(msg)

        self.get_logger().info(f'Published fake frame: {label}')

        self.step = (self.step + 1) % 6


def main(args=None):
    rclpy.init(args=args)
    node = FakeCameraPublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()