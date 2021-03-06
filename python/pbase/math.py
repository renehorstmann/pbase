import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from . import types as t
from . import mathctypes as mt
from . import bindingbase as bb

from . import plib

# /**
#  * Creates an orthogonal camera matrix
#  * @param near: near clipping plane
#  * @param far: far flipping plane
#  */
# mat4 p_math_camera_ortho(float left, float right,
#                          float bottom, float top,
#                          float near, float far);
plib.p_math_camera_ortho.argtypes = [bb.c_float, bb.c_float,
                                     bb.c_float, bb.c_float,
                                     bb.c_float, bb.c_float]
plib.p_math_camera_ortho.restype = mt.mat4


def camera_ortho(left: float, right: float,
                 bottom: float, top: float,
                 near: float, far: float) -> np.ndarray:
    '''
    Creates an orthogonal camera matrix

    :param near: near clipping plane
    :param far: far flipping plane
    :return: mat4
    '''
    res = plib.p_math_camera_ortho(left, right,
                                   bottom, top,
                                   near, far)
    return mt.cast_from_mat4(res)


# /**
#  * Creates a perspective (frustum) camera matrix
#  * @param near: near clipping plane
#  * @param far: far flipping plane
#  */
# mat4 p_math_camera_frustum(float left, float right,
#                            float bottom, float top,
#                            float near, float far);
plib.p_math_camera_frustum.argtypes = [bb.c_float, bb.c_float,
                                       bb.c_float, bb.c_float,
                                       bb.c_float, bb.c_float]
plib.p_math_camera_frustum.restype = mt.mat4


def camera_frustum(left: float, right: float,
                   bottom: float, top: float,
                   near: float, far: float) -> np.ndarray:
    '''
    Creates a perspective (frustum) camera matrix

    :param near: near clipping plane
    :param far: far flipping plane
    :return: mat4
    '''
    res = plib.p_math_camera_frustum(left, right,
                                     bottom, top,
                                     near, far)
    return mt.cast_from_mat4(res)


# /**
#  * Creates a perspective camera matrix.
#  * @param fovy: field of view angle [rad]
#  * @param aspect: width/height ratio
#  * @param near: near clipping plane
#  * @param far: far flipping plane
#  */
# mat4 p_math_camera_perspective(float fovy, float aspect, float near, float far);
plib.p_math_camera_perspective.argtypes = [bb.c_float, bb.c_float, bb.c_float, bb.c_float]
plib.p_math_camera_perspective.restype = mt.mat4


def camera_perspective(fovy: float, aspect: float, near: float, far: float) -> np.ndarray:
    '''
    Creates a perspective camera matrix.

    :param fovy: field of view angle [rad]
    :param aspect: width/height ratio
    :param near: near clipping plane
    :param far: far flipping plane
    :return: mat4
    '''
    res = plib.p_math_camera_perspective(fovy, aspect, near, far)
    return mt.cast_from_mat4(res)


# /**
#  * Creates the view matrix for a 3d camera.
#  * up vector must not be parallel with eye to center vector
#  */
# mat4 p_math_camera_lookat(vec3 eye, vec3 center, vec3 up);
plib.p_math_camera_lookat.argtypes = [mt.vec3,
                                      mt.vec3,
                                      mt.vec3]
plib.p_math_camera_lookat.restype = mt.mat4


def camera_lookat(eye: mt.Array,
                  center: mt.Array,
                  up: mt.Array) -> np.ndarray:
    '''
    Creates the view matrix for a 3d camera.
    up vector must not be parallel with eye to center vector

    :return: mat4
    '''
    res = plib.p_math_camera_lookat(mt.cast_array_vec3(eye),
                                    mt.cast_array_vec3(center),
                                    mt.cast_array_vec3(up))
    return mt.cast_from_mat4(res)


# // rgb[0:1] hsv[0:360, 0:1, 0:1]
# vec3 p_math_rgb2hsv(vec3 rgb);
plib.p_math_rgb2hsv.argtypes = [mt.vec3]
plib.p_math_rgb2hsv.restype = mt.vec3


