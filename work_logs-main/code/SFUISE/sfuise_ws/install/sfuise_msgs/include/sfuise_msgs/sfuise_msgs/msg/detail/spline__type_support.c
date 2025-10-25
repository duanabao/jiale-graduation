// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from sfuise_msgs:msg/Spline.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "sfuise_msgs/msg/detail/spline__rosidl_typesupport_introspection_c.h"
#include "sfuise_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "sfuise_msgs/msg/detail/spline__functions.h"
#include "sfuise_msgs/msg/detail/spline__struct.h"


// Include directives for member types
// Member `knots`
// Member `idles`
#include "sfuise_msgs/msg/knot.h"
// Member `knots`
// Member `idles`
#include "sfuise_msgs/msg/detail/knot__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sfuise_msgs__msg__Spline__init(message_memory);
}

void sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_fini_function(void * message_memory)
{
  sfuise_msgs__msg__Spline__fini(message_memory);
}

size_t sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__size_function__Spline__knots(
  const void * untyped_member)
{
  const sfuise_msgs__msg__Knot__Sequence * member =
    (const sfuise_msgs__msg__Knot__Sequence *)(untyped_member);
  return member->size;
}

const void * sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_const_function__Spline__knots(
  const void * untyped_member, size_t index)
{
  const sfuise_msgs__msg__Knot__Sequence * member =
    (const sfuise_msgs__msg__Knot__Sequence *)(untyped_member);
  return &member->data[index];
}

void * sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_function__Spline__knots(
  void * untyped_member, size_t index)
{
  sfuise_msgs__msg__Knot__Sequence * member =
    (sfuise_msgs__msg__Knot__Sequence *)(untyped_member);
  return &member->data[index];
}

void sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__fetch_function__Spline__knots(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const sfuise_msgs__msg__Knot * item =
    ((const sfuise_msgs__msg__Knot *)
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_const_function__Spline__knots(untyped_member, index));
  sfuise_msgs__msg__Knot * value =
    (sfuise_msgs__msg__Knot *)(untyped_value);
  *value = *item;
}

void sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__assign_function__Spline__knots(
  void * untyped_member, size_t index, const void * untyped_value)
{
  sfuise_msgs__msg__Knot * item =
    ((sfuise_msgs__msg__Knot *)
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_function__Spline__knots(untyped_member, index));
  const sfuise_msgs__msg__Knot * value =
    (const sfuise_msgs__msg__Knot *)(untyped_value);
  *item = *value;
}

bool sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__resize_function__Spline__knots(
  void * untyped_member, size_t size)
{
  sfuise_msgs__msg__Knot__Sequence * member =
    (sfuise_msgs__msg__Knot__Sequence *)(untyped_member);
  sfuise_msgs__msg__Knot__Sequence__fini(member);
  return sfuise_msgs__msg__Knot__Sequence__init(member, size);
}

size_t sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__size_function__Spline__idles(
  const void * untyped_member)
{
  const sfuise_msgs__msg__Knot__Sequence * member =
    (const sfuise_msgs__msg__Knot__Sequence *)(untyped_member);
  return member->size;
}

const void * sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_const_function__Spline__idles(
  const void * untyped_member, size_t index)
{
  const sfuise_msgs__msg__Knot__Sequence * member =
    (const sfuise_msgs__msg__Knot__Sequence *)(untyped_member);
  return &member->data[index];
}

void * sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_function__Spline__idles(
  void * untyped_member, size_t index)
{
  sfuise_msgs__msg__Knot__Sequence * member =
    (sfuise_msgs__msg__Knot__Sequence *)(untyped_member);
  return &member->data[index];
}

void sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__fetch_function__Spline__idles(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const sfuise_msgs__msg__Knot * item =
    ((const sfuise_msgs__msg__Knot *)
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_const_function__Spline__idles(untyped_member, index));
  sfuise_msgs__msg__Knot * value =
    (sfuise_msgs__msg__Knot *)(untyped_value);
  *value = *item;
}

void sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__assign_function__Spline__idles(
  void * untyped_member, size_t index, const void * untyped_value)
{
  sfuise_msgs__msg__Knot * item =
    ((sfuise_msgs__msg__Knot *)
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_function__Spline__idles(untyped_member, index));
  const sfuise_msgs__msg__Knot * value =
    (const sfuise_msgs__msg__Knot *)(untyped_value);
  *item = *value;
}

bool sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__resize_function__Spline__idles(
  void * untyped_member, size_t size)
{
  sfuise_msgs__msg__Knot__Sequence * member =
    (sfuise_msgs__msg__Knot__Sequence *)(untyped_member);
  sfuise_msgs__msg__Knot__Sequence__fini(member);
  return sfuise_msgs__msg__Knot__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_message_member_array[5] = {
  {
    "start_idx",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sfuise_msgs__msg__Spline, start_idx),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "dt",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sfuise_msgs__msg__Spline, dt),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "start_t",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sfuise_msgs__msg__Spline, start_t),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "knots",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sfuise_msgs__msg__Spline, knots),  // bytes offset in struct
    NULL,  // default value
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__size_function__Spline__knots,  // size() function pointer
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_const_function__Spline__knots,  // get_const(index) function pointer
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_function__Spline__knots,  // get(index) function pointer
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__fetch_function__Spline__knots,  // fetch(index, &value) function pointer
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__assign_function__Spline__knots,  // assign(index, value) function pointer
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__resize_function__Spline__knots  // resize(index) function pointer
  },
  {
    "idles",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sfuise_msgs__msg__Spline, idles),  // bytes offset in struct
    NULL,  // default value
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__size_function__Spline__idles,  // size() function pointer
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_const_function__Spline__idles,  // get_const(index) function pointer
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__get_function__Spline__idles,  // get(index) function pointer
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__fetch_function__Spline__idles,  // fetch(index, &value) function pointer
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__assign_function__Spline__idles,  // assign(index, value) function pointer
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__resize_function__Spline__idles  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_message_members = {
  "sfuise_msgs__msg",  // message namespace
  "Spline",  // message name
  5,  // number of fields
  sizeof(sfuise_msgs__msg__Spline),
  sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_message_member_array,  // message members
  sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_init_function,  // function to initialize message memory (memory has to be allocated)
  sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_message_type_support_handle = {
  0,
  &sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sfuise_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sfuise_msgs, msg, Spline)() {
  sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sfuise_msgs, msg, Knot)();
  sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sfuise_msgs, msg, Knot)();
  if (!sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_message_type_support_handle.typesupport_identifier) {
    sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sfuise_msgs__msg__Spline__rosidl_typesupport_introspection_c__Spline_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
