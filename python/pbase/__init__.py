import ctypes

lib = ctypes.cdll.LoadLibrary('/usr/local/lib/libpbase.so')

# after loading lib!
from . import mathc
from . import types
from . import log

from .typefun import *

# pure python

