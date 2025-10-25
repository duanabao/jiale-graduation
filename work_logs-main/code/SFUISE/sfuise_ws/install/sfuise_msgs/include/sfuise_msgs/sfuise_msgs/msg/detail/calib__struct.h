// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sfuise_msgs:msg/Calib.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__CALIB__STRUCT_H_
#define SFUISE_MSGS__MSG__DETAIL__CALIB__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'gravity'
// Member 't_nav_uwb'
// Member 't_tag_body_set'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'q_nav_uwb'
#include "geometry_msgs/msg/detail/quaternion__struct.h"

/// Struct defined in msg/Calib in the package sfuise_msgs.
typedef struct sfuise_msgs__msg__Calib
{
  geometry_msgs__msg__Point gravity;
  geometry_msgs__msg__Point t_nav_uwb;
  geometry_msgs__msg__Quaternion q_nav_uwb;
  geometry_msgs__msg__Point t_tag_body_set;
} sfuise_msgs__msg__Calib;

// Struct for a sequence of sfuise_msgs__msg__Calib.
typedef struct sfuise_msgs__msg__Calib__Sequence
{
  sfuise_msgs__msg__Calib * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sfuise_msgs__msg__Calib__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SFUISE_MSGS__MSG__DETAIL__CALIB__STRUCT_H_
