// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from sfuise_msgs:msg/Calib.idl
// generated code does not contain a copyright notice

#ifndef SFUISE_MSGS__MSG__DETAIL__CALIB__FUNCTIONS_H_
#define SFUISE_MSGS__MSG__DETAIL__CALIB__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "sfuise_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "sfuise_msgs/msg/detail/calib__struct.h"

/// Initialize msg/Calib message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * sfuise_msgs__msg__Calib
 * )) before or use
 * sfuise_msgs__msg__Calib__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Calib__init(sfuise_msgs__msg__Calib * msg);

/// Finalize msg/Calib message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
void
sfuise_msgs__msg__Calib__fini(sfuise_msgs__msg__Calib * msg);

/// Create msg/Calib message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * sfuise_msgs__msg__Calib__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
sfuise_msgs__msg__Calib *
sfuise_msgs__msg__Calib__create();

/// Destroy msg/Calib message.
/**
 * It calls
 * sfuise_msgs__msg__Calib__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
void
sfuise_msgs__msg__Calib__destroy(sfuise_msgs__msg__Calib * msg);

/// Check for msg/Calib message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Calib__are_equal(const sfuise_msgs__msg__Calib * lhs, const sfuise_msgs__msg__Calib * rhs);

/// Copy a msg/Calib message.
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
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Calib__copy(
  const sfuise_msgs__msg__Calib * input,
  sfuise_msgs__msg__Calib * output);

/// Initialize array of msg/Calib messages.
/**
 * It allocates the memory for the number of elements and calls
 * sfuise_msgs__msg__Calib__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Calib__Sequence__init(sfuise_msgs__msg__Calib__Sequence * array, size_t size);

/// Finalize array of msg/Calib messages.
/**
 * It calls
 * sfuise_msgs__msg__Calib__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
void
sfuise_msgs__msg__Calib__Sequence__fini(sfuise_msgs__msg__Calib__Sequence * array);

/// Create array of msg/Calib messages.
/**
 * It allocates the memory for the array and calls
 * sfuise_msgs__msg__Calib__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
sfuise_msgs__msg__Calib__Sequence *
sfuise_msgs__msg__Calib__Sequence__create(size_t size);

/// Destroy array of msg/Calib messages.
/**
 * It calls
 * sfuise_msgs__msg__Calib__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
void
sfuise_msgs__msg__Calib__Sequence__destroy(sfuise_msgs__msg__Calib__Sequence * array);

/// Check for msg/Calib message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Calib__Sequence__are_equal(const sfuise_msgs__msg__Calib__Sequence * lhs, const sfuise_msgs__msg__Calib__Sequence * rhs);

/// Copy an array of msg/Calib messages.
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
ROSIDL_GENERATOR_C_PUBLIC_sfuise_msgs
bool
sfuise_msgs__msg__Calib__Sequence__copy(
  const sfuise_msgs__msg__Calib__Sequence * input,
  sfuise_msgs__msg__Calib__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // SFUISE_MSGS__MSG__DETAIL__CALIB__FUNCTIONS_H_
