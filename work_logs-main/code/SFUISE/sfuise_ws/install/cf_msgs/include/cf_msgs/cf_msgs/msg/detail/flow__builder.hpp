// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cf_msgs:msg/Flow.idl
// generated code does not contain a copyright notice

#ifndef CF_MSGS__MSG__DETAIL__FLOW__BUILDER_HPP_
#define CF_MSGS__MSG__DETAIL__FLOW__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cf_msgs/msg/detail/flow__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cf_msgs
{

namespace msg
{

namespace builder
{

class Init_Flow_delta_y
{
public:
  explicit Init_Flow_delta_y(::cf_msgs::msg::Flow & msg)
  : msg_(msg)
  {}
  ::cf_msgs::msg::Flow delta_y(::cf_msgs::msg::Flow::_delta_y_type arg)
  {
    msg_.delta_y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cf_msgs::msg::Flow msg_;
};

class Init_Flow_delta_x
{
public:
  explicit Init_Flow_delta_x(::cf_msgs::msg::Flow & msg)
  : msg_(msg)
  {}
  Init_Flow_delta_y delta_x(::cf_msgs::msg::Flow::_delta_x_type arg)
  {
    msg_.delta_x = std::move(arg);
    return Init_Flow_delta_y(msg_);
  }

private:
  ::cf_msgs::msg::Flow msg_;
};

class Init_Flow_header
{
public:
  Init_Flow_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Flow_delta_x header(::cf_msgs::msg::Flow::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Flow_delta_x(msg_);
  }

private:
  ::cf_msgs::msg::Flow msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cf_msgs::msg::Flow>()
{
  return cf_msgs::msg::builder::Init_Flow_header();
}

}  // namespace cf_msgs

#endif  // CF_MSGS__MSG__DETAIL__FLOW__BUILDER_HPP_
