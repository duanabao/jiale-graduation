// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from isas_msgs:msg/Anchorlist.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__ANCHORLIST__STRUCT_H_
#define ISAS_MSGS__MSG__DETAIL__ANCHORLIST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'anchor'
#include "isas_msgs/msg/detail/anchor_position__struct.h"

/// Struct defined in msg/Anchorlist in the package isas_msgs.
typedef struct isas_msgs__msg__Anchorlist
{
  isas_msgs__msg__AnchorPosition__Sequence anchor;
} isas_msgs__msg__Anchorlist;

// Struct for a sequence of isas_msgs__msg__Anchorlist.
typedef struct isas_msgs__msg__Anchorlist__Sequence
{
  isas_msgs__msg__Anchorlist * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} isas_msgs__msg__Anchorlist__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ISAS_MSGS__MSG__DETAIL__ANCHORLIST__STRUCT_H_
