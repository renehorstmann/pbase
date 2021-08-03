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


def camera_lookat(eye: mathc.Array,
                  center: mathc.Array,
                  up: mathc.Array) -> np.ndarray:
    '''
    Creates the view matrix for a 3d camera.
    up vector must not be parallel with eye to center vector

    :return: mat4
    '''
    res = plib.p_geoc_camera_lookat(mathc.cast_array_vec3(eye),
                                    mathc.cast_array_vec3(center),
                                    mathc.cast_array_vec3(up))
    return mathc.cast_mat4_np(res)


# // rgb[0:1] hsv[0:360, 0:1, 0:1]
# vec3 p_geoc_rgb2hsv(vec3 rgb);
plib.p_geoc_rgb2hsv.argtypes = [mathc.vec3]
plib.p_geoc_rgb2hsv.restype = mathc.vec3


def rgb2hsv(rgb: mathc.Array) -> np.ndarray:
    '''
    rgb[0:1] hsv[0:360, 0:1, 0:1]

    :return: vec3
    '''
    res = plib.p_geoc_rgb2hsv(mathc.cast_array_vec3(rgb))
    return mathc.cast_vec3_np(res)


# // rgb[0:1] hsv[0:360, 0:1, 0:1]
# vec3 p_geoc_hsv2rgb(vec3 hsv);
plib.p_geoc_hsv2rgb.argtypes = [mathc.vec3]
plib.p_geoc_hsv2rgb.restype = mathc.vec3


def hsv2rgb(hsv: mathc.Array) -> np.ndarray:
    '''
    rgb[0:1] hsv[0:360, 0:1, 0:1]

    :return: vec3
    '''
    res = plib.p_geoc_hsv2rgb(mathc.cast_array_vec3(hsv))
    return mathc.cast_vec3_np(res)


# /** returns false if planes are parallel */
# bool p_geoc_intersection_plane_plane(vec3 *out_pos, vec3 *out_dir,
#                                      vec4 plane_hessian_a, vec4 plane_hessian_b);
plib.p_geoc_intersection_plane_plane.argtypes = [mathc.vec3_p, mathc.vec3_p,
                                                 mathc.vec4, mathc.vec4]
plib.p_geoc_intersection_plane_plane.restype = bb.c_bool


def intersection_plane_plane(plane_hessian_a: mathc.Array,
                             plane_hessian_b: mathc.Array) \
        -> Tuple[np.ndarray, np.ndarray, bool]:
    '''
    returns false if planes are parallel

    :return: out_pos: vec3, out_dir: vec3, bool
    '''
    out_pos = mathc.vec3()
    out_dir = mathc.vec3()
    res = plib.p_geoc_intersection_plane_plane(bb.ref(out_pos),
                                               bb.ref(out_dir),
                                               mathc.cast_array_vec4(plane_hessian_a),
                                               mathc.cast_array_vec4(plane_hessian_b))
    return mathc.cast_vec3_np(out_pos), mathc.cast_vec3_np(out_dir), res


# /** returns false if plane and line are parallel */
# bool p_geoc_intersection_plane_line(vec3 *out_pos, vec4 plane_hessian,
#                                     vec3 line_pos, vec3 line_dir);
plib.p_geoc_intersection_plane_line.argtypes = [mathc.vec3_p, mathc.vec4,
                                                mathc.vec3, mathc.vec3]
plib.p_geoc_intersection_plane_line.restype = bb.c_bool


def intersection_plane_line(plane_hessian: mathc.Array,
                            line_pos: mathc.Array,
                            line_dir: mathc.Array) \
        -> Tuple[np.ndarray, bool]:
    '''
    returns false if plane and line are parallel

    :return: out_pos: vec3, bool
    '''
    out_pos = mathc.vec3()
    res = plib.p_geoc_intersection_plane_line(bb.ref(out_pos),
                                              mathc.cast_array_vec4(plane_hessian),
                                              mathc.cast_array_vec3(line_pos),
                                              mathc.cast_array_vec3(line_dir))
    return mathc.cast_vec3_np(out_pos), res


# /** returns t (line_pos + line_dir * t), or NAN if not intersecting */
# float p_geoc_intersection_triangle_line(vec3 v0, vec3 v1, vec3 v2,
#                                         vec3 line_pos, vec3 line_dir,
#                                         bool culling);
plib.p_geoc_intersection_triangle_line.argtypes = [mathc.vec3, mathc.vec3, mathc.vec3,
                                                   mathc.vec3, mathc.vec3,
                                                   bb.c_bool]
plib.p_geoc_intersection_triangle_line.restype = bb.c_float


