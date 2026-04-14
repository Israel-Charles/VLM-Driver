// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vlm_driver_msgs:msg/DrivingDecisions.idl
// generated code does not contain a copyright notice

#ifndef VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__BUILDER_HPP_
#define VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vlm_driver_msgs/msg/detail/driving_decisions__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vlm_driver_msgs
{

namespace msg
{

namespace builder
{

class Init_DrivingDecisions_emergency_stop
{
public:
  explicit Init_DrivingDecisions_emergency_stop(::vlm_driver_msgs::msg::DrivingDecisions & msg)
  : msg_(msg)
  {}
  ::vlm_driver_msgs::msg::DrivingDecisions emergency_stop(::vlm_driver_msgs::msg::DrivingDecisions::_emergency_stop_type arg)
  {
    msg_.emergency_stop = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vlm_driver_msgs::msg::DrivingDecisions msg_;
};

class Init_DrivingDecisions_confidence
{
public:
  explicit Init_DrivingDecisions_confidence(::vlm_driver_msgs::msg::DrivingDecisions & msg)
  : msg_(msg)
  {}
  Init_DrivingDecisions_emergency_stop confidence(::vlm_driver_msgs::msg::DrivingDecisions::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_DrivingDecisions_emergency_stop(msg_);
  }

private:
  ::vlm_driver_msgs::msg::DrivingDecisions msg_;
};

class Init_DrivingDecisions_speed_mps
{
public:
  explicit Init_DrivingDecisions_speed_mps(::vlm_driver_msgs::msg::DrivingDecisions & msg)
  : msg_(msg)
  {}
  Init_DrivingDecisions_confidence speed_mps(::vlm_driver_msgs::msg::DrivingDecisions::_speed_mps_type arg)
  {
    msg_.speed_mps = std::move(arg);
    return Init_DrivingDecisions_confidence(msg_);
  }

private:
  ::vlm_driver_msgs::msg::DrivingDecisions msg_;
};

class Init_DrivingDecisions_steering_deg
{
public:
  explicit Init_DrivingDecisions_steering_deg(::vlm_driver_msgs::msg::DrivingDecisions & msg)
  : msg_(msg)
  {}
  Init_DrivingDecisions_speed_mps steering_deg(::vlm_driver_msgs::msg::DrivingDecisions::_steering_deg_type arg)
  {
    msg_.steering_deg = std::move(arg);
    return Init_DrivingDecisions_speed_mps(msg_);
  }

private:
  ::vlm_driver_msgs::msg::DrivingDecisions msg_;
};

class Init_DrivingDecisions_speed_label
{
public:
  explicit Init_DrivingDecisions_speed_label(::vlm_driver_msgs::msg::DrivingDecisions & msg)
  : msg_(msg)
  {}
  Init_DrivingDecisions_steering_deg speed_label(::vlm_driver_msgs::msg::DrivingDecisions::_speed_label_type arg)
  {
    msg_.speed_label = std::move(arg);
    return Init_DrivingDecisions_steering_deg(msg_);
  }

private:
  ::vlm_driver_msgs::msg::DrivingDecisions msg_;
};

class Init_DrivingDecisions_steering_label
{
public:
  explicit Init_DrivingDecisions_steering_label(::vlm_driver_msgs::msg::DrivingDecisions & msg)
  : msg_(msg)
  {}
  Init_DrivingDecisions_speed_label steering_label(::vlm_driver_msgs::msg::DrivingDecisions::_steering_label_type arg)
  {
    msg_.steering_label = std::move(arg);
    return Init_DrivingDecisions_speed_label(msg_);
  }

private:
  ::vlm_driver_msgs::msg::DrivingDecisions msg_;
};

class Init_DrivingDecisions_source
{
public:
  explicit Init_DrivingDecisions_source(::vlm_driver_msgs::msg::DrivingDecisions & msg)
  : msg_(msg)
  {}
  Init_DrivingDecisions_steering_label source(::vlm_driver_msgs::msg::DrivingDecisions::_source_type arg)
  {
    msg_.source = std::move(arg);
    return Init_DrivingDecisions_steering_label(msg_);
  }

private:
  ::vlm_driver_msgs::msg::DrivingDecisions msg_;
};

class Init_DrivingDecisions_header
{
public:
  Init_DrivingDecisions_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DrivingDecisions_source header(::vlm_driver_msgs::msg::DrivingDecisions::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_DrivingDecisions_source(msg_);
  }

private:
  ::vlm_driver_msgs::msg::DrivingDecisions msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vlm_driver_msgs::msg::DrivingDecisions>()
{
  return vlm_driver_msgs::msg::builder::Init_DrivingDecisions_header();
}

}  // namespace vlm_driver_msgs

#endif  // VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__BUILDER_HPP_
