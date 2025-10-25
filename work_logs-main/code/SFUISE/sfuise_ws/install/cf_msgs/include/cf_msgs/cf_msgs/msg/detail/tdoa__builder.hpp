// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cf_msgs:msg/Tdoa.idl
// generated code does not contain a copyright notice

#ifndef CF_MSGS__MSG__DETAIL__TDOA__BUILDER_HPP_
#define CF_MSGS__MSG__DETAIL__TDOA__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cf_msgs/msg/detail/tdoa__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cf_msgs
{

namespace msg
{

namespace builder
{

class Init_Tdoa_data
{
public:
  explicit Init_Tdoa_data(::cf_msgs::msg::Tdoa & msg)
  : msg_(msg)
  {}
  ::cf_msgs::msg::Tdoa data(::cf_msgs::msg::Tdoa::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cf_msgs::msg::Tdoa msg_;
};

class Init_Tdoa_id_b
{
public:
  explicit Init_Tdoa_id_b(::cf_msgs::msg::Tdoa & msg)
  : msg_(msg)
  {}
  Init_Tdoa_data id_b(::cf_msgs::msg::Tdoa::_id_b_type arg)
  {
    msg_.id_b = std::move(arg);
    return Init_Tdoa_data(msg_);
  }

private:
  ::cf_msgs::msg::Tdoa msg_;
};

class Init_Tdoa_id_a
{
public:
  explicit Init_Tdoa_id_a(::cf_msgs::msg::Tdoa & msg)
  : msg_(msg)
  {}
  Init_Tdoa_id_b id_a(::cf_msgs::msg::Tdoa::_id_a_type arg)
  {
    msg_.id_a = std::move(arg);
    return Init_Tdoa_id_b(msg_);
  }

private:
  ::cf_msgs::msg::Tdoa msg_;
};

class Init_Tdoa_header
{
public:
  Init_Tdoa_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Tdoa_id_a header(::cf_msgs::msg::Tdoa::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Tdoa_id_a(msg_);
  }

private:
  ::cf_msgs::msg::Tdoa msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cf_msgs::msg::Tdoa>()
{
  return cf_msgs::msg::builder::Init_Tdoa_header();
}

}  // namespace cf_msgs

#endif  // CF_MSGS__MSG__DETAIL__TDOA__BUILDER_HPP_
