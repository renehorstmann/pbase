import ctypes as ct
import numpy as np
from typing import Optional, Union

# array like type
Array = Union[np.ndarray, list, tuple]

c_float_p = ct.POINTER(ct.c_float)
c_double_p = ct.POINTER(ct.c_double)
c_int_p = ct.POINTER(ct.c_int)

# warning:
# a ct.Structure with ('v', ct.c_float * 4) fails to pass to library functions!

class vec2(ct.Structure):
    _fields_ = [
        ('v0', ct.c_float),
        ('v1', ct.c_float)
    ]

class vec3(ct.Structure):
    _fields_ = [
        ('v0', ct.c_float),
        ('v1', ct.c_float),
        ('v2', ct.c_float)
    ]

class vec4(ct.Structure):
    _fields_ = [
        ('v0', ct.c_float),
        ('v1', ct.c_float),
        ('v2', ct.c_float),
        ('v3', ct.c_float)
    ]

class mat2(ct.Structure):
    _fields_ = [
        ('v0', ct.c_float),
        ('v1', ct.c_float),
        ('v2', ct.c_float),
        ('v3', ct.c_float)
    ]
    
class mat3(ct.Structure):
    _fields_ = [
        ('v0', ct.c_float),
        ('v1', ct.c_float),
        ('v2', ct.c_float),
        ('v3', ct.c_float),
        ('v4', ct.c_float),
        ('v5', ct.c_float),
        ('v6', ct.c_float),
        ('v7', ct.c_float),
        ('v8', ct.c_float)
    ]
    
class mat4(ct.Structure):
    _fields_ = [
        ('v0', ct.c_float),
        ('v1', ct.c_float),
        ('v2', ct.c_float),
        ('v3', ct.c_float),
        ('v4', ct.c_float),
        ('v5', ct.c_float),
        ('v6', ct.c_float),
        ('v7', ct.c_float),
        ('v8', ct.c_float),
        ('v9', ct.c_float),
        ('v10', ct.c_float),
        ('v11', ct.c_float),
        ('v12', ct.c_float),
        ('v13', ct.c_float),
        ('v14', ct.c_float),
        ('v15', ct.c_float)
    ]

class dvec2(ct.Structure):
    _fields_ = [
        ('v0', ct.c_double),
        ('v1', ct.c_double)
    ]

class dvec3(ct.Structure):
    _fields_ = [
        ('v0', ct.c_double),
        ('v1', ct.c_double),
        ('v2', ct.c_double)
    ]

class dvec4(ct.Structure):
    _fields_ = [
        ('v0', ct.c_double),
        ('v1', ct.c_double),
        ('v2', ct.c_double),
        ('v3', ct.c_double)
    ]

class dmat2(ct.Structure):
    _fields_ = [
        ('v0', ct.c_double),
        ('v1', ct.c_double),
        ('v2', ct.c_double),
        ('v3', ct.c_double)
    ]

class dmat3(ct.Structure):
    _fields_ = [
        ('v0', ct.c_double),
        ('v1', ct.c_double),
        ('v2', ct.c_double),
        ('v3', ct.c_double),
        ('v4', ct.c_double),
        ('v5', ct.c_double),
        ('v6', ct.c_double),
        ('v7', ct.c_double),
        ('v8', ct.c_double)
    ]

class dmat4(ct.Structure):
    _fields_ = [
        ('v0', ct.c_double),
        ('v1', ct.c_double),
        ('v2', ct.c_double),
        ('v3', ct.c_double),
        ('v4', ct.c_double),
        ('v5', ct.c_double),
        ('v6', ct.c_double),
        ('v7', ct.c_double),
        ('v8', ct.c_double),
        ('v9', ct.c_double),
        ('v10', ct.c_double),
        ('v11', ct.c_double),
        ('v12', ct.c_double),
        ('v13', ct.c_double),
        ('v14', ct.c_double),
        ('v15', ct.c_double)
    ]

class ivec2(ct.Structure):
    _fields_ = [
        ('v0', ct.c_int),
        ('v1', ct.c_int)
    ]

class ivec3(ct.Structure):
    _fields_ = [
        ('v0', ct.c_int),
        ('v1', ct.c_int),
        ('v2', ct.c_int)
    ]

class ivec4(ct.Structure):
    _fields_ = [
        ('v0', ct.c_int),
        ('v1', ct.c_int),
        ('v2', ct.c_int),
        ('v3', ct.c_int)
    ]

