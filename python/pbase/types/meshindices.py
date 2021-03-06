import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from .. import mathctypes
from .. import bindingbase as bb

from .. import plib

from .indices import *


class pMeshIndices(ct.Structure):
    _fields_ = [
        ('data', mathctypes.ivec3_p),
        ('size', bb.c_int)
    ]


pMeshIndices_p = ct.POINTER(pMeshIndices)

plib.p_mesh_indices_kill.argtypes = [pMeshIndices_p]


def p_mesh_indices_valid(self: pMeshIndices):
    return self.data is not None and self.size > 0


class NpMeshIndices(np.ndarray):
    def __new__(cls, mesh_indices: pMeshIndices):
        shape = mesh_indices.size, 3
        # create a numpy array from a ct pointer
        arr = np.ctypeslib.as_array(mesh_indices.data, shape=shape)
        # create the NumpyCloud and set p_cloud
        res = super(NpMeshIndices, cls).__new__(cls, shape=arr.shape, dtype=np.int32, buffer=arr)
        res.p_mesh_indices = mesh_indices
        return res

    def __array_finalize__(self, obj):
        # in the creation process of __new__, so p_mesh_indices will be set in new to the real cloud
        if obj is None:
            return
        # view, so set to None (views del shouldn't kill it)
        self.p_mesh_indices = None

    def __del__(self):
        # only kill, if its the real cloud and not a view
        if self.p_mesh_indices is not None:
            plib.p_mesh_indices_kill(bb.ref(self.p_mesh_indices))


def cast_from_pMeshIndices(data: pMeshIndices) -> NpMeshIndices:
    if not p_mesh_indices_valid(data):
        raise RuntimeError("cast_from_pMeshIndices failed, mesh_indices are not valid")
    return NpMeshIndices(data)


def cast_into_pMeshIndices(data: np.ndarray) -> pMeshIndices:
    if data.dtype != np.int32:
        raise RuntimeError('cast_np_pMeshIndices failed: must be int')
    if data.ndim != 2 or data.shape[1] != 3:
        raise RuntimeError('cast_np_pMeshIndices failed: must be a matrix n*3')
    if np.isfortran(data):
        raise RuntimeError('cast_np_pCloud failed: must be C order')
    size = data.shape[0]
    return pMeshIndices(mathctypes.cast_into_ivec3_p(data), size)


def cast_into_pMeshIndices_p(data: Optional[np.ndarray]) -> Optional[pMeshIndices_p]:
    if data is None or data.size == 0:
        return None
    return ct.pointer(cast_into_pMeshIndices(data))


# /** Prints all mesh indices to stdout */
# void p_mesh_indices_print(pMeshIndices self);
plib.p_mesh_indices_print.argtypes = [pMeshIndices]


def mesh_indices_print(self: np.ndarray):
    '''
    Prints all mesh_indices to stdout
    '''
    plib.p_mesh_indices_print(cast_into_pMeshIndices(self))


# /** Adds an offset to each index */
# void p_mesh_indices_add_offset(pMeshIndices *self, int offset);
plib.p_mesh_indices_add_offset.argtypes = [pMeshIndices_p,
                                           bb.c_int]


def mesh_indices_add_offset(self: np.ndarray,
                            offset: int):
    '''
    Adds an offset to each index
    '''
    plib.p_mesh_indices_add_offset(cast_into_pMeshIndices_p(self),
                                   offset)


# /** Concatenates two mesh_indices together, into the new pMeshIndices out_concatenate. */
# pMeshIndices p_mesh_indices_concatenate(pMeshIndices a, pMeshIndices b);
plib.p_mesh_indices_concatenate.argtypes = [pMeshIndices,
                                            pMeshIndices]
plib.p_mesh_indices_concatenate.restype = pMeshIndices


