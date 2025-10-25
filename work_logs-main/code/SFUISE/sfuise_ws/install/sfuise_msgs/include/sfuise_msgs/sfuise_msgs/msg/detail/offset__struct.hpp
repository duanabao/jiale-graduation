// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sfuise_msgs:msg/Offset.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__OFFSET__STRUCT_HPP_
#define SFUISE_MSGS__MSG__DETAIL__OFFSET__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 't_tag_body'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sfuise_msgs__msg__Offset __attribute__((deprecated))
#else
# define DEPRECATED__sfuise_msgs__msg__Offset __declspec(deprecated)
#endif

namespace sfuise_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Offset_
{
  using Type = Offset_<ContainerAllocator>;

  explicit Offset_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : t_tag_body(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id_tag = 0;
      this->id_antenna = 0;
    }
  }

  explicit Offset_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : t_tag_body(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id_tag = 0;
      this->id_antenna = 0;
    }
  }

  // field types and members
  using _id_tag_type =
    int8_t;
  _id_tag_type id_tag;
  using _id_antenna_type =
    int8_t;
  _id_antenna_type id_antenna;
  using _t_tag_body_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _t_tag_body_type t_tag_body;

  // setters for named parameter idiom
  Type & set__id_tag(
    const int8_t & _arg)
  {
    this->id_tag = _arg;
    return *this;
  }
  Type & set__id_antenna(
    const int8_t & _arg)
  {
    this->id_antenna = _arg;
    return *this;
  }
  Type & set__t_tag_body(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->t_tag_body = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sfuise_msgs::msg::Offset_<ContainerAllocator> *;
  using ConstRawPtr =
    const sfuise_msgs::msg::Offset_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sfuise_msgs::msg::Offset_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sfuise_msgs::msg::Offset_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sfuise_msgs::msg::Offset_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sfuise_msgs::msg::Offset_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sfuise_msgs::msg::Offset_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sfuise_msgs::msg::Offset_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sfuise_msgs::msg::Offset_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sfuise_msgs::msg::Offset_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sfuise_msgs__msg__Offset
    std::shared_ptr<sfuise_msgs::msg::Offset_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sfuise_msgs__msg__Offset
    std::shared_ptr<sfuise_msgs::msg::Offset_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Offset_ & other) const
  {
    if (this->id_tag != other.id_tag) {
      return false;
    }
    if (this->id_antenna != other.id_antenna) {
      return false;
    }
    if (this->t_tag_body != other.t_tag_body) {
      return false;
    }
    return true;
  }
  bool operator!=(const Offset_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Offset_

// alias to use template instance with default allocator
using Offset =
  sfuise_msgs::msg::Offset_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sfuise_msgs

#endif  // SFUISE_MSGS__MSG__DETAIL__OFFSET__STRUCT_HPP_