vec2_p = ct.POINTER(vec2)
vec3_p = ct.POINTER(vec3)
vec4_p = ct.POINTER(vec4)
mat2_p = ct.POINTER(mat2)
mat3_p = ct.POINTER(mat3)
mat4_p = ct.POINTER(mat4)
dvec2_p = ct.POINTER(dvec2)
dvec3_p = ct.POINTER(dvec3)
dvec4_p = ct.POINTER(dvec4)
dmat2_p = ct.POINTER(dmat2)
dmat3_p = ct.POINTER(dmat3)
dmat4_p = ct.POINTER(dmat4)
ivec2_p = ct.POINTER(ivec2)
ivec3_p = ct.POINTER(ivec3)
ivec4_p = ct.POINTER(ivec4)

#
# casts
#

def cast_from_vec2(data: vec2) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_float_p), shape=(2,))

def cast_into_vec2_p(data: np.ndarray) -> vec2_p:
    if data is None:
        data = np.zeros(2, dtype=np.float32)
    else:
        if data.dtype != np.float32 or data.size < 2:
            raise RuntimeError('cast_into_vec2_p failed')
    return data.ctypes.data_as(vec2_p)

def cast_into_vec2(data: np.ndarray) -> vec2:
    return cast_into_vec2_p(data).contents

def cast_array_vec2(data) -> vec2:
    if data is None:
        data = np.zeros(2, dtype=np.float32)
    return cast_into_vec2(np.float32(data))


def cast_from_vec3(data: vec3) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_float_p), shape=(3,))

def cast_into_vec3_p(data: np.ndarray) -> vec3_p:
    if data is None:
        data = np.zeros(3, dtype=np.float32)
    else:
        if data.dtype != np.float32 or data.size < 3:
            raise RuntimeError('cast_into_vec3_p failed')
    return data.ctypes.data_as(vec3_p)

def cast_into_vec3(data: np.ndarray) -> vec3:
    return cast_into_vec3_p(data).contents

def cast_array_vec3(data) -> vec3:
    if data is None:
        data = np.zeros(3, dtype=np.float32)
    return cast_into_vec3(np.float32(data))


def cast_from_vec4(data: vec4) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_float_p), shape=(4,))

def cast_into_vec4_p(data: np.ndarray) -> vec4_p:
    if data is None:
        data = np.zeros(4, dtype=np.float32)
    else:
        if data.dtype != np.float32 or data.size < 4:
            raise RuntimeError('cast_into_vec4_p failed')
    return data.ctypes.data_as(vec4_p)

def cast_into_vec4(data: np.ndarray) -> vec4:
    return cast_into_vec4_p(data).contents

def cast_array_vec4(data) -> vec4:
    if data is None:
        data = np.zeros(4, dtype=np.float32)
    return cast_into_vec4(np.float32(data))



def cast_from_mat2(data: mat2) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_float_p), shape=(2, 2))

def cast_into_mat2_p(data: np.ndarray) -> mat2_p:
    if data is None:
        data = np.zeros(4, dtype=np.float32)
    else:
        if data.dtype != np.float32:
            raise RuntimeError('cast_into_mat2_p failed, wrong type')
        if data.ndim != 2 or data.shape[0] != 2 or data.shape[1] != 2:
            raise RuntimeError('cast_into_mat2_p failed, wrong size')
        if np.isfortran(data):
            raise RuntimeError('cast_into_mat2_p failed: must be C order')
    return data.ctypes.data_as(mat2_p)

def cast_into_mat2(data: np.ndarray) -> mat2:
    return cast_into_mat2_p(data).contents

def cast_array_mat2(data) -> mat2:
    if data is None:
        data = np.zeros(4, dtype=np.float32)
    return cast_into_mat2(np.float32(data))


def cast_from_mat3(data: mat3) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_float_p), shape=(3, 3))

def cast_into_mat3_p(data: np.ndarray) -> mat3_p:
    if data is None:
        data = np.zeros(3*3, dtype=np.float32)
    else:
        if data.dtype != np.float32:
            raise RuntimeError('cast_into_mat3_p failed, wrong type')
        if data.ndim != 2 or data.shape[0] != 3 or data.shape[1] != 3:
            raise RuntimeError('cast_into_mat3_p failed, wrong size')
        if np.isfortran(data):
            raise RuntimeError('cast_into_mat3_p failed: must be C order')
    return data.ctypes.data_as(mat3_p)