def rgb2hsv(rgb: mt.Array) -> np.ndarray:
    '''
    rgb[0:1] hsv[0:360, 0:1, 0:1]

    :return: vec3
    '''
    res = plib.p_math_rgb2hsv(mt.cast_array_vec3(rgb))
    return mt.cast_from_vec3(res)


# // rgb[0:1] hsv[0:360, 0:1, 0:1]
# vec3 p_math_hsv2rgb(vec3 hsv);
plib.p_math_hsv2rgb.argtypes = [mt.vec3]
plib.p_math_hsv2rgb.restype = mt.vec3


def hsv2rgb(hsv: mt.Array) -> np.ndarray:
    '''
    rgb[0:1] hsv[0:360, 0:1, 0:1]

    :return: vec3
    '''
    res = plib.p_math_hsv2rgb(mt.cast_array_vec3(hsv))
    return mt.cast_from_vec3(res)


# /** returns false if planes are parallel */
# bool p_math_intersection_plane_plane(vec3 *out_pos, vec3 *out_dir,
#                                      vec4 plane_hessian_a, vec4 plane_hessian_b);
plib.p_math_intersection_plane_plane.argtypes = [mt.vec3_p, mt.vec3_p,
                                                 mt.vec4, mt.vec4]
plib.p_math_intersection_plane_plane.restype = bb.c_bool


def intersection_plane_plane(plane_hessian_a: mt.Array,
                             plane_hessian_b: mt.Array) \
        -> Tuple[np.ndarray, np.ndarray, bool]:
    '''
    returns false if planes are parallel

    :return: out_pos: vec3, out_dir: vec3, bool
    '''
    out_pos = mt.vec3()
    out_dir = mt.vec3()
    res = plib.p_math_intersection_plane_plane(bb.ref(out_pos),
                                               bb.ref(out_dir),
                                               mt.cast_array_vec4(plane_hessian_a),
                                               mt.cast_array_vec4(plane_hessian_b))
    return mt.cast_from_vec3(out_pos), mt.cast_from_vec3(out_dir), res


# /** returns false if plane and line are parallel */
# bool p_math_intersection_plane_line(vec3 *out_pos, vec4 plane_hessian,
#                                     vec3 line_pos, vec3 line_dir);
plib.p_math_intersection_plane_line.argtypes = [mt.vec3_p, mt.vec4,
                                                mt.vec3, mt.vec3]
plib.p_math_intersection_plane_line.restype = bb.c_bool


def intersection_plane_line(plane_hessian: mt.Array,
                            line_pos: mt.Array,
                            line_dir: mt.Array) \
        -> Tuple[np.ndarray, bool]:
    '''
    returns false if plane and line are parallel

    :return: out_pos: vec3, bool
    '''
    out_pos = mt.vec3()
    res = plib.p_math_intersection_plane_line(bb.ref(out_pos),
                                              mt.cast_array_vec4(plane_hessian),
                                              mt.cast_array_vec3(line_pos),
                                              mt.cast_array_vec3(line_dir))
    return mt.cast_from_vec3(out_pos), res


# /** returns t (line_pos + line_dir * t), or NAN if not intersecting */
# float p_math_intersection_triangle_line(vec3 v0, vec3 v1, vec3 v2,
#                                         vec3 line_pos, vec3 line_dir,
#                                         bool culling);
plib.p_math_intersection_triangle_line.argtypes = [mt.vec3, mt.vec3, mt.vec3,
                                                   mt.vec3, mt.vec3,
                                                   bb.c_bool]
plib.p_math_intersection_triangle_line.restype = bb.c_float


def intersection_triangle_line(v0: mt.Array,
                               v1: mt.Array,
                               v2: mt.Array,
                               line_pos: mt.Array,
                               line_dir: mt.Array,
                               culling: bool) \
        -> float:
    '''
    returns t (line_pos + line_dir * t), or NAN if not intersecting

    :return: float
    '''
    res = plib.p_math_intersection_triangle_line(mt.cast_array_vec3(v0),
                                                 mt.cast_array_vec3(v1),
                                                 mt.cast_array_vec3(v2),
                                                 mt.cast_array_vec3(line_pos),
                                                 mt.cast_array_vec3(line_dir),
                                                 culling)
    return res


