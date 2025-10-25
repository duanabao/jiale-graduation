# generated from rosidl_generator_py/resource/_idl.py.em
# with input from cf_msgs:msg/Tdoa.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Tdoa(type):
    """Metaclass of message 'Tdoa'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('cf_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'cf_msgs.msg.Tdoa')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__tdoa
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__tdoa
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__tdoa
            cls._TYPE_SUPPORT = module.type_support_msg__msg__tdoa
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__tdoa

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Tdoa(metaclass=Metaclass_Tdoa):
    """Message class 'Tdoa'."""

    __slots__ = [
        '_header',
        '_id_a',
        '_id_b',
        '_data',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'id_a': 'int32',
        'id_b': 'int32',
        'data': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.id_a = kwargs.get('id_a', int())
        self.id_b = kwargs.get('id_b', int())
        self.data = kwargs.get('data', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.id_a != other.id_a:
            return False
        if self.id_b != other.id_b:
            return False
        if self.data != other.data:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def id_a(self):
        """Message field 'id_a'."""
        return self._id_a

    @id_a.setter
    def id_a(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'id_a' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'id_a' field must be an integer in [-2147483648, 2147483647]"
        self._id_a = value

    @builtins.property
    def id_b(self):
        """Message field 'id_b'."""
        return self._id_b

    @id_b.setter
    def id_b(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'id_b' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'id_b' field must be an integer in [-2147483648, 2147483647]"
        self._id_b = value

    @builtins.property
    def data(self):
        """Message field 'data'."""
        return self._data

    @data.setter
    def data(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'data' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'data' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._data = value
