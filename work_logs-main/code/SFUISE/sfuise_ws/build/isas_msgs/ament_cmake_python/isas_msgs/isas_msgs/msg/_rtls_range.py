# generated from rosidl_generator_py/resource/_idl.py.em
# with input from isas_msgs:msg/RTLSRange.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RTLSRange(type):
    """Metaclass of message 'RTLSRange'."""

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
            module = import_type_support('isas_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'isas_msgs.msg.RTLSRange')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__rtls_range
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__rtls_range
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__rtls_range
            cls._TYPE_SUPPORT = module.type_support_msg__msg__rtls_range
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__rtls_range

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RTLSRange(metaclass=Metaclass_RTLSRange):
    """Message class 'RTLSRange'."""

    __slots__ = [
        '_id',
        '_pos',
        '_pr',
        '_range',
        '_mean',
        '_var',
        '_fpp',
        '_rxp',
        '_csn',
        '_cmn',
        '_toc',
        '_ra',
    ]

    _fields_and_field_types = {
        'id': 'uint16',
        'pos': 'geometry_msgs/Point',
        'pr': 'float',
        'range': 'float',
        'mean': 'float',
        'var': 'float',
        'fpp': 'float',
        'rxp': 'float',
        'csn': 'float',
        'cmn': 'float',
        'toc': 'uint8',
        'ra': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.id = kwargs.get('id', int())
        from geometry_msgs.msg import Point
        self.pos = kwargs.get('pos', Point())
        self.pr = kwargs.get('pr', float())
        self.range = kwargs.get('range', float())
        self.mean = kwargs.get('mean', float())
        self.var = kwargs.get('var', float())
        self.fpp = kwargs.get('fpp', float())
        self.rxp = kwargs.get('rxp', float())
        self.csn = kwargs.get('csn', float())
        self.cmn = kwargs.get('cmn', float())
        self.toc = kwargs.get('toc', int())
        self.ra = kwargs.get('ra', int())

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
        if self.id != other.id:
            return False
        if self.pos != other.pos:
            return False
        if self.pr != other.pr:
            return False
        if self.range != other.range:
            return False
        if self.mean != other.mean:
            return False
        if self.var != other.var:
            return False
        if self.fpp != other.fpp:
            return False
        if self.rxp != other.rxp:
            return False
        if self.csn != other.csn:
            return False
        if self.cmn != other.cmn:
            return False
        if self.toc != other.toc:
            return False
        if self.ra != other.ra:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property  # noqa: A003
    def id(self):  # noqa: A003
        """Message field 'id'."""
        return self._id

    @id.setter  # noqa: A003
    def id(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'id' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'id' field must be an unsigned integer in [0, 65535]"
        self._id = value

    @builtins.property
    def pos(self):
        """Message field 'pos'."""
        return self._pos

    @pos.setter
    def pos(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'pos' field must be a sub message of type 'Point'"
        self._pos = value

    @builtins.property
    def pr(self):
        """Message field 'pr'."""
        return self._pr

    @pr.setter
    def pr(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pr' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pr' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pr = value

    @builtins.property  # noqa: A003
    def range(self):  # noqa: A003
        """Message field 'range'."""
        return self._range

    @range.setter  # noqa: A003
    def range(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'range' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'range' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._range = value

    @builtins.property
    def mean(self):
        """Message field 'mean'."""
        return self._mean

    @mean.setter
    def mean(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mean' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'mean' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._mean = value

    @builtins.property
    def var(self):
        """Message field 'var'."""
        return self._var

    @var.setter
    def var(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'var' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'var' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._var = value

    @builtins.property
    def fpp(self):
        """Message field 'fpp'."""
        return self._fpp

    @fpp.setter
    def fpp(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'fpp' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'fpp' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._fpp = value

    @builtins.property
    def rxp(self):
        """Message field 'rxp'."""
        return self._rxp

    @rxp.setter
    def rxp(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'rxp' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'rxp' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._rxp = value

    @builtins.property
    def csn(self):
        """Message field 'csn'."""
        return self._csn

    @csn.setter
    def csn(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'csn' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'csn' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._csn = value

    @builtins.property
    def cmn(self):
        """Message field 'cmn'."""
        return self._cmn

    @cmn.setter
    def cmn(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'cmn' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'cmn' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._cmn = value

    @builtins.property
    def toc(self):
        """Message field 'toc'."""
        return self._toc

    @toc.setter
    def toc(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'toc' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'toc' field must be an unsigned integer in [0, 255]"
        self._toc = value

    @builtins.property
    def ra(self):
        """Message field 'ra'."""
        return self._ra

    @ra.setter
    def ra(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ra' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'ra' field must be an unsigned integer in [0, 255]"
        self._ra = value