# /** returns false if lines are parallel, searches for the nearest distance points */
# bool p_math_intersection_line_line(float *out_tau_a, float *out_tau_b,
#                                    vec3 line_a_pos, vec3 line_a_dir,
#                                    vec3 line_b_pos, vec3 line_b_dir);
plib.p_math_intersection_line_line.argtypes = [bb.c_float_p, bb.c_float_p,
                                               mt.vec3, mt.vec3,
                                               mt.vec3, mt.vec3]
plib.p_math_intersection_line_line.restype = bb.c_bool


def intersection_line_line(line_a_pos: mt.Array,
                           line_a_dir: mt.Array,
                           line_b_pos: mt.Array,
                           line_b_dir: mt.Array) \
        -> Tuple[float, float, bool]:
    '''
    returns false if lines are parallel, searches for the nearest distance points

    :return: out_tau_a: float, out_tau_b: float, bool
    '''
    out_tau_a = bb.c_float()
    out_tau_b = bb.c_float()
    res = plib.p_math_intersection_line_line(bb.ref(out_tau_a),
                                             bb.ref(out_tau_b),
                                             mt.cast_array_vec3(line_a_pos),
                                             mt.cast_array_vec3(line_a_dir),
                                             mt.cast_array_vec3(line_b_pos),
                                             mt.cast_array_vec3(line_b_dir))
    return out_tau_a.value, out_tau_b.value, res



# /** creates a rotation matrix from angle_axis as xyz = axis and w = angle [rad] */
# mat3 p_math_rotation_from_angle_axis(vec4 angle_axis);
plib.p_math_rotation_from_angle_axis.argtypes = [mt.vec4]
plib.p_math_rotation_from_angle_axis.restype = mt.mat3


def rotation_from_angle_axis(angle_axis: mt.Array) -> np.ndarray:
    '''
    creates a rotation matrix from angle_axis as xyz = axis and w = angle [rad]

    :return: mat3
    '''
    res = plib.p_math_rotation_from_angle_axis(mt.cast_array_vec4(angle_axis))
    return mt.cast_from_mat3(res)



# /** creates a rotation matrix aligned to x (or y if dir_z~=x), so that the z axis is dir_z */
# mat3 p_math_rotation_from_dir_z(vec3 dir_z);
plib.p_math_rotation_from_dir_z.argtypes = [mt.vec3]
plib.p_math_rotation_from_dir_z.restype = mt.mat3


def rotation_from_dir_z(dir_z: mt.Array) -> np.ndarray:
    '''
    creates a rotation matrix aligned to x (or y if dir_z~=x), so that the z axis is dir_z

    :return: mat3
    '''
    res = plib.p_math_rotation_from_dir_z(mt.cast_array_vec3(dir_z))
    return mt.cast_from_mat3(res)



# /** uses mat3_rotation_from_dir with ray_dir and sets the pose translation to ray_start */
# mat4 p_math_pose_from_ray(vec3 ray_start, vec3 ray_dir);
plib.p_math_pose_from_ray.argtypes = [mt.vec3, mt.vec3]
plib.p_math_pose_from_ray.restype = mt.mat4


def pose_from_ray(ray_start: mt.Array, ray_dir: mt.Array) -> np.ndarray:
    '''
    uses mat3_rotation_from_dir with ray_dir and sets the pose translation to ray_start

    :return: mat4
    '''
    res = plib.p_math_pose_from_ray(mt.cast_array_vec3(ray_start),
                                    mt.cast_array_vec3(ray_dir))
    return mt.cast_from_mat4(res)



# /** quat = [0, 0, 0, 1] */
# quat p_math_quat_eye();
plib.p_math_quat_eye.restype = mt.vec4


def quat_eye() -> np.ndarray:
    '''
    quat = [0, 0, 0, 1]

    :return: quat
    '''
    res = plib.p_math_quat_eye()
    return mt.cast_from_vec4(res)



# /** dst = -x, -y, -z, w */
# quat p_math_quat_conj(quat q);
plib.p_math_quat_conj.argtypes = [mt.vec4]
plib.p_math_quat_conj.restype = mt.vec4


