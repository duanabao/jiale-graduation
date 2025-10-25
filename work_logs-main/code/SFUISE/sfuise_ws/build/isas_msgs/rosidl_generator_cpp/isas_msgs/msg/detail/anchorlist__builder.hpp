// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from isas_msgs:msg/Anchorlist.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__ANCHORLIST__BUILDER_HPP_
#define ISAS_MSGS__MSG__DETAIL__ANCHORLIST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "isas_msgs/msg/detail/anchorlist__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace isas_msgs
{

namespace msg
{

namespace builder
{

class Init_Anchorlist_anchor
{
public:
  Init_Anchorlist_anchor()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::isas_msgs::msg::Anchorlist anchor(::isas_msgs::msg::Anchorlist::_anchor_type arg)
  {
    msg_.anchor = std::move(arg);
    return std::move(msg_);
  }

private:
  ::isas_msgs::msg::Anchorlist msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::isas_msgs::msg::Anchorlist>()
{
  return isas_msgs::msg::builder::Init_Anchorlist_anchor();
}

}  // namespace isas_msgs

#endif  // ISAS_MSGS__MSG__DETAIL__ANCHORLIST__BUILDER_HPP_
