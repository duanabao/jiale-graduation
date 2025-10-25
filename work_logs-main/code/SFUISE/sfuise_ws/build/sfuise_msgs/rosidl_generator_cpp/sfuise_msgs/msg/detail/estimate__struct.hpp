// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sfuise_msgs:msg/Estimate.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__ESTIMATE__STRUCT_HPP_
#define SFUISE_MSGS__MSG__DETAIL__ESTIMATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'spline'
#include "sfuise_msgs/msg/detail/spline__struct.hpp"
// Member 'if_full_window'
#include "std_msgs/msg/detail/bool__struct.hpp"
// Member 'runtime'
#include "std_msgs/msg/detail/float64__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sfuise_msgs__msg__Estimate __attribute__((deprecated))
#else
# define DEPRECATED__sfuise_msgs__msg__Estimate __declspec(deprecated)
#endif

namespace sfuise_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Estimate_
{
  using Type = Estimate_<ContainerAllocator>;

  explicit Estimate_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : spline(_init),
    if_full_window(_init),
    runtime(_init)
  {
    (void)_init;
  }

  explicit Estimate_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : spline(_alloc, _init),
    if_full_window(_alloc, _init),
    runtime(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _spline_type =
    sfuise_msgs::msg::Spline_<ContainerAllocator>;
  _spline_type spline;
  using _if_full_window_type =
    std_msgs::msg::Bool_<ContainerAllocator>;
  _if_full_window_type if_full_window;
  using _runtime_type =
    std_msgs::msg::Float64_<ContainerAllocator>;
  _runtime_type runtime;

  // setters for named parameter idiom
  Type & set__spline(
    const sfuise_msgs::msg::Spline_<ContainerAllocator> & _arg)
  {
    this->spline = _arg;
    return *this;
  }
  Type & set__if_full_window(
    const std_msgs::msg::Bool_<ContainerAllocator> & _arg)
  {
    this->if_full_window = _arg;
    return *this;
  }
  Type & set__runtime(
    const std_msgs::msg::Float64_<ContainerAllocator> & _arg)
  {
    this->runtime = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sfuise_msgs::msg::Estimate_<ContainerAllocator> *;
  using ConstRawPtr =
    const sfuise_msgs::msg::Estimate_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sfuise_msgs::msg::Estimate_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sfuise_msgs::msg::Estimate_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sfuise_msgs::msg::Estimate_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sfuise_msgs::msg::Estimate_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sfuise_msgs::msg::Estimate_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sfuise_msgs::msg::Estimate_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sfuise_msgs::msg::Estimate_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sfuise_msgs::msg::Estimate_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sfuise_msgs__msg__Estimate
    std::shared_ptr<sfuise_msgs::msg::Estimate_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sfuise_msgs__msg__Estimate
    std::shared_ptr<sfuise_msgs::msg::Estimate_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Estimate_ & other) const
  {
    if (this->spline != other.spline) {
      return false;
    }
    if (this->if_full_window != other.if_full_window) {
      return false;
    }
    if (this->runtime != other.runtime) {
      return false;
    }
    return true;
  }
  bool operator!=(const Estimate_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Estimate_

// alias to use template instance with default allocator
using Estimate =
  sfuise_msgs::msg::Estimate_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sfuise_msgs

#endif  // SFUISE_MSGS__MSG__DETAIL__ESTIMATE__STRUCT_HPP_
