// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vlm_driver_msgs:msg/DrivingDecisions.idl
// generated code does not contain a copyright notice

#ifndef VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__STRUCT_HPP_
#define VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__STRUCT_HPP_

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
# define DEPRECATED__vlm_driver_msgs__msg__DrivingDecisions __attribute__((deprecated))
#else
# define DEPRECATED__vlm_driver_msgs__msg__DrivingDecisions __declspec(deprecated)
#endif

namespace vlm_driver_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DrivingDecisions_
{
  using Type = DrivingDecisions_<ContainerAllocator>;

  explicit DrivingDecisions_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source = "";
      this->steering_label = "";
      this->speed_label = "";
      this->steering_deg = 0.0f;
      this->speed_mps = 0.0f;
      this->confidence = 0.0f;
      this->emergency_stop = false;
    }
  }

  explicit DrivingDecisions_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    source(_alloc),
    steering_label(_alloc),
    speed_label(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->source = "";
      this->steering_label = "";
      this->speed_label = "";
      this->steering_deg = 0.0f;
      this->speed_mps = 0.0f;
      this->confidence = 0.0f;
      this->emergency_stop = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _source_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _source_type source;
  using _steering_label_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _steering_label_type steering_label;
  using _speed_label_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _speed_label_type speed_label;
  using _steering_deg_type =
    float;
  _steering_deg_type steering_deg;
  using _speed_mps_type =
    float;
  _speed_mps_type speed_mps;
  using _confidence_type =
    float;
  _confidence_type confidence;
  using _emergency_stop_type =
    bool;
  _emergency_stop_type emergency_stop;

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
  Type & set__steering_label(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->steering_label = _arg;
    return *this;
  }
  Type & set__speed_label(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->speed_label = _arg;
    return *this;
  }
  Type & set__steering_deg(
    const float & _arg)
  {
    this->steering_deg = _arg;
    return *this;
  }
  Type & set__speed_mps(
    const float & _arg)
  {
    this->speed_mps = _arg;
    return *this;
  }
  Type & set__confidence(
    const float & _arg)
  {
    this->confidence = _arg;
    return *this;
  }
  Type & set__emergency_stop(
    const bool & _arg)
  {
    this->emergency_stop = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator> *;
  using ConstRawPtr =
    const vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vlm_driver_msgs__msg__DrivingDecisions
    std::shared_ptr<vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vlm_driver_msgs__msg__DrivingDecisions
    std::shared_ptr<vlm_driver_msgs::msg::DrivingDecisions_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DrivingDecisions_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->source != other.source) {
      return false;
    }
    if (this->steering_label != other.steering_label) {
      return false;
    }
    if (this->speed_label != other.speed_label) {
      return false;
    }
    if (this->steering_deg != other.steering_deg) {
      return false;
    }
    if (this->speed_mps != other.speed_mps) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    if (this->emergency_stop != other.emergency_stop) {
      return false;
    }
    return true;
  }
  bool operator!=(const DrivingDecisions_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DrivingDecisions_

// alias to use template instance with default allocator
using DrivingDecisions =
  vlm_driver_msgs::msg::DrivingDecisions_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vlm_driver_msgs

#endif  // VLM_DRIVER_MSGS__MSG__DETAIL__DRIVING_DECISIONS__STRUCT_HPP_
