import ctypes as ct
import numpy as np
from typing import Optional

class vec2(ct.Structure):
    _fields_ = [
        ('v', ct.c_float * 2)
    ]

class vec3(ct.Structure):
    _fields_ = [
        ('v', ct.c_float * 3)
    ]

class vec4(ct.Structure):
    _fields_ = [
        ('v', ct.c_float * 4)
    ]

class mat2(ct.Structure):
    _fields_ = [
        ('v', ct.c_float * (2*2))
    ]  
    
class mat3(ct.Structure):
    _fields_ = [
        ('v', ct.c_float * (3*3))
    ]
    
class mat4(ct.Structure):
    _fields_ = [
        ('v', ct.c_float * (4*4))
    ]  

class dvec2(ct.Structure):
    _fields_ = [
        ('v', ct.c_double * 2)
    ]

class dvec3(ct.Structure):
    _fields_ = [
        ('v', ct.c_double * 3)
    ]

class dvec4(ct.Structure):
    _fields_ = [
        ('v', ct.c_double * 4)
    ]

class ivec2(ct.Structure):
    _fields_ = [
        ('v', ct.c_int * 2)
    ]

class ivec3(ct.Structure):
    _fields_ = [
        ('v', ct.c_int * 3)
    ]

class ivec4(ct.Structure):
    _fields_ = [
        ('v', ct.c_int * 4)
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
ivec2_p = ct.POINTER(ivec2)
ivec3_p = ct.POINTER(ivec3)
ivec4_p = ct.POINTER(ivec4)

#
# casts
#

def cast_vec2_np(data: vec2) -> np.ndarray:
    return np.ctypeslib.as_array(data.v)

def cast_np_vec2_p(data: np.ndarray) -> vec2_p:
    if data is None:
        data = np.zeros(2, dtype=np.float32)
    else:
        if data.dtype != np.float32 or data.size < 2:
            raise RuntimeError('cast_np_vec2_p failed')
    return data.ctypes.data_as(vec2_p)

def cast_np_vec2(data: np.ndarray) -> vec2:
    return cast_np_vec2_p(data).contents

def cast_array_vec2(data) -> vec2:
    if data is None:
        data = np.zeros(2, dtype=np.float32)
    return cast_np_vec2(np.float32(data))


def cast_vec3_np(data: vec3) -> np.ndarray:
    return np.ctypeslib.as_array(data.v)

def cast_np_vec3_p(data: np.ndarray) -> vec3_p:
    if data is None:
        data = np.zeros(3, dtype=np.float32)
    else:
        if data.dtype != np.float32 or data.size < 3:
            raise RuntimeError('cast_np_vec3_p failed')
    return data.ctypes.data_as(vec3_p)

def cast_np_vec3(data: np.ndarray) -> vec3:
    return cast_np_vec3_p(data).contents

def cast_array_vec3(data) -> vec3:
    if data is None:
        data = np.zeros(3, dtype=np.float32)
    return cast_np_vec3(np.float32(data))


def cast_vec4_np(data: vec4) -> np.ndarray:
    return np.ctypeslib.as_array(data.v)

def cast_np_vec4_p(data: np.ndarray) -> vec4_p:
    if data is None:
        data = np.zeros(4, dtype=np.float32)
    else:
        if data.dtype != np.float32 or data.size < 4:
            raise RuntimeError('cast_np_vec4_p failed')
    return data.ctypes.data_as(vec4_p)

def cast_np_vec4(data: np.ndarray) -> vec4:
    return cast_np_vec4_p(data).contents

def cast_array_vec4(data) -> vec4:
    if data is None:
        data = np.zeros(4, dtype=np.float32)
    return cast_np_vec4(np.float32(data))



def cast_mat2_np(data: mat2) -> np.ndarray:
    return np.ctypeslib.as_array(data.v).reshape(2, 2)

def cast_np_mat2_p(data: np.ndarray) -> mat2_p:
    if data is None:
        data = np.zeros(4, dtype=np.float32)
    else:
        if data.dtype != np.float32:
            raise RuntimeError('cast_np_mat2_p failed, wrong type')
        if data.ndim != 2 or data.shape[0] != 2 or data.shape[1] != 2:
            raise RuntimeError('cast_np_mat2_p failed, wrong size')
        if np.isfortran(data):
            raise RuntimeError('cast_np_mat2_p failed: must be C order')
    return data.ctypes.data_as(mat2_p)

def cast_np_mat2(data: np.ndarray) -> mat2:
    return cast_np_mat2_p(data).contents

def cast_array_mat2(data) -> mat2:
    if data is None:
        data = np.zeros(4, dtype=np.float32)
    return cast_np_mat2(np.float32(data))


def cast_mat3_np(data: mat3) -> np.ndarray:
    return np.ctypeslib.as_array(data.v).reshape(3, 3)

def cast_np_mat3_p(data: np.ndarray) -> mat3_p:
    if data is None:
        data = np.zeros(3*3, dtype=np.float32)
    else:
        if data.dtype != np.float32:
            raise RuntimeError('cast_np_mat3_p failed, wrong type')
        if data.ndim != 3 or data.shape[0] != 3 or data.shape[1] != 3:
            raise RuntimeError('cast_np_mat3_p failed, wrong size')
        if np.isfortran(data):
            raise RuntimeError('cast_np_mat3_p failed: must be C order')
    return data.ctypes.data_as(mat3_p)

def cast_np_mat3(data: np.ndarray) -> mat3:
    return cast_np_mat3_p(data).contents

def cast_array_mat3(data) -> mat3:
    if data is None:
        data = np.zeros(3*3, dtype=np.float32)
    return cast_np_mat3(np.float32(data))


def cast_mat4_np(data: mat4) -> np.ndarray:
    return np.ctypeslib.as_array(data.v).reshape(4, 4)

def cast_np_mat4_p(data: np.ndarray) -> mat4_p:
    if data is None:
        data = np.zeros(4*4, dtype=np.float32)
    else:
        if data.dtype != np.float32:
            raise RuntimeError('cast_np_mat4_p failed, wrong type')
        if data.ndim != 4 or data.shape[0] != 4 or data.shape[1] != 4:
            raise RuntimeError('cast_np_mat4_p failed, wrong size')
        if np.isfortran(data):
            raise RuntimeError('cast_np_mat4_p failed: must be C order')
    return data.ctypes.data_as(mat4_p)

def cast_np_mat4(data: np.ndarray) -> mat4:
    return cast_np_mat4_p(data).contents

def cast_array_mat4(data) -> mat4:
    if data is None:
        data = np.zeros(4*4, dtype=np.float32)
    return cast_np_mat4(np.float32(data))




def cast_dvec2_np(data: dvec2) -> np.ndarray:
    return np.ctypeslib.as_array(data.v)

def cast_np_dvec2_p(data: np.ndarray) -> dvec2_p:
    if data is None:
        data = np.zeros(2, dtype=np.float64)
    else:
        if data.dtype != np.float64 or data.size < 2:
            raise RuntimeError('cast_np_dvec2_p failed')
    return data.ctypes.data_as(dvec2_p)

def cast_np_dvec2(data: np.ndarray) -> dvec2:
    return cast_np_dvec2_p(data).contents

def cast_array_dvec2(data) -> dvec2:
    if data is None:
        data = np.zeros(2, dtype=np.float64)
    return cast_np_dvec2(np.float64(data))


def cast_dvec3_np(data: dvec3) -> np.ndarray:
    return np.ctypeslib.as_array(data.v)

def cast_np_dvec3_p(data: np.ndarray) -> dvec3_p:
    if data is None:
        data = np.zeros(3, dtype=np.float64)
    else:
        if data.dtype != np.float64 or data.size < 3:
            raise RuntimeError('cast_np_dvec3_p failed')
    return data.ctypes.data_as(dvec3_p)

def cast_np_dvec3(data: np.ndarray) -> dvec3:
    return cast_np_dvec3_p(data).contents

def cast_array_dvec3(data) -> dvec3:
    if data is None:
        data = np.zeros(3, dtype=np.float64)
    return cast_np_dvec3(np.float64(data))


def cast_dvec4_np(data: dvec4) -> np.ndarray:
    return np.ctypeslib.as_array(data.v)

def cast_np_dvec4_p(data: np.ndarray) -> dvec4_p:
    if data is None:
        data = np.zeros(4, dtype=np.float64)
    else:
        if data.dtype != np.float64 or data.size < 4:
            raise RuntimeError('cast_np_dvec4_p failed')
    return data.ctypes.data_as(dvec4_p)

def cast_np_dvec4(data: np.ndarray) -> dvec4:
    return cast_np_dvec4_p(data).contents

def cast_array_dvec4(data) -> dvec4:
    if data is None:
        data = np.zeros(4, dtype=np.float64)
    return cast_np_dvec4(np.float64(data))



def cast_ivec2_np(data: ivec2) -> np.ndarray:
    return np.ctypeslib.as_array(data.v)

def cast_np_ivec2_p(data: np.ndarray) -> ivec2_p:
    if data is None:
        data = np.zeros(2, dtype=np.int32)
    else:
        if data.dtype != np.int32 or data.size < 2:
            raise RuntimeError('cast_np_ivec2_p failed')
    return data.ctypes.data_as(ivec2_p)

def cast_np_ivec2(data: np.ndarray) -> ivec2:
    return cast_np_ivec2_p(data).contents

def cast_array_ivec2(data) -> ivec2:
    if data is None:
        data = np.zeros(2, dtype=np.int32)
    return cast_np_ivec2(np.int32(data))


def cast_ivec3_np(data: ivec3) -> np.ndarray:
    return np.ctypeslib.as_array(data.v)

def cast_np_ivec3_p(data: np.ndarray) -> ivec3_p:
    if data is None:
        data = np.zeros(3, dtype=np.int32)
    else:
        if data.dtype != np.int32 or data.size < 3:
            raise RuntimeError('cast_np_ivec3_p failed')
    return data.ctypes.data_as(ivec3_p)

def cast_np_ivec3(data: np.ndarray) -> ivec3:
    return cast_np_ivec3_p(data).contents

def cast_array_ivec3(data) -> ivec3:
    if data is None:
        data = np.zeros(3, dtype=np.int32)
    return cast_np_ivec3(np.int32(data))


def cast_ivec4_np(data: ivec4) -> np.ndarray:
    return np.ctypeslib.as_array(data.v)

def cast_np_ivec4_p(data: np.ndarray) -> ivec4_p:
    if data is None:
        data = np.zeros(4, dtype=np.int32)
    else:
        if data.dtype != np.int32 or data.size < 4:
            raise RuntimeError('cast_np_ivec4_p failed')
    return data.ctypes.data_as(ivec4_p)

def cast_np_ivec4(data: np.ndarray) -> ivec4:
    return cast_np_ivec4_p(data).contents

def cast_array_ivec4(data) -> ivec4:
    if data is None:
        data = np.zeros(4, dtype=np.int32)
    return cast_np_ivec4(np.int32(data))

