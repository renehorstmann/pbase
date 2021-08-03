import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from .. import mathc
from .. import bindingbase as bb

from .. import lib


class pIndices(ct.Structure):
    _fields_ = [
        ('data', bb.c_int_p),
        ('size', bb.c_size_t)
    ]


pIndices_p = ct.POINTER(pIndices)

lib.p_indices_kill.argtypes = [pIndices_p]


class NpIndices(np.ndarray):
    def __new__(cls, indices: pIndices):
        # create a numpy array from a ct pointer
        arr = np.ctypeslib.as_array(indices.data, shape=(indices.size,))
        # create the NumpyIndices and set pbb.c_indices
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
            lib.p_indices_kill(bb.ref(self.p_indices))


def cast_pIndices_np(data: pIndices) -> np.ndarray:
    return NpIndices(data)


def cast_np_pIndices(data: np.ndarray) -> pIndices:
    if data.dtype != np.int32:
        raise RuntimeError('cast_np_pIndices failed: must be int')
    if data.ndim != 1:
        raise RuntimeError('cast_np_pIndices failed: must be a list')
    size = data.shape[0]
    return pIndices(data.ctypes.data_as(bb.c_int_p), size)


def cast_np_pIndices_p(data: Optional[np.ndarray]) -> Optional[pIndices_p]:
    if data is None or data.size == 0:
        return None
    return ct.pointer(cast_np_pIndices(data))



# // Prints all indices to stdout
# void p_indices_print(pIndices self);
lib.p_indices_print.argtypes = [pIndices]


def indices_print(self: np.ndarray):
    '''
    Prints all indices to stdout
    '''
    lib.p_indices_print(cast_np_pIndices(self))


# // Sorts the internal indices list in ascending order
# void p_indices_sort(pIndices *self);
lib.p_indices_sort.argtypes = [pIndices_p]


def indices_sort(self: np.ndarray):
    '''
    Sorts the internal indices list in ascending order
    '''
    lib.p_indices_sort(cast_np_pIndices_p(self))


# // Deletes all duplicate indices (result will be sorted)
# void p_indices_as_set(pIndices *self);
lib.p_indices_as_set.argtypes = [pIndices_p]


def indices_as_set(self: np.ndarray):
    '''
    Deletes all duplicate indices (result will be sorted)
    '''
    lib.p_indices_as_set(cast_np_pIndices_p(self))


# /**
#  * Removes all indices of the (sorted) set remove from the (sorted) set self.
#  * @param self: must be a sorted set.
#  * @param remove: must be a sorted set.
#  */
# void p_indices_set_diff(pIndices *self, pIndices remove);
lib.p_indices_set_diff.argtypes = [pIndices_p,
                                   pIndices]


def indices_set_diff(self: np.ndarray,
                     remove: np.ndarray):
    '''
    Removes all indices of the (sorted) set remove from the (sorted) set self.

    :param self: must be a sorted set.
    :param remove: must be a sorted set.
    '''
    lib.p_indices_set_diff(cast_np_pIndices_p(self),
                           cast_np_pIndices(remove))


# // Adds an offset to each index
# void p_indices_add_offset(pIndices *self, int offset);
lib.p_indices_add_offset.argtypes = [pIndices_p,
                                     bb.c_int]


def indices_add_offset(self: np.ndarray,
                       offset: int):
    '''
    Adds an offset to each index
    '''
    lib.p_indices_add_offset(cast_np_pIndices_p(self),
                             offset)


# // Concatenates two indices together, into the new pIndices out_concatenate.
# pIndices p_indices_concatenate(pIndices a, pIndices b);
lib.p_indices_concatenate.argtypes = [pIndices,
                                      pIndices]
lib.p_indices_concatenate.restype = pIndices


def indices_concatenate(a: np.ndarray,
                        b: np.ndarray) \
        -> np.ndarray:
    '''
    Concatenates two indices together, into the new pIndices out_concatenate.

    :return: pIndices
    '''
    res = lib.p_indices_concatenate(cast_np_pIndices(a),
                                    cast_np_pIndices(b))
    return cast_pIndices_np(res)


# // Concatenates a list/vector of indices together, into the new pIndices out_concatenate.
# pIndices p_indices_concatenate_v(const pIndices *indices_list, int n);
lib.p_indices_concatenate_v.argtypes = [pIndices_p,
                                      bb.c_int]
lib.p_indices_concatenate_v.restype = pIndices


def indices_concatenate_v(indices_list: List[np.ndarray]) \
        -> np.ndarray:
    '''
    Concatenates a list/vector of indices together, into the new pIndices out_concatenate.

    :return: pIndices
    '''
    n = len(indices_list)
    LIST = pIndices * n
    list = LIST()
    for i in range(n):
        list[i] = cast_np_pIndices(indices_list[i])
    res = lib.p_indices_concatenate_v(list,
                                      n)
    return cast_pIndices_np(res)



# // Applies indices on indices, so that all not used indices are removed
# pIndices p_indices_apply_indices(pIndices self, pIndices indices);
lib.p_indices_apply_indices.argtypes = [pIndices,
                                      pIndices]
lib.p_indices_apply_indices.restype = pIndices


def indices_apply_indices(self: np.ndarray,
                        indices: np.ndarray) \
        -> np.ndarray:
    '''
    Applies indices on indices, so that all not used points are removed

    :return: pIndices
    '''
    res = lib.p_indices_apply_indices(cast_np_pIndices(self),
                                    cast_np_pIndices(indices))
    return cast_pIndices_np(res)