def quat_conj(q: mt.Array) -> np.ndarray:
    '''
    dst = -x, -y, -z, w

    :return: quat
    '''
    res = plib.p_math_quat_conj(mt.cast_array_vec4(q))
    return mt.cast_from_vec4(res)



# /** dst = inv(quat) */
# quat p_math_quat_inv(quat q);
plib.p_math_quat_inv.argtypes = [mt.vec4]
plib.p_math_quat_inv.restype = mt.vec4


def quat_inv(q: mt.Array) -> np.ndarray:
    '''
    dst = inv(quat)

    :return: quat
    '''
    res = plib.p_math_quat_inv(mt.cast_array_vec4(q))
    return mt.cast_from_vec4(res)



# /** dst = a @ b Hamilton Product */
# quat p_math_quat_mul(quat q_a, quat q_b);
plib.p_math_quat_mul.argtypes = [mt.vec4, mt.vec4]
plib.p_math_quat_mul.restype = mt.vec4


def quat_mul(q_a: mt.Array, q_b: mt.Array) -> np.ndarray:
    '''
    dst = a @ b Hamilton Product

    :return: quat
    '''
    res = plib.p_math_quat_mul(mt.cast_array_vec4(q_a),
                               mt.cast_array_vec4(q_b))
    return mt.cast_from_vec4(res)



# /** angle_axis = xyz + w=angle in rad */
# quat p_math_quat_from_angle_axis(vec4 angle_axis);
plib.p_math_quat_from_angle_axis.argtypes = [mt.vec4]
plib.p_math_quat_from_angle_axis.restype = mt.vec4


def quat_from_angle_axis(angle_axis: mt.Array) -> np.ndarray:
    '''
    angle_axis = xyz + w=angle in rad

    :return: quat
    '''
    res = plib.p_math_quat_from_angle_axis(mt.cast_array_vec4(angle_axis))
    return mt.cast_from_vec4(res)



# /** angle_axis = xyz + w=angle in rad */
# vec4 p_math_quat_to_angle_axis(quat q);
plib.p_math_quat_to_angle_axis.argtypes = [mt.vec4]
plib.p_math_quat_to_angle_axis.restype = mt.vec4


def quat_to_angle_axis(q: mt.Array) -> np.ndarray:
    '''
    angle_axis = xyz + w=angle in rad

    :return: vec4
    '''
    res = plib.p_math_quat_to_angle_axis(mt.cast_array_vec4(q))
    return mt.cast_from_vec4(res)



# mat3 p_math_quat_to_rotation_matrix(quat q);
plib.p_math_quat_to_rotation_matrix.argtypes = [mt.vec4]
plib.p_math_quat_to_rotation_matrix.restype = mt.mat3


def quat_to_rotation_matrix(q: mt.Array) -> np.ndarray:
    '''
    :return: mat3
    '''
    res = plib.p_math_quat_to_rotation_matrix(mt.cast_array_vec4(q))
    return mt.cast_from_mat3(res)



# quat p_math_quat_from_rotation_matrix(mat3 mat);
plib.p_math_quat_from_rotation_matrix.argtypes = [mt.mat3]
plib.p_math_quat_from_rotation_matrix.restype = mt.vec4


def quat_from_rotation_matrix(mat: mt.Array) -> np.ndarray:
    '''
    :return: quat
    '''
    res = plib.p_math_quat_from_rotation_matrix(mt.cast_array_mat3(mat))
    return mt.cast_from_vec4(res)



# quat p_math_quat_slerp(quat q_a, quat q_b, float t);
plib.p_math_quat_slerp.argtypes = [mt.vec4, mt.vec4, bb.c_float]
plib.p_math_quat_slerp.restype = mt.vec4


def quat_slerp(q_a: mt.Array, q_b: mt.Array, t: float) -> np.ndarray:
    '''
    :return: quat
    '''
    res = plib.p_math_quat_slerp(mt.cast_array_vec4(q_a),
                                 mt.cast_array_vec4(q_b),
                                 t)
    return mt.cast_from_vec4(res)