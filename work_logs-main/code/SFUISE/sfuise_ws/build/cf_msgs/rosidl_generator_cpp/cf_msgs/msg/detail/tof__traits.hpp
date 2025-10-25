// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cf_msgs:msg/Tof.idl
// generated code does not contain a copyright notice

#ifndef CF_MSGS__MSG__DETAIL__TOF__TRAITS_HPP_
#define CF_MSGS__MSG__DETAIL__TOF__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cf_msgs/msg/detail/tof__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace cf_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Tof & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: zrange
  {
    out << "zrange: ";
    rosidl_generator_traits::value_to_yaml(msg.zrange, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Tof & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: zrange
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zrange: ";
    rosidl_generator_traits::value_to_yaml(msg.zrange, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Tof & msg, bool use_flow_style = false)
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

}  // namespace cf_msgs

namespace rosidl_generator_traits
{

[[deprecated("use cf_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cf_msgs::msg::Tof & msg,
  std::ostream & out, size_t indentation = 0)
{
  cf_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cf_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const cf_msgs::msg::Tof & msg)
{
  return cf_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cf_msgs::msg::Tof>()
{
  return "cf_msgs::msg::Tof";
}

template<>
inline const char * name<cf_msgs::msg::Tof>()
{
  return "cf_msgs/msg/Tof";
}

template<>
struct has_fixed_size<cf_msgs::msg::Tof>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<cf_msgs::msg::Tof>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<cf_msgs::msg::Tof>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CF_MSGS__MSG__DETAIL__TOF__TRAITS_HPP_
