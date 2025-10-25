// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from isas_msgs:msg/RTLSRange.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__BUILDER_HPP_
#define ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "isas_msgs/msg/detail/rtls_range__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace isas_msgs
{

namespace msg
{

namespace builder
{

class Init_RTLSRange_ra
{
public:
  explicit Init_RTLSRange_ra(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  ::isas_msgs::msg::RTLSRange ra(::isas_msgs::msg::RTLSRange::_ra_type arg)
  {
    msg_.ra = std::move(arg);
    return std::move(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_toc
{
public:
  explicit Init_RTLSRange_toc(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  Init_RTLSRange_ra toc(::isas_msgs::msg::RTLSRange::_toc_type arg)
  {
    msg_.toc = std::move(arg);
    return Init_RTLSRange_ra(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_cmn
{
public:
  explicit Init_RTLSRange_cmn(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  Init_RTLSRange_toc cmn(::isas_msgs::msg::RTLSRange::_cmn_type arg)
  {
    msg_.cmn = std::move(arg);
    return Init_RTLSRange_toc(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_csn
{
public:
  explicit Init_RTLSRange_csn(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  Init_RTLSRange_cmn csn(::isas_msgs::msg::RTLSRange::_csn_type arg)
  {
    msg_.csn = std::move(arg);
    return Init_RTLSRange_cmn(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_rxp
{
public:
  explicit Init_RTLSRange_rxp(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  Init_RTLSRange_csn rxp(::isas_msgs::msg::RTLSRange::_rxp_type arg)
  {
    msg_.rxp = std::move(arg);
    return Init_RTLSRange_csn(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_fpp
{
public:
  explicit Init_RTLSRange_fpp(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  Init_RTLSRange_rxp fpp(::isas_msgs::msg::RTLSRange::_fpp_type arg)
  {
    msg_.fpp = std::move(arg);
    return Init_RTLSRange_rxp(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_var
{
public:
  explicit Init_RTLSRange_var(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  Init_RTLSRange_fpp var(::isas_msgs::msg::RTLSRange::_var_type arg)
  {
    msg_.var = std::move(arg);
    return Init_RTLSRange_fpp(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_mean
{
public:
  explicit Init_RTLSRange_mean(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  Init_RTLSRange_var mean(::isas_msgs::msg::RTLSRange::_mean_type arg)
  {
    msg_.mean = std::move(arg);
    return Init_RTLSRange_var(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_range
{
public:
  explicit Init_RTLSRange_range(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  Init_RTLSRange_mean range(::isas_msgs::msg::RTLSRange::_range_type arg)
  {
    msg_.range = std::move(arg);
    return Init_RTLSRange_mean(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_pr
{
public:
  explicit Init_RTLSRange_pr(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  Init_RTLSRange_range pr(::isas_msgs::msg::RTLSRange::_pr_type arg)
  {
    msg_.pr = std::move(arg);
    return Init_RTLSRange_range(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_pos
{
public:
  explicit Init_RTLSRange_pos(::isas_msgs::msg::RTLSRange & msg)
  : msg_(msg)
  {}
  Init_RTLSRange_pr pos(::isas_msgs::msg::RTLSRange::_pos_type arg)
  {
    msg_.pos = std::move(arg);
    return Init_RTLSRange_pr(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

class Init_RTLSRange_id
{
public:
  Init_RTLSRange_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RTLSRange_pos id(::isas_msgs::msg::RTLSRange::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_RTLSRange_pos(msg_);
  }

private:
  ::isas_msgs::msg::RTLSRange msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::isas_msgs::msg::RTLSRange>()
{
  return isas_msgs::msg::builder::Init_RTLSRange_id();
}

}  // namespace isas_msgs

#endif  // ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__BUILDER_HPP_
