// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sfuise_msgs:msg/Spline.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__SPLINE__STRUCT_H_
#define SFUISE_MSGS__MSG__DETAIL__SPLINE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'knots'
// Member 'idles'
#include "sfuise_msgs/msg/detail/knot__struct.h"

/// Struct defined in msg/Spline in the package sfuise_msgs.
typedef struct sfuise_msgs__msg__Spline
{
  uint64_t start_idx;
  int64_t dt;
  int64_t start_t;
  sfuise_msgs__msg__Knot__Sequence knots;
  sfuise_msgs__msg__Knot__Sequence idles;
} sfuise_msgs__msg__Spline;

// Struct for a sequence of sfuise_msgs__msg__Spline.
typedef struct sfuise_msgs__msg__Spline__Sequence
{
  sfuise_msgs__msg__Spline * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sfuise_msgs__msg__Spline__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SFUISE_MSGS__MSG__DETAIL__SPLINE__STRUCT_H_
