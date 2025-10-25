// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sfuise_msgs:msg/Knot.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__KNOT__TRAITS_HPP_
#define SFUISE_MSGS__MSG__DETAIL__KNOT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sfuise_msgs/msg/detail/knot__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'position'
// Member 'bias_acc'
// Member 'bias_gyro'
#include "geometry_msgs/msg/detail/point__traits.hpp"
// Member 'orientation'
#include "geometry_msgs/msg/detail/quaternion__traits.hpp"

namespace sfuise_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Knot & msg,
  std::ostream & out)
{
  out << "{";
  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
    out << ", ";
  }

  // member: orientation
  {
    out << "orientation: ";
    to_flow_style_yaml(msg.orientation, out);
    out << ", ";
  }

  // member: bias_acc
  {
    out << "bias_acc: ";
    to_flow_style_yaml(msg.bias_acc, out);
    out << ", ";
  }

  // member: bias_gyro
  {
    out << "bias_gyro: ";
    to_flow_style_yaml(msg.bias_gyro, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Knot & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }

  // member: orientation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "orientation:\n";
    to_block_style_yaml(msg.orientation, out, indentation + 2);
  }

  // member: bias_acc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bias_acc:\n";
    to_block_style_yaml(msg.bias_acc, out, indentation + 2);
  }

  // member: bias_gyro
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "bias_gyro:\n";
    to_block_style_yaml(msg.bias_gyro, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Knot & msg, bool use_flow_style = false)
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
  const sfuise_msgs::msg::Knot & msg,
  std::ostream & out, size_t indentation = 0)
{
  sfuise_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sfuise_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sfuise_msgs::msg::Knot & msg)
{
  return sfuise_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sfuise_msgs::msg::Knot>()
{
  return "sfuise_msgs::msg::Knot";
}

template<>
inline const char * name<sfuise_msgs::msg::Knot>()
{
  return "sfuise_msgs/msg/Knot";
}

template<>
struct has_fixed_size<sfuise_msgs::msg::Knot>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value && has_fixed_size<geometry_msgs::msg::Quaternion>::value> {};

template<>
struct has_bounded_size<sfuise_msgs::msg::Knot>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value && has_bounded_size<geometry_msgs::msg::Quaternion>::value> {};

template<>
struct is_message<sfuise_msgs::msg::Knot>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SFUISE_MSGS__MSG__DETAIL__KNOT__TRAITS_HPP_
