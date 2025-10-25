// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from isas_msgs:msg/Anchorlist.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "isas_msgs/msg/detail/anchorlist__rosidl_typesupport_introspection_c.h"
#include "isas_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "isas_msgs/msg/detail/anchorlist__functions.h"
#include "isas_msgs/msg/detail/anchorlist__struct.h"


// Include directives for member types
// Member `anchor`
#include "isas_msgs/msg/anchor_position.h"
// Member `anchor`
#include "isas_msgs/msg/detail/anchor_position__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  isas_msgs__msg__Anchorlist__init(message_memory);
}

void isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_fini_function(void * message_memory)
{
  isas_msgs__msg__Anchorlist__fini(message_memory);
}

size_t isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__size_function__Anchorlist__anchor(
  const void * untyped_member)
{
  const isas_msgs__msg__AnchorPosition__Sequence * member =
    (const isas_msgs__msg__AnchorPosition__Sequence *)(untyped_member);
  return member->size;
}

const void * isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__get_const_function__Anchorlist__anchor(
  const void * untyped_member, size_t index)
{
  const isas_msgs__msg__AnchorPosition__Sequence * member =
    (const isas_msgs__msg__AnchorPosition__Sequence *)(untyped_member);
  return &member->data[index];
}

void * isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__get_function__Anchorlist__anchor(
  void * untyped_member, size_t index)
{
  isas_msgs__msg__AnchorPosition__Sequence * member =
    (isas_msgs__msg__AnchorPosition__Sequence *)(untyped_member);
  return &member->data[index];
}

void isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__fetch_function__Anchorlist__anchor(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const isas_msgs__msg__AnchorPosition * item =
    ((const isas_msgs__msg__AnchorPosition *)
    isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__get_const_function__Anchorlist__anchor(untyped_member, index));
  isas_msgs__msg__AnchorPosition * value =
    (isas_msgs__msg__AnchorPosition *)(untyped_value);
  *value = *item;
}

void isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__assign_function__Anchorlist__anchor(
  void * untyped_member, size_t index, const void * untyped_value)
{
  isas_msgs__msg__AnchorPosition * item =
    ((isas_msgs__msg__AnchorPosition *)
    isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__get_function__Anchorlist__anchor(untyped_member, index));
  const isas_msgs__msg__AnchorPosition * value =
    (const isas_msgs__msg__AnchorPosition *)(untyped_value);
  *item = *value;
}

bool isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__resize_function__Anchorlist__anchor(
  void * untyped_member, size_t size)
{
  isas_msgs__msg__AnchorPosition__Sequence * member =
    (isas_msgs__msg__AnchorPosition__Sequence *)(untyped_member);
  isas_msgs__msg__AnchorPosition__Sequence__fini(member);
  return isas_msgs__msg__AnchorPosition__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_message_member_array[1] = {
  {
    "anchor",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__Anchorlist, anchor),  // bytes offset in struct
    NULL,  // default value
    isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__size_function__Anchorlist__anchor,  // size() function pointer
    isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__get_const_function__Anchorlist__anchor,  // get_const(index) function pointer
    isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__get_function__Anchorlist__anchor,  // get(index) function pointer
    isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__fetch_function__Anchorlist__anchor,  // fetch(index, &value) function pointer
    isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__assign_function__Anchorlist__anchor,  // assign(index, value) function pointer
    isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__resize_function__Anchorlist__anchor  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_message_members = {
  "isas_msgs__msg",  // message namespace
  "Anchorlist",  // message name
  1,  // number of fields
  sizeof(isas_msgs__msg__Anchorlist),
  isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_message_member_array,  // message members
  isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_init_function,  // function to initialize message memory (memory has to be allocated)
  isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_message_type_support_handle = {
  0,
  &isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_isas_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, isas_msgs, msg, Anchorlist)() {
  isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, isas_msgs, msg, AnchorPosition)();
  if (!isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_message_type_support_handle.typesupport_identifier) {
    isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &isas_msgs__msg__Anchorlist__rosidl_typesupport_introspection_c__Anchorlist_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
