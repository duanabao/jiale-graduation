// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from isas_msgs:msg/RTLSStick.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "isas_msgs/msg/detail/rtls_stick__rosidl_typesupport_introspection_c.h"
#include "isas_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "isas_msgs/msg/detail/rtls_stick__functions.h"
#include "isas_msgs/msg/detail/rtls_stick__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `pos`
// Member `mean`
#include "geometry_msgs/msg/point.h"
// Member `pos`
// Member `mean`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"
// Member `hrp`
#include "geometry_msgs/msg/vector3.h"
// Member `hrp`
#include "geometry_msgs/msg/detail/vector3__rosidl_typesupport_introspection_c.h"
// Member `ranges`
#include "isas_msgs/msg/rtls_range.h"
// Member `ranges`
#include "isas_msgs/msg/detail/rtls_range__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  isas_msgs__msg__RTLSStick__init(message_memory);
}

void isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_fini_function(void * message_memory)
{
  isas_msgs__msg__RTLSStick__fini(message_memory);
}

size_t isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__size_function__RTLSStick__ranges(
  const void * untyped_member)
{
  const isas_msgs__msg__RTLSRange__Sequence * member =
    (const isas_msgs__msg__RTLSRange__Sequence *)(untyped_member);
  return member->size;
}

const void * isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__get_const_function__RTLSStick__ranges(
  const void * untyped_member, size_t index)
{
  const isas_msgs__msg__RTLSRange__Sequence * member =
    (const isas_msgs__msg__RTLSRange__Sequence *)(untyped_member);
  return &member->data[index];
}

void * isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__get_function__RTLSStick__ranges(
  void * untyped_member, size_t index)
{
  isas_msgs__msg__RTLSRange__Sequence * member =
    (isas_msgs__msg__RTLSRange__Sequence *)(untyped_member);
  return &member->data[index];
}

void isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__fetch_function__RTLSStick__ranges(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const isas_msgs__msg__RTLSRange * item =
    ((const isas_msgs__msg__RTLSRange *)
    isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__get_const_function__RTLSStick__ranges(untyped_member, index));
  isas_msgs__msg__RTLSRange * value =
    (isas_msgs__msg__RTLSRange *)(untyped_value);
  *value = *item;
}

void isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__assign_function__RTLSStick__ranges(
  void * untyped_member, size_t index, const void * untyped_value)
{
  isas_msgs__msg__RTLSRange * item =
    ((isas_msgs__msg__RTLSRange *)
    isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__get_function__RTLSStick__ranges(untyped_member, index));
  const isas_msgs__msg__RTLSRange * value =
    (const isas_msgs__msg__RTLSRange *)(untyped_value);
  *item = *value;
}

bool isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__resize_function__RTLSStick__ranges(
  void * untyped_member, size_t size)
{
  isas_msgs__msg__RTLSRange__Sequence * member =
    (isas_msgs__msg__RTLSRange__Sequence *)(untyped_member);
  isas_msgs__msg__RTLSRange__Sequence__fini(member);
  return isas_msgs__msg__RTLSRange__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_member_array[9] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__RTLSStick, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__RTLSStick, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "t",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__RTLSStick, t),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pos",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__RTLSStick, pos),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mean",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__RTLSStick, mean),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "hrp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__RTLSStick, hrp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "noga",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__RTLSStick, noga),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "nora",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__RTLSStick, nora),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ranges",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__RTLSStick, ranges),  // bytes offset in struct
    NULL,  // default value
    isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__size_function__RTLSStick__ranges,  // size() function pointer
    isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__get_const_function__RTLSStick__ranges,  // get_const(index) function pointer
    isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__get_function__RTLSStick__ranges,  // get(index) function pointer
    isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__fetch_function__RTLSStick__ranges,  // fetch(index, &value) function pointer
    isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__assign_function__RTLSStick__ranges,  // assign(index, value) function pointer
    isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__resize_function__RTLSStick__ranges  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_members = {
  "isas_msgs__msg",  // message namespace
  "RTLSStick",  // message name
  9,  // number of fields
  sizeof(isas_msgs__msg__RTLSStick),
  isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_member_array,  // message members
  isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_init_function,  // function to initialize message memory (memory has to be allocated)
  isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_type_support_handle = {
  0,
  &isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_isas_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, isas_msgs, msg, RTLSStick)() {
  isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Vector3)();
  isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_member_array[8].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, isas_msgs, msg, RTLSRange)();
  if (!isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_type_support_handle.typesupport_identifier) {
    isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &isas_msgs__msg__RTLSStick__rosidl_typesupport_introspection_c__RTLSStick_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
