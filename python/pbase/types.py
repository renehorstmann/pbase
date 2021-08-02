import ctypes as ct
import numpy as np
from typing import Optional

from . import lib
from . import mathc

ref = ct.byref

#
# basics:
#
c_void_p = ct.c_void_p
c_bool = ct.c_bool
c_bool_p = ct.POINTER(c_bool)
c_char = ct.c_char
c_char_p = ct.c_char_p
c_int = ct.c_int
c_int_p = ct.POINTER(c_int)
c_size_t = ct.c_size_t
c_size_t_p = ct.POINTER(c_size_t)
c_float = ct.c_float
c_float_p = ct.POINTER(c_float)
c_double = ct.c_double
c_double_p = ct.POINTER(c_double)


class pCloud(ct.Structure):
    _fields_ = [
        ('data', mathc.vec4_p),
        ('size', c_size_t)
    ]


pCloud_p = ct.POINTER(pCloud)

lib.p_cloud_kill.argtypes = [pCloud_p]


class NpCloud(np.ndarray):
    def __new__(cls, cloud: pCloud):
        shape = cloud.size, 4
        # create a numpy array from a ct pointer
        arr = np.ctypeslib.as_array(cloud.data, shape=shape)
        # create the NumpyCloud and set p_cloud
        res = super(NpCloud, cls).__new__(cls, shape=arr.shape, dtype=np.float32, buffer=arr)
        res.p_cloud = cloud
        return res

    def __array_finalize__(self, obj):
        # in the creation process of __new__, so p_cloud will be set in new to the real cloud
        if obj is None:
            return
        # view, so set to None (views del shouldn't kill it)
        self.p_cloud = None

    def __del__(self):
        # only kill, if its the real cloud and not a view
        if self.p_cloud is not None:
            lib.p_cloud_kill(ref(self.p_cloud))


def cast_pCloud_np(data: pCloud) -> np.ndarray:
    return NpCloud(data)


def cast_np_pCloud(data: np.ndarray) -> pCloud:
    if data.dtype != np.float32:
        raise RuntimeError('cast_np_pCloud failed: must be float32')
    if data.ndim != 2 or data.shape[1] != 4:
        raise RuntimeError('cast_np_pCloud failed: must be a matrix with the shape[1]==4 (xyzw)')
    if np.isfortran(data):
        raise RuntimeError('cast_np_pCloud failed: must be C order')
    size = data.shape[0]
    return pCloud(mathc.cast_np_vec4_p(data), size)


def cast_np_pCloud_p(data: Optional[np.ndarray]) -> pCloud_p:
    if data is None or data.size == 0:
        return None
    return ref(cast_np_pCloud(data))


class pIndices(ct.Structure):
    _fields_ = [
        ('data', c_int_p),
        ('size', c_size_t)
    ]


pIndices_p = ct.POINTER(pIndices)

lib.p_indices_kill.argtypes = [pIndices_p]


class NpIndices(np.ndarray):
    def __new__(cls, indices: pIndices):
        # create a numpy array from a ct pointer
        arr = np.ctypeslib.as_array(indices.data, shape=(indices.size,))
        # create the NumpyIndices and set pc_indices
        res = super(NpIndices, cls).__new__(cls, shape=arr.shape, dtype=np.int32, buffer=arr)
        res.p_indices = indices
        return res

    def __array_finalize__(self, obj):
        # in the creation process of __new__, so p_indices will be set in new to the real cloud
        if obj is None:
            return
        # view, so set to None (views del shouldn't kill it)
        self.p_indices = None

    def __del__(self):
        # only kill, if its the real cloud and not a view
        if self.p_indices is not None:
            lib.p_indices_kill(ref(self.p_indices))


def cast_pIndices_np(data: pIndices) -> np.ndarray:
    return NpIndices(data)


def cast_np_pIndices(data: np.ndarray) -> pIndices:
    if data.dtype != np.int32:
        raise RuntimeError('cast_np_pIndices failed: must be int')
    if data.ndim != 1:
        raise RuntimeError('cast_np_pIndices failed: must be a list')
    size = data.shape[0]
    return pIndices(data.ctypes.data_as(c_int_p), size)


def cast_np_pIndices_p(data: Optional[np.ndarray]) -> pIndices_p:
    if data is None or data.size == 0:
        return None
    return ref(cast_np_pIndices(data))
