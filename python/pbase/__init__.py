import ctypes

plib = ctypes.cdll.LoadLibrary('/usr/local/lib/libpbase.so')

# after loading lib!
from . import mathc
from . import log
from . import geoc

from .types import *

# pure python

