// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from isas_msgs:msg/Anchorlist.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__ANCHORLIST__TRAITS_HPP_
#define ISAS_MSGS__MSG__DETAIL__ANCHORLIST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "isas_msgs/msg/detail/anchorlist__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'anchor'
#include "isas_msgs/msg/detail/anchor_position__traits.hpp"

namespace isas_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Anchorlist & msg,
  std::ostream & out)
{
  out << "{";
  // member: anchor
  {
    if (msg.anchor.size() == 0) {
      out << "anchor: []";
    } else {
      out << "anchor: [";
      size_t pending_items = msg.anchor.size();
      for (auto item : msg.anchor) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Anchorlist & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: anchor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.anchor.size() == 0) {
      out << "anchor: []\n";
    } else {
      out << "anchor:\n";
      for (auto item : msg.anchor) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Anchorlist & msg, bool use_flow_style = false)
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
  const isas_msgs::msg::Anchorlist & msg,
  std::ostream & out, size_t indentation = 0)
{
  isas_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use isas_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const isas_msgs::msg::Anchorlist & msg)
{
  return isas_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<isas_msgs::msg::Anchorlist>()
{
  return "isas_msgs::msg::Anchorlist";
}

template<>
inline const char * name<isas_msgs::msg::Anchorlist>()
{
  return "isas_msgs/msg/Anchorlist";
}

template<>
struct has_fixed_size<isas_msgs::msg::Anchorlist>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<isas_msgs::msg::Anchorlist>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<isas_msgs::msg::Anchorlist>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ISAS_MSGS__MSG__DETAIL__ANCHORLIST__TRAITS_HPP_
