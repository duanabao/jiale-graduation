// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from sfuise_msgs:msg/Calib.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "sfuise_msgs/msg/detail/calib__rosidl_typesupport_introspection_c.h"
#include "sfuise_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "sfuise_msgs/msg/detail/calib__functions.h"
#include "sfuise_msgs/msg/detail/calib__struct.h"


// Include directives for member types
// Member `gravity`
// Member `t_nav_uwb`
// Member `t_tag_body_set`
#include "geometry_msgs/msg/point.h"
// Member `gravity`
// Member `t_nav_uwb`
// Member `t_tag_body_set`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"
// Member `q_nav_uwb`
#include "geometry_msgs/msg/quaternion.h"
// Member `q_nav_uwb`
#include "geometry_msgs/msg/detail/quaternion__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  sfuise_msgs__msg__Calib__init(message_memory);
}

void sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_fini_function(void * message_memory)
{
  sfuise_msgs__msg__Calib__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_member_array[4] = {
  {
    "gravity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sfuise_msgs__msg__Calib, gravity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "t_nav_uwb",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sfuise_msgs__msg__Calib, t_nav_uwb),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "q_nav_uwb",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sfuise_msgs__msg__Calib, q_nav_uwb),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "t_tag_body_set",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sfuise_msgs__msg__Calib, t_tag_body_set),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_members = {
  "sfuise_msgs__msg",  // message namespace
  "Calib",  // message name
  4,  // number of fields
  sizeof(sfuise_msgs__msg__Calib),
  sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_member_array,  // message members
  sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_init_function,  // function to initialize message memory (memory has to be allocated)
  sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_type_support_handle = {
  0,
  &sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_sfuise_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sfuise_msgs, msg, Calib)() {
  sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Quaternion)();
  sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_type_support_handle.typesupport_identifier) {
    sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &sfuise_msgs__msg__Calib__rosidl_typesupport_introspection_c__Calib_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
