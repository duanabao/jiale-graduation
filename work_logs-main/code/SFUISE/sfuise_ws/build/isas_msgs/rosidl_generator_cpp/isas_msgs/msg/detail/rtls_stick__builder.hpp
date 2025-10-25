// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from isas_msgs:msg/RTLSStick.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__RTLS_STICK__BUILDER_HPP_
#define ISAS_MSGS__MSG__DETAIL__RTLS_STICK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "isas_msgs/msg/detail/rtls_stick__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace isas_msgs
{

namespace msg
{

namespace builder
{

class Init_RTLSStick_ranges
{
public:
  explicit Init_RTLSStick_ranges(::isas_msgs::msg::RTLSStick & msg)
  : msg_(msg)
  {}
  ::isas_msgs::msg::RTLSStick ranges(::isas_msgs::msg::RTLSStick::_ranges_type arg)
  {
    msg_.ranges = std::move(arg);
    return std::move(msg_);
  }

private:
  ::isas_msgs::msg::RTLSStick msg_;
};

class Init_RTLSStick_nora
{
public:
  explicit Init_RTLSStick_nora(::isas_msgs::msg::RTLSStick & msg)
  : msg_(msg)
  {}
  Init_RTLSStick_ranges nora(::isas_msgs::msg::RTLSStick::_nora_type arg)
  {
    msg_.nora = std::move(arg);
    return Init_RTLSStick_ranges(msg_);
  }

private:
  ::isas_msgs::msg::RTLSStick msg_;
};

class Init_RTLSStick_noga
{
public:
  explicit Init_RTLSStick_noga(::isas_msgs::msg::RTLSStick & msg)
  : msg_(msg)
  {}
  Init_RTLSStick_nora noga(::isas_msgs::msg::RTLSStick::_noga_type arg)
  {
    msg_.noga = std::move(arg);
    return Init_RTLSStick_nora(msg_);
  }

private:
  ::isas_msgs::msg::RTLSStick msg_;
};

class Init_RTLSStick_hrp
{
public:
  explicit Init_RTLSStick_hrp(::isas_msgs::msg::RTLSStick & msg)
  : msg_(msg)
  {}
  Init_RTLSStick_noga hrp(::isas_msgs::msg::RTLSStick::_hrp_type arg)
  {
    msg_.hrp = std::move(arg);
    return Init_RTLSStick_noga(msg_);
  }

private:
  ::isas_msgs::msg::RTLSStick msg_;
};

class Init_RTLSStick_mean
{
public:
  explicit Init_RTLSStick_mean(::isas_msgs::msg::RTLSStick & msg)
  : msg_(msg)
  {}
  Init_RTLSStick_hrp mean(::isas_msgs::msg::RTLSStick::_mean_type arg)
  {
    msg_.mean = std::move(arg);
    return Init_RTLSStick_hrp(msg_);
  }

private:
  ::isas_msgs::msg::RTLSStick msg_;
};

class Init_RTLSStick_pos
{
public:
  explicit Init_RTLSStick_pos(::isas_msgs::msg::RTLSStick & msg)
  : msg_(msg)
  {}
  Init_RTLSStick_mean pos(::isas_msgs::msg::RTLSStick::_pos_type arg)
  {
    msg_.pos = std::move(arg);
    return Init_RTLSStick_mean(msg_);
  }

private:
  ::isas_msgs::msg::RTLSStick msg_;
};

class Init_RTLSStick_t
{
public:
  explicit Init_RTLSStick_t(::isas_msgs::msg::RTLSStick & msg)
  : msg_(msg)
  {}
  Init_RTLSStick_pos t(::isas_msgs::msg::RTLSStick::_t_type arg)
  {
    msg_.t = std::move(arg);
    return Init_RTLSStick_pos(msg_);
  }

private:
  ::isas_msgs::msg::RTLSStick msg_;
};

class Init_RTLSStick_id
{
public:
  explicit Init_RTLSStick_id(::isas_msgs::msg::RTLSStick & msg)
  : msg_(msg)
  {}
  Init_RTLSStick_t id(::isas_msgs::msg::RTLSStick::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_RTLSStick_t(msg_);
  }

private:
  ::isas_msgs::msg::RTLSStick msg_;
};

class Init_RTLSStick_header
{
public:
  Init_RTLSStick_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RTLSStick_id header(::isas_msgs::msg::RTLSStick::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_RTLSStick_id(msg_);
  }

private:
  ::isas_msgs::msg::RTLSStick msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::isas_msgs::msg::RTLSStick>()
{
  return isas_msgs::msg::builder::Init_RTLSStick_header();
}

}  // namespace isas_msgs

#endif  // ISAS_MSGS__MSG__DETAIL__RTLS_STICK__BUILDER_HPP_
