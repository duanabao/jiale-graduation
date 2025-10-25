// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from isas_msgs:msg/RTLSStick.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__RTLS_STICK__STRUCT_H_
#define ISAS_MSGS__MSG__DETAIL__RTLS_STICK__STRUCT_H_

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
// Member 'pos'
// Member 'mean'
#include "geometry_msgs/msg/detail/point__struct.h"
// Member 'hrp'
#include "geometry_msgs/msg/detail/vector3__struct.h"
// Member 'ranges'
#include "isas_msgs/msg/detail/rtls_range__struct.h"

/// Struct defined in msg/RTLSStick in the package isas_msgs.
typedef struct isas_msgs__msg__RTLSStick
{
  std_msgs__msg__Header header;
  uint16_t id;
  /// timestamp in ms since the modul is turned on
  uint32_t t;
  /// current position
  geometry_msgs__msg__Point pos;
  /// mean position
  geometry_msgs__msg__Point mean;
  /// heading, roll, pitch
  geometry_msgs__msg__Vector3 hrp;
  /// number of known anchors
  uint8_t noga;
  /// number of anchors used for the current estimation of position
  uint8_t nora;
  /// range measurements
  isas_msgs__msg__RTLSRange__Sequence ranges;
} isas_msgs__msg__RTLSStick;

// Struct for a sequence of isas_msgs__msg__RTLSStick.
typedef struct isas_msgs__msg__RTLSStick__Sequence
{
  isas_msgs__msg__RTLSStick * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} isas_msgs__msg__RTLSStick__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ISAS_MSGS__MSG__DETAIL__RTLS_STICK__STRUCT_H_
