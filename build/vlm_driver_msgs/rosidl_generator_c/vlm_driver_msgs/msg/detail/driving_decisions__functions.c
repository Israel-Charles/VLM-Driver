// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from vlm_driver_msgs:msg/DrivingDecisions.idl
// generated code does not contain a copyright notice
#include "vlm_driver_msgs/msg/detail/driving_decisions__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `source`
// Member `steering_label`
// Member `speed_label`
#include "rosidl_runtime_c/string_functions.h"

bool
vlm_driver_msgs__msg__DrivingDecisions__init(vlm_driver_msgs__msg__DrivingDecisions * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    vlm_driver_msgs__msg__DrivingDecisions__fini(msg);
    return false;
  }
  // source
  if (!rosidl_runtime_c__String__init(&msg->source)) {
    vlm_driver_msgs__msg__DrivingDecisions__fini(msg);
    return false;
  }
  // steering_label
  if (!rosidl_runtime_c__String__init(&msg->steering_label)) {
    vlm_driver_msgs__msg__DrivingDecisions__fini(msg);
    return false;
  }
  // speed_label
  if (!rosidl_runtime_c__String__init(&msg->speed_label)) {
    vlm_driver_msgs__msg__DrivingDecisions__fini(msg);
    return false;
  }
  // steering_deg
  // speed_mps
  // confidence
  // emergency_stop
  return true;
}

void
vlm_driver_msgs__msg__DrivingDecisions__fini(vlm_driver_msgs__msg__DrivingDecisions * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // source
  rosidl_runtime_c__String__fini(&msg->source);
  // steering_label
  rosidl_runtime_c__String__fini(&msg->steering_label);
  // speed_label
  rosidl_runtime_c__String__fini(&msg->speed_label);
  // steering_deg
  // speed_mps
  // confidence
  // emergency_stop
}

bool
vlm_driver_msgs__msg__DrivingDecisions__are_equal(const vlm_driver_msgs__msg__DrivingDecisions * lhs, const vlm_driver_msgs__msg__DrivingDecisions * rhs)
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
  // steering_label
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->steering_label), &(rhs->steering_label)))
  {
    return false;
  }
  // speed_label
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->speed_label), &(rhs->speed_label)))
  {
    return false;
  }
  // steering_deg
  if (lhs->steering_deg != rhs->steering_deg) {
    return false;
  }
  // speed_mps
  if (lhs->speed_mps != rhs->speed_mps) {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  // emergency_stop
  if (lhs->emergency_stop != rhs->emergency_stop) {
    return false;
  }
  return true;
}

bool
vlm_driver_msgs__msg__DrivingDecisions__copy(
  const vlm_driver_msgs__msg__DrivingDecisions * input,
  vlm_driver_msgs__msg__DrivingDecisions * output)
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
  // steering_label
  if (!rosidl_runtime_c__String__copy(
      &(input->steering_label), &(output->steering_label)))
  {
    return false;
  }
  // speed_label
  if (!rosidl_runtime_c__String__copy(
      &(input->speed_label), &(output->speed_label)))
  {
    return false;
  }
  // steering_deg
  output->steering_deg = input->steering_deg;
  // speed_mps
  output->speed_mps = input->speed_mps;
  // confidence
  output->confidence = input->confidence;
  // emergency_stop
  output->emergency_stop = input->emergency_stop;
  return true;
}

vlm_driver_msgs__msg__DrivingDecisions *
vlm_driver_msgs__msg__DrivingDecisions__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vlm_driver_msgs__msg__DrivingDecisions * msg = (vlm_driver_msgs__msg__DrivingDecisions *)allocator.allocate(sizeof(vlm_driver_msgs__msg__DrivingDecisions), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(vlm_driver_msgs__msg__DrivingDecisions));
  bool success = vlm_driver_msgs__msg__DrivingDecisions__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
vlm_driver_msgs__msg__DrivingDecisions__destroy(vlm_driver_msgs__msg__DrivingDecisions * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    vlm_driver_msgs__msg__DrivingDecisions__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
vlm_driver_msgs__msg__DrivingDecisions__Sequence__init(vlm_driver_msgs__msg__DrivingDecisions__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vlm_driver_msgs__msg__DrivingDecisions * data = NULL;

  if (size) {
    data = (vlm_driver_msgs__msg__DrivingDecisions *)allocator.zero_allocate(size, sizeof(vlm_driver_msgs__msg__DrivingDecisions), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = vlm_driver_msgs__msg__DrivingDecisions__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        vlm_driver_msgs__msg__DrivingDecisions__fini(&data[i - 1]);
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
vlm_driver_msgs__msg__DrivingDecisions__Sequence__fini(vlm_driver_msgs__msg__DrivingDecisions__Sequence * array)
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
      vlm_driver_msgs__msg__DrivingDecisions__fini(&array->data[i]);
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

vlm_driver_msgs__msg__DrivingDecisions__Sequence *
vlm_driver_msgs__msg__DrivingDecisions__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  vlm_driver_msgs__msg__DrivingDecisions__Sequence * array = (vlm_driver_msgs__msg__DrivingDecisions__Sequence *)allocator.allocate(sizeof(vlm_driver_msgs__msg__DrivingDecisions__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = vlm_driver_msgs__msg__DrivingDecisions__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
vlm_driver_msgs__msg__DrivingDecisions__Sequence__destroy(vlm_driver_msgs__msg__DrivingDecisions__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    vlm_driver_msgs__msg__DrivingDecisions__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
vlm_driver_msgs__msg__DrivingDecisions__Sequence__are_equal(const vlm_driver_msgs__msg__DrivingDecisions__Sequence * lhs, const vlm_driver_msgs__msg__DrivingDecisions__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!vlm_driver_msgs__msg__DrivingDecisions__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
vlm_driver_msgs__msg__DrivingDecisions__Sequence__copy(
  const vlm_driver_msgs__msg__DrivingDecisions__Sequence * input,
  vlm_driver_msgs__msg__DrivingDecisions__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(vlm_driver_msgs__msg__DrivingDecisions);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    vlm_driver_msgs__msg__DrivingDecisions * data =
      (vlm_driver_msgs__msg__DrivingDecisions *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!vlm_driver_msgs__msg__DrivingDecisions__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          vlm_driver_msgs__msg__DrivingDecisions__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!vlm_driver_msgs__msg__DrivingDecisions__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
