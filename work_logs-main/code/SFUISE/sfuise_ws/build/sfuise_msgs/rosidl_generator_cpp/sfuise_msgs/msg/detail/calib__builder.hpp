// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sfuise_msgs:msg/Calib.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__CALIB__BUILDER_HPP_
#define SFUISE_MSGS__MSG__DETAIL__CALIB__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sfuise_msgs/msg/detail/calib__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sfuise_msgs
{

namespace msg
{

namespace builder
{

class Init_Calib_t_tag_body_set
{
public:
  explicit Init_Calib_t_tag_body_set(::sfuise_msgs::msg::Calib & msg)
  : msg_(msg)
  {}
  ::sfuise_msgs::msg::Calib t_tag_body_set(::sfuise_msgs::msg::Calib::_t_tag_body_set_type arg)
  {
    msg_.t_tag_body_set = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sfuise_msgs::msg::Calib msg_;
};

class Init_Calib_q_nav_uwb
{
public:
  explicit Init_Calib_q_nav_uwb(::sfuise_msgs::msg::Calib & msg)
  : msg_(msg)
  {}
  Init_Calib_t_tag_body_set q_nav_uwb(::sfuise_msgs::msg::Calib::_q_nav_uwb_type arg)
  {
    msg_.q_nav_uwb = std::move(arg);
    return Init_Calib_t_tag_body_set(msg_);
  }

private:
  ::sfuise_msgs::msg::Calib msg_;
};

class Init_Calib_t_nav_uwb
{
public:
  explicit Init_Calib_t_nav_uwb(::sfuise_msgs::msg::Calib & msg)
  : msg_(msg)
  {}
  Init_Calib_q_nav_uwb t_nav_uwb(::sfuise_msgs::msg::Calib::_t_nav_uwb_type arg)
  {
    msg_.t_nav_uwb = std::move(arg);
    return Init_Calib_q_nav_uwb(msg_);
  }

private:
  ::sfuise_msgs::msg::Calib msg_;
};

class Init_Calib_gravity
{
public:
  Init_Calib_gravity()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Calib_t_nav_uwb gravity(::sfuise_msgs::msg::Calib::_gravity_type arg)
  {
    msg_.gravity = std::move(arg);
    return Init_Calib_t_nav_uwb(msg_);
  }

private:
  ::sfuise_msgs::msg::Calib msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sfuise_msgs::msg::Calib>()
{
  return sfuise_msgs::msg::builder::Init_Calib_gravity();
}

}  // namespace sfuise_msgs

#endif  // SFUISE_MSGS__MSG__DETAIL__CALIB__BUILDER_HPP_
