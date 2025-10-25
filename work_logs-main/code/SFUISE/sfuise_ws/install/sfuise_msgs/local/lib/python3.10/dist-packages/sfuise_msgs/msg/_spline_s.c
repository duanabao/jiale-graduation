// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from sfuise_msgs:msg/Spline.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "sfuise_msgs/msg/detail/spline__struct.h"
#include "sfuise_msgs/msg/detail/spline__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "sfuise_msgs/msg/detail/knot__functions.h"
// end nested array functions include
bool sfuise_msgs__msg__knot__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * sfuise_msgs__msg__knot__convert_to_py(void * raw_ros_message);
bool sfuise_msgs__msg__knot__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * sfuise_msgs__msg__knot__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool sfuise_msgs__msg__spline__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[31];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("sfuise_msgs.msg._spline.Spline", full_classname_dest, 30) == 0);
  }
  sfuise_msgs__msg__Spline * ros_message = _ros_message;
  {  // start_idx
    PyObject * field = PyObject_GetAttrString(_pymsg, "start_idx");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->start_idx = PyLong_AsUnsignedLongLong(field);
    Py_DECREF(field);
  }
  {  // dt
    PyObject * field = PyObject_GetAttrString(_pymsg, "dt");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->dt = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // start_t
    PyObject * field = PyObject_GetAttrString(_pymsg, "start_t");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->start_t = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // knots
    PyObject * field = PyObject_GetAttrString(_pymsg, "knots");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'knots'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!sfuise_msgs__msg__Knot__Sequence__init(&(ros_message->knots), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create sfuise_msgs__msg__Knot__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    sfuise_msgs__msg__Knot * dest = ros_message->knots.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!sfuise_msgs__msg__knot__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // idles
    PyObject * field = PyObject_GetAttrString(_pymsg, "idles");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'idles'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!sfuise_msgs__msg__Knot__Sequence__init(&(ros_message->idles), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create sfuise_msgs__msg__Knot__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    sfuise_msgs__msg__Knot * dest = ros_message->idles.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!sfuise_msgs__msg__knot__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * sfuise_msgs__msg__spline__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Spline */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("sfuise_msgs.msg._spline");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Spline");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  sfuise_msgs__msg__Spline * ros_message = (sfuise_msgs__msg__Spline *)raw_ros_message;
  {  // start_idx
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLongLong(ros_message->start_idx);
    {
      int rc = PyObject_SetAttrString(_pymessage, "start_idx", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // dt
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->dt);
    {
      int rc = PyObject_SetAttrString(_pymessage, "dt", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // start_t
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->start_t);
    {
      int rc = PyObject_SetAttrString(_pymessage, "start_t", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // knots
    PyObject * field = NULL;
    size_t size = ros_message->knots.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    sfuise_msgs__msg__Knot * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->knots.data[i]);
      PyObject * pyitem = sfuise_msgs__msg__knot__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "knots", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // idles
    PyObject * field = NULL;
    size_t size = ros_message->idles.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    sfuise_msgs__msg__Knot * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->idles.data[i]);
      PyObject * pyitem = sfuise_msgs__msg__knot__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "idles", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
