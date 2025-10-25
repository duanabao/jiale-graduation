// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sfuise_msgs:msg/Spline.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__SPLINE__TRAITS_HPP_
#define SFUISE_MSGS__MSG__DETAIL__SPLINE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sfuise_msgs/msg/detail/spline__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'knots'
// Member 'idles'
#include "sfuise_msgs/msg/detail/knot__traits.hpp"

namespace sfuise_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Spline & msg,
  std::ostream & out)
{
  out << "{";
  // member: start_idx
  {
    out << "start_idx: ";
    rosidl_generator_traits::value_to_yaml(msg.start_idx, out);
    out << ", ";
  }

  // member: dt
  {
    out << "dt: ";
    rosidl_generator_traits::value_to_yaml(msg.dt, out);
    out << ", ";
  }

  // member: start_t
  {
    out << "start_t: ";
    rosidl_generator_traits::value_to_yaml(msg.start_t, out);
    out << ", ";
  }

  // member: knots
  {
    if (msg.knots.size() == 0) {
      out << "knots: []";
    } else {
      out << "knots: [";
      size_t pending_items = msg.knots.size();
      for (auto item : msg.knots) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: idles
  {
    if (msg.idles.size() == 0) {
      out << "idles: []";
    } else {
      out << "idles: [";
      size_t pending_items = msg.idles.size();
      for (auto item : msg.idles) {
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
  const Spline & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: start_idx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start_idx: ";
    rosidl_generator_traits::value_to_yaml(msg.start_idx, out);
    out << "\n";
  }

  // member: dt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dt: ";
    rosidl_generator_traits::value_to_yaml(msg.dt, out);
    out << "\n";
  }

  // member: start_t
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start_t: ";
    rosidl_generator_traits::value_to_yaml(msg.start_t, out);
    out << "\n";
  }

  // member: knots
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.knots.size() == 0) {
      out << "knots: []\n";
    } else {
      out << "knots:\n";
      for (auto item : msg.knots) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: idles
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.idles.size() == 0) {
      out << "idles: []\n";
    } else {
      out << "idles:\n";
      for (auto item : msg.idles) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Spline & msg, bool use_flow_style = false)
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
  const sfuise_msgs::msg::Spline & msg,
  std::ostream & out, size_t indentation = 0)
{
  sfuise_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sfuise_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const sfuise_msgs::msg::Spline & msg)
{
  return sfuise_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sfuise_msgs::msg::Spline>()
{
  return "sfuise_msgs::msg::Spline";
}

template<>
inline const char * name<sfuise_msgs::msg::Spline>()
{
  return "sfuise_msgs/msg/Spline";
}

template<>
struct has_fixed_size<sfuise_msgs::msg::Spline>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sfuise_msgs::msg::Spline>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sfuise_msgs::msg::Spline>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SFUISE_MSGS__MSG__DETAIL__SPLINE__TRAITS_HPP_
