#!/usr/bin/env python3
"""Map high-level driving decisions into Ackermann drive commands."""

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
        """Set up the ROS topics and the label-to-number maps."""
        super().__init__('command_mapper_node')

        # The mapper can listen to both the baseline CV output and the model output.
        self.declare_parameter('decision_topic1', '/baseline/decision')
        self.declare_parameter('decision_topic2', 'model_oa/decision')
        self.declare_parameter('command_topic', '/drive')

        # Steering labels stay human-readable until this node turns them into degrees.
        self.steering_map_deg: Dict[str, float] = {
            'hard_left': 40.0,
            'left': 25.0,
            'slight_left': 10.0,
            'straight': 0.0,
            'slight_right': -10.0,
            'right': -25.0,
            'hard_right': -40.0,
        }

        # Speed labels are converted to meters per second right before publishing.
        self.speed_map_mps: Dict[str, float] = {
            'stop': 0.0,
            'creep': 0.3,
            'slow': 1.0,
            'medium': 2.0,
            'fast': 3.0,
        }

        decision_topic1 = self.get_parameter('decision_topic1').value
        decision_topic2=self.get_parameter('decision_topic2').value
        command_topic = self.get_parameter('command_topic').value

        # Baseline CV decisions use the same callback as the model decisions.
        self.sub = self.create_subscription(
            DrivingDecisions,
            decision_topic1,
            self.decision_callback, #everytime the topic is received run this call_back
            10
        )

        # Model OA decisions also get mapped into the same Ackermann command format.
        self.sub = self.create_subscription(
            DrivingDecisions,
            decision_topic2,
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
        """Convert one DrivingDecisions message into an Ackermann command."""
        steering_deg = msg.steering_deg #starts from values in the msg field
        speed_mps = msg.speed_mps

        # Prefer the label map when the message gives a known steering label.
        if msg.steering_label in self.steering_map_deg:
            steering_deg = self.steering_map_deg[msg.steering_label] #it just recomputes the mapping from labels to numbers 
            #(in case baseline doesn't send numeric values, which it will mostly) 

        # Same idea for speed: labels make the upstream decision easy to read.
        if msg.speed_label in self.speed_map_mps:
            speed_mps = self.speed_map_mps[msg.speed_label]

        # Emergency stop always wins over any requested speed.
        if msg.emergency_stop:
            speed_mps = 0.0

        # Ackermann messages expect steering in radians, not degrees.
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
    """Start the command mapper node."""
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