import os
import ctypes

if os.name == 'posix':
    plib = ctypes.cdll.LoadLibrary('/usr/local/lib/libpbase.so')
elif os.name == 'nt':
    plib = ctypes.cdll.LoadLibrary('C:/Libraries/lib/libpbase.dll')
else:
    print('unknown os?:', os.name)
    exit(1)

# after loading lib!
from . import bindingbase
from . import mathctypes
from . import log
from . import math
from . import error
from . import meshprimitives

from . import types
from . import io

# pure python

