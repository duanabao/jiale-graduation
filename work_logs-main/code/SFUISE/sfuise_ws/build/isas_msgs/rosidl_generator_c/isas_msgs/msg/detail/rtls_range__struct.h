// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from isas_msgs:msg/RTLSRange.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__STRUCT_H_
#define ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pos'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/RTLSRange in the package isas_msgs.
typedef struct isas_msgs__msg__RTLSRange
{
  /// anchor id
  uint16_t id;
  /// anchor position
  geometry_msgs__msg__Point pos;
  /// position rate for the quality of the estimated anchor position
  float pr;
  /// current distance to the anchor in m
  float range;
  /// mean value of distances since reset
  float mean;
  /// variance of the distance
  float var;
  /// first path power
  float fpp;
  /// received power
  float rxp;
  /// channel standard noise
  float csn;
  /// channel maximum noise
  float cmn;
  /// time out counter, increases if the range measurement fails
  uint8_t toc;
  /// 1 denotes valid data and has been used for the estimation of position, 0 denotes old data, the measurement didn't success
  uint8_t ra;
} isas_msgs__msg__RTLSRange;

// Struct for a sequence of isas_msgs__msg__RTLSRange.
typedef struct isas_msgs__msg__RTLSRange__Sequence
{
  isas_msgs__msg__RTLSRange * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} isas_msgs__msg__RTLSRange__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__STRUCT_H_
