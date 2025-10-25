// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sfuise_msgs:msg/Knot.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__KNOT__STRUCT_H_
#define SFUISE_MSGS__MSG__DETAIL__KNOT__STRUCT_H_

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
// Member 'bias_acc'
// Member 'bias_gyro'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'orientation'
#include "geometry_msgs/msg/detail/quaternion__struct.h"

/// Struct defined in msg/Knot in the package sfuise_msgs.
typedef struct sfuise_msgs__msg__Knot
{
  geometry_msgs__msg__Point position;
  geometry_msgs__msg__Quaternion orientation;
  geometry_msgs__msg__Point bias_acc;
  geometry_msgs__msg__Point bias_gyro;
} sfuise_msgs__msg__Knot;

// Struct for a sequence of sfuise_msgs__msg__Knot.
typedef struct sfuise_msgs__msg__Knot__Sequence
{
  sfuise_msgs__msg__Knot * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sfuise_msgs__msg__Knot__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SFUISE_MSGS__MSG__DETAIL__KNOT__STRUCT_H_
