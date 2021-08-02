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

vec2_p = ct.POINTER(vec3)
vec3_p = ct.POINTER(vec3)
vec4_p = ct.POINTER(vec4)

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

