// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from isas_msgs:msg/RTLSRange.idl
// generated code does not contain a copyright notice

#ifndef ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__FUNCTIONS_H_
#define ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "isas_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "isas_msgs/msg/detail/rtls_range__struct.h"

/// Initialize msg/RTLSRange message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * isas_msgs__msg__RTLSRange
 * )) before or use
 * isas_msgs__msg__RTLSRange__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
bool
isas_msgs__msg__RTLSRange__init(isas_msgs__msg__RTLSRange * msg);

/// Finalize msg/RTLSRange message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
void
isas_msgs__msg__RTLSRange__fini(isas_msgs__msg__RTLSRange * msg);

/// Create msg/RTLSRange message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * isas_msgs__msg__RTLSRange__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
isas_msgs__msg__RTLSRange *
isas_msgs__msg__RTLSRange__create();

/// Destroy msg/RTLSRange message.
/**
 * It calls
 * isas_msgs__msg__RTLSRange__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
void
isas_msgs__msg__RTLSRange__destroy(isas_msgs__msg__RTLSRange * msg);

/// Check for msg/RTLSRange message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
bool
isas_msgs__msg__RTLSRange__are_equal(const isas_msgs__msg__RTLSRange * lhs, const isas_msgs__msg__RTLSRange * rhs);

/// Copy a msg/RTLSRange message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
bool
isas_msgs__msg__RTLSRange__copy(
  const isas_msgs__msg__RTLSRange * input,
  isas_msgs__msg__RTLSRange * output);

/// Initialize array of msg/RTLSRange messages.
/**
 * It allocates the memory for the number of elements and calls
 * isas_msgs__msg__RTLSRange__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
bool
isas_msgs__msg__RTLSRange__Sequence__init(isas_msgs__msg__RTLSRange__Sequence * array, size_t size);

/// Finalize array of msg/RTLSRange messages.
/**
 * It calls
 * isas_msgs__msg__RTLSRange__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
void
isas_msgs__msg__RTLSRange__Sequence__fini(isas_msgs__msg__RTLSRange__Sequence * array);

/// Create array of msg/RTLSRange messages.
/**
 * It allocates the memory for the array and calls
 * isas_msgs__msg__RTLSRange__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
isas_msgs__msg__RTLSRange__Sequence *
isas_msgs__msg__RTLSRange__Sequence__create(size_t size);

/// Destroy array of msg/RTLSRange messages.
/**
 * It calls
 * isas_msgs__msg__RTLSRange__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
void
isas_msgs__msg__RTLSRange__Sequence__destroy(isas_msgs__msg__RTLSRange__Sequence * array);

/// Check for msg/RTLSRange message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
bool
isas_msgs__msg__RTLSRange__Sequence__are_equal(const isas_msgs__msg__RTLSRange__Sequence * lhs, const isas_msgs__msg__RTLSRange__Sequence * rhs);

/// Copy an array of msg/RTLSRange messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_isas_msgs
bool
isas_msgs__msg__RTLSRange__Sequence__copy(
  const isas_msgs__msg__RTLSRange__Sequence * input,
  isas_msgs__msg__RTLSRange__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // ISAS_MSGS__MSG__DETAIL__RTLS_RANGE__FUNCTIONS_H_
