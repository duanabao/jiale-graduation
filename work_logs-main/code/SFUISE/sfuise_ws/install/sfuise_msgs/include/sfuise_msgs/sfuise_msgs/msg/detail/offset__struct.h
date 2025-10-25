// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sfuise_msgs:msg/Offset.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__OFFSET__STRUCT_H_
#define SFUISE_MSGS__MSG__DETAIL__OFFSET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 't_tag_body'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/Offset in the package sfuise_msgs.
typedef struct sfuise_msgs__msg__Offset
{
  int8_t id_tag;
  int8_t id_antenna;
  geometry_msgs__msg__Point t_tag_body;
} sfuise_msgs__msg__Offset;

// Struct for a sequence of sfuise_msgs__msg__Offset.
typedef struct sfuise_msgs__msg__Offset__Sequence
{
  sfuise_msgs__msg__Offset * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sfuise_msgs__msg__Offset__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SFUISE_MSGS__MSG__DETAIL__OFFSET__STRUCT_H_
