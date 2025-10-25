// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from isas_msgs:msg/RTLSStick.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__RTLS_STICK__TRAITS_HPP_
#define ISAS_MSGS__MSG__DETAIL__RTLS_STICK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "isas_msgs/msg/detail/rtls_stick__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'pos'
// Member 'mean'
#include "geometry_msgs/msg/detail/point__traits.hpp"
// Member 'hrp'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"
// Member 'ranges'
#include "isas_msgs/msg/detail/rtls_range__traits.hpp"

namespace isas_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RTLSStick & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << ", ";
  }

  // member: t
  {
    out << "t: ";
    rosidl_generator_traits::value_to_yaml(msg.t, out);
    out << ", ";
  }

  // member: pos
  {
    out << "pos: ";
    to_flow_style_yaml(msg.pos, out);
    out << ", ";
  }

  // member: mean
  {
    out << "mean: ";
    to_flow_style_yaml(msg.mean, out);
    out << ", ";
  }

  // member: hrp
  {
    out << "hrp: ";
    to_flow_style_yaml(msg.hrp, out);
    out << ", ";
  }

  // member: noga
  {
    out << "noga: ";
    rosidl_generator_traits::value_to_yaml(msg.noga, out);
    out << ", ";
  }

  // member: nora
  {
    out << "nora: ";
    rosidl_generator_traits::value_to_yaml(msg.nora, out);
    out << ", ";
  }

  // member: ranges
  {
    if (msg.ranges.size() == 0) {
      out << "ranges: []";
    } else {
      out << "ranges: [";
      size_t pending_items = msg.ranges.size();
      for (auto item : msg.ranges) {
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
  const RTLSStick & msg,
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

  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }

  // member: t
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "t: ";
    rosidl_generator_traits::value_to_yaml(msg.t, out);
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

  // member: mean
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mean:\n";
    to_block_style_yaml(msg.mean, out, indentation + 2);
  }

  // member: hrp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hrp:\n";
    to_block_style_yaml(msg.hrp, out, indentation + 2);
  }

  // member: noga
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "noga: ";
    rosidl_generator_traits::value_to_yaml(msg.noga, out);
    out << "\n";
  }

  // member: nora
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "nora: ";
    rosidl_generator_traits::value_to_yaml(msg.nora, out);
    out << "\n";
  }

  // member: ranges
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.ranges.size() == 0) {
      out << "ranges: []\n";
    } else {
      out << "ranges:\n";
      for (auto item : msg.ranges) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RTLSStick & msg, bool use_flow_style = false)
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
  const isas_msgs::msg::RTLSStick & msg,
  std::ostream & out, size_t indentation = 0)
{
  isas_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use isas_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const isas_msgs::msg::RTLSStick & msg)
{
  return isas_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<isas_msgs::msg::RTLSStick>()
{
  return "isas_msgs::msg::RTLSStick";
}

template<>
inline const char * name<isas_msgs::msg::RTLSStick>()
{
  return "isas_msgs/msg/RTLSStick";
}

template<>
struct has_fixed_size<isas_msgs::msg::RTLSStick>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<isas_msgs::msg::RTLSStick>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<isas_msgs::msg::RTLSStick>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ISAS_MSGS__MSG__DETAIL__RTLS_STICK__TRAITS_HPP_