def intersection_triangle_line(v0: mathc.Array,
                               v1: mathc.Array,
                               v2: mathc.Array,
                               line_pos: mathc.Array,
                               line_dir: mathc.Array,
                               culling: bool) \
        -> float:
    '''
    returns t (line_pos + line_dir * t), or NAN if not intersecting

    :return: float
    '''
    res = plib.p_geoc_intersection_triangle_line(mathc.cast_array_vec3(v0),
                                                 mathc.cast_array_vec3(v1),
                                                 mathc.cast_array_vec3(v2),
                                                 mathc.cast_array_vec3(line_pos),
                                                 mathc.cast_array_vec3(line_dir),
                                                 culling)
    return res


# /** returns false if lines are parallel, searches for the nearest distance points */
# bool p_geoc_intersection_line_line(float *out_tau_a, float *out_tau_b,
#                                    vec3 line_a_pos, vec3 line_a_dir,
#                                    vec3 line_b_pos, vec3 line_b_dir);
plib.p_geoc_intersection_line_line.argtypes = [bb.c_float_p, bb.c_float_p,
                                               mathc.vec3, mathc.vec3,
                                               mathc.vec3, mathc.vec3]
plib.p_geoc_intersection_line_line.restype = bb.c_bool


def intersection_line_line(line_a_pos: mathc.Array,
                           line_a_dir: mathc.Array,
                           line_b_pos: mathc.Array,
                           line_b_dir: mathc.Array) \
        -> Tuple[float, float, bool]:
    '''
    returns false if lines are parallel, searches for the nearest distance points

    :return: out_tau_a: float, out_tau_b: float, bool
    '''
    out_tau_a = bb.c_float()
    out_tau_b = bb.c_float()
    res = plib.p_geoc_intersection_line_line(bb.ref(out_tau_a),
                                             bb.ref(out_tau_b),
                                             mathc.cast_array_vec3(line_a_pos),
                                             mathc.cast_array_vec3(line_a_dir),
                                             mathc.cast_array_vec3(line_b_pos),
                                             mathc.cast_array_vec3(line_b_dir))
    return out_tau_a.value, out_tau_b.value, res



# /** creates a rotation matrix from angle_axis as xyz = axis and w = angle [rad] */
# mat3 p_geoc_rotation_from_angle_axis(vec4 angle_axis);
plib.p_geoc_rotation_from_angle_axis.argtypes = [mathc.vec4]
plib.p_geoc_rotation_from_angle_axis.restype = mathc.mat3


def rotation_from_angle_axis(angle_axis: mathc.Array) -> np.ndarray:
    '''
    creates a rotation matrix from angle_axis as xyz = axis and w = angle [rad]

    :return: mat3
    '''
    res = plib.p_geoc_rotation_from_angle_axis(mathc.cast_array_vec4(angle_axis))
    return mathc.cast_mat3_np(res)



# /** creates a rotation matrix aligned to x (or y if dir_z~=x), so that the z axis is dir_z */
# mat3 p_geoc_rotation_from_dir_z(vec3 dir_z);
plib.p_geoc_rotation_from_dir_z.argtypes = [mathc.vec3]
plib.p_geoc_rotation_from_dir_z.restype = mathc.mat3


def rotation_from_dir_z(dir_z: mathc.Array) -> np.ndarray:
    '''
    creates a rotation matrix aligned to x (or y if dir_z~=x), so that the z axis is dir_z

    :return: mat3
    '''
    res = plib.p_geoc_rotation_from_dir_z(mathc.cast_array_vec3(dir_z))
    return mathc.cast_mat3_np(res)



# /** uses mat3_rotation_from_dir with ray_dir and sets the pose translation to ray_start */
# mat4 p_geoc_pose_from_ray(vec3 ray_start, vec3 ray_dir);
plib.p_geoc_pose_from_ray.argtypes = [mathc.vec3, mathc.vec3]
plib.p_geoc_pose_from_ray.restype = mathc.mat4


def pose_from_ray(ray_start: mathc.Array, ray_dir: mathc.Array) -> np.ndarray:
    '''
    uses mat3_rotation_from_dir with ray_dir and sets the pose translation to ray_start

    :return: mat4
    '''
    res = plib.p_geoc_pose_from_ray(mathc.cast_array_vec3(ray_start),
                                    mathc.cast_array_vec3(ray_dir))
    return mathc.cast_mat4_np(res)



# /** quat = [0, 0, 0, 1] */
# quat p_geoc_quat_eye();
plib.p_geoc_quat_eye.restype = mathc.vec4


def quat_eye() -> np.ndarray:
    '''
    quat = [0, 0, 0, 1]

    :return: quat
    '''
    res = plib.p_geoc_quat_eye()
    return mathc.cast_vec4_np(res)



