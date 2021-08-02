import ctypes
import inspect

# import library, where log is used:
# lib = ctypes.cdll.LoadLibrary('./liblog.so')     # (linux lib_example)

# or make it visible from the python package level:
from . import lib

# if a namespace is used, change it here: (for example ns_logc_set_*)
p_rhc_log_set_min_level = lib.p_rhc_log_set_min_level
p_rhc_log_set_quiet = lib.p_rhc_log_set_quiet
p_rhc_log_base_ = lib.p_rhc_log_base_


#
# Implementation:
#

p_rhc_log_set_min_level.argtypes = [ctypes.c_int]
p_rhc_log_set_quiet.argtypes = [ctypes.c_bool]
p_rhc_log_base_.argtypes = [ctypes.c_int, ctypes.c_char_p, ctypes.c_int, ctypes.c_char_p]

TRACE = 0
DEBUG = 1
INFO = 2
WARN = 3
ERROR = 4
WTF = 5
NUM_LEVELS = 6


def set_min_level(level: int):
    p_rhc_log_set_min_level(level)


def set_quiet(set: bool):
    p_rhc_log_set_quiet(set)


def trace(*text, sep=' '):
    frame = inspect.stack()[1]
    p_rhc_log_base_(TRACE, frame.filename.encode(), frame.lineno, sep.join(text).encode())


def debug(*text, sep=' '):
    frame = inspect.stack()[1]
    p_rhc_log_base_(DEBUG, frame.filename.encode(), frame.lineno, sep.join(text).encode())


def info(*text, sep=' '):
    frame = inspect.stack()[1]
    p_rhc_log_base_(INFO, frame.filename.encode(), frame.lineno, sep.join(text).encode())


def warn(*text, sep=' '):
    frame = inspect.stack()[1]
    p_rhc_log_base_(WARN, frame.filename.encode(), frame.lineno, sep.join(text).encode())


def error(*text, sep=' '):
    frame = inspect.stack()[1]
    p_rhc_log_base_(ERROR, frame.filename.encode(), frame.lineno, sep.join(text).encode())


def wtf(*text, sep=' '):
    frame = inspect.stack()[1]
    p_rhc_log_base_(WTF, frame.filename.encode(), frame.lineno, sep.join(text).encode())

