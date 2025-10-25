// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from isas_msgs:msg/RTLSRange.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__TRAITS_HPP_
#define ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "isas_msgs/msg/detail/rtls_range__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pos'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace isas_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RTLSRange & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: pos
  {
    out << "pos: ";
    to_flow_style_yaml(msg.pos, out);
    out << ", ";
  }

  // member: pr
  {
    out << "pr: ";
    rosidl_generator_traits::value_to_yaml(msg.pr, out);
    out << ", ";
  }

  // member: range
  {
    out << "range: ";
    rosidl_generator_traits::value_to_yaml(msg.range, out);
    out << ", ";
  }

  // member: mean
  {
    out << "mean: ";
    rosidl_generator_traits::value_to_yaml(msg.mean, out);
    out << ", ";
  }

  // member: var
  {
    out << "var: ";
    rosidl_generator_traits::value_to_yaml(msg.var, out);
    out << ", ";
  }

  // member: fpp
  {
    out << "fpp: ";
    rosidl_generator_traits::value_to_yaml(msg.fpp, out);
    out << ", ";
  }

  // member: rxp
  {
    out << "rxp: ";
    rosidl_generator_traits::value_to_yaml(msg.rxp, out);
    out << ", ";
  }

  // member: csn
  {
    out << "csn: ";
    rosidl_generator_traits::value_to_yaml(msg.csn, out);
    out << ", ";
  }

  // member: cmn
  {
    out << "cmn: ";
    rosidl_generator_traits::value_to_yaml(msg.cmn, out);
    out << ", ";
  }

  // member: toc
  {
    out << "toc: ";
    rosidl_generator_traits::value_to_yaml(msg.toc, out);
    out << ", ";
  }

  // member: ra
  {
    out << "ra: ";
    rosidl_generator_traits::value_to_yaml(msg.ra, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RTLSRange & msg,
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

  // member: pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pos:\n";
    to_block_style_yaml(msg.pos, out, indentation + 2);
  }

  // member: pr
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pr: ";
    rosidl_generator_traits::value_to_yaml(msg.pr, out);
    out << "\n";
  }

  // member: range
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "range: ";
    rosidl_generator_traits::value_to_yaml(msg.range, out);
    out << "\n";
  }

  // member: mean
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mean: ";
    rosidl_generator_traits::value_to_yaml(msg.mean, out);
    out << "\n";
  }

  // member: var
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "var: ";
    rosidl_generator_traits::value_to_yaml(msg.var, out);
    out << "\n";
  }

  // member: fpp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fpp: ";
    rosidl_generator_traits::value_to_yaml(msg.fpp, out);
    out << "\n";
  }

  // member: rxp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rxp: ";
    rosidl_generator_traits::value_to_yaml(msg.rxp, out);
    out << "\n";
  }

  // member: csn
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "csn: ";
    rosidl_generator_traits::value_to_yaml(msg.csn, out);
    out << "\n";
  }

  // member: cmn
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cmn: ";
    rosidl_generator_traits::value_to_yaml(msg.cmn, out);
    out << "\n";
  }

  // member: toc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "toc: ";
    rosidl_generator_traits::value_to_yaml(msg.toc, out);
    out << "\n";
  }

  // member: ra
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ra: ";
    rosidl_generator_traits::value_to_yaml(msg.ra, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RTLSRange & msg, bool use_flow_style = false)
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
  const isas_msgs::msg::RTLSRange & msg,
  std::ostream & out, size_t indentation = 0)
{
  isas_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use isas_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const isas_msgs::msg::RTLSRange & msg)
{
  return isas_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<isas_msgs::msg::RTLSRange>()
{
  return "isas_msgs::msg::RTLSRange";
}

template<>
inline const char * name<isas_msgs::msg::RTLSRange>()
{
  return "isas_msgs/msg/RTLSRange";
}

template<>
struct has_fixed_size<isas_msgs::msg::RTLSRange>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value> {};

template<>
struct has_bounded_size<isas_msgs::msg::RTLSRange>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value> {};

template<>
struct is_message<isas_msgs::msg::RTLSRange>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__TRAITS_HPP_
