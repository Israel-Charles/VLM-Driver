#!/usr/bin/env python3

import time
from typing import Dict, Tuple

import cv2
import numpy as np
import rclpy
from cv_bridge import CvBridge
from rclpy.node import Node
from sensor_msgs.msg import Image

from vlm_driver_msgs.msg import DrivingDecisions, PipelineMetrics


class BaselineCVNode(Node):
    def __init__(self) -> None:
        super().__init__('baseline_cv_node')

        self.bridge = CvBridge() #library to conver ros msgs to opencv 

        self.declare_parameter('image_topic', '/camera/camera/color/image_raw')
        self.declare_parameter('roi_top_ratio', 0) #no cutting
        self.declare_parameter('blur_kernel', 5)
        self.declare_parameter('canny_low', 60)
        self.declare_parameter('canny_high', 150)
        self.declare_parameter('dilate_iterations', 1)

        self.declare_parameter('stop_score_threshold', 0.08)
        self.declare_parameter('blocked_score_threshold', 0.05)
        self.declare_parameter('fast_score_threshold', 0.015)
        self.declare_parameter('medium_score_threshold', 0.04)

        image_topic = self.get_parameter('image_topic').value #subscribes to the camera image topic

        self.image_sub = self.create_subscription(
            Image,
            image_topic,
            self.image_callback,
            10
        )

        self.decision_pub = self.create_publisher(
            DrivingDecisions,
            '/baseline/decision',
            10
        )
        self.overlay_pub = self.create_publisher(
            Image,
            '/baseline/debug/overlay',
            10
        )
        self.mask_pub = self.create_publisher(
            Image,
            '/baseline/debug/mask',
            10
        )
        self.metrics_pub = self.create_publisher(
            PipelineMetrics,
            '/baseline/metrics',
            10
        )

        self.last_frame_time = None

        self.stop_streak = 0
        self.creep_frames_left = 0
        self.creep_steering_label = 'straight'

        self.declare_parameter('creep_trigger_frames', 10)
        self.declare_parameter('creep_duration_frames', 12)
        self.declare_parameter('creep_clear_margin', 0.03)

        self.steering_map_deg: Dict[str, float] = {
            'hard_left': 30.0,
            'left': 20.0,
            'slight_left': 10.0,
            'straight': 0.0,
            'slight_right': -10.0,
            'right': -20.0,
            'hard_right': -30.0,
        }

        self.speed_map_mps: Dict[str, float] = {
            'stop': 0.0,
            'creep': 0.3,
            'slow': 1.0,
            'medium': 2.0,
            'fast': 3.0,
        }

        self.get_logger().info('Baseline CV node started.')

    def image_callback(self, msg: Image) -> None:
        total_start = time.perf_counter()

        try:
            #converts img to cv2
            frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8') #3 bit unsigned BGR image
        except Exception as exc:
            self.get_logger().error(f'Failed to convert image: {exc}')
            return

        preprocess_start = time.perf_counter()
        roi, roi_offset_y = self.extract_roi(frame)
        mask = self.compute_obstacle_mask(roi)
        preprocess_end = time.perf_counter()

        decision_start = time.perf_counter()
        sector_scores = self.compute_sector_scores(mask)
        steering_label, speed_label, confidence, emergency_stop = self.make_decision(sector_scores)
        steering_label, speed_label, confidence, emergency_stop = self.apply_creep_recovery(
        sector_scores,
        steering_label,
        speed_label,
        confidence,
        emergency_stop )
        decision_end = time.perf_counter()

        decision_msg = DrivingDecisions()
        decision_msg.header = msg.header
        decision_msg.source = 'baseline'
        decision_msg.steering_label = steering_label
        decision_msg.speed_label = speed_label
        decision_msg.steering_deg = float(self.steering_map_deg[steering_label])
        decision_msg.speed_mps = float(self.speed_map_mps[speed_label])
        decision_msg.confidence = float(confidence)
        decision_msg.emergency_stop = bool(emergency_stop)
        self.decision_pub.publish(decision_msg)
         
        self.get_logger().info(f"Speed_label: {decision_msg.speed_label}, steering_label: {decision_msg.steering_label}")
        overlay = self.draw_overlay(
            frame=frame,
            roi=roi,
            roi_offset_y=roi_offset_y,
            mask=mask,
            sector_scores=sector_scores,
            steering_label=steering_label,
            speed_label=speed_label,
            confidence=confidence,
            emergency_stop=emergency_stop,
        )

        try:
            overlay_msg = self.bridge.cv2_to_imgmsg(overlay, encoding='bgr8')
            overlay_msg.header = msg.header
            self.overlay_pub.publish(overlay_msg)

            mask_bgr = cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR)
            mask_msg = self.bridge.cv2_to_imgmsg(mask_bgr, encoding='bgr8')
            mask_msg.header = msg.header
            self.mask_pub.publish(mask_msg)
        except Exception as exc:
            self.get_logger().warn(f'Failed to publish debug image: {exc}')

        total_end = time.perf_counter()

        fps = 0.0
        now = time.perf_counter()
        if self.last_frame_time is not None:
            dt = now - self.last_frame_time
            if dt > 1e-6:
                fps = 1.0 / dt
        self.last_frame_time = now

        metrics = PipelineMetrics()
        metrics.header = msg.header
        metrics.source = 'baseline'
        metrics.preprocess_ms = float((preprocess_end - preprocess_start) * 1000.0)
        metrics.decision_ms = float((decision_end - decision_start) * 1000.0)
        metrics.total_ms = float((total_end - total_start) * 1000.0)
        metrics.fps = float(fps)
        self.metrics_pub.publish(metrics)
    
    
    def extract_roi(self, frame: np.ndarray) -> Tuple[np.ndarray, int]:

        """
        It selects the amount of image to use near the ground. For the ground, most 
        of the useful data is present near the ground.
        """
        h, _, _ = frame.shape
        roi_top_ratio = float(self.get_parameter('roi_top_ratio').value)
        roi_y = int(h * roi_top_ratio)
        roi = frame[roi_y:, :] #using the bottom half of the image
        return roi, roi_y

    def compute_obstacle_mask(self, roi: np.ndarray) -> np.ndarray:
        """
        Computes obstacle mask.

        For the current track, the main obstacle is orange.
        So instead of detecting generic edges, detect orange regions in HSV.
        White pixels = obstacle.
        Black pixels = free/ignored.
        """

        # Convert BGR image to HSV because color thresholding is easier in HSV.
        hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)

        # Orange color range.
        lower_orange = np.array([0, 45, 40], dtype=np.uint8)
        upper_orange = np.array([35, 255, 255], dtype=np.uint8)

        mask = cv2.inRange(hsv, lower_orange, upper_orange)

        # Clean small holes and random dots.
        kernel = np.ones((5, 5), np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel, iterations=1)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=1)

        # Remove very small blobs.
        num_labels, labels, stats, _ = cv2.connectedComponentsWithStats(mask, connectivity=8)
        cleaned = np.zeros_like(mask)

        min_area = 80

        for label in range(1, num_labels):
            area = stats[label, cv2.CC_STAT_AREA]
            if area >= min_area:
                cleaned[labels == label] = 255

        return cleaned

    def compute_sector_scores(self, mask: np.ndarray) -> Dict[str, float]:

        """
        Computes score based on mask
        if score is near 0, the area is empty else there's an obstalce
        """
        h, w = mask.shape
        third = w // 3 #dividing the obstacles into 3 parts

        left = mask[:, :third]
        center = mask[:, third:2 * third]
        right = mask[:, 2 * third:]

        def score(region: np.ndarray) -> float:
            total_pixels = float(region.size)
            if total_pixels == 0:
                return 1.0
            return float(np.count_nonzero(region)) / total_pixels

        return {
            'left': score(left),
            'center': score(center),
            'right': score(right),
        }

    def make_decision(self, scores: Dict[str, float]) -> Tuple[str, str, float, bool]:
        left = scores['left']
        center = scores['center']
        right = scores['right']

        stop_thresh = float(self.get_parameter('stop_score_threshold').value)
        blocked_thresh = float(self.get_parameter('blocked_score_threshold').value)
        fast_thresh = float(self.get_parameter('fast_score_threshold').value)
        medium_thresh = float(self.get_parameter('medium_score_threshold').value)

        all_blocked = left > blocked_thresh and center > blocked_thresh and right > blocked_thresh
        center_heavily_blocked = center > stop_thresh

        if all_blocked or center_heavily_blocked:
            if left < right and left < blocked_thresh: #greater number means more obstacles
                return 'left', 'slow', 0.75, False
            if right < left and right < blocked_thresh:
                return 'right', 'slow', 0.75, False
            return 'straight', 'stop', 0.90, True

        best_sector = min(scores, key=scores.get) #most clear region
        spread = max(scores.values()) - min(scores.values())
        confidence = max(0.1, min(1.0, 0.5 + 2.0 * spread)) #if one region is different from the other, confidence is high

        if best_sector == 'center':
            if center < fast_thresh and left < medium_thresh and right < medium_thresh:
                return 'straight', 'fast', confidence, False
            return 'straight', 'medium', confidence, False

        if best_sector == 'left':
            if left + 0.03 < center:
                return 'left', 'slow', confidence, False
            return 'slight_left', 'slow', confidence, False

        if right + 0.03 < center:
            return 'right', 'slow', confidence, False
        return 'slight_right', 'slow', confidence, False
     
    def apply_creep_recovery(
        self,
        scores: Dict[str, float],
        steering_label: str,
        speed_label: str,
        confidence: float,
        emergency_stop: bool
    ) -> Tuple[str, str, float, bool]:
        """
        Forward-only recovery.

        If the car has been stopped for several frames, it creeps very slowly
        toward the side with the lower obstacle score.
        """

        trigger_frames = int(self.get_parameter('creep_trigger_frames').value)
        creep_duration = int(self.get_parameter('creep_duration_frames').value)
        margin = float(self.get_parameter('creep_clear_margin').value)

        left = scores['left']
        center = scores['center']
        right = scores['right']

        # If already creeping, keep the same command for a short time.
        if self.creep_frames_left > 0:
            self.creep_frames_left -= 1
            return self.creep_steering_label, 'creep', 0.70, False

        # Count consecutive stop frames.
        if speed_label == 'stop':
            self.stop_streak += 1
        else:
            self.stop_streak = 0

        # Not stuck long enough yet.
        if self.stop_streak < trigger_frames:
            return steering_label, speed_label, confidence, emergency_stop

        # Reset stop streak once recovery begins.
        self.stop_streak = 0

        # Pick the clearer side.
        # Lower score = less obstacle.
        if left + margin < right:
            self.creep_steering_label = 'hard_left'
        elif right + margin < left:
            self.creep_steering_label = 'hard_right'
        else:
            # If both sides look similar, do not blindly creep.
            # This avoids driving into a fully blocked wall.
            return 'straight', 'stop', 0.90, True

        self.creep_frames_left = creep_duration

        return self.creep_steering_label, 'creep', 0.70, False
    def draw_overlay(
        self,
        frame: np.ndarray,
        roi: np.ndarray,
        roi_offset_y: int,
        mask: np.ndarray,
        sector_scores: Dict[str, float],
        steering_label: str,
        speed_label: str,
        confidence: float,
        emergency_stop: bool,
    ) -> np.ndarray:
        overlay = frame.copy()
        h, w, _ = frame.shape
        roi_h, roi_w, _ = roi.shape

        cv2.rectangle(overlay, (0, roi_offset_y), (w - 1, h - 1), (0, 255, 255), 2)

        third = roi_w // 3
        x1 = third
        x2 = 2 * third

        cv2.line(overlay, (x1, roi_offset_y), (x1, roi_offset_y + roi_h), (255, 0, 0), 2)
        cv2.line(overlay, (x2, roi_offset_y), (x2, roi_offset_y + roi_h), (255, 0, 0), 2)

        color = (0, 0, 255) if emergency_stop else (0, 255, 0)
        cv2.putText(
            overlay,
            f'Steer: {steering_label} | Speed: {speed_label} | Conf: {confidence:.2f}',
            (20, 40),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.8,
            color,
            2,
            cv2.LINE_AA
        )

        cv2.putText(
            overlay,
            f'L={sector_scores["left"]:.3f} C={sector_scores["center"]:.3f} R={sector_scores["right"]:.3f}',
            (20, 75),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.7,
            (255, 255, 255),
            2,
            cv2.LINE_AA
        )

        # Small mask preview in top-right corner
        preview = cv2.cvtColor(mask, cv2.COLOR_GRAY2BGR)
        preview = cv2.resize(preview, (240, 140))
        ph, pw, _ = preview.shape
        overlay[10:10 + ph, w - pw - 10:w - 10] = preview

        return overlay


def main(args=None) -> None:
    rclpy.init(args=args)
    node = BaselineCVNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        if node is not None:
            node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()