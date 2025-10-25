// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from isas_msgs:msg/RTLSRange.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__STRUCT_HPP_
#define ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pos'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__isas_msgs__msg__RTLSRange __attribute__((deprecated))
#else
# define DEPRECATED__isas_msgs__msg__RTLSRange __declspec(deprecated)
#endif

namespace isas_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RTLSRange_
{
  using Type = RTLSRange_<ContainerAllocator>;

  explicit RTLSRange_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pos(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->pr = 0.0f;
      this->range = 0.0f;
      this->mean = 0.0f;
      this->var = 0.0f;
      this->fpp = 0.0f;
      this->rxp = 0.0f;
      this->csn = 0.0f;
      this->cmn = 0.0f;
      this->toc = 0;
      this->ra = 0;
    }
  }

  explicit RTLSRange_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pos(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->pr = 0.0f;
      this->range = 0.0f;
      this->mean = 0.0f;
      this->var = 0.0f;
      this->fpp = 0.0f;
      this->rxp = 0.0f;
      this->csn = 0.0f;
      this->cmn = 0.0f;
      this->toc = 0;
      this->ra = 0;
    }
  }

  // field types and members
  using _id_type =
    uint16_t;
  _id_type id;
  using _pos_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _pos_type pos;
  using _pr_type =
    float;
  _pr_type pr;
  using _range_type =
    float;
  _range_type range;
  using _mean_type =
    float;
  _mean_type mean;
  using _var_type =
    float;
  _var_type var;
  using _fpp_type =
    float;
  _fpp_type fpp;
  using _rxp_type =
    float;
  _rxp_type rxp;
  using _csn_type =
    float;
  _csn_type csn;
  using _cmn_type =
    float;
  _cmn_type cmn;
  using _toc_type =
    uint8_t;
  _toc_type toc;
  using _ra_type =
    uint8_t;
  _ra_type ra;

  // setters for named parameter idiom
  Type & set__id(
    const uint16_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__pos(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->pos = _arg;
    return *this;
  }
  Type & set__pr(
    const float & _arg)
  {
    this->pr = _arg;
    return *this;
  }
  Type & set__range(
    const float & _arg)
  {
    this->range = _arg;
    return *this;
  }
  Type & set__mean(
    const float & _arg)
  {
    this->mean = _arg;
    return *this;
  }
  Type & set__var(
    const float & _arg)
  {
    this->var = _arg;
    return *this;
  }
  Type & set__fpp(
    const float & _arg)
  {
    this->fpp = _arg;
    return *this;
  }
  Type & set__rxp(
    const float & _arg)
  {
    this->rxp = _arg;
    return *this;
  }
  Type & set__csn(
    const float & _arg)
  {
    this->csn = _arg;
    return *this;
  }
  Type & set__cmn(
    const float & _arg)
  {
    this->cmn = _arg;
    return *this;
  }
  Type & set__toc(
    const uint8_t & _arg)
  {
    this->toc = _arg;
    return *this;
  }
  Type & set__ra(
    const uint8_t & _arg)
  {
    this->ra = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    isas_msgs::msg::RTLSRange_<ContainerAllocator> *;
  using ConstRawPtr =
    const isas_msgs::msg::RTLSRange_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<isas_msgs::msg::RTLSRange_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<isas_msgs::msg::RTLSRange_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      isas_msgs::msg::RTLSRange_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<isas_msgs::msg::RTLSRange_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      isas_msgs::msg::RTLSRange_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<isas_msgs::msg::RTLSRange_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<isas_msgs::msg::RTLSRange_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<isas_msgs::msg::RTLSRange_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__isas_msgs__msg__RTLSRange
    std::shared_ptr<isas_msgs::msg::RTLSRange_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__isas_msgs__msg__RTLSRange
    std::shared_ptr<isas_msgs::msg::RTLSRange_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RTLSRange_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->pos != other.pos) {
      return false;
    }
    if (this->pr != other.pr) {
      return false;
    }
    if (this->range != other.range) {
      return false;
    }
    if (this->mean != other.mean) {
      return false;
    }
    if (this->var != other.var) {
      return false;
    }
    if (this->fpp != other.fpp) {
      return false;
    }
    if (this->rxp != other.rxp) {
      return false;
    }
    if (this->csn != other.csn) {
      return false;
    }
    if (this->cmn != other.cmn) {
      return false;
    }
    if (this->toc != other.toc) {
      return false;
    }
    if (this->ra != other.ra) {
      return false;
    }
    return true;
  }
  bool operator!=(const RTLSRange_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RTLSRange_

// alias to use template instance with default allocator
using RTLSRange =
  isas_msgs::msg::RTLSRange_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace isas_msgs

#endif  // ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__STRUCT_HPP_
