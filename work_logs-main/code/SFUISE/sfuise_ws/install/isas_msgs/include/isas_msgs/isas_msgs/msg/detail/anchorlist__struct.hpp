// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from isas_msgs:msg/Anchorlist.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__ANCHORLIST__STRUCT_HPP_
#define ISAS_MSGS__MSG__DETAIL__ANCHORLIST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'anchor'
#include "isas_msgs/msg/detail/anchor_position__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__isas_msgs__msg__Anchorlist __attribute__((deprecated))
#else
# define DEPRECATED__isas_msgs__msg__Anchorlist __declspec(deprecated)
#endif

namespace isas_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Anchorlist_
{
  using Type = Anchorlist_<ContainerAllocator>;

  explicit Anchorlist_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit Anchorlist_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _anchor_type =
    std::vector<isas_msgs::msg::AnchorPosition_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<isas_msgs::msg::AnchorPosition_<ContainerAllocator>>>;
  _anchor_type anchor;

  // setters for named parameter idiom
  Type & set__anchor(
    const std::vector<isas_msgs::msg::AnchorPosition_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<isas_msgs::msg::AnchorPosition_<ContainerAllocator>>> & _arg)
  {
    this->anchor = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    isas_msgs::msg::Anchorlist_<ContainerAllocator> *;
  using ConstRawPtr =
    const isas_msgs::msg::Anchorlist_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<isas_msgs::msg::Anchorlist_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<isas_msgs::msg::Anchorlist_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      isas_msgs::msg::Anchorlist_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<isas_msgs::msg::Anchorlist_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      isas_msgs::msg::Anchorlist_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<isas_msgs::msg::Anchorlist_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<isas_msgs::msg::Anchorlist_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<isas_msgs::msg::Anchorlist_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__isas_msgs__msg__Anchorlist
    std::shared_ptr<isas_msgs::msg::Anchorlist_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__isas_msgs__msg__Anchorlist
    std::shared_ptr<isas_msgs::msg::Anchorlist_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Anchorlist_ & other) const
  {
    if (this->anchor != other.anchor) {
      return false;
    }
    return true;
  }
  bool operator!=(const Anchorlist_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Anchorlist_

// alias to use template instance with default allocator
using Anchorlist =
  isas_msgs::msg::Anchorlist_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace isas_msgs

#endif  // ISAS_MSGS__MSG__DETAIL__ANCHORLIST__STRUCT_HPP_
