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


#
# classes:
#
class pCloud(ct.Structure):
    _fields_ = [
        ('data', mathc.vec4_p),
        ('size', c_size_t)
    ]


pCloud_p = ct.POINTER(pCloud)




#
# cast classes
#

# PcCloud
lib.p_cloud_kill.argtypes = [pCloud_p]


class NpCloud(np.ndarray):
    def __new__(cls, cloud: pCloud):
        shape = cloud.size, 4
        # create a numpy array from a ct pointer
        arr = np.ctypeslib.as_array(cloud.data, shape=shape)
        # create the NumpyCloud and set pc_cloud
        res = super(NpCloud, cls).__new__(cls, shape=arr.shape, dtype=np.float32, buffer=arr)
        res.p_cloud = cloud
        return res

    def __array_finalize__(self, obj):
        # in the creation process of __new__, so pc_cloud will be set in new to the real cloud
        if obj is None:
            return
        # view, so set to None (views del shouldn't kill it)
        self.p_cloud = None

    def __del__(self):
        # only kill, if its the real cloud and not a view
        if self.p_cloud is not None:
            lib.p_cloud_kill(ref(self.p_cloud))


#
# casts
#


def cast_pCloud_np(data: pCloud) -> np.ndarray:
    return NpCloud(data)


def cast_np_pCloud(data: np.ndarray) -> pCloud:
    if data.dtype != np.float32:
        raise RuntimeError('cast_np_pCloud failed: must be float32')
    if (data.ndim != 2) or data.shape[1] != 4:
        raise RuntimeError('cast_np_pCloud failed: must be a matrix with the shape[1]==4 (xyzw)')
    if np.isfortran(data):
        raise RuntimeError('cast_np_pCloud failed: must be C order')
    size = data.shape[0]
    return pCloud(mathc.cast_np_vec4_p(data), size)


def cast_np_pCloud_p(data: Optional[np.ndarray]) -> pCloud_p:
    if data is None or data.size == 0:
        return None
    return ref(cast_np_pCloud(data))
