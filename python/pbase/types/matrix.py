import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from .. import mathctypes
from .. import bindingbase as bb

from .. import plib

from .indices import *

class pMatrix(ct.Structure):
    _fields_ = [
        ('data', bb.c_float_p),
        ('cols', bb.c_size_t),
        ('rows', bb.c_size_t)
    ]


pMatrix_p = ct.POINTER(pMatrix)

plib.p_matrix_kill.argtypes = [pMatrix_p]


class NpMatrix(np.ndarray):
    def __new__(cls, matrix: pMatrix):
        shape = matrix.rows, matrix.cols
        # create a numpy array from a ct pointer
        arr = np.ctypeslib.as_array(matrix.data, shape=shape)
        # create the NumpyCloud and set p_cloud
        res = super(NpMatrix, cls).__new__(cls, shape=arr.shape, dtype=np.float32, buffer=arr)
        res.p_matrix = matrix
        return res

    def __array_finalize__(self, obj):
        # in the creation process of __new__, so p_matrix will be set in new to the real matrix
        if obj is None:
            return
        # view, so set to None (views del shouldn't kill it)
        self.p_matrix = None

    def __del__(self):
        # only kill, if its the real matrix and not a view
        if self.p_matrix is not None:
            plib.p_matrix_kill(bb.ref(self.p_matrix))


def cast_from_pMatrix(data: pMatrix) -> NpMatrix:
    return NpMatrix(data)


def cast_into_pMatrix(data: np.ndarray) -> pMatrix:
    if data.dtype != np.float32:
        raise RuntimeError('cast_np_pMatrix failed: must be float32')
    if data.ndim != 2:
        raise RuntimeError('cast_np_pMatrix failed: must be a matrix')
    rows = data.shape[0]
    cols = data.shape[1]
    return pMatrix(data.ctypes.data_as(bb.c_float_p), cols, rows)


def cast_into_pMatrix_p(data: Optional[np.ndarray]) -> Optional[pMatrix_p]:
    if data is None or data.size == 0:
        return None
    return ct.pointer(cast_into_pMatrix(data))


# /** Prints the whole matrix data to stdout */
# void p_matrix_print(pMatrix self);
plib.p_matrix_print.argtypes = [pMatrix]


def matrix_print(self: np.ndarray):
    '''
    Prints the whole matrix data to stdout
    '''
    plib.p_matrix_print(cast_into_pMatrix(self))
