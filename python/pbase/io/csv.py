import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from .. import mathctypes
from .. import bindingbase as bb
from .. import types as t
from .. import error

from .. import plib

# /** Saves an IndicesList as .csv file */
# pError p_io_save_indices_list_csv(pIndicesList list, const char *file);
plib.p_io_save_indices_list_csv.argtypes = [t.pIndicesList, bb.c_char_p]
plib.p_io_save_indices_list_csv.restype = error.pError


def save_indices_list_csv(list: t.IndicesList, file: str):
    '''
    Saves an IndicesList as .csv file
    '''
    err = plib.p_io_save_indices_list_csv(t.cast_into_pIndicesList(list), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads an IndicesList from a .csv file */
# pError p_io_load_indices_list_csv(pIndicesList *out_list, const char *file);
plib.p_io_load_indices_list_csv.argtypes = [t.pIndicesList_p, bb.c_char_p]
plib.p_io_load_indices_list_csv.restype = error.pError


def load_indices_list_csv(file: str) \
        -> t.IndicesList:
    '''
    Loads an IndicesList from a .csv file

    :returns: out_list
    '''
    out_list = t.pIndicesList()
    err = plib.p_io_load_indices_list_csv(bb.ref(out_list), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pIndicesList(out_list)


# /** Saves a Matrix as a .csv file */
# pError p_io_save_matrix_csv(pMatrix mat, const char *file);
plib.p_io_save_matrix_csv.argtypes = [t.pMatrix, bb.c_char_p]
plib.p_io_save_matrix_csv.restype = error.pError


def save_matrix_csv(mat: np.ndarray, file: str):
    '''
    Saves a Matrix as a .csv file
    '''
    err = plib.p_io_save_matrix_csv(t.cast_into_pMatrix(mat), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads a Matrix from a .csv file */
# pError p_io_load_matrix_csv(pMatrix *out_mat, const char *file);
plib.p_io_load_matrix_csv.argtypes = [t.pMatrix_p, bb.c_char_p]
plib.p_io_load_matrix_csv.restype = error.pError


def load_matrix_csv(file: str) \
        -> t.NpMatrix:
    '''
    Loads a Matrix from a .csv file

    :returns: out_mat
    '''
    out_mat = t.pMatrix()
    err = plib.p_io_load_matrix_csv(bb.ref(out_mat), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pMatrix(out_mat)


#
# wrapper
#

# /** Saves Indices as .csv file */
# pError p_io_save_indices_csv(pIndices indices, const char *file);
plib.p_io_save_indices_csv.argtypes = [t.pIndices, bb.c_char_p]
plib.p_io_save_indices_csv.restype = error.pError


def save_indices_csv(indices: np.ndarray, file: str):
    '''
    Saves Indices as .csv file
    '''
    err = plib.p_io_save_indices_csv(t.cast_into_pIndices(indices), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads Indices from a .csv file */
# pError p_io_load_indices_csv(pIndices *out_indices, const char *file);
plib.p_io_load_indices_csv.argtypes = [t.pIndices_p, bb.c_char_p]
plib.p_io_load_indices_csv.restype = error.pError


def load_indices_csv(file: str) \
        -> t.NpIndices:
    '''
    Loads Indices from a .csv file

    :returns: out_indices
    '''
    out_indices = t.pIndices()
    err = plib.p_io_load_indices_csv(bb.ref(out_indices), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pIndices(out_indices)


# /** Saves a Vector as a .csv file */
# pError p_io_save_vector_csv(pVector vec, const char *file);
plib.p_io_save_vector_csv.argtypes = [t.pVector, bb.c_char_p]
plib.p_io_save_vector_csv.restype = error.pError


def save_vector_csv(vec: np.ndarray, file: str):
    '''
    Saves a Vector as a .csv file
    '''
    err = plib.p_io_save_vector_csv(t.cast_into_pVector(vec), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads a Vector from a .csv file */
# pError p_io_load_vector_csv(pVector *out_vec, const char *file);
plib.p_io_load_vector_csv.argtypes = [t.pVector_p, bb.c_char_p]
plib.p_io_load_vector_csv.restype = error.pError


def load_vector_csv(file: str) \
        -> t.NpVector:
    '''
    Loads a Vector from a .csv file

    :returns: out_vec
    '''
    out_vec = t.pVector()
    err = plib.p_io_load_vector_csv(bb.ref(out_vec), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pVector(out_vec)
