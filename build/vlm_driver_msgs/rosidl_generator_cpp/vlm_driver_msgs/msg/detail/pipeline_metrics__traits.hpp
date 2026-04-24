// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vlm_driver_msgs:msg/PipelineMetrics.idl
// generated code does not contain a copyright notice

#ifndef VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__TRAITS_HPP_
#define VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vlm_driver_msgs/msg/detail/pipeline_metrics__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace vlm_driver_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PipelineMetrics & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: source
  {
    out << "source: ";
    rosidl_generator_traits::value_to_yaml(msg.source, out);
    out << ", ";
  }

  // member: preprocess_ms
  {
    out << "preprocess_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.preprocess_ms, out);
    out << ", ";
  }

  // member: decision_ms
  {
    out << "decision_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.decision_ms, out);
    out << ", ";
  }

  // member: total_ms
  {
    out << "total_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.total_ms, out);
    out << ", ";
  }

  // member: fps
  {
    out << "fps: ";
    rosidl_generator_traits::value_to_yaml(msg.fps, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PipelineMetrics & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: source
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "source: ";
    rosidl_generator_traits::value_to_yaml(msg.source, out);
    out << "\n";
  }

  // member: preprocess_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "preprocess_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.preprocess_ms, out);
    out << "\n";
  }

  // member: decision_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "decision_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.decision_ms, out);
    out << "\n";
  }

  // member: total_ms
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_ms: ";
    rosidl_generator_traits::value_to_yaml(msg.total_ms, out);
    out << "\n";
  }

  // member: fps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fps: ";
    rosidl_generator_traits::value_to_yaml(msg.fps, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PipelineMetrics & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace vlm_driver_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vlm_driver_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vlm_driver_msgs::msg::PipelineMetrics & msg,
  std::ostream & out, size_t indentation = 0)
{
  vlm_driver_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vlm_driver_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vlm_driver_msgs::msg::PipelineMetrics & msg)
{
  return vlm_driver_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vlm_driver_msgs::msg::PipelineMetrics>()
{
  return "vlm_driver_msgs::msg::PipelineMetrics";
}

template<>
inline const char * name<vlm_driver_msgs::msg::PipelineMetrics>()
{
  return "vlm_driver_msgs/msg/PipelineMetrics";
}

template<>
struct has_fixed_size<vlm_driver_msgs::msg::PipelineMetrics>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vlm_driver_msgs::msg::PipelineMetrics>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vlm_driver_msgs::msg::PipelineMetrics>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__TRAITS_HPP_
