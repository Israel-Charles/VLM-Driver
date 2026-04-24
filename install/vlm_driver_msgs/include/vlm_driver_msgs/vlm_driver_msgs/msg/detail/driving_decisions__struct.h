// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vlm_driver_msgs:msg/DrivingDecisions.idl
// generated code does not contain a copyright notice

#ifndef VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__STRUCT_H_
#define VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'source'
// Member 'steering_label'
// Member 'speed_label'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/DrivingDecisions in the package vlm_driver_msgs.
typedef struct vlm_driver_msgs__msg__DrivingDecisions
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String source;
  rosidl_runtime_c__String steering_label;
  rosidl_runtime_c__String speed_label;
  float steering_deg;
  float speed_mps;
  float confidence;
  bool emergency_stop;
} vlm_driver_msgs__msg__DrivingDecisions;

// Struct for a sequence of vlm_driver_msgs__msg__DrivingDecisions.
typedef struct vlm_driver_msgs__msg__DrivingDecisions__Sequence
{
  vlm_driver_msgs__msg__DrivingDecisions * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vlm_driver_msgs__msg__DrivingDecisions__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__STRUCT_H_
