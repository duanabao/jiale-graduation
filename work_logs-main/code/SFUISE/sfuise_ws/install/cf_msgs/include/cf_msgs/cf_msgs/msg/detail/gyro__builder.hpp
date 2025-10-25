// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cf_msgs:msg/Gyro.idl
// generated code does not contain a copyright notice

#ifndef CF_MSGS__MSG__DETAIL__GYRO__BUILDER_HPP_
#define CF_MSGS__MSG__DETAIL__GYRO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cf_msgs/msg/detail/gyro__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cf_msgs
{

namespace msg
{

namespace builder
{

class Init_Gyro_z
{
public:
  explicit Init_Gyro_z(::cf_msgs::msg::Gyro & msg)
  : msg_(msg)
  {}
  ::cf_msgs::msg::Gyro z(::cf_msgs::msg::Gyro::_z_type arg)
  {
    msg_.z = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cf_msgs::msg::Gyro msg_;
};

class Init_Gyro_y
{
public:
  explicit Init_Gyro_y(::cf_msgs::msg::Gyro & msg)
  : msg_(msg)
  {}
  Init_Gyro_z y(::cf_msgs::msg::Gyro::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Gyro_z(msg_);
  }

private:
  ::cf_msgs::msg::Gyro msg_;
};

class Init_Gyro_x
{
public:
  explicit Init_Gyro_x(::cf_msgs::msg::Gyro & msg)
  : msg_(msg)
  {}
  Init_Gyro_y x(::cf_msgs::msg::Gyro::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Gyro_y(msg_);
  }

private:
  ::cf_msgs::msg::Gyro msg_;
};

class Init_Gyro_header
{
public:
  Init_Gyro_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Gyro_x header(::cf_msgs::msg::Gyro::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Gyro_x(msg_);
  }

private:
  ::cf_msgs::msg::Gyro msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cf_msgs::msg::Gyro>()
{
  return cf_msgs::msg::builder::Init_Gyro_header();
}

}  // namespace cf_msgs

#endif  // CF_MSGS__MSG__DETAIL__GYRO__BUILDER_HPP_
