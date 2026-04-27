#!/usr/bin/env python3

import math
from typing import Dict

import rclpy
from ackermann_msgs.msg import AckermannDriveStamped
from rclpy.node import Node

from vlm_driver_msgs.msg import DrivingDecisions


class CommandMapperNode(Node):

    """converts discrete decisions into AckermannDriveStamped by
    subcribing to /baseline/decision and publishing to /vehicle/ackermann_cmd"""

    def __init__(self) -> None:
        super().__init__('command_mapper_node')

        self.declare_parameter('decision_topic', '/baseline/decision')
        self.declare_parameter('command_topic', '/drive')

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

        decision_topic = self.get_parameter('decision_topic').value
        command_topic = self.get_parameter('command_topic').value

        self.sub = self.create_subscription(
            DrivingDecisions,
            decision_topic,
            self.decision_callback, #everytime the topic is received run this call_back
            10
        )

        self.pub = self.create_publisher(
            AckermannDriveStamped,
            command_topic,
            10
        )

        self.get_logger().info('Command mapper node started.')

    def decision_callback(self, msg: DrivingDecisions) -> None:
        steering_deg = msg.steering_deg #starts from values in the msg field
        speed_mps = msg.speed_mps

        if msg.steering_label in self.steering_map_deg:
            steering_deg = self.steering_map_deg[msg.steering_label] #it just recomputes the mapping from labels to numbers 
            #(in case baseline doesn't send numeric values, which it will mostly) 

        if msg.speed_label in self.speed_map_mps:
            speed_mps = self.speed_map_mps[msg.speed_label]

        if msg.emergency_stop:
            speed_mps = 0.0

        cmd = AckermannDriveStamped()
        cmd.header = msg.header
        cmd.drive.steering_angle = math.radians(float(steering_deg)) #converting angle from deg to radians
        cmd.drive.speed = float(speed_mps)

        self.pub.publish(cmd)

        self.get_logger().info(
            f'Published ackermann cmd | source={msg.source} '
            f'steer={steering_deg:.1f} deg speed={speed_mps:.2f} m/s stop={msg.emergency_stop}'
        )


def main(args=None) -> None:
    rclpy.init(args=args)
    node = CommandMapperNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()