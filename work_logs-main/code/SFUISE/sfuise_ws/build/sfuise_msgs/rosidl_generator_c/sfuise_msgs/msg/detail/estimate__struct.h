// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sfuise_msgs:msg/Estimate.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__ESTIMATE__STRUCT_H_
#define SFUISE_MSGS__MSG__DETAIL__ESTIMATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'spline'
#include "sfuise_msgs/msg/detail/spline__struct.h"
// Member 'if_full_window'
#include "std_msgs/msg/detail/bool__struct.h"
// Member 'runtime'
#include "std_msgs/msg/detail/float64__struct.h"

/// Struct defined in msg/Estimate in the package sfuise_msgs.
typedef struct sfuise_msgs__msg__Estimate
{
  sfuise_msgs__msg__Spline spline;
  std_msgs__msg__Bool if_full_window;
  std_msgs__msg__Float64 runtime;
} sfuise_msgs__msg__Estimate;

// Struct for a sequence of sfuise_msgs__msg__Estimate.
typedef struct sfuise_msgs__msg__Estimate__Sequence
{
  sfuise_msgs__msg__Estimate * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sfuise_msgs__msg__Estimate__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SFUISE_MSGS__MSG__DETAIL__ESTIMATE__STRUCT_H_