# /** dst = -x, -y, -z, w */
# quat p_geoc_quat_conj(quat q);
plib.p_geoc_quat_conj.argtypes = [mathc.vec4]
plib.p_geoc_quat_conj.restype = mathc.vec4


def quat_conj(q: mathc.Array) -> np.ndarray:
    '''
    dst = -x, -y, -z, w

    :return: quat
    '''
    res = plib.p_geoc_quat_conj(mathc.cast_array_vec4(q))
    return mathc.cast_vec4_np(res)



# /** dst = inv(quat) */
# quat p_geoc_quat_inv(quat q);
plib.p_geoc_quat_inv.argtypes = [mathc.vec4]
plib.p_geoc_quat_inv.restype = mathc.vec4


def quat_inv(q: mathc.Array) -> np.ndarray:
    '''
    dst = inv(quat)

    :return: quat
    '''
    res = plib.p_geoc_quat_inv(mathc.cast_array_vec4(q))
    return mathc.cast_vec4_np(res)



# /** dst = a @ b Hamilton Product */
# quat p_geoc_quat_mul(quat q_a, quat q_b);
plib.p_geoc_quat_mul.argtypes = [mathc.vec4, mathc.vec4]
plib.p_geoc_quat_mul.restype = mathc.vec4


def quat_mul(q_a: mathc.Array, q_b: mathc.Array) -> np.ndarray:
    '''
    dst = a @ b Hamilton Product

    :return: quat
    '''
    res = plib.p_geoc_quat_mul(mathc.cast_array_vec4(q_a),
                               mathc.cast_array_vec4(q_b))
    return mathc.cast_vec4_np(res)



# /** angle_axis = xyz + w=angle in rad */
# quat p_geoc_quat_from_angle_axis(vec4 angle_axis);
plib.p_geoc_quat_from_angle_axis.argtypes = [mathc.vec4]
plib.p_geoc_quat_from_angle_axis.restype = mathc.vec4


def quat_from_angle_axis(angle_axis: mathc.Array) -> np.ndarray:
    '''
    angle_axis = xyz + w=angle in rad

    :return: quat
    '''
    res = plib.p_geoc_quat_from_angle_axis(mathc.cast_array_vec4(angle_axis))
    return mathc.cast_vec4_np(res)



# /** angle_axis = xyz + w=angle in rad */
# vec4 p_geoc_quat_to_angle_axis(quat q);
plib.p_geoc_quat_to_angle_axis.argtypes = [mathc.vec4]
plib.p_geoc_quat_to_angle_axis.restype = mathc.vec4


def quat_to_angle_axis(q: mathc.Array) -> np.ndarray:
    '''
    angle_axis = xyz + w=angle in rad

    :return: vec4
    '''
    res = plib.p_geoc_quat_to_angle_axis(mathc.cast_array_vec4(q))
    return mathc.cast_vec4_np(res)



# mat3 p_geoc_quat_to_rotation_matrix(quat q);
plib.p_geoc_quat_to_rotation_matrix.argtypes = [mathc.vec4]
plib.p_geoc_quat_to_rotation_matrix.restype = mathc.mat3


def quat_to_rotation_matrix(q: mathc.Array) -> np.ndarray:
    '''
    :return: mat3
    '''
    res = plib.p_geoc_quat_to_rotation_matrix(mathc.cast_array_vec4(q))
    return mathc.cast_mat3_np(res)



# quat p_geoc_quat_from_rotation_matrix(mat3 mat);
plib.p_geoc_quat_from_rotation_matrix.argtypes = [mathc.mat3]
plib.p_geoc_quat_from_rotation_matrix.restype = mathc.vec4


def quat_from_rotation_matrix(mat: mathc.Array) -> np.ndarray:
    '''
    :return: quat
    '''
    res = plib.p_geoc_quat_from_rotation_matrix(mathc.cast_array_mat3(mat))
    return mathc.cast_vec4_np(res)



# quat p_geoc_quat_slerp(quat q_a, quat q_b, float t);
plib.p_geoc_quat_slerp.argtypes = [mathc.vec4, mathc.vec4, bb.c_float]
plib.p_geoc_quat_slerp.restype = mathc.vec4


def quat_slerp(q_a: mathc.Array, q_b: mathc.Array, t: float) -> np.ndarray:
    '''
    :return: quat
    '''
    res = plib.p_geoc_quat_slerp(mathc.cast_array_vec4(q_a),
                                 mathc.cast_array_vec4(q_b),
                                 t)
    return mathc.cast_vec4_np(res)