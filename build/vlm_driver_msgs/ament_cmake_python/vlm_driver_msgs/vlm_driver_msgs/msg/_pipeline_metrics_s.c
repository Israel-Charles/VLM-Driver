// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from vlm_driver_msgs:msg/PipelineMetrics.idl
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
#include "vlm_driver_msgs/msg/detail/pipeline_metrics__struct.h"
#include "vlm_driver_msgs/msg/detail/pipeline_metrics__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool vlm_driver_msgs__msg__pipeline_metrics__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[54];
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
    assert(strncmp("vlm_driver_msgs.msg._pipeline_metrics.PipelineMetrics", full_classname_dest, 53) == 0);
  }
  vlm_driver_msgs__msg__PipelineMetrics * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // source
    PyObject * field = PyObject_GetAttrString(_pymsg, "source");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->source, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // preprocess_ms
    PyObject * field = PyObject_GetAttrString(_pymsg, "preprocess_ms");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->preprocess_ms = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // decision_ms
    PyObject * field = PyObject_GetAttrString(_pymsg, "decision_ms");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->decision_ms = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // total_ms
    PyObject * field = PyObject_GetAttrString(_pymsg, "total_ms");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->total_ms = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // fps
    PyObject * field = PyObject_GetAttrString(_pymsg, "fps");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->fps = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * vlm_driver_msgs__msg__pipeline_metrics__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of PipelineMetrics */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("vlm_driver_msgs.msg._pipeline_metrics");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "PipelineMetrics");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  vlm_driver_msgs__msg__PipelineMetrics * ros_message = (vlm_driver_msgs__msg__PipelineMetrics *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // source
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->source.data,
      strlen(ros_message->source.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "source", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // preprocess_ms
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->preprocess_ms);
    {
      int rc = PyObject_SetAttrString(_pymessage, "preprocess_ms", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // decision_ms
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->decision_ms);
    {
      int rc = PyObject_SetAttrString(_pymessage, "decision_ms", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // total_ms
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->total_ms);
    {
      int rc = PyObject_SetAttrString(_pymessage, "total_ms", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // fps
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->fps);
    {
      int rc = PyObject_SetAttrString(_pymessage, "fps", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
