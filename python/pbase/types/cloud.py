import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from .. import mathctypes
from .. import bindingbase as bb

from .. import plib

from .indices import *


class pCloud(ct.Structure):
    _fields_ = [
        ('data', mathctypes.vec4_p),
        ('size', bb.c_int)
    ]


pCloud_p = ct.POINTER(pCloud)

plib.p_cloud_kill.argtypes = [pCloud_p]


def p_cloud_valid(self: pCloud):
    return self.data is not None and self.size > 0


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
            plib.p_cloud_kill(bb.ref(self.p_cloud))


def cast_from_pCloud(data: pCloud) -> NpCloud:
    if not p_cloud_valid(data):
        raise RuntimeError("cast_from_pCloud failed, cloud is not valid")
    return NpCloud(data)


def cast_into_pCloud(data: np.ndarray) -> pCloud:
    if data.dtype != np.float32:
        raise RuntimeError('cast_np_pCloud failed: must be float32')
    if data.ndim != 2 or data.shape[1] != 4:
        raise RuntimeError('cast_np_pCloud failed: must be a matrix with the shape[1]==4 (xyzw)')
    if np.isfortran(data):
        raise RuntimeError('cast_np_pCloud failed: must be C order')
    size = data.shape[0]
    return pCloud(mathctypes.cast_into_vec4_p(data), size)


def cast_into_pCloud_p(data: Optional[np.ndarray]) -> Optional[pCloud_p]:
    if data is None or data.size == 0:
        return None
    return ct.pointer(cast_into_pCloud(data))


# /** Prints the whole cloud data to stdout */
# void p_cloud_print(pCloud self);
plib.p_cloud_print.argtypes = [pCloud]


def cloud_print(self: np.ndarray):
    '''
    Prints the whole cloud data to stdout
    '''
    plib.p_cloud_print(cast_into_pCloud(self))


# /** Concatenates two point clouds together */
# pCloud p_cloud_concatenate(pCloud a, pCloud b);
plib.p_cloud_concatenate.argtypes = [pCloud,
                                     pCloud]
plib.p_cloud_concatenate.restype = pCloud


def cloud_concatenate(a: np.ndarray,
                      b: np.ndarray) \
        -> np.ndarray:
    '''
    Concatenates two point clouds together
    
    :return: pCloud
    '''
    res = plib.p_cloud_concatenate(cast_into_pCloud(a),
                                   cast_into_pCloud(b))
    return cast_from_pCloud(res)


# /** Concatenates a list/vector of point clouds together */
# pCloud p_cloud_concatenate_v(const pCloud *cloud_list, int n);
plib.p_cloud_concatenate_v.argtypes = [pCloud_p,
                                       bb.c_int]
plib.p_cloud_concatenate_v.restype = pCloud


def cloud_concatenate_v(cloud_list: List[np.ndarray]) \
        -> np.ndarray:
    '''
    Concatenates a list/vector of point clouds together
    
    :return: pCloud
    '''
    n = len(cloud_list)
    LIST = pCloud * n
    list = LIST()
    for i in range(n):
        list[i] = cast_into_pCloud(cloud_list[i])

    res = plib.p_cloud_concatenate_v(list,
                                     n)
    return cast_from_pCloud(res)


# /** Applies indices on cloud, so that all not used points are removed */
# pCloud p_cloud_apply_indices(pCloud cloud, pIndices indices);
plib.p_cloud_apply_indices.argtypes = [pCloud,
                                       pIndices]
plib.p_cloud_apply_indices.restype = pCloud


def cloud_apply_indices(self: np.ndarray,
                        indices: np.ndarray) \
        -> np.ndarray:
    '''
    Applies indices on cloud, so that all not used points are removed

    :return: pCloud
    '''
    res = plib.p_cloud_apply_indices(cast_into_pCloud(self),
                                     cast_into_pIndices(indices))
    return cast_from_pCloud(res)


# /** Returns the minimum values for x, y, z, w */
# vec4 p_cloud_min(pCloud self);
plib.p_cloud_min.argtypes = [pCloud]
plib.p_cloud_min.restype = mathctypes.vec4


def cloud_min(self: np.ndarray) \
        -> np.ndarray:
    '''
    Returns the minimum values for x, y, z, w

    :return: vec4
    '''
    res = plib.p_cloud_min(cast_into_pCloud(self))
    return mathctypes.cast_from_vec4(res)


# /** Returns the maximum values for x, y, z, w */
# vec4 p_cloud_max(pCloud self);
plib.p_cloud_max.argtypes = [pCloud]
plib.p_cloud_max.restype = mathctypes.vec4


def cloud_max(self: np.ndarray) \
        -> np.ndarray:
    '''
    Returns the maximum values for x, y, z, w

    :return: vec4
    '''
    res = plib.p_cloud_max(cast_into_pCloud(self))
    return mathctypes.cast_from_vec4(res)
