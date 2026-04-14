// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from vlm_driver_msgs:msg/PipelineMetrics.idl
// generated code does not contain a copyright notice
#include "vlm_driver_msgs/msg/detail/pipeline_metrics__rosidl_typesupport_fastrtps_cpp.hpp"
#include "vlm_driver_msgs/msg/detail/pipeline_metrics__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace std_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const std_msgs::msg::Header &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  std_msgs::msg::Header &);
size_t get_serialized_size(
  const std_msgs::msg::Header &,
  size_t current_alignment);
size_t
max_serialized_size_Header(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace std_msgs


namespace vlm_driver_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vlm_driver_msgs
cdr_serialize(
  const vlm_driver_msgs::msg::PipelineMetrics & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.header,
    cdr);
  // Member: source
  cdr << ros_message.source;
  // Member: preprocess_ms
  cdr << ros_message.preprocess_ms;
  // Member: decision_ms
  cdr << ros_message.decision_ms;
  // Member: total_ms
  cdr << ros_message.total_ms;
  // Member: fps
  cdr << ros_message.fps;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vlm_driver_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  vlm_driver_msgs::msg::PipelineMetrics & ros_message)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.header);

  // Member: source
  cdr >> ros_message.source;

  // Member: preprocess_ms
  cdr >> ros_message.preprocess_ms;

  // Member: decision_ms
  cdr >> ros_message.decision_ms;

  // Member: total_ms
  cdr >> ros_message.total_ms;

  // Member: fps
  cdr >> ros_message.fps;

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vlm_driver_msgs
get_serialized_size(
  const vlm_driver_msgs::msg::PipelineMetrics & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: header

  current_alignment +=
    std_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.header, current_alignment);
  // Member: source
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.source.size() + 1);
  // Member: preprocess_ms
  {
    size_t item_size = sizeof(ros_message.preprocess_ms);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: decision_ms
  {
    size_t item_size = sizeof(ros_message.decision_ms);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: total_ms
  {
    size_t item_size = sizeof(ros_message.total_ms);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: fps
  {
    size_t item_size = sizeof(ros_message.fps);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_vlm_driver_msgs
max_serialized_size_PipelineMetrics(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: header
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        std_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Header(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: source
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: preprocess_ms
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: decision_ms
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: total_ms
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: fps
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = vlm_driver_msgs::msg::PipelineMetrics;
    is_plain =
      (
      offsetof(DataType, fps) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _PipelineMetrics__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const vlm_driver_msgs::msg::PipelineMetrics *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _PipelineMetrics__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<vlm_driver_msgs::msg::PipelineMetrics *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _PipelineMetrics__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const vlm_driver_msgs::msg::PipelineMetrics *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _PipelineMetrics__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_PipelineMetrics(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _PipelineMetrics__callbacks = {
  "vlm_driver_msgs::msg",
  "PipelineMetrics",
  _PipelineMetrics__cdr_serialize,
  _PipelineMetrics__cdr_deserialize,
  _PipelineMetrics__get_serialized_size,
  _PipelineMetrics__max_serialized_size
};

static rosidl_message_type_support_t _PipelineMetrics__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_PipelineMetrics__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace vlm_driver_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_vlm_driver_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<vlm_driver_msgs::msg::PipelineMetrics>()
{
  return &vlm_driver_msgs::msg::typesupport_fastrtps_cpp::_PipelineMetrics__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, vlm_driver_msgs, msg, PipelineMetrics)() {
  return &vlm_driver_msgs::msg::typesupport_fastrtps_cpp::_PipelineMetrics__handle;
}

#ifdef __cplusplus
}
#endif
