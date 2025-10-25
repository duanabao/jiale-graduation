// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from isas_msgs:msg/AnchorPosition.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__STRUCT_H_
#define ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/AnchorPosition in the package isas_msgs.
typedef struct isas_msgs__msg__AnchorPosition
{
  uint16_t id;
  geometry_msgs__msg__Point position;
} isas_msgs__msg__AnchorPosition;

// Struct for a sequence of isas_msgs__msg__AnchorPosition.
typedef struct isas_msgs__msg__AnchorPosition__Sequence
{
  isas_msgs__msg__AnchorPosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} isas_msgs__msg__AnchorPosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ISAS_MSGS__MSG__DETAIL__ANCHOR_POSITION__STRUCT_H_
