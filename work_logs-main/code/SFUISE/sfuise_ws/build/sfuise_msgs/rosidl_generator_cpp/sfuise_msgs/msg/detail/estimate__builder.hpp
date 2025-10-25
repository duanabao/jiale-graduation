// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sfuise_msgs:msg/Estimate.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__ESTIMATE__BUILDER_HPP_
#define SFUISE_MSGS__MSG__DETAIL__ESTIMATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sfuise_msgs/msg/detail/estimate__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sfuise_msgs
{

namespace msg
{

namespace builder
{

class Init_Estimate_runtime
{
public:
  explicit Init_Estimate_runtime(::sfuise_msgs::msg::Estimate & msg)
  : msg_(msg)
  {}
  ::sfuise_msgs::msg::Estimate runtime(::sfuise_msgs::msg::Estimate::_runtime_type arg)
  {
    msg_.runtime = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sfuise_msgs::msg::Estimate msg_;
};

class Init_Estimate_if_full_window
{
public:
  explicit Init_Estimate_if_full_window(::sfuise_msgs::msg::Estimate & msg)
  : msg_(msg)
  {}
  Init_Estimate_runtime if_full_window(::sfuise_msgs::msg::Estimate::_if_full_window_type arg)
  {
    msg_.if_full_window = std::move(arg);
    return Init_Estimate_runtime(msg_);
  }

private:
  ::sfuise_msgs::msg::Estimate msg_;
};

class Init_Estimate_spline
{
public:
  Init_Estimate_spline()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Estimate_if_full_window spline(::sfuise_msgs::msg::Estimate::_spline_type arg)
  {
    msg_.spline = std::move(arg);
    return Init_Estimate_if_full_window(msg_);
  }

private:
  ::sfuise_msgs::msg::Estimate msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sfuise_msgs::msg::Estimate>()
{
  return sfuise_msgs::msg::builder::Init_Estimate_spline();
}

}  // namespace sfuise_msgs

#endif  // SFUISE_MSGS__MSG__DETAIL__ESTIMATE__BUILDER_HPP_
