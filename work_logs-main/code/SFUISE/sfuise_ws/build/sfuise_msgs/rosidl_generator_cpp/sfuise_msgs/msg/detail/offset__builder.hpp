// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sfuise_msgs:msg/Offset.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__OFFSET__BUILDER_HPP_
#define SFUISE_MSGS__MSG__DETAIL__OFFSET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sfuise_msgs/msg/detail/offset__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sfuise_msgs
{

namespace msg
{

namespace builder
{

class Init_Offset_t_tag_body
{
public:
  explicit Init_Offset_t_tag_body(::sfuise_msgs::msg::Offset & msg)
  : msg_(msg)
  {}
  ::sfuise_msgs::msg::Offset t_tag_body(::sfuise_msgs::msg::Offset::_t_tag_body_type arg)
  {
    msg_.t_tag_body = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sfuise_msgs::msg::Offset msg_;
};

class Init_Offset_id_antenna
{
public:
  explicit Init_Offset_id_antenna(::sfuise_msgs::msg::Offset & msg)
  : msg_(msg)
  {}
  Init_Offset_t_tag_body id_antenna(::sfuise_msgs::msg::Offset::_id_antenna_type arg)
  {
    msg_.id_antenna = std::move(arg);
    return Init_Offset_t_tag_body(msg_);
  }

private:
  ::sfuise_msgs::msg::Offset msg_;
};

class Init_Offset_id_tag
{
public:
  Init_Offset_id_tag()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Offset_id_antenna id_tag(::sfuise_msgs::msg::Offset::_id_tag_type arg)
  {
    msg_.id_tag = std::move(arg);
    return Init_Offset_id_antenna(msg_);
  }

private:
  ::sfuise_msgs::msg::Offset msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sfuise_msgs::msg::Offset>()
{
  return sfuise_msgs::msg::builder::Init_Offset_id_tag();
}

}  // namespace sfuise_msgs

#endif  // SFUISE_MSGS__MSG__DETAIL__OFFSET__BUILDER_HPP_
