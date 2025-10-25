// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cf_msgs:msg/Tof.idl
// generated code does not contain a copyright notice

#ifndef CF_MSGS__MSG__DETAIL__TOF__STRUCT_H_
#define CF_MSGS__MSG__DETAIL__TOF__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/Tof in the package cf_msgs.
typedef struct cf_msgs__msg__Tof
{
  std_msgs__msg__Header header;
  float zrange;
} cf_msgs__msg__Tof;

// Struct for a sequence of cf_msgs__msg__Tof.
typedef struct cf_msgs__msg__Tof__Sequence
{
  cf_msgs__msg__Tof * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cf_msgs__msg__Tof__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CF_MSGS__MSG__DETAIL__TOF__STRUCT_H_
