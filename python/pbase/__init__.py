import ctypes

lib = ctypes.cdll.LoadLibrary('/usr/local/lib/libpbase.so')

# after loading lib!
from . import mathc
from . import log

from .types import *

# pure python

