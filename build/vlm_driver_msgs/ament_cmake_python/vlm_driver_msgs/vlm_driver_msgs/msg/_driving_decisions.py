# generated from rosidl_generator_py/resource/_idl.py.em
# with input from vlm_driver_msgs:msg/DrivingDecisions.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_DrivingDecisions(type):
    """Metaclass of message 'DrivingDecisions'."""

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
            module = import_type_support('vlm_driver_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'vlm_driver_msgs.msg.DrivingDecisions')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__driving_decisions
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__driving_decisions
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__driving_decisions
            cls._TYPE_SUPPORT = module.type_support_msg__msg__driving_decisions
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__driving_decisions

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


class DrivingDecisions(metaclass=Metaclass_DrivingDecisions):
    """Message class 'DrivingDecisions'."""

    __slots__ = [
        '_header',
        '_source',
        '_steering_label',
        '_speed_label',
        '_steering_deg',
        '_speed_mps',
        '_confidence',
        '_emergency_stop',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'source': 'string',
        'steering_label': 'string',
        'speed_label': 'string',
        'steering_deg': 'float',
        'speed_mps': 'float',
        'confidence': 'float',
        'emergency_stop': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.source = kwargs.get('source', str())
        self.steering_label = kwargs.get('steering_label', str())
        self.speed_label = kwargs.get('speed_label', str())
        self.steering_deg = kwargs.get('steering_deg', float())
        self.speed_mps = kwargs.get('speed_mps', float())
        self.confidence = kwargs.get('confidence', float())
        self.emergency_stop = kwargs.get('emergency_stop', bool())

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
        if self.source != other.source:
            return False
        if self.steering_label != other.steering_label:
            return False
        if self.speed_label != other.speed_label:
            return False
        if self.steering_deg != other.steering_deg:
            return False
        if self.speed_mps != other.speed_mps:
            return False
        if self.confidence != other.confidence:
            return False
        if self.emergency_stop != other.emergency_stop:
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
    def source(self):
        """Message field 'source'."""
        return self._source

    @source.setter
    def source(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'source' field must be of type 'str'"
        self._source = value

    @builtins.property
    def steering_label(self):
        """Message field 'steering_label'."""
        return self._steering_label

    @steering_label.setter
    def steering_label(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'steering_label' field must be of type 'str'"
        self._steering_label = value

    @builtins.property
    def speed_label(self):
        """Message field 'speed_label'."""
        return self._speed_label

    @speed_label.setter
    def speed_label(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'speed_label' field must be of type 'str'"
        self._speed_label = value

    @builtins.property
    def steering_deg(self):
        """Message field 'steering_deg'."""
        return self._steering_deg

    @steering_deg.setter
    def steering_deg(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'steering_deg' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'steering_deg' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._steering_deg = value

    @builtins.property
    def speed_mps(self):
        """Message field 'speed_mps'."""
        return self._speed_mps

    @speed_mps.setter
    def speed_mps(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'speed_mps' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'speed_mps' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._speed_mps = value

    @builtins.property
    def confidence(self):
        """Message field 'confidence'."""
        return self._confidence

    @confidence.setter
    def confidence(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'confidence' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'confidence' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._confidence = value

    @builtins.property
    def emergency_stop(self):
        """Message field 'emergency_stop'."""
        return self._emergency_stop

    @emergency_stop.setter
    def emergency_stop(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'emergency_stop' field must be of type 'bool'"
        self._emergency_stop = value