def cast_into_mat3(data: np.ndarray) -> mat3:
    return cast_into_mat3_p(data).contents

def cast_array_mat3(data) -> mat3:
    if data is None:
        data = np.zeros(3*3, dtype=np.float32).reshape(3, 3)
    return cast_into_mat3(np.float32(data))


def cast_from_mat4(data: mat4) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_float_p), shape=(4, 4))

def cast_into_mat4_p(data: np.ndarray) -> mat4_p:
    if data is None:
        data = np.zeros(4*4, dtype=np.float32)
    else:
        if data.dtype != np.float32:
            raise RuntimeError('cast_into_mat4_p failed, wrong type')
        if data.ndim != 2 or data.shape[0] != 4 or data.shape[1] != 4:
            raise RuntimeError('cast_into_mat4_p failed, wrong size')
        if np.isfortran(data):
            raise RuntimeError('cast_into_mat4_p failed: must be C order')
    return data.ctypes.data_as(mat4_p)

def cast_into_mat4(data: np.ndarray) -> mat4:
    return cast_into_mat4_p(data).contents

def cast_array_mat4(data) -> mat4:
    if data is None:
        data = np.zeros(4*4, dtype=np.float32).reshape(4, 4)
    return cast_into_mat4(np.float32(data))




def cast_from_dvec2(data: dvec2) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_double_p), shape=(2,))

def cast_into_dvec2_p(data: np.ndarray) -> dvec2_p:
    if data is None:
        data = np.zeros(2, dtype=np.float64)
    else:
        if data.dtype != np.float64 or data.size < 2:
            raise RuntimeError('cast_into_dvec2_p failed')
    return data.ctypes.data_as(dvec2_p)

def cast_into_dvec2(data: np.ndarray) -> dvec2:
    return cast_into_dvec2_p(data).contents

def cast_array_dvec2(data) -> dvec2:
    if data is None:
        data = np.zeros(2, dtype=np.float64)
    return cast_into_dvec2(np.float64(data))


def cast_from_dvec3(data: dvec3) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_double_p), shape=(3,))

def cast_into_dvec3_p(data: np.ndarray) -> dvec3_p:
    if data is None:
        data = np.zeros(3, dtype=np.float64)
    else:
        if data.dtype != np.float64 or data.size < 3:
            raise RuntimeError('cast_into_dvec3_p failed')
    return data.ctypes.data_as(dvec3_p)

def cast_into_dvec3(data: np.ndarray) -> dvec3:
    return cast_into_dvec3_p(data).contents

def cast_array_dvec3(data) -> dvec3:
    if data is None:
        data = np.zeros(3, dtype=np.float64)
    return cast_into_dvec3(np.float64(data))


def cast_from_dvec4(data: dvec4) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_double_p), shape=(4,))

def cast_into_dvec4_p(data: np.ndarray) -> dvec4_p:
    if data is None:
        data = np.zeros(4, dtype=np.float64)
    else:
        if data.dtype != np.float64 or data.size < 4:
            raise RuntimeError('cast_into_dvec4_p failed')
    return data.ctypes.data_as(dvec4_p)

def cast_into_dvec4(data: np.ndarray) -> dvec4:
    return cast_into_dvec4_p(data).contents

def cast_array_dvec4(data) -> dvec4:
    if data is None:
        data = np.zeros(4, dtype=np.float64)
    return cast_into_dvec4(np.float64(data))


def cast_from_dmat2(data: dmat2) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_double_p), shape=(2, 2))

def cast_into_dmat2_p(data: np.ndarray) -> dmat2_p:
    if data is None:
        data = np.zeros(4, dtype=np.float64)
    else:
        if data.dtype != np.float64:
            raise RuntimeError('cast_into_dmat2_p failed, wrong type')
        if data.ndim != 2 or data.shape[0] != 2 or data.shape[1] != 2:
            raise RuntimeError('cast_into_dmat2_p failed, wrong size')
        if np.isfortran(data):
            raise RuntimeError('cast_into_dmat2_p failed: must be C order')
    return data.ctypes.data_as(dmat2_p)

def cast_into_dmat2(data: np.ndarray) -> dmat2:
    return cast_into_dmat2_p(data).contents

