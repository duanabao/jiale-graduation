// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sfuise_msgs:msg/Calib.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__CALIB__STRUCT_HPP_
#define SFUISE_MSGS__MSG__DETAIL__CALIB__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'gravity'
// Member 't_nav_uwb'
// Member 't_tag_body_set'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'q_nav_uwb'
#include "geometry_msgs/msg/detail/quaternion__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sfuise_msgs__msg__Calib __attribute__((deprecated))
#else
# define DEPRECATED__sfuise_msgs__msg__Calib __declspec(deprecated)
#endif

namespace sfuise_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Calib_
{
  using Type = Calib_<ContainerAllocator>;

  explicit Calib_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : gravity(_init),
    t_nav_uwb(_init),
    q_nav_uwb(_init),
    t_tag_body_set(_init)
  {
    (void)_init;
  }

  explicit Calib_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : gravity(_alloc, _init),
    t_nav_uwb(_alloc, _init),
    q_nav_uwb(_alloc, _init),
    t_tag_body_set(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _gravity_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _gravity_type gravity;
  using _t_nav_uwb_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _t_nav_uwb_type t_nav_uwb;
  using _q_nav_uwb_type =
    geometry_msgs::msg::Quaternion_<ContainerAllocator>;
  _q_nav_uwb_type q_nav_uwb;
  using _t_tag_body_set_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _t_tag_body_set_type t_tag_body_set;

  // setters for named parameter idiom
  Type & set__gravity(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->gravity = _arg;
    return *this;
  }
  Type & set__t_nav_uwb(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->t_nav_uwb = _arg;
    return *this;
  }
  Type & set__q_nav_uwb(
    const geometry_msgs::msg::Quaternion_<ContainerAllocator> & _arg)
  {
    this->q_nav_uwb = _arg;
    return *this;
  }
  Type & set__t_tag_body_set(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->t_tag_body_set = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sfuise_msgs::msg::Calib_<ContainerAllocator> *;
  using ConstRawPtr =
    const sfuise_msgs::msg::Calib_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sfuise_msgs::msg::Calib_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sfuise_msgs::msg::Calib_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sfuise_msgs::msg::Calib_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sfuise_msgs::msg::Calib_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sfuise_msgs::msg::Calib_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sfuise_msgs::msg::Calib_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sfuise_msgs::msg::Calib_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sfuise_msgs::msg::Calib_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sfuise_msgs__msg__Calib
    std::shared_ptr<sfuise_msgs::msg::Calib_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sfuise_msgs__msg__Calib
    std::shared_ptr<sfuise_msgs::msg::Calib_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Calib_ & other) const
  {
    if (this->gravity != other.gravity) {
      return false;
    }
    if (this->t_nav_uwb != other.t_nav_uwb) {
      return false;
    }
    if (this->q_nav_uwb != other.q_nav_uwb) {
      return false;
    }
    if (this->t_tag_body_set != other.t_tag_body_set) {
      return false;
    }
    return true;
  }
  bool operator!=(const Calib_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Calib_

// alias to use template instance with default allocator
using Calib =
  sfuise_msgs::msg::Calib_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sfuise_msgs

#endif  // SFUISE_MSGS__MSG__DETAIL__CALIB__STRUCT_HPP_
