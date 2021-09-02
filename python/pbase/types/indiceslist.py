import numpy as np
import ctypes as ct
from typing import Union, Tuple, List, Optional

from .. import mathctypes
from .. import bindingbase as bb

from .. import plib

from .indices import *


class pIndicesList(ct.Structure):
    _fields_ = [
        ('data', pIndices_p),
        ('size', bb.c_size_t)
    ]


pIndicesList_p = ct.POINTER(pIndicesList)

plib.p_indices_list_kill.argtypes = [pIndicesList_p]

class IndicesList:
    def __init__(self, indices_list):
        self._indices_list = indices_list

    def __del__(self):
        plib.p_indices_list_kill(bb.ref(self._indices_list))

    def size(self) -> int:
        return int(self._indices_list.size)

    def get(self, i: int) -> np.ndarray:
        if i < 0 or i > self._indices_list.size:
            raise IndexError('IndicesList.get out of range')
        indices = self._indices_list.list[i]
        return np.ctypeslib.as_array(indices.data, shape=(indices.size,))

    def copy_to_list(self):
        return [self.get(i).copy() for i in range(self.size())]



def cast_from_pIndicesList(data: pIndicesList) -> IndicesList:
    return IndicesList(data)


def cast_into_pIndicesList(indices_list: Union[List[np.ndarray], IndicesList]) -> pIndicesList:
    if isinstance(indices_list, IndicesList):
        return indices_list._indices_list

    LIST = (pIndices * len(indices_list))
    list = LIST()
    for i in range(len(indices_list)):
        list[i] = cast_into_pIndices(indices_list[i])
    return pIndicesList(list, len(indices_list))


def cast_into_pIndicesList_p(indices_list: Union[List[np.ndarray], IndicesList]) -> Optional[pIndicesList_p]:
    if indices_list is None:
        return None

    if isinstance(indices_list, IndicesList):
        return ct.pointer(indices_list._indices_list)

    if len(indices_list) == 0:
        return None
    return ct.pointer(cast_into_pIndicesList(indices_list))

