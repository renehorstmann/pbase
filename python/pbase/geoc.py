import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from . import mathc
from . import bindingbase as bb

from . import plib

# /**
#  * Creates an orthogonal camera matrix
#  * @param near: near clipping plane
#  * @param far: far flipping plane
#  */
# mat4 p_geoc_camera_ortho(float left, float right,
#                          float bottom, float top,
#                          float near, float far);
plib.p_geoc_camera_ortho.argtypes = [bb.c_float, bb.c_float,
                                     bb.c_float, bb.c_float,
                                     bb.c_float, bb.c_float]
plib.p_geoc_camera_ortho.restype = mathc.mat4


def camera_ortho(left: float, right: float,
                 bottom: float, top: float,
                 near: float, far: float) -> np.ndarray:
    '''
    Creates an orthogonal camera matrix

    :param near: near clipping plane
    :param far: far flipping plane
    :return: mat4
    '''
    res = plib.p_geoc_camera_ortho(left, right,
                                   bottom, top,
                                   near, far)
    return mathc.cast_mat4_np(res)


# /**
#  * Creates a perspective (frustum) camera matrix
#  * @param near: near clipping plane
#  * @param far: far flipping plane
#  */
# mat4 p_geoc_camera_frustum(float left, float right,
#                            float bottom, float top,
#                            float near, float far);
plib.p_geoc_camera_frustum.argtypes = [bb.c_float, bb.c_float,
                                       bb.c_float, bb.c_float,
                                       bb.c_float, bb.c_float]
plib.p_geoc_camera_frustum.restype = mathc.mat4


def camera_frustum(left: float, right: float,
                   bottom: float, top: float,
                   near: float, far: float) -> np.ndarray:
    '''
    Creates a perspective (frustum) camera matrix

    :param near: near clipping plane
    :param far: far flipping plane
    :return: mat4
    '''
    res = plib.p_geoc_camera_frustum(left, right,
                                     bottom, top,
                                     near, far)
    return mathc.cast_mat4_np(res)


# /**
#  * Creates a perspective camera matrix.
#  * @param fovy: field of view angle [rad]
#  * @param aspect: width/height ratio
#  * @param near: near clipping plane
#  * @param far: far flipping plane
#  */
# mat4 p_geoc_camera_perspective(float fovy, float aspect, float near, float far);
plib.p_geoc_camera_perspective.argtypes = [bb.c_float, bb.c_float, bb.c_float, bb.c_float]
plib.p_geoc_camera_perspective.restype = mathc.mat4


def camera_perspective(fovy: float, aspect: float, near: float, far: float) -> np.ndarray:
    '''
    Creates a perspective camera matrix.

    :param fovy: field of view angle [rad]
    :param aspect: width/height ratio
    :param near: near clipping plane
    :param far: far flipping plane
    :return: mat4
    '''
    res = plib.p_geoc_camera_perspective(fovy, aspect, near, far)
    return mathc.cast_mat4_np(res)


# /**
#  * Creates the view matrix for a 3d camera.
#  * up vector must not be parallel with eye to center vector
#  */
# mat4 p_geoc_camera_lookat(vec3 eye, vec3 center, vec3 up);
plib.p_geoc_camera_lookat.argtypes = [mathc.vec3,
                                      mathc.vec3,
                                      mathc.vec3]
plib.p_geoc_camera_lookat.restype = mathc.mat4


def camera_lookat(eye: np.ndarray,
                  center: np.ndarray,
                  up: np.ndarray) -> np.ndarray:
    '''
    Creates the view matrix for a 3d camera.
    up vector must not be parallel with eye to center vector

    :return: mat4
    '''
    res = plib.p_geoc_camera_lookat(mathc.cast_np_vec3(eye),
                                    mathc.cast_np_vec3(center),
                                    mathc.cast_np_vec3(up))
    return mathc.cast_mat4_np(res)