def mesh_indices_concatenate(a: np.ndarray,
                             b: np.ndarray) \
        -> np.ndarray:
    '''
    Concatenates two mesh_indices together, into the new pMeshIndices out_concatenate.

    :return: pMeshIndices
    '''
    res = plib.p_mesh_indices_concatenate(cast_into_pMeshIndices(a),
                                          cast_into_pMeshIndices(b))
    return cast_from_pMeshIndices(res)


# /** Concatenates a list/vector of mesh_indices together, into the new pMeshIndices out_concatenate. */
# pMeshIndices p_mesh_indices_concatenate_v(const pMeshIndices *mesh_indices_list, int n);
plib.p_mesh_indices_concatenate_v.argtypes = [pMeshIndices_p,
                                              bb.c_int]
plib.p_mesh_indices_concatenate_v.restype = pMeshIndices


def mesh_indices_concatenate_v(mesh_indices_list: List[np.ndarray]) \
        -> np.ndarray:
    '''
    Concatenates a list/vector of mesh_indices together, into the new pMeshIndices out_concatenate.

    :return: pMeshIndices
    '''
    n = len(mesh_indices_list)
    LIST = pMeshIndices * n
    list = LIST()
    for i in range(n):
        list[i] = cast_into_pMeshIndices(mesh_indices_list[i])
    res = plib.p_mesh_indices_concatenate_v(list,
                                            n)
    return cast_from_pMeshIndices(res)


# /** Applies mesh_indices on mesh_indices, so that all not used mesh_indices are removed */
# pMeshIndices p_mesh_indices_apply_mesh_indices(pMeshIndices self, pMeshIndices mesh_indices);
plib.p_mesh_indices_apply_indices.argtypes = [pMeshIndices,
                                              pIndices]
plib.p_mesh_indices_apply_indices.restype = pMeshIndices


def mesh_indices_apply_indices(self: np.ndarray,
                               indices: np.ndarray) \
        -> np.ndarray:
    '''
    Applies indices on mesh_indices, so that all not used points are removed

    :return: pMeshIndices
    '''
    res = plib.p_mesh_indices_apply_indices(cast_into_pMeshIndices(self),
                                            cast_into_pIndices(indices))
    return cast_from_pMeshIndices(res)


# /** Returns the minimum values for v0, v1, v2 */
# ivec3 p_mesh_indices_min(pMeshIndices self);
plib.p_mesh_indices_min.argtypes = [pMeshIndices]
plib.p_mesh_indices_min.restype = mathctypes.ivec3


def mesh_indices_min(self: np.ndarray) \
        -> np.ndarray:
    '''
    Returns the minimum values for v0, v1, v2

    :return: ivec3
    '''
    res = plib.p_mesh_indices_min(cast_into_pMeshIndices(self))
    return mathctypes.cast_from_ivec3(res)


# /** Returns the maximum values for v0, v1, v2 */
# ivec3 p_mesh_indices_max(pMeshIndices self);
plib.p_mesh_indices_max.argtypes = [pMeshIndices]
plib.p_mesh_indices_max.restype = mathctypes.ivec3


def mesh_indices_max(self: np.ndarray) \
        -> np.ndarray:
    '''
    Returns the maximum values for v0, v1, v2

    :return: ivec3
    '''
    res = plib.p_mesh_indices_max(cast_into_pMeshIndices(self))
    return mathctypes.cast_from_ivec3(res)



# /** returns true, if all mesh index values are in the given range [min_incl:max_exl) */
# bool p_mesh_indices_check_in_range(pMeshIndices self, int min_incl, int max_excl);
plib.p_mesh_indices_check_in_range.argtypes = [pIndices, bb.c_int, bb.c_int]
plib.p_mesh_indices_check_in_range.restype = bb.c_bool


def mesh_indices_check_in_range(self: np.ndarray, min_incl: int, max_excl: int) \
        -> bool:
    '''
    returns true, if all mesh index values are in the given range [min_incl:max_exl)

    :return: bool
    '''
    res = plib.p_mesh_indices_check_in_range(cast_into_pMeshIndices(self), min_incl, max_excl)
    return res.value