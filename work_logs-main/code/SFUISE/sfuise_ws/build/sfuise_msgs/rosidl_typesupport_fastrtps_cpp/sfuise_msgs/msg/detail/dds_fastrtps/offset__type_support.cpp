// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from sfuise_msgs:msg/Offset.idl
// generated code does not contain a copyright notice
#include "sfuise_msgs/msg/detail/offset__rosidl_typesupport_fastrtps_cpp.hpp"
#include "sfuise_msgs/msg/detail/offset__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace geometry_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const geometry_msgs::msg::Point &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  geometry_msgs::msg::Point &);
size_t get_serialized_size(
  const geometry_msgs::msg::Point &,
  size_t current_alignment);
size_t
max_serialized_size_Point(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace geometry_msgs


namespace sfuise_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
cdr_serialize(
  const sfuise_msgs::msg::Offset & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: id_tag
  cdr << ros_message.id_tag;
  // Member: id_antenna
  cdr << ros_message.id_antenna;
  // Member: t_tag_body
  geometry_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.t_tag_body,
    cdr);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  sfuise_msgs::msg::Offset & ros_message)
{
  // Member: id_tag
  cdr >> ros_message.id_tag;

  // Member: id_antenna
  cdr >> ros_message.id_antenna;

  // Member: t_tag_body
  geometry_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.t_tag_body);

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
get_serialized_size(
  const sfuise_msgs::msg::Offset & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: id_tag
  {
    size_t item_size = sizeof(ros_message.id_tag);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: id_antenna
  {
    size_t item_size = sizeof(ros_message.id_antenna);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: t_tag_body

  current_alignment +=
    geometry_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.t_tag_body, current_alignment);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
max_serialized_size_Offset(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: id_tag
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: id_antenna
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: t_tag_body
  {
    size_t array_size = 1;


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        geometry_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Point(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = sfuise_msgs::msg::Offset;
    is_plain =
      (
      offsetof(DataType, t_tag_body) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _Offset__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const sfuise_msgs::msg::Offset *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _Offset__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<sfuise_msgs::msg::Offset *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _Offset__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const sfuise_msgs::msg::Offset *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _Offset__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_Offset(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _Offset__callbacks = {
  "sfuise_msgs::msg",
  "Offset",
  _Offset__cdr_serialize,
  _Offset__cdr_deserialize,
  _Offset__get_serialized_size,
  _Offset__max_serialized_size
};

static rosidl_message_type_support_t _Offset__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_Offset__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace sfuise_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_sfuise_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<sfuise_msgs::msg::Offset>()
{
  return &sfuise_msgs::msg::typesupport_fastrtps_cpp::_Offset__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, sfuise_msgs, msg, Offset)() {
  return &sfuise_msgs::msg::typesupport_fastrtps_cpp::_Offset__handle;
}

#ifdef __cplusplus
}
#endif
