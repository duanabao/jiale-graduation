// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cf_msgs:msg/Accel.idl
// generated code does not contain a copyright notice

#ifndef CF_MSGS__MSG__DETAIL__ACCEL__BUILDER_HPP_
#define CF_MSGS__MSG__DETAIL__ACCEL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cf_msgs/msg/detail/accel__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cf_msgs
{

namespace msg
{

namespace builder
{

class Init_Accel_z
{
public:
  explicit Init_Accel_z(::cf_msgs::msg::Accel & msg)
  : msg_(msg)
  {}
  ::cf_msgs::msg::Accel z(::cf_msgs::msg::Accel::_z_type arg)
  {
    msg_.z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cf_msgs::msg::Accel msg_;
};

class Init_Accel_y
{
public:
  explicit Init_Accel_y(::cf_msgs::msg::Accel & msg)
  : msg_(msg)
  {}
  Init_Accel_z y(::cf_msgs::msg::Accel::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Accel_z(msg_);
  }

private:
  ::cf_msgs::msg::Accel msg_;
};

class Init_Accel_x
{
public:
  explicit Init_Accel_x(::cf_msgs::msg::Accel & msg)
  : msg_(msg)
  {}
  Init_Accel_y x(::cf_msgs::msg::Accel::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Accel_y(msg_);
  }

private:
  ::cf_msgs::msg::Accel msg_;
};

class Init_Accel_header
{
public:
  Init_Accel_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Accel_x header(::cf_msgs::msg::Accel::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Accel_x(msg_);
  }

private:
  ::cf_msgs::msg::Accel msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cf_msgs::msg::Accel>()
{
  return cf_msgs::msg::builder::Init_Accel_header();
}

}  // namespace cf_msgs

#endif  // CF_MSGS__MSG__DETAIL__ACCEL__BUILDER_HPP_
