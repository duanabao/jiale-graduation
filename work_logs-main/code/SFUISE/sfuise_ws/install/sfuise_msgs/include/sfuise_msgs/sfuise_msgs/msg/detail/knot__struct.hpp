// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sfuise_msgs:msg/Knot.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__KNOT__STRUCT_HPP_
#define SFUISE_MSGS__MSG__DETAIL__KNOT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'position'
// Member 'bias_acc'
// Member 'bias_gyro'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'orientation'
#include "geometry_msgs/msg/detail/quaternion__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sfuise_msgs__msg__Knot __attribute__((deprecated))
#else
# define DEPRECATED__sfuise_msgs__msg__Knot __declspec(deprecated)
#endif

namespace sfuise_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Knot_
{
  using Type = Knot_<ContainerAllocator>;

  explicit Knot_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_init),
    orientation(_init),
    bias_acc(_init),
    bias_gyro(_init)
  {
    (void)_init;
  }

  explicit Knot_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_alloc, _init),
    orientation(_alloc, _init),
    bias_acc(_alloc, _init),
    bias_gyro(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;
  using _orientation_type =
    geometry_msgs::msg::Quaternion_<ContainerAllocator>;
  _orientation_type orientation;
  using _bias_acc_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _bias_acc_type bias_acc;
  using _bias_gyro_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _bias_gyro_type bias_gyro;

  // setters for named parameter idiom
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__orientation(
    const geometry_msgs::msg::Quaternion_<ContainerAllocator> & _arg)
  {
    this->orientation = _arg;
    return *this;
  }
  Type & set__bias_acc(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->bias_acc = _arg;
    return *this;
  }
  Type & set__bias_gyro(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->bias_gyro = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sfuise_msgs::msg::Knot_<ContainerAllocator> *;
  using ConstRawPtr =
    const sfuise_msgs::msg::Knot_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sfuise_msgs::msg::Knot_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sfuise_msgs::msg::Knot_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sfuise_msgs::msg::Knot_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sfuise_msgs::msg::Knot_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sfuise_msgs::msg::Knot_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sfuise_msgs::msg::Knot_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sfuise_msgs::msg::Knot_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sfuise_msgs::msg::Knot_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sfuise_msgs__msg__Knot
    std::shared_ptr<sfuise_msgs::msg::Knot_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sfuise_msgs__msg__Knot
    std::shared_ptr<sfuise_msgs::msg::Knot_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Knot_ & other) const
  {
    if (this->position != other.position) {
      return false;
    }
    if (this->orientation != other.orientation) {
      return false;
    }
    if (this->bias_acc != other.bias_acc) {
      return false;
    }
    if (this->bias_gyro != other.bias_gyro) {
      return false;
    }
    return true;
  }
  bool operator!=(const Knot_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Knot_

// alias to use template instance with default allocator
using Knot =
  sfuise_msgs::msg::Knot_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sfuise_msgs

#endif  // SFUISE_MSGS__MSG__DETAIL__KNOT__STRUCT_HPP_
