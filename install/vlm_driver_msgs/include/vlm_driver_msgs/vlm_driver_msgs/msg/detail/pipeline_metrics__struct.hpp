// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vlm_driver_msgs:msg/PipelineMetrics.idl
// generated code does not contain a copyright notice

#ifndef VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__STRUCT_HPP_
#define VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vlm_driver_msgs__msg__PipelineMetrics __attribute__((deprecated))
#else
# define DEPRECATED__vlm_driver_msgs__msg__PipelineMetrics __declspec(deprecated)
#endif

namespace vlm_driver_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PipelineMetrics_
{
  using Type = PipelineMetrics_<ContainerAllocator>;

  explicit PipelineMetrics_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source = "";
      this->preprocess_ms = 0.0f;
      this->decision_ms = 0.0f;
      this->total_ms = 0.0f;
      this->fps = 0.0f;
    }
  }

  explicit PipelineMetrics_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    source(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source = "";
      this->preprocess_ms = 0.0f;
      this->decision_ms = 0.0f;
      this->total_ms = 0.0f;
      this->fps = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_type source;
  using _preprocess_ms_type =
    float;
  _preprocess_ms_type preprocess_ms;
  using _decision_ms_type =
    float;
  _decision_ms_type decision_ms;
  using _total_ms_type =
    float;
  _total_ms_type total_ms;
  using _fps_type =
    float;
  _fps_type fps;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__source(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->source = _arg;
    return *this;
  }
  Type & set__preprocess_ms(
    const float & _arg)
  {
    this->preprocess_ms = _arg;
    return *this;
  }
  Type & set__decision_ms(
    const float & _arg)
  {
    this->decision_ms = _arg;
    return *this;
  }
  Type & set__total_ms(
    const float & _arg)
  {
    this->total_ms = _arg;
    return *this;
  }
  Type & set__fps(
    const float & _arg)
  {
    this->fps = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator> *;
  using ConstRawPtr =
    const vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vlm_driver_msgs__msg__PipelineMetrics
    std::shared_ptr<vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vlm_driver_msgs__msg__PipelineMetrics
    std::shared_ptr<vlm_driver_msgs::msg::PipelineMetrics_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PipelineMetrics_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->source != other.source) {
      return false;
    }
    if (this->preprocess_ms != other.preprocess_ms) {
      return false;
    }
    if (this->decision_ms != other.decision_ms) {
      return false;
    }
    if (this->total_ms != other.total_ms) {
      return false;
    }
    if (this->fps != other.fps) {
      return false;
    }
    return true;
  }
  bool operator!=(const PipelineMetrics_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PipelineMetrics_

// alias to use template instance with default allocator
using PipelineMetrics =
  vlm_driver_msgs::msg::PipelineMetrics_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vlm_driver_msgs

#endif  // VLM_DRIVER_MSGS__MSG__DETAIL__PIPELINE_METRICS__STRUCT_HPP_
