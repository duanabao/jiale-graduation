// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sfuise_msgs:msg/Spline.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__SPLINE__BUILDER_HPP_
#define SFUISE_MSGS__MSG__DETAIL__SPLINE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sfuise_msgs/msg/detail/spline__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sfuise_msgs
{

namespace msg
{

namespace builder
{

class Init_Spline_idles
{
public:
  explicit Init_Spline_idles(::sfuise_msgs::msg::Spline & msg)
  : msg_(msg)
  {}
  ::sfuise_msgs::msg::Spline idles(::sfuise_msgs::msg::Spline::_idles_type arg)
  {
    msg_.idles = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sfuise_msgs::msg::Spline msg_;
};

class Init_Spline_knots
{
public:
  explicit Init_Spline_knots(::sfuise_msgs::msg::Spline & msg)
  : msg_(msg)
  {}
  Init_Spline_idles knots(::sfuise_msgs::msg::Spline::_knots_type arg)
  {
    msg_.knots = std::move(arg);
    return Init_Spline_idles(msg_);
  }

private:
  ::sfuise_msgs::msg::Spline msg_;
};

class Init_Spline_start_t
{
public:
  explicit Init_Spline_start_t(::sfuise_msgs::msg::Spline & msg)
  : msg_(msg)
  {}
  Init_Spline_knots start_t(::sfuise_msgs::msg::Spline::_start_t_type arg)
  {
    msg_.start_t = std::move(arg);
    return Init_Spline_knots(msg_);
  }

private:
  ::sfuise_msgs::msg::Spline msg_;
};

class Init_Spline_dt
{
public:
  explicit Init_Spline_dt(::sfuise_msgs::msg::Spline & msg)
  : msg_(msg)
  {}
  Init_Spline_start_t dt(::sfuise_msgs::msg::Spline::_dt_type arg)
  {
    msg_.dt = std::move(arg);
    return Init_Spline_start_t(msg_);
  }

private:
  ::sfuise_msgs::msg::Spline msg_;
};

class Init_Spline_start_idx
{
public:
  Init_Spline_start_idx()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Spline_dt start_idx(::sfuise_msgs::msg::Spline::_start_idx_type arg)
  {
    msg_.start_idx = std::move(arg);
    return Init_Spline_dt(msg_);
  }

private:
  ::sfuise_msgs::msg::Spline msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sfuise_msgs::msg::Spline>()
{
  return sfuise_msgs::msg::builder::Init_Spline_start_idx();
}

}  // namespace sfuise_msgs

#endif  // SFUISE_MSGS__MSG__DETAIL__SPLINE__BUILDER_HPP_
