// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from sfuise_msgs:msg/Spline.idl
// generated code does not contain a copyright notice
#include "sfuise_msgs/msg/detail/spline__rosidl_typesupport_fastrtps_cpp.hpp"
#include "sfuise_msgs/msg/detail/spline__struct.hpp"

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
namespace sfuise_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const sfuise_msgs::msg::Knot &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  sfuise_msgs::msg::Knot &);
size_t get_serialized_size(
  const sfuise_msgs::msg::Knot &,
  size_t current_alignment);
size_t
max_serialized_size_Knot(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace sfuise_msgs

// functions for sfuise_msgs::msg::Knot already declared above


namespace sfuise_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
cdr_serialize(
  const sfuise_msgs::msg::Spline & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: start_idx
  cdr << ros_message.start_idx;
  // Member: dt
  cdr << ros_message.dt;
  // Member: start_t
  cdr << ros_message.start_t;
  // Member: knots
  {
    size_t size = ros_message.knots.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      sfuise_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.knots[i],
        cdr);
    }
  }
  // Member: idles
  {
    size_t size = ros_message.idles.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      sfuise_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.idles[i],
        cdr);
    }
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  sfuise_msgs::msg::Spline & ros_message)
{
  // Member: start_idx
  cdr >> ros_message.start_idx;

  // Member: dt
  cdr >> ros_message.dt;

  // Member: start_t
  cdr >> ros_message.start_t;

  // Member: knots
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.knots.resize(size);
    for (size_t i = 0; i < size; i++) {
      sfuise_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.knots[i]);
    }
  }

  // Member: idles
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    ros_message.idles.resize(size);
    for (size_t i = 0; i < size; i++) {
      sfuise_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.idles[i]);
    }
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
get_serialized_size(
  const sfuise_msgs::msg::Spline & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: start_idx
  {
    size_t item_size = sizeof(ros_message.start_idx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: dt
  {
    size_t item_size = sizeof(ros_message.dt);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: start_t
  {
    size_t item_size = sizeof(ros_message.start_t);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: knots
  {
    size_t array_size = ros_message.knots.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        sfuise_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.knots[index], current_alignment);
    }
  }
  // Member: idles
  {
    size_t array_size = ros_message.idles.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        sfuise_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.idles[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_sfuise_msgs
max_serialized_size_Spline(
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


  // Member: start_idx
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: dt
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: start_t
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: knots
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        sfuise_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Knot(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  // Member: idles
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);


    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        sfuise_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Knot(
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
    using DataType = sfuise_msgs::msg::Spline;
    is_plain =
      (
      offsetof(DataType, idles) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _Spline__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const sfuise_msgs::msg::Spline *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _Spline__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<sfuise_msgs::msg::Spline *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _Spline__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const sfuise_msgs::msg::Spline *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _Spline__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_Spline(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _Spline__callbacks = {
  "sfuise_msgs::msg",
  "Spline",
  _Spline__cdr_serialize,
  _Spline__cdr_deserialize,
  _Spline__get_serialized_size,
  _Spline__max_serialized_size
};

static rosidl_message_type_support_t _Spline__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_Spline__callbacks,
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
get_message_type_support_handle<sfuise_msgs::msg::Spline>()
{
  return &sfuise_msgs::msg::typesupport_fastrtps_cpp::_Spline__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, sfuise_msgs, msg, Spline)() {
  return &sfuise_msgs::msg::typesupport_fastrtps_cpp::_Spline__handle;
}

#ifdef __cplusplus
}
#endif
