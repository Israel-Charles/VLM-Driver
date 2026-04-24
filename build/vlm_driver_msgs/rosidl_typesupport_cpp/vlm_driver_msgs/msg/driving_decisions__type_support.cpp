// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from vlm_driver_msgs:msg/DrivingDecisions.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "vlm_driver_msgs/msg/detail/driving_decisions__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace vlm_driver_msgs
{

namespace msg
{

namespace rosidl_typesupport_cpp
{

typedef struct _DrivingDecisions_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _DrivingDecisions_type_support_ids_t;

static const _DrivingDecisions_type_support_ids_t _DrivingDecisions_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _DrivingDecisions_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _DrivingDecisions_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _DrivingDecisions_type_support_symbol_names_t _DrivingDecisions_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vlm_driver_msgs, msg, DrivingDecisions)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, vlm_driver_msgs, msg, DrivingDecisions)),
  }
};

typedef struct _DrivingDecisions_type_support_data_t
{
  void * data[2];
} _DrivingDecisions_type_support_data_t;

static _DrivingDecisions_type_support_data_t _DrivingDecisions_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _DrivingDecisions_message_typesupport_map = {
  2,
  "vlm_driver_msgs",
  &_DrivingDecisions_message_typesupport_ids.typesupport_identifier[0],
  &_DrivingDecisions_message_typesupport_symbol_names.symbol_name[0],
  &_DrivingDecisions_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t DrivingDecisions_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_DrivingDecisions_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace msg

}  // namespace vlm_driver_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<vlm_driver_msgs::msg::DrivingDecisions>()
{
  return &::vlm_driver_msgs::msg::rosidl_typesupport_cpp::DrivingDecisions_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, vlm_driver_msgs, msg, DrivingDecisions)() {
  return get_message_type_support_handle<vlm_driver_msgs::msg::DrivingDecisions>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp
