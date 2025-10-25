// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from isas_msgs:msg/AnchorPosition.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__BUILDER_HPP_
#define ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "isas_msgs/msg/detail/anchor_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace isas_msgs
{

namespace msg
{

namespace builder
{

class Init_AnchorPosition_position
{
public:
  explicit Init_AnchorPosition_position(::isas_msgs::msg::AnchorPosition & msg)
  : msg_(msg)
  {}
  ::isas_msgs::msg::AnchorPosition position(::isas_msgs::msg::AnchorPosition::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::isas_msgs::msg::AnchorPosition msg_;
};

class Init_AnchorPosition_id
{
public:
  Init_AnchorPosition_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AnchorPosition_position id(::isas_msgs::msg::AnchorPosition::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_AnchorPosition_position(msg_);
  }

private:
  ::isas_msgs::msg::AnchorPosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::isas_msgs::msg::AnchorPosition>()
{
  return isas_msgs::msg::builder::Init_AnchorPosition_id();
}

}  // namespace isas_msgs

#endif  // ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__BUILDER_HPP_
