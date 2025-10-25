// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sfuise_msgs:msg/Calib.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__CALIB__TRAITS_HPP_
#define SFUISE_MSGS__MSG__DETAIL__CALIB__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sfuise_msgs/msg/detail/calib__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'gravity'
// Member 't_nav_uwb'
// Member 't_tag_body_set'
#include "geometry_msgs/msg/detail/point__traits.hpp"
// Member 'q_nav_uwb'
#include "geometry_msgs/msg/detail/quaternion__traits.hpp"

namespace sfuise_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Calib & msg,
  std::ostream & out)
{
  out << "{";
  // member: gravity
  {
    out << "gravity: ";
    to_flow_style_yaml(msg.gravity, out);
    out << ", ";
  }

  // member: t_nav_uwb
  {
    out << "t_nav_uwb: ";
    to_flow_style_yaml(msg.t_nav_uwb, out);
    out << ", ";
  }

  // member: q_nav_uwb
  {
    out << "q_nav_uwb: ";
    to_flow_style_yaml(msg.q_nav_uwb, out);
    out << ", ";
  }

  // member: t_tag_body_set
  {
    out << "t_tag_body_set: ";
    to_flow_style_yaml(msg.t_tag_body_set, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Calib & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: gravity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gravity:\n";
    to_block_style_yaml(msg.gravity, out, indentation + 2);
  }

  // member: t_nav_uwb
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "t_nav_uwb:\n";
    to_block_style_yaml(msg.t_nav_uwb, out, indentation + 2);
  }

  // member: q_nav_uwb
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "q_nav_uwb:\n";
    to_block_style_yaml(msg.q_nav_uwb, out, indentation + 2);
  }

  // member: t_tag_body_set
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "t_tag_body_set:\n";
    to_block_style_yaml(msg.t_tag_body_set, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Calib & msg, bool use_flow_style = false)
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
  const sfuise_msgs::msg::Calib & msg,
  std::ostream & out, size_t indentation = 0)
{
  sfuise_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sfuise_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sfuise_msgs::msg::Calib & msg)
{
  return sfuise_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sfuise_msgs::msg::Calib>()
{
  return "sfuise_msgs::msg::Calib";
}

template<>
inline const char * name<sfuise_msgs::msg::Calib>()
{
  return "sfuise_msgs/msg/Calib";
}

template<>
struct has_fixed_size<sfuise_msgs::msg::Calib>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value && has_fixed_size<geometry_msgs::msg::Quaternion>::value> {};

template<>
struct has_bounded_size<sfuise_msgs::msg::Calib>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value && has_bounded_size<geometry_msgs::msg::Quaternion>::value> {};

template<>
struct is_message<sfuise_msgs::msg::Calib>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SFUISE_MSGS__MSG__DETAIL__CALIB__TRAITS_HPP_
