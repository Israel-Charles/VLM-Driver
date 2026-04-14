// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vlm_driver_msgs:msg/PipelineMetrics.idl
// generated code does not contain a copyright notice
#include "vlm_driver_msgs/msg/detail/pipeline_metrics__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `source`
#include "rosidl_runtime_c/string_functions.h"

bool
vlm_driver_msgs__msg__PipelineMetrics__init(vlm_driver_msgs__msg__PipelineMetrics * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vlm_driver_msgs__msg__PipelineMetrics__fini(msg);
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__init(&msg->source)) {
    vlm_driver_msgs__msg__PipelineMetrics__fini(msg);
    return false;
  }
  // preprocess_ms
  // decision_ms
  // total_ms
  // fps
  return true;
}

void
vlm_driver_msgs__msg__PipelineMetrics__fini(vlm_driver_msgs__msg__PipelineMetrics * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // source
  rosidl_runtime_c__String__fini(&msg->source);
  // preprocess_ms
  // decision_ms
  // total_ms
  // fps
}

bool
vlm_driver_msgs__msg__PipelineMetrics__are_equal(const vlm_driver_msgs__msg__PipelineMetrics * lhs, const vlm_driver_msgs__msg__PipelineMetrics * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->source), &(rhs->source)))
  {
    return false;
  }
  // preprocess_ms
  if (lhs->preprocess_ms != rhs->preprocess_ms) {
    return false;
  }
  // decision_ms
  if (lhs->decision_ms != rhs->decision_ms) {
    return false;
  }
  // total_ms
  if (lhs->total_ms != rhs->total_ms) {
    return false;
  }
  // fps
  if (lhs->fps != rhs->fps) {
    return false;
  }
  return true;
}

bool
vlm_driver_msgs__msg__PipelineMetrics__copy(
  const vlm_driver_msgs__msg__PipelineMetrics * input,
  vlm_driver_msgs__msg__PipelineMetrics * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__copy(
      &(input->source), &(output->source)))
  {
    return false;
  }
  // preprocess_ms
  output->preprocess_ms = input->preprocess_ms;
  // decision_ms
  output->decision_ms = input->decision_ms;
  // total_ms
  output->total_ms = input->total_ms;
  // fps
  output->fps = input->fps;
  return true;
}

vlm_driver_msgs__msg__PipelineMetrics *
vlm_driver_msgs__msg__PipelineMetrics__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vlm_driver_msgs__msg__PipelineMetrics * msg = (vlm_driver_msgs__msg__PipelineMetrics *)allocator.allocate(sizeof(vlm_driver_msgs__msg__PipelineMetrics), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vlm_driver_msgs__msg__PipelineMetrics));
  bool success = vlm_driver_msgs__msg__PipelineMetrics__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vlm_driver_msgs__msg__PipelineMetrics__destroy(vlm_driver_msgs__msg__PipelineMetrics * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vlm_driver_msgs__msg__PipelineMetrics__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vlm_driver_msgs__msg__PipelineMetrics__Sequence__init(vlm_driver_msgs__msg__PipelineMetrics__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vlm_driver_msgs__msg__PipelineMetrics * data = NULL;

  if (size) {
    data = (vlm_driver_msgs__msg__PipelineMetrics *)allocator.zero_allocate(size, sizeof(vlm_driver_msgs__msg__PipelineMetrics), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vlm_driver_msgs__msg__PipelineMetrics__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vlm_driver_msgs__msg__PipelineMetrics__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
vlm_driver_msgs__msg__PipelineMetrics__Sequence__fini(vlm_driver_msgs__msg__PipelineMetrics__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      vlm_driver_msgs__msg__PipelineMetrics__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

vlm_driver_msgs__msg__PipelineMetrics__Sequence *
vlm_driver_msgs__msg__PipelineMetrics__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vlm_driver_msgs__msg__PipelineMetrics__Sequence * array = (vlm_driver_msgs__msg__PipelineMetrics__Sequence *)allocator.allocate(sizeof(vlm_driver_msgs__msg__PipelineMetrics__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vlm_driver_msgs__msg__PipelineMetrics__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vlm_driver_msgs__msg__PipelineMetrics__Sequence__destroy(vlm_driver_msgs__msg__PipelineMetrics__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vlm_driver_msgs__msg__PipelineMetrics__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vlm_driver_msgs__msg__PipelineMetrics__Sequence__are_equal(const vlm_driver_msgs__msg__PipelineMetrics__Sequence * lhs, const vlm_driver_msgs__msg__PipelineMetrics__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vlm_driver_msgs__msg__PipelineMetrics__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vlm_driver_msgs__msg__PipelineMetrics__Sequence__copy(
  const vlm_driver_msgs__msg__PipelineMetrics__Sequence * input,
  vlm_driver_msgs__msg__PipelineMetrics__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vlm_driver_msgs__msg__PipelineMetrics);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vlm_driver_msgs__msg__PipelineMetrics * data =
      (vlm_driver_msgs__msg__PipelineMetrics *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vlm_driver_msgs__msg__PipelineMetrics__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vlm_driver_msgs__msg__PipelineMetrics__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vlm_driver_msgs__msg__PipelineMetrics__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
