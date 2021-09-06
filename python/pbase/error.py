import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from . import types as t
from . import mathctypes as mt
from . import bindingbase as bb

from . import plib

pError = bb.c_char_p

# /** returns the error code/text p_rhc_error */
# const char *p_error();
plib.p_error.restype = pError


def get() -> Optional[str]:
    '''
    returns the error code/text p_rhc_error
    '''
    res = plib.p_error()
    if res is None:
        return None
    return res.decode()


# /**
#  * Sets and returns the error code/text p_rhc_error.
#  * If error is set to NULL, it will clear the error
#  * If p_rhc_error is not NULL (and error!=NULL), it will log a warning.
#  */
# const char *p_error_set(const char *error);
plib.p_error_set.argtypes = [pError]
plib.p_error_set.restype = pError


def set(error: Optional[str]) -> Optional[str]:
    '''
    returns the error code/text p_rhc_error
    '''
    if error is not None:
        error = error.encode()
    res = plib.p_error_set(error)
    if res is None:
        return None
    return res.decode()
