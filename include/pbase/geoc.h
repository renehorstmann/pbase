#ifndef PBASE_GEOC_H
#define PBASE_GEOC_H
#ifdef __cplusplus
extern "C" {
#endif

#include "mathc/types/float.h"

//
// This file contains mappings of some useful mathc functions, to generate bindings for python
//

/**
 * Creates an orthogonal camera matrix
 * @param near: near clipping plane
 * @param far: far flipping plane
 */
mat4 p_geoc_camera_ortho(float left, float right,
                              float bottom, float top,
                              float near, float far);

/**
 * Creates a perspective (frustum) camera matrix
 * @param near: near clipping plane
 * @param far: far flipping plane
 */
mat4 p_geoc_camera_frustum(float left, float right,
                                float bottom, float top,
                                float near, float far);

/**
 * Creates a perspective camera matrix.
 * @param fovy: field of view angle [rad]
 * @param aspect: width/height ratio
 * @param near: near clipping plane
 * @param far: far flipping plane
 */
mat4 p_geoc_camera_perspective(float fovy, float aspect, float near, float far);

/**
 * Creates the view matrix for a 3d camera.
 * up vector must not be parallel with eye to center vector
 */
mat4 p_geoc_camera_lookat(vec3 eye, vec3 center, vec3 up);


// rgb[0:1] hsv[0:360, 0:1, 0:1]
vec3 p_geoc_rgb2hsv(vec3 rgb);

// rgb[0:1] hsv[0:360, 0:1, 0:1]
vec3 p_geoc_hsv2rgb(vec3 hsv);



/** returns false if planes are parallel */
bool p_geoc_intersection_plane_plane(vec3 *out_pos, vec3 *out_dir,
                                     vec4 plane_hessian_a, vec4 plane_hessian_b);

/** returns false if plane and line are parallel */
bool p_geoc_intersection_plane_line(vec3 *out_pos, vec4 plane_hessian,
                                    vec3 line_pos, vec3 line_dir);

/** returns t (line_pos + line_dir * t), or NAN if not intersecting */
float p_geoc_intersection_triangle_line(vec3 v0, vec3 v1, vec3 v2,
                                        vec3 line_pos, vec3 line_dir,
                                        bool culling);

/** returns false if lines are parallel, searches for the nearest distance points */
bool p_geoc_intersection_line_line(float *out_tau_a, float *out_tau_b,
                                   vec3 line_a_pos, vec3 line_a_dir,
                                   vec3 line_b_pos, vec3 line_b_dir);



/** creates a rotation matrix from angle_axis as xyz = axis and w = angle [rad] */
mat3 p_geoc_rotation_from_angle_axis(vec4 angle_axis);

/** creates a rotation matrix aligned to x (or y if dir_z~=x), so that the z axis is dir_z */
mat3 p_geoc_rotation_from_dir_z(vec3 dir_z);

/** uses mat3_rotation_from_dir with ray_dir and sets the pose translation to ray_start */
mat4 p_geoc_pose_from_ray(vec3 ray_start, vec3 ray_dir);


/** quat = [0, 0, 0, 1] */
quat p_geoc_quat_eye();

/** dst = -x, -y, -z, w */
quat p_geoc_quat_conj(quat q);

/** dst = inv(quat) */
quat p_geoc_quat_inv(quat q);

/** dst = a @ b Hamilton Product */
quat p_geoc_quat_mul(quat q_a, quat q_b);

/** angle_axis = xyz + w=angle in rad */
quat p_geoc_quat_from_angle_axis(vec4 angle_axis);

/** angle_axis = xyz + w=angle in rad */
vec4 p_geoc_quat_to_angle_axis(quat q);

mat3 p_geoc_quat_to_rotation_matrix(quat q);

quat p_geoc_quat_from_rotation_matrix(mat3 mat);

quat p_geoc_quat_slerp(quat q_a, quat q_b, float t);

#ifdef __cplusplus
}
#endif
#endif //PBASE_GEOC_H
