// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from isas_msgs:msg/RTLSStick.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__RTLS_STICK__STRUCT_HPP_
#define ISAS_MSGS__MSG__DETAIL__RTLS_STICK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'pos'
// Member 'mean'
#include "geometry_msgs/msg/detail/point__struct.hpp"
// Member 'hrp'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"
// Member 'ranges'
#include "isas_msgs/msg/detail/rtls_range__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__isas_msgs__msg__RTLSStick __attribute__((deprecated))
#else
# define DEPRECATED__isas_msgs__msg__RTLSStick __declspec(deprecated)
#endif

namespace isas_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RTLSStick_
{
  using Type = RTLSStick_<ContainerAllocator>;

  explicit RTLSStick_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    pos(_init),
    mean(_init),
    hrp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->t = 0ul;
      this->noga = 0;
      this->nora = 0;
    }
  }

  explicit RTLSStick_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    pos(_alloc, _init),
    mean(_alloc, _init),
    hrp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->t = 0ul;
      this->noga = 0;
      this->nora = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _id_type =
    uint16_t;
  _id_type id;
  using _t_type =
    uint32_t;
  _t_type t;
  using _pos_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _pos_type pos;
  using _mean_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _mean_type mean;
  using _hrp_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _hrp_type hrp;
  using _noga_type =
    uint8_t;
  _noga_type noga;
  using _nora_type =
    uint8_t;
  _nora_type nora;
  using _ranges_type =
    std::vector<isas_msgs::msg::RTLSRange_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<isas_msgs::msg::RTLSRange_<ContainerAllocator>>>;
  _ranges_type ranges;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__id(
    const uint16_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__t(
    const uint32_t & _arg)
  {
    this->t = _arg;
    return *this;
  }
  Type & set__pos(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->pos = _arg;
    return *this;
  }
  Type & set__mean(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->mean = _arg;
    return *this;
  }
  Type & set__hrp(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->hrp = _arg;
    return *this;
  }
  Type & set__noga(
    const uint8_t & _arg)
  {
    this->noga = _arg;
    return *this;
  }
  Type & set__nora(
    const uint8_t & _arg)
  {
    this->nora = _arg;
    return *this;
  }
  Type & set__ranges(
    const std::vector<isas_msgs::msg::RTLSRange_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<isas_msgs::msg::RTLSRange_<ContainerAllocator>>> & _arg)
  {
    this->ranges = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    isas_msgs::msg::RTLSStick_<ContainerAllocator> *;
  using ConstRawPtr =
    const isas_msgs::msg::RTLSStick_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<isas_msgs::msg::RTLSStick_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<isas_msgs::msg::RTLSStick_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      isas_msgs::msg::RTLSStick_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<isas_msgs::msg::RTLSStick_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      isas_msgs::msg::RTLSStick_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<isas_msgs::msg::RTLSStick_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<isas_msgs::msg::RTLSStick_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<isas_msgs::msg::RTLSStick_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__isas_msgs__msg__RTLSStick
    std::shared_ptr<isas_msgs::msg::RTLSStick_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__isas_msgs__msg__RTLSStick
    std::shared_ptr<isas_msgs::msg::RTLSStick_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RTLSStick_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->id != other.id) {
      return false;
    }
    if (this->t != other.t) {
      return false;
    }
    if (this->pos != other.pos) {
      return false;
    }
    if (this->mean != other.mean) {
      return false;
    }
    if (this->hrp != other.hrp) {
      return false;
    }
    if (this->noga != other.noga) {
      return false;
    }
    if (this->nora != other.nora) {
      return false;
    }
    if (this->ranges != other.ranges) {
      return false;
    }
    return true;
  }
  bool operator!=(const RTLSStick_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RTLSStick_

// alias to use template instance with default allocator
using RTLSStick =
  isas_msgs::msg::RTLSStick_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace isas_msgs

#endif  // ISAS_MSGS__MSG__DETAIL__RTLS_STICK__STRUCT_HPP_
