// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from isas_msgs:msg/AnchorPosition.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__TRAITS_HPP_
#define ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "isas_msgs/msg/detail/anchor_position__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace isas_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AnchorPosition & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AnchorPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AnchorPosition & msg, bool use_flow_style = false)
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

}  // namespace isas_msgs

namespace rosidl_generator_traits
{

[[deprecated("use isas_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const isas_msgs::msg::AnchorPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  isas_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use isas_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const isas_msgs::msg::AnchorPosition & msg)
{
  return isas_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<isas_msgs::msg::AnchorPosition>()
{
  return "isas_msgs::msg::AnchorPosition";
}

template<>
inline const char * name<isas_msgs::msg::AnchorPosition>()
{
  return "isas_msgs/msg/AnchorPosition";
}

template<>
struct has_fixed_size<isas_msgs::msg::AnchorPosition>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value> {};

template<>
struct has_bounded_size<isas_msgs::msg::AnchorPosition>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value> {};

template<>
struct is_message<isas_msgs::msg::AnchorPosition>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__TRAITS_HPP_
