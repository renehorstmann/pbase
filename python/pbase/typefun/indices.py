import numpy as np
from typing import Tuple, List, Optional

from .. import mathc
from .. import types

from .. import lib

# // Prints all indices to stdout
# void p_indices_print(pIndices self);
lib.p_indices_print.argtypes = [types.pIndices]


def indices_print(self: np.ndarray):
    '''
    Prints all indices to stdout
    '''
    lib.p_indices_print(types.cast_np_pIndices(self))


# // Sorts the internal indices list in ascending order
# void p_indices_sort(pIndices *self);
lib.p_indices_sort.argtypes = [types.pIndices_p]


def indices_sort(self: np.ndarray):
    '''
    Sorts the internal indices list in ascending order
    '''
    lib.p_indices_sort(types.cast_np_pIndices_p(self))


# // Deletes all duplicate indices (result will be sorted)
# void p_indices_as_set(pIndices *self);
lib.p_indices_as_set.argtypes = [types.pIndices_p]


def indices_as_set(self: np.ndarray):
    '''
    Deletes all duplicate indices (result will be sorted)
    '''
    lib.p_indices_as_set(types.cast_np_pIndices_p(self))


# /**
#  * Removes all indices of the (sorted) set remove from the (sorted) set self.
#  * @param self: must be a sorted set.
#  * @param remove: must be a sorted set.
#  */
# void p_indices_set_diff(pIndices *self, pIndices remove);
lib.p_indices_set_diff.argtypes = [types.pIndices_p,
                                   types.pIndices]


def indices_set_diff(self: np.ndarray,
                     remove: np.ndarray):
    '''
    Removes all indices of the (sorted) set remove from the (sorted) set self.

    :param self: must be a sorted set.
    :param remove: must be a sorted set.
    '''
    lib.p_indices_set_diff(types.cast_np_pIndices_p(self),
                           types.cast_np_pIndices(remove))


# // Adds an offset to each index
# void p_indices_add_offset(pIndices *self, int offset);
lib.p_indices_add_offset.argtypes = [types.pIndices_p,
                                     types.c_int]


def indices_add_offset(self: np.ndarray,
                       offset: int):
    '''
    Adds an offset to each index
    '''
    lib.p_indices_add_offset(types.cast_np_pIndices_p(self),
                             offset)


# // Concatenates two indices together, into the new pIndices out_concatenate.
# pIndices p_indices_concatenate(pIndices a, pIndices b);
lib.p_indices_concatenate.argtypes = [types.pIndices,
                                      types.pIndices]
lib.p_indices_concatenate.restype = types.pIndices


def indices_concatenate(a: np.ndarray,
                        b: np.ndarray) \
        -> np.ndarray:
    '''
    Concatenates two indices together, into the new pIndices out_concatenate.

    :return: pIndices
    '''
    res = lib.p_indices_concatenate(types.cast_np_pIndices(a),
                                    types.cast_np_pIndices(b))
    return types.cast_pIndices_np(res)


# // Concatenates a list/vector of indices together, into the new pIndices out_concatenate.
# pIndices p_indices_concatenate_v(const pIndices *indices_list, int n);
lib.p_indices_concatenate_v.argtypes = [types.pIndices_p,
                                      types.c_int]
lib.p_indices_concatenate_v.restype = types.pIndices


def indices_concatenate_v(indices_list: List[np.ndarray]) \
        -> np.ndarray:
    '''
    Concatenates a list/vector of indices together, into the new pIndices out_concatenate.

    :return: pIndices
    '''
    n = len(indices_list)
    LIST = types.pIndices * n
    list = LIST()
    for i in range(n):
        list[i] = types.cast_np_pIndices(indices_list[i])
    res = lib.p_indices_concatenate_v(list,
                                      n)
    return types.cast_pIndices_np(res)



# // Applies indices on indices, so that all not used indices are removed
# pIndices p_indices_apply_indices(pIndices self, pIndices indices);
lib.p_indices_apply_indices.argtypes = [types.pIndices,
                                      types.pIndices]
lib.p_indices_apply_indices.restype = types.pIndices


def indices_apply_indices(self: np.ndarray,
                        indices: np.ndarray) \
        -> np.ndarray:
    '''
    Applies indices on indices, so that all not used points are removed

    :return: pIndices
    '''
    res = lib.p_indices_apply_indices(types.cast_np_pIndices(self),
                                    types.cast_np_pIndices(indices))
    return types.cast_pIndices_np(res)