def cast_array_dmat2(data) -> dmat2:
    if data is None:
        data = np.zeros(4, dtype=np.float64)
    return cast_into_dmat2(np.float64(data))


def cast_from_dmat3(data: dmat3) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_double_p), shape=(3, 3))

def cast_into_dmat3_p(data: np.ndarray) -> dmat3_p:
    if data is None:
        data = np.zeros(3*3, dtype=np.float64)
    else:
        if data.dtype != np.float64:
            raise RuntimeError('cast_into_dmat3_p failed, wrong type')
        if data.ndim != 2 or data.shape[0] != 3 or data.shape[1] != 3:
            raise RuntimeError('cast_into_dmat3_p failed, wrong size')
        if np.isfortran(data):
            raise RuntimeError('cast_into_dmat3_p failed: must be C order')
    return data.ctypes.data_as(dmat3_p)

def cast_into_dmat3(data: np.ndarray) -> dmat3:
    return cast_into_dmat3_p(data).contents

def cast_array_dmat3(data) -> dmat3:
    if data is None:
        data = np.zeros(3*3, dtype=np.float64).reshape(3, 3)
    return cast_into_dmat3(np.float64(data))


def cast_from_dmat4(data: dmat4) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_double_p), shape=(4, 4))

def cast_into_dmat4_p(data: np.ndarray) -> dmat4_p:
    if data is None:
        data = np.zeros(4*4, dtype=np.float64)
    else:
        if data.dtype != np.float64:
            raise RuntimeError('cast_into_dmat4_p failed, wrong type')
        if data.ndim != 2 or data.shape[0] != 4 or data.shape[1] != 4:
            raise RuntimeError('cast_into_dmat4_p failed, wrong size')
        if np.isfortran(data):
            raise RuntimeError('cast_into_dmat4_p failed: must be C order')
    return data.ctypes.data_as(dmat4_p)

def cast_into_dmat4(data: np.ndarray) -> dmat4:
    return cast_into_dmat4_p(data).contents

def cast_array_dmat4(data) -> dmat4:
    if data is None:
        data = np.zeros(4*4, dtype=np.float64).reshape(4, 4)
    return cast_into_dmat4(np.float64(data))



def cast_from_ivec2(data: ivec2) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_int_p), shape=(2,))

def cast_into_ivec2_p(data: np.ndarray) -> ivec2_p:
    if data is None:
        data = np.zeros(2, dtype=np.int32)
    else:
        if data.dtype != np.int32 or data.size < 2:
            raise RuntimeError('cast_into_ivec2_p failed')
    return data.ctypes.data_as(ivec2_p)

def cast_into_ivec2(data: np.ndarray) -> ivec2:
    return cast_into_ivec2_p(data).contents

def cast_array_ivec2(data) -> ivec2:
    if data is None:
        data = np.zeros(2, dtype=np.int32)
    return cast_into_ivec2(np.int32(data))


def cast_from_ivec3(data: ivec3) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_int_p), shape=(3,))

def cast_into_ivec3_p(data: np.ndarray) -> ivec3_p:
    if data is None:
        data = np.zeros(3, dtype=np.int32)
    else:
        if data.dtype != np.int32 or data.size < 3:
            raise RuntimeError('cast_into_ivec3_p failed')
    return data.ctypes.data_as(ivec3_p)

def cast_into_ivec3(data: np.ndarray) -> ivec3:
    return cast_into_ivec3_p(data).contents

def cast_array_ivec3(data) -> ivec3:
    if data is None:
        data = np.zeros(3, dtype=np.int32)
    return cast_into_ivec3(np.int32(data))


def cast_from_ivec4(data: ivec4) -> np.ndarray:
    return np.ctypeslib.as_array(ct.cast(ct.pointer(data), c_int_p), shape=(4,))

def cast_into_ivec4_p(data: np.ndarray) -> ivec4_p:
    if data is None:
        data = np.zeros(4, dtype=np.int32)
    else:
        if data.dtype != np.int32 or data.size < 4:
            raise RuntimeError('cast_into_ivec4_p failed')
    return data.ctypes.data_as(ivec4_p)

def cast_into_ivec4(data: np.ndarray) -> ivec4:
    return cast_into_ivec4_p(data).contents

def cast_array_ivec4(data) -> ivec4:
    if data is None:
        data = np.zeros(4, dtype=np.int32)
    return cast_into_ivec4(np.int32(data))

