// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sfuise_msgs:msg/Knot.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__KNOT__BUILDER_HPP_
#define SFUISE_MSGS__MSG__DETAIL__KNOT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sfuise_msgs/msg/detail/knot__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sfuise_msgs
{

namespace msg
{

namespace builder
{

class Init_Knot_bias_gyro
{
public:
  explicit Init_Knot_bias_gyro(::sfuise_msgs::msg::Knot & msg)
  : msg_(msg)
  {}
  ::sfuise_msgs::msg::Knot bias_gyro(::sfuise_msgs::msg::Knot::_bias_gyro_type arg)
  {
    msg_.bias_gyro = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sfuise_msgs::msg::Knot msg_;
};

class Init_Knot_bias_acc
{
public:
  explicit Init_Knot_bias_acc(::sfuise_msgs::msg::Knot & msg)
  : msg_(msg)
  {}
  Init_Knot_bias_gyro bias_acc(::sfuise_msgs::msg::Knot::_bias_acc_type arg)
  {
    msg_.bias_acc = std::move(arg);
    return Init_Knot_bias_gyro(msg_);
  }

private:
  ::sfuise_msgs::msg::Knot msg_;
};

class Init_Knot_orientation
{
public:
  explicit Init_Knot_orientation(::sfuise_msgs::msg::Knot & msg)
  : msg_(msg)
  {}
  Init_Knot_bias_acc orientation(::sfuise_msgs::msg::Knot::_orientation_type arg)
  {
    msg_.orientation = std::move(arg);
    return Init_Knot_bias_acc(msg_);
  }

private:
  ::sfuise_msgs::msg::Knot msg_;
};

class Init_Knot_position
{
public:
  Init_Knot_position()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Knot_orientation position(::sfuise_msgs::msg::Knot::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_Knot_orientation(msg_);
  }

private:
  ::sfuise_msgs::msg::Knot msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sfuise_msgs::msg::Knot>()
{
  return sfuise_msgs::msg::builder::Init_Knot_position();
}

}  // namespace sfuise_msgs

#endif  // SFUISE_MSGS__MSG__DETAIL__KNOT__BUILDER_HPP_
