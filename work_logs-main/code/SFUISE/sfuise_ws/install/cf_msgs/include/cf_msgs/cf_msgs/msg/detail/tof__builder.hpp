// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cf_msgs:msg/Tof.idl
// generated code does not contain a copyright notice

#ifndef CF_MSGS__MSG__DETAIL__TOF__BUILDER_HPP_
#define CF_MSGS__MSG__DETAIL__TOF__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cf_msgs/msg/detail/tof__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cf_msgs
{

namespace msg
{

namespace builder
{

class Init_Tof_zrange
{
public:
  explicit Init_Tof_zrange(::cf_msgs::msg::Tof & msg)
  : msg_(msg)
  {}
  ::cf_msgs::msg::Tof zrange(::cf_msgs::msg::Tof::_zrange_type arg)
  {
    msg_.zrange = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cf_msgs::msg::Tof msg_;
};

class Init_Tof_header
{
public:
  Init_Tof_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Tof_zrange header(::cf_msgs::msg::Tof::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Tof_zrange(msg_);
  }

private:
  ::cf_msgs::msg::Tof msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cf_msgs::msg::Tof>()
{
  return cf_msgs::msg::builder::Init_Tof_header();
}

}  // namespace cf_msgs

#endif  // CF_MSGS__MSG__DETAIL__TOF__BUILDER_HPP_
