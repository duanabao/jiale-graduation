// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cf_msgs:msg/Twr.idl
// generated code does not contain a copyright notice

#ifndef CF_MSGS__MSG__DETAIL__TWR__BUILDER_HPP_
#define CF_MSGS__MSG__DETAIL__TWR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cf_msgs/msg/detail/twr__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cf_msgs
{

namespace msg
{

namespace builder
{

class Init_Twr_data
{
public:
  explicit Init_Twr_data(::cf_msgs::msg::Twr & msg)
  : msg_(msg)
  {}
  ::cf_msgs::msg::Twr data(::cf_msgs::msg::Twr::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cf_msgs::msg::Twr msg_;
};

class Init_Twr_id
{
public:
  explicit Init_Twr_id(::cf_msgs::msg::Twr & msg)
  : msg_(msg)
  {}
  Init_Twr_data id(::cf_msgs::msg::Twr::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_Twr_data(msg_);
  }

private:
  ::cf_msgs::msg::Twr msg_;
};

class Init_Twr_header
{
public:
  Init_Twr_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Twr_id header(::cf_msgs::msg::Twr::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Twr_id(msg_);
  }

private:
  ::cf_msgs::msg::Twr msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cf_msgs::msg::Twr>()
{
  return cf_msgs::msg::builder::Init_Twr_header();
}

}  // namespace cf_msgs

#endif  // CF_MSGS__MSG__DETAIL__TWR__BUILDER_HPP_
