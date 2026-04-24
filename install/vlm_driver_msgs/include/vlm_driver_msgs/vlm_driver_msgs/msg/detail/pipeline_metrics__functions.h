// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from vlm_driver_msgs:msg/PipelineMetrics.idl
// generated code does not contain a copyright notice

#ifndef VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__FUNCTIONS_H_
#define VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "vlm_driver_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "vlm_driver_msgs/msg/detail/pipeline_metrics__struct.h"

/// Initialize msg/PipelineMetrics message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * vlm_driver_msgs__msg__PipelineMetrics
 * )) before or use
 * vlm_driver_msgs__msg__PipelineMetrics__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
bool
vlm_driver_msgs__msg__PipelineMetrics__init(vlm_driver_msgs__msg__PipelineMetrics * msg);

/// Finalize msg/PipelineMetrics message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
void
vlm_driver_msgs__msg__PipelineMetrics__fini(vlm_driver_msgs__msg__PipelineMetrics * msg);

/// Create msg/PipelineMetrics message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * vlm_driver_msgs__msg__PipelineMetrics__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
vlm_driver_msgs__msg__PipelineMetrics *
vlm_driver_msgs__msg__PipelineMetrics__create();

/// Destroy msg/PipelineMetrics message.
/**
 * It calls
 * vlm_driver_msgs__msg__PipelineMetrics__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
void
vlm_driver_msgs__msg__PipelineMetrics__destroy(vlm_driver_msgs__msg__PipelineMetrics * msg);

/// Check for msg/PipelineMetrics message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
bool
vlm_driver_msgs__msg__PipelineMetrics__are_equal(const vlm_driver_msgs__msg__PipelineMetrics * lhs, const vlm_driver_msgs__msg__PipelineMetrics * rhs);

/// Copy a msg/PipelineMetrics message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
bool
vlm_driver_msgs__msg__PipelineMetrics__copy(
  const vlm_driver_msgs__msg__PipelineMetrics * input,
  vlm_driver_msgs__msg__PipelineMetrics * output);

/// Initialize array of msg/PipelineMetrics messages.
/**
 * It allocates the memory for the number of elements and calls
 * vlm_driver_msgs__msg__PipelineMetrics__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
bool
vlm_driver_msgs__msg__PipelineMetrics__Sequence__init(vlm_driver_msgs__msg__PipelineMetrics__Sequence * array, size_t size);

/// Finalize array of msg/PipelineMetrics messages.
/**
 * It calls
 * vlm_driver_msgs__msg__PipelineMetrics__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
void
vlm_driver_msgs__msg__PipelineMetrics__Sequence__fini(vlm_driver_msgs__msg__PipelineMetrics__Sequence * array);

/// Create array of msg/PipelineMetrics messages.
/**
 * It allocates the memory for the array and calls
 * vlm_driver_msgs__msg__PipelineMetrics__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
vlm_driver_msgs__msg__PipelineMetrics__Sequence *
vlm_driver_msgs__msg__PipelineMetrics__Sequence__create(size_t size);

/// Destroy array of msg/PipelineMetrics messages.
/**
 * It calls
 * vlm_driver_msgs__msg__PipelineMetrics__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
void
vlm_driver_msgs__msg__PipelineMetrics__Sequence__destroy(vlm_driver_msgs__msg__PipelineMetrics__Sequence * array);

/// Check for msg/PipelineMetrics message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
bool
vlm_driver_msgs__msg__PipelineMetrics__Sequence__are_equal(const vlm_driver_msgs__msg__PipelineMetrics__Sequence * lhs, const vlm_driver_msgs__msg__PipelineMetrics__Sequence * rhs);

/// Copy an array of msg/PipelineMetrics messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_vlm_driver_msgs
bool
vlm_driver_msgs__msg__PipelineMetrics__Sequence__copy(
  const vlm_driver_msgs__msg__PipelineMetrics__Sequence * input,
  vlm_driver_msgs__msg__PipelineMetrics__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__FUNCTIONS_H_
