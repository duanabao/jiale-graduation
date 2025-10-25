// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from isas_msgs:msg/AnchorPosition.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__STRUCT_HPP_
#define ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__isas_msgs__msg__AnchorPosition __attribute__((deprecated))
#else
# define DEPRECATED__isas_msgs__msg__AnchorPosition __declspec(deprecated)
#endif

namespace isas_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AnchorPosition_
{
  using Type = AnchorPosition_<ContainerAllocator>;

  explicit AnchorPosition_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
    }
  }

  explicit AnchorPosition_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
    }
  }

  // field types and members
  using _id_type =
    uint16_t;
  _id_type id;
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;

  // setters for named parameter idiom
  Type & set__id(
    const uint16_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    isas_msgs::msg::AnchorPosition_<ContainerAllocator> *;
  using ConstRawPtr =
    const isas_msgs::msg::AnchorPosition_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<isas_msgs::msg::AnchorPosition_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<isas_msgs::msg::AnchorPosition_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      isas_msgs::msg::AnchorPosition_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<isas_msgs::msg::AnchorPosition_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      isas_msgs::msg::AnchorPosition_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<isas_msgs::msg::AnchorPosition_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<isas_msgs::msg::AnchorPosition_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<isas_msgs::msg::AnchorPosition_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__isas_msgs__msg__AnchorPosition
    std::shared_ptr<isas_msgs::msg::AnchorPosition_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__isas_msgs__msg__AnchorPosition
    std::shared_ptr<isas_msgs::msg::AnchorPosition_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AnchorPosition_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    return true;
  }
  bool operator!=(const AnchorPosition_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AnchorPosition_

// alias to use template instance with default allocator
using AnchorPosition =
  isas_msgs::msg::AnchorPosition_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace isas_msgs

#endif  // ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__STRUCT_HPP_
