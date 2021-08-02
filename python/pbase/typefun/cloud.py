import numpy as np
from typing import Tuple, List, Optional

from .. import mathc
from .. import types

from .. import lib

# // Prints the whole cloud data to stdout
# void p_cloud_print(pCloud self);
lib.p_cloud_print.argtypes = [types.pCloud]


def cloud_print(self: np.ndarray):
    '''
    Prints the whole cloud data to stdout
    '''
    lib.p_cloud_print(types.cast_np_pCloud(self))


# // Concatenates two point clouds together
# pCloud p_cloud_concatenate(pCloud a, pCloud b);
lib.p_cloud_concatenate.argtypes = [types.pCloud,
                                    types.pCloud]
lib.p_cloud_concatenate.restype = types.pCloud


def cloud_concatenate(a: np.ndarray,
                      b: np.ndarray) \
        -> np.ndarray:
    '''
    Concatenates two point clouds together
    
    :return: pCloud
    '''
    res = lib.p_cloud_concatenate(types.cast_np_pCloud(a),
                                  types.cast_np_pCloud(b))
    return types.cast_pCloud_np(res)


# // Concatenates a list/vector of point clouds together
# pCloud p_cloud_concatenate_v(const pCloud *cloud_list, int n);
lib.p_cloud_concatenate_v.argtypes = [types.pCloud_p,
                                      types.c_int]
lib.p_cloud_concatenate_v.restype = types.pCloud


def cloud_concatenate_v(cloud_list: List[np.ndarray]) \
        -> np.ndarray:
    '''
    Concatenates a list/vector of point clouds together
    
    :return: pCloud
    '''
    n = len(cloud_list)
    LIST = types.pCloud * n
    list = LIST()
    for i in range(n):
        list[i] = types.cast_np_pCloud(cloud_list[i])

    res = lib.p_cloud_concatenate_v(list,
                                    n)
    return types.cast_pCloud_np(res)


# // Applies indices on cloud, so that all not used points are removed
# pCloud p_cloud_apply_indices(pCloud cloud, pIndices indices);
lib.p_cloud_apply_indices.argtypes = [types.pCloud,
                                      types.pIndices]
lib.p_cloud_apply_indices.restype = types.pCloud


def cloud_apply_indices(self: np.ndarray,
                        indices: np.ndarray) \
        -> np.ndarray:
    '''
    Applies indices on cloud, so that all not used points are removed

    :return: pCloud
    '''
    res = lib.p_cloud_apply_indices(types.cast_np_pCloud(self),
                                    types.cast_np_pIndices(indices))
    return types.cast_pCloud_np(res)
