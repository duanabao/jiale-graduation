// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sfuise_msgs:msg/Offset.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__OFFSET__TRAITS_HPP_
#define SFUISE_MSGS__MSG__DETAIL__OFFSET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sfuise_msgs/msg/detail/offset__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 't_tag_body'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace sfuise_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Offset & msg,
  std::ostream & out)
{
  out << "{";
  // member: id_tag
  {
    out << "id_tag: ";
    rosidl_generator_traits::value_to_yaml(msg.id_tag, out);
    out << ", ";
  }

  // member: id_antenna
  {
    out << "id_antenna: ";
    rosidl_generator_traits::value_to_yaml(msg.id_antenna, out);
    out << ", ";
  }

  // member: t_tag_body
  {
    out << "t_tag_body: ";
    to_flow_style_yaml(msg.t_tag_body, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Offset & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id_tag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id_tag: ";
    rosidl_generator_traits::value_to_yaml(msg.id_tag, out);
    out << "\n";
  }

  // member: id_antenna
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id_antenna: ";
    rosidl_generator_traits::value_to_yaml(msg.id_antenna, out);
    out << "\n";
  }

  // member: t_tag_body
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "t_tag_body:\n";
    to_block_style_yaml(msg.t_tag_body, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Offset & msg, bool use_flow_style = false)
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
  const sfuise_msgs::msg::Offset & msg,
  std::ostream & out, size_t indentation = 0)
{
  sfuise_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sfuise_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sfuise_msgs::msg::Offset & msg)
{
  return sfuise_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sfuise_msgs::msg::Offset>()
{
  return "sfuise_msgs::msg::Offset";
}

template<>
inline const char * name<sfuise_msgs::msg::Offset>()
{
  return "sfuise_msgs/msg/Offset";
}

template<>
struct has_fixed_size<sfuise_msgs::msg::Offset>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value> {};

template<>
struct has_bounded_size<sfuise_msgs::msg::Offset>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value> {};

template<>
struct is_message<sfuise_msgs::msg::Offset>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SFUISE_MSGS__MSG__DETAIL__OFFSET__TRAITS_HPP_
