// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cf_msgs:msg/Baro.idl
// generated code does not contain a copyright notice

#ifndef CF_MSGS__MSG__DETAIL__BARO__BUILDER_HPP_
#define CF_MSGS__MSG__DETAIL__BARO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cf_msgs/msg/detail/baro__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cf_msgs
{

namespace msg
{

namespace builder
{

class Init_Baro_asl
{
public:
  explicit Init_Baro_asl(::cf_msgs::msg::Baro & msg)
  : msg_(msg)
  {}
  ::cf_msgs::msg::Baro asl(::cf_msgs::msg::Baro::_asl_type arg)
  {
    msg_.asl = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cf_msgs::msg::Baro msg_;
};

class Init_Baro_header
{
public:
  Init_Baro_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Baro_asl header(::cf_msgs::msg::Baro::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Baro_asl(msg_);
  }

private:
  ::cf_msgs::msg::Baro msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cf_msgs::msg::Baro>()
{
  return cf_msgs::msg::builder::Init_Baro_header();
}

}  // namespace cf_msgs

#endif  // CF_MSGS__MSG__DETAIL__BARO__BUILDER_HPP_
