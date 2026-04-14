// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vlm_driver_msgs:msg/DrivingDecisions.idl
// generated code does not contain a copyright notice

#ifndef VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__TRAITS_HPP_
#define VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vlm_driver_msgs/msg/detail/driving_decisions__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace vlm_driver_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const DrivingDecisions & msg,
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

  // member: steering_label
  {
    out << "steering_label: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_label, out);
    out << ", ";
  }

  // member: speed_label
  {
    out << "speed_label: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_label, out);
    out << ", ";
  }

  // member: steering_deg
  {
    out << "steering_deg: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_deg, out);
    out << ", ";
  }

  // member: speed_mps
  {
    out << "speed_mps: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_mps, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << ", ";
  }

  // member: emergency_stop
  {
    out << "emergency_stop: ";
    rosidl_generator_traits::value_to_yaml(msg.emergency_stop, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DrivingDecisions & msg,
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

  // member: steering_label
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steering_label: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_label, out);
    out << "\n";
  }

  // member: speed_label
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed_label: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_label, out);
    out << "\n";
  }

  // member: steering_deg
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steering_deg: ";
    rosidl_generator_traits::value_to_yaml(msg.steering_deg, out);
    out << "\n";
  }

  // member: speed_mps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed_mps: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_mps, out);
    out << "\n";
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }

  // member: emergency_stop
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "emergency_stop: ";
    rosidl_generator_traits::value_to_yaml(msg.emergency_stop, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DrivingDecisions & msg, bool use_flow_style = false)
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
  const vlm_driver_msgs::msg::DrivingDecisions & msg,
  std::ostream & out, size_t indentation = 0)
{
  vlm_driver_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vlm_driver_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vlm_driver_msgs::msg::DrivingDecisions & msg)
{
  return vlm_driver_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vlm_driver_msgs::msg::DrivingDecisions>()
{
  return "vlm_driver_msgs::msg::DrivingDecisions";
}

template<>
inline const char * name<vlm_driver_msgs::msg::DrivingDecisions>()
{
  return "vlm_driver_msgs/msg/DrivingDecisions";
}

template<>
struct has_fixed_size<vlm_driver_msgs::msg::DrivingDecisions>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vlm_driver_msgs::msg::DrivingDecisions>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vlm_driver_msgs::msg::DrivingDecisions>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__TRAITS_HPP_
