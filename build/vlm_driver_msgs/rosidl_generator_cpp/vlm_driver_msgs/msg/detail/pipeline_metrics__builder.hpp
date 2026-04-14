// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vlm_driver_msgs:msg/PipelineMetrics.idl
// generated code does not contain a copyright notice

#ifndef VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__BUILDER_HPP_
#define VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vlm_driver_msgs/msg/detail/pipeline_metrics__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vlm_driver_msgs
{

namespace msg
{

namespace builder
{

class Init_PipelineMetrics_fps
{
public:
  explicit Init_PipelineMetrics_fps(::vlm_driver_msgs::msg::PipelineMetrics & msg)
  : msg_(msg)
  {}
  ::vlm_driver_msgs::msg::PipelineMetrics fps(::vlm_driver_msgs::msg::PipelineMetrics::_fps_type arg)
  {
    msg_.fps = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vlm_driver_msgs::msg::PipelineMetrics msg_;
};

class Init_PipelineMetrics_total_ms
{
public:
  explicit Init_PipelineMetrics_total_ms(::vlm_driver_msgs::msg::PipelineMetrics & msg)
  : msg_(msg)
  {}
  Init_PipelineMetrics_fps total_ms(::vlm_driver_msgs::msg::PipelineMetrics::_total_ms_type arg)
  {
    msg_.total_ms = std::move(arg);
    return Init_PipelineMetrics_fps(msg_);
  }

private:
  ::vlm_driver_msgs::msg::PipelineMetrics msg_;
};

class Init_PipelineMetrics_decision_ms
{
public:
  explicit Init_PipelineMetrics_decision_ms(::vlm_driver_msgs::msg::PipelineMetrics & msg)
  : msg_(msg)
  {}
  Init_PipelineMetrics_total_ms decision_ms(::vlm_driver_msgs::msg::PipelineMetrics::_decision_ms_type arg)
  {
    msg_.decision_ms = std::move(arg);
    return Init_PipelineMetrics_total_ms(msg_);
  }

private:
  ::vlm_driver_msgs::msg::PipelineMetrics msg_;
};

class Init_PipelineMetrics_preprocess_ms
{
public:
  explicit Init_PipelineMetrics_preprocess_ms(::vlm_driver_msgs::msg::PipelineMetrics & msg)
  : msg_(msg)
  {}
  Init_PipelineMetrics_decision_ms preprocess_ms(::vlm_driver_msgs::msg::PipelineMetrics::_preprocess_ms_type arg)
  {
    msg_.preprocess_ms = std::move(arg);
    return Init_PipelineMetrics_decision_ms(msg_);
  }

private:
  ::vlm_driver_msgs::msg::PipelineMetrics msg_;
};

class Init_PipelineMetrics_source
{
public:
  explicit Init_PipelineMetrics_source(::vlm_driver_msgs::msg::PipelineMetrics & msg)
  : msg_(msg)
  {}
  Init_PipelineMetrics_preprocess_ms source(::vlm_driver_msgs::msg::PipelineMetrics::_source_type arg)
  {
    msg_.source = std::move(arg);
    return Init_PipelineMetrics_preprocess_ms(msg_);
  }

private:
  ::vlm_driver_msgs::msg::PipelineMetrics msg_;
};

class Init_PipelineMetrics_header
{
public:
  Init_PipelineMetrics_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PipelineMetrics_source header(::vlm_driver_msgs::msg::PipelineMetrics::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_PipelineMetrics_source(msg_);
  }

private:
  ::vlm_driver_msgs::msg::PipelineMetrics msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vlm_driver_msgs::msg::PipelineMetrics>()
{
  return vlm_driver_msgs::msg::builder::Init_PipelineMetrics_header();
}

}  // namespace vlm_driver_msgs

#endif  // VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__BUILDER_HPP_
