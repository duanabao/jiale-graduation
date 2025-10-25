// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sfuise_msgs:msg/Spline.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__SPLINE__STRUCT_HPP_
#define SFUISE_MSGS__MSG__DETAIL__SPLINE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'knots'
// Member 'idles'
#include "sfuise_msgs/msg/detail/knot__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sfuise_msgs__msg__Spline __attribute__((deprecated))
#else
# define DEPRECATED__sfuise_msgs__msg__Spline __declspec(deprecated)
#endif

namespace sfuise_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Spline_
{
  using Type = Spline_<ContainerAllocator>;

  explicit Spline_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->start_idx = 0ull;
      this->dt = 0ll;
      this->start_t = 0ll;
    }
  }

  explicit Spline_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->start_idx = 0ull;
      this->dt = 0ll;
      this->start_t = 0ll;
    }
  }

  // field types and members
  using _start_idx_type =
    uint64_t;
  _start_idx_type start_idx;
  using _dt_type =
    int64_t;
  _dt_type dt;
  using _start_t_type =
    int64_t;
  _start_t_type start_t;
  using _knots_type =
    std::vector<sfuise_msgs::msg::Knot_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<sfuise_msgs::msg::Knot_<ContainerAllocator>>>;
  _knots_type knots;
  using _idles_type =
    std::vector<sfuise_msgs::msg::Knot_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<sfuise_msgs::msg::Knot_<ContainerAllocator>>>;
  _idles_type idles;

  // setters for named parameter idiom
  Type & set__start_idx(
    const uint64_t & _arg)
  {
    this->start_idx = _arg;
    return *this;
  }
  Type & set__dt(
    const int64_t & _arg)
  {
    this->dt = _arg;
    return *this;
  }
  Type & set__start_t(
    const int64_t & _arg)
  {
    this->start_t = _arg;
    return *this;
  }
  Type & set__knots(
    const std::vector<sfuise_msgs::msg::Knot_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<sfuise_msgs::msg::Knot_<ContainerAllocator>>> & _arg)
  {
    this->knots = _arg;
    return *this;
  }
  Type & set__idles(
    const std::vector<sfuise_msgs::msg::Knot_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<sfuise_msgs::msg::Knot_<ContainerAllocator>>> & _arg)
  {
    this->idles = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sfuise_msgs::msg::Spline_<ContainerAllocator> *;
  using ConstRawPtr =
    const sfuise_msgs::msg::Spline_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sfuise_msgs::msg::Spline_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sfuise_msgs::msg::Spline_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sfuise_msgs::msg::Spline_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sfuise_msgs::msg::Spline_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sfuise_msgs::msg::Spline_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sfuise_msgs::msg::Spline_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sfuise_msgs::msg::Spline_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sfuise_msgs::msg::Spline_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sfuise_msgs__msg__Spline
    std::shared_ptr<sfuise_msgs::msg::Spline_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sfuise_msgs__msg__Spline
    std::shared_ptr<sfuise_msgs::msg::Spline_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Spline_ & other) const
  {
    if (this->start_idx != other.start_idx) {
      return false;
    }
    if (this->dt != other.dt) {
      return false;
    }
    if (this->start_t != other.start_t) {
      return false;
    }
    if (this->knots != other.knots) {
      return false;
    }
    if (this->idles != other.idles) {
      return false;
    }
    return true;
  }
  bool operator!=(const Spline_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Spline_

// alias to use template instance with default allocator
using Spline =
  sfuise_msgs::msg::Spline_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sfuise_msgs

#endif  // SFUISE_MSGS__MSG__DETAIL__SPLINE__STRUCT_HPP_
