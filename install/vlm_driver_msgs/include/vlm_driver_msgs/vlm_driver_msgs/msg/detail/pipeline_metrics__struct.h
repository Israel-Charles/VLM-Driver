// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vlm_driver_msgs:msg/PipelineMetrics.idl
// generated code does not contain a copyright notice

#ifndef VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__STRUCT_H_
#define VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__STRUCT_H_

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
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/PipelineMetrics in the package vlm_driver_msgs.
typedef struct vlm_driver_msgs__msg__PipelineMetrics
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String source;
  float preprocess_ms;
  float decision_ms;
  float total_ms;
  float fps;
} vlm_driver_msgs__msg__PipelineMetrics;

// Struct for a sequence of vlm_driver_msgs__msg__PipelineMetrics.
typedef struct vlm_driver_msgs__msg__PipelineMetrics__Sequence
{
  vlm_driver_msgs__msg__PipelineMetrics * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vlm_driver_msgs__msg__PipelineMetrics__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__STRUCT_H_
