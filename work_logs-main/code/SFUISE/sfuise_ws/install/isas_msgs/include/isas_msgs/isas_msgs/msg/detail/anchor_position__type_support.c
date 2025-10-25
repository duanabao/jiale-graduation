// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from isas_msgs:msg/AnchorPosition.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "isas_msgs/msg/detail/anchor_position__rosidl_typesupport_introspection_c.h"
#include "isas_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "isas_msgs/msg/detail/anchor_position__functions.h"
#include "isas_msgs/msg/detail/anchor_position__struct.h"


// Include directives for member types
// Member `position`
#include "geometry_msgs/msg/point.h"
// Member `position`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  isas_msgs__msg__AnchorPosition__init(message_memory);
}

void isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_fini_function(void * message_memory)
{
  isas_msgs__msg__AnchorPosition__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_message_member_array[2] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__AnchorPosition, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(isas_msgs__msg__AnchorPosition, position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_message_members = {
  "isas_msgs__msg",  // message namespace
  "AnchorPosition",  // message name
  2,  // number of fields
  sizeof(isas_msgs__msg__AnchorPosition),
  isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_message_member_array,  // message members
  isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_init_function,  // function to initialize message memory (memory has to be allocated)
  isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_message_type_support_handle = {
  0,
  &isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_isas_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, isas_msgs, msg, AnchorPosition)() {
  isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_message_type_support_handle.typesupport_identifier) {
    isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &isas_msgs__msg__AnchorPosition__rosidl_typesupport_introspection_c__AnchorPosition_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
