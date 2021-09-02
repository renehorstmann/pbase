#include "pbase/mathc/utils/float.h"
#include "pbase/math.h"



mat4 p_math_camera_ortho(float left, float right,
                         float bottom, float top,
                         float near, float far) {
    return mat4_camera_ortho(left, right, bottom, top, near, far);
}

mat4 p_math_camera_frustum(float left, float right,
                           float bottom, float top,
                           float near, float far) {
    return mat4_camera_frustum(left, right, bottom, top, near, far);
}

mat4 p_math_camera_perspective(float fovy, float aspect, float near, float far) {
    return mat4_camera_perspective(fovy, aspect, near, far);
}

mat4 p_math_camera_lookat(vec3 eye, vec3 center, vec3 up) {
    return mat4_camera_lookat(eye, center, up);
}


vec3 p_math_rgb2hsv(vec3 rgb) {
    return vec3_rgb2hsv(rgb);
}

vec3 p_math_hsv2rgb(vec3 hsv) {
    return vec3_hsv2rgb(hsv);
}


bool p_math_intersection_plane_plane(vec3 *out_pos, vec3 *out_dir,
                                     vec4 plane_hessian_a, vec4 plane_hessian_b) {
    return intersection_plane_plane(out_pos, out_dir, plane_hessian_a, plane_hessian_b);
}

bool p_math_intersection_plane_line(vec3 *out_pos, vec4 plane_hessian,
                                    vec3 line_pos, vec3 line_dir) {
    return intersection_plane_line(out_pos, plane_hessian, line_pos, line_dir);
}

float p_math_intersection_triangle_line(vec3 v0, vec3 v1, vec3 v2,
                                        vec3 line_pos, vec3 line_dir,
                                        bool culling) {
    return intersection_triangle_line(v0, v1, v2, line_pos, line_dir, culling);
}

bool p_math_intersection_line_line(float *out_tau_a, float *out_tau_b,
                                   vec3 line_a_pos, vec3 line_a_dir,
                                   vec3 line_b_pos, vec3 line_b_dir) {
    return intersection_line_line(out_tau_a, out_tau_b, line_a_pos, line_a_dir, line_b_pos, line_b_dir);
}

mat3 p_math_rotation_from_angle_axis(vec4 angle_axis) {
    return mat3_rotation_from_angle_axis(angle_axis);
}

mat3 p_math_rotation_from_dir_z(vec3 dir_z) {
    return mat3_rotation_from_dir_z(dir_z);
}

mat4 p_math_pose_from_ray(vec3 ray_start, vec3 ray_dir) {
    return mat4_pose_from_ray(ray_start, ray_dir);
}

quat p_math_quat_eye() {
    return quat_eye();
}

quat p_math_quat_conj(quat q) {
    return quat_conj(q);
}

quat p_math_quat_inv(quat q) {
    return quat_inv(q);
}

quat p_math_quat_mul(quat q_a, quat q_b) {
    return quat_mul(q_a, q_b);
}

quat p_math_quat_from_angle_axis(vec4 angle_axis) {
    return quat_from_angle_axis(angle_axis);
}

vec4 p_math_quat_to_angle_axis(quat q) {
    return quat_to_angle_axis(q);
}

mat3 p_math_quat_to_rotation_matrix(quat q) {
    return quat_to_rotation_matrix(q);
}

quat p_math_quat_from_rotation_matrix(mat3 mat) {
    return quat_from_rotation_matrix(mat);
}

quat p_math_quat_slerp(quat q_a, quat q_b, float t) {
    return quat_slerp(q_a, q_b, t);
}
