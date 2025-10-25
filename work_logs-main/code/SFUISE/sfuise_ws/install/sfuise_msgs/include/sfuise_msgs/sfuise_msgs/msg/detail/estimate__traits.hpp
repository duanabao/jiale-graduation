// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sfuise_msgs:msg/Estimate.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__ESTIMATE__TRAITS_HPP_
#define SFUISE_MSGS__MSG__DETAIL__ESTIMATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sfuise_msgs/msg/detail/estimate__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'spline'
#include "sfuise_msgs/msg/detail/spline__traits.hpp"
// Member 'if_full_window'
#include "std_msgs/msg/detail/bool__traits.hpp"
// Member 'runtime'
#include "std_msgs/msg/detail/float64__traits.hpp"

namespace sfuise_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Estimate & msg,
  std::ostream & out)
{
  out << "{";
  // member: spline
  {
    out << "spline: ";
    to_flow_style_yaml(msg.spline, out);
    out << ", ";
  }

  // member: if_full_window
  {
    out << "if_full_window: ";
    to_flow_style_yaml(msg.if_full_window, out);
    out << ", ";
  }

  // member: runtime
  {
    out << "runtime: ";
    to_flow_style_yaml(msg.runtime, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Estimate & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: spline
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "spline:\n";
    to_block_style_yaml(msg.spline, out, indentation + 2);
  }

  // member: if_full_window
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "if_full_window:\n";
    to_block_style_yaml(msg.if_full_window, out, indentation + 2);
  }

  // member: runtime
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "runtime:\n";
    to_block_style_yaml(msg.runtime, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Estimate & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace sfuise_msgs

namespace rosidl_generator_traits
{

[[deprecated("use sfuise_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const sfuise_msgs::msg::Estimate & msg,
  std::ostream & out, size_t indentation = 0)
{
  sfuise_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sfuise_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sfuise_msgs::msg::Estimate & msg)
{
  return sfuise_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sfuise_msgs::msg::Estimate>()
{
  return "sfuise_msgs::msg::Estimate";
}

template<>
inline const char * name<sfuise_msgs::msg::Estimate>()
{
  return "sfuise_msgs/msg/Estimate";
}

template<>
struct has_fixed_size<sfuise_msgs::msg::Estimate>
  : std::integral_constant<bool, has_fixed_size<sfuise_msgs::msg::Spline>::value && has_fixed_size<std_msgs::msg::Bool>::value && has_fixed_size<std_msgs::msg::Float64>::value> {};

template<>
struct has_bounded_size<sfuise_msgs::msg::Estimate>
  : std::integral_constant<bool, has_bounded_size<sfuise_msgs::msg::Spline>::value && has_bounded_size<std_msgs::msg::Bool>::value && has_bounded_size<std_msgs::msg::Float64>::value> {};

template<>
struct is_message<sfuise_msgs::msg::Estimate>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SFUISE_MSGS__MSG__DETAIL__ESTIMATE__TRAITS_HPP_
