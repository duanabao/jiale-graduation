// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from sfuise_msgs:msg/Calib.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__CALIB__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define SFUISE_MSGS__MSG__DETAIL__CALIB__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "sfuise_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "sfuise_msgs/msg/detail/calib__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace sfuise_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
cdr_serialize(
  const sfuise_msgs::msg::Calib & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  sfuise_msgs::msg::Calib & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
get_serialized_size(
  const sfuise_msgs::msg::Calib & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
max_serialized_size_Calib(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace sfuise_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, sfuise_msgs, msg, Calib)();

#ifdef __cplusplus
}
#endif

#endif  // SFUISE_MSGS__MSG__DETAIL__CALIB__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
