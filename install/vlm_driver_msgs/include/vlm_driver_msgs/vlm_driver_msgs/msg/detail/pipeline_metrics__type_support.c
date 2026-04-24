// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vlm_driver_msgs:msg/PipelineMetrics.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vlm_driver_msgs/msg/detail/pipeline_metrics__rosidl_typesupport_introspection_c.h"
#include "vlm_driver_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vlm_driver_msgs/msg/detail/pipeline_metrics__functions.h"
#include "vlm_driver_msgs/msg/detail/pipeline_metrics__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `source`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vlm_driver_msgs__msg__PipelineMetrics__init(message_memory);
}

void vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_fini_function(void * message_memory)
{
  vlm_driver_msgs__msg__PipelineMetrics__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_message_member_array[6] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vlm_driver_msgs__msg__PipelineMetrics, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "source",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vlm_driver_msgs__msg__PipelineMetrics, source),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "preprocess_ms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vlm_driver_msgs__msg__PipelineMetrics, preprocess_ms),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "decision_ms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vlm_driver_msgs__msg__PipelineMetrics, decision_ms),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "total_ms",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vlm_driver_msgs__msg__PipelineMetrics, total_ms),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "fps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vlm_driver_msgs__msg__PipelineMetrics, fps),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_message_members = {
  "vlm_driver_msgs__msg",  // message namespace
  "PipelineMetrics",  // message name
  6,  // number of fields
  sizeof(vlm_driver_msgs__msg__PipelineMetrics),
  vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_message_member_array,  // message members
  vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_init_function,  // function to initialize message memory (memory has to be allocated)
  vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_message_type_support_handle = {
  0,
  &vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vlm_driver_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vlm_driver_msgs, msg, PipelineMetrics)() {
  vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_message_type_support_handle.typesupport_identifier) {
    vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vlm_driver_msgs__msg__PipelineMetrics__rosidl_typesupport_introspection_c__PipelineMetrics_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
