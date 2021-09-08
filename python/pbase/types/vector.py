import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from .. import mathctypes
from .. import bindingbase as bb

from .. import plib

from .indices import *


class pVector(ct.Structure):
    _fields_ = [
        ('data', bb.c_float_p),
        ('size', bb.c_size_t)
    ]


pVector_p = ct.POINTER(pVector)

plib.p_vector_kill.argtypes = [pVector_p]


def p_vector_valid(self: pVector):
    return self.data is not None and self.size > 0


class NpVector(np.ndarray):
    def __new__(cls, vector: pVector):
        # create a numpy array from a ct pointer
        arr = np.ctypeslib.as_array(vector.data, shape=(vector.size,))
        # create the NumpyIndices and set pbb.c_indices
        res = super(NpVector, cls).__new__(cls, shape=arr.shape, dtype=np.float32, buffer=arr)
        res.p_vector = vector
        return res

    def __array_finalize__(self, obj):
        # in the creation process of __new__, so p_vector will be set in new to the real vector
        if obj is None:
            return
        # view, so set to None (views del shouldn't kill it)
        self.p_vector = None

    def __del__(self):
        # only kill, if its the real vector and not a view
        if self.p_vector is not None:
            plib.p_vector_kill(bb.ref(self.p_vector))


def cast_from_pVector(data: pVector) -> NpVector:
    if not p_vector_valid(data):
        raise RuntimeError("cast_from_pVector failed, vector is not valid")
    return NpVector(data)


def cast_into_pVector(data: np.ndarray) -> pVector:
    if data.dtype != np.float32:
        raise RuntimeError('cast_np_pVector failed: must be float32')
    if data.ndim != 1:
        raise RuntimeError('cast_np_pVector failed: must be a vector')
    size = data.shape[0]
    return pVector(data.ctypes.data_as(bb.c_float_p), size)


def cast_into_pVector_p(data: Optional[np.ndarray]) -> Optional[pVector_p]:
    if data is None or data.size == 0:
        return None
    return ct.pointer(cast_into_pVector(data))


# /** Prints the whole vector data to stdout */
# void p_vector_print(pVector self);
plib.p_vector_print.argtypes = [pVector]


def vector_print(self: np.ndarray):
    '''
    Prints the whole vector data to stdout
    '''
    plib.p_vector_print(cast_into_pVector(self))
