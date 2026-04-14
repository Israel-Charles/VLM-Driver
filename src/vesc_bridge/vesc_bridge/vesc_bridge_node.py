#!/usr/bin/env python3

import rclpy
from ackermann_msgs.msg import AckermannDriveStamped
from rclpy.node import Node


class VescBridgeNode(Node):
    def __init__(self) -> None:
        super().__init__('vesc_bridge_node')

        self.declare_parameter('command_topic', '/vehicle/ackermann_cmd')

        command_topic = self.get_parameter('command_topic').value

        self.sub = self.create_subscription(
            AckermannDriveStamped,
            command_topic,
            self.cmd_callback,
            10
        )

        self.get_logger().info('VESC bridge node started.')

    def cmd_callback(self, msg: AckermannDriveStamped) -> None:
        steering_rad = float(msg.drive.steering_angle)
        speed_mps = float(msg.drive.speed)

        # TODO:
        # 1. Converting speed_mps to whatever the VESC interface expects
        # 2. Converting steering_rad to servo or steering motor command
        # 3. Sending commands over chosen transport (serial/CAN/etc.)

        self.get_logger().info(
            f'[VESC BRIDGE PLACEHOLDER] steering={steering_rad:.3f} rad speed={speed_mps:.3f} m/s'
        )


def main(args=None) -> None:
    rclpy.init(args=args)
    node = VescBridgeNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()