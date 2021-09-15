#include "pbase/meshprimitives.h"
#include "helper.h"


void p_meshprimitives_cone_part_hull(pCloud *out_points, pMeshIndices *out_indices,
                                     vec3 start_point, vec3 extend,
                                     float start_radius, float end_radius, float vertex_density) {
    mat4 pose = mat4_pose_from_ray(start_point, extend);

    float length = vec3_norm(extend);
    int steps = calc_steps(fmaxf(start_radius, end_radius), vertex_density);

    *out_points = p_cloud_new_empty(steps * 2);
    *out_indices = p_mesh_indices_new_empty(steps * 2);

    vec4 points[steps * 2];
    for (int i = 0; i < steps; i++) {
        float alpha = (float) M_PI * 2 * i / steps;
        points[i].x = start_radius * cosf(alpha);
        points[i].y = start_radius * sinf(alpha);
        points[i].z = 0;
        points[i].w = 1;

        points[i + steps].x = end_radius * cosf(alpha);
        points[i + steps].y = end_radius * sinf(alpha);
        points[i + steps].z = length;
        points[i + steps].w = 1;
    }

    for (int i = 0; i < steps * 2; i++)
        out_points->data[i] = mat4_mul_vec(pose, points[i]);


    for (int i = 0; i < steps; i++) {
        out_indices->data[i].v0 = i;
        out_indices->data[i].v1 = (i + 1) % steps;
        out_indices->data[i].v2 = i + steps;

        out_indices->data[i + steps].v0 = i + steps;
        out_indices->data[i + steps].v1 = (i + 1) % steps;
        out_indices->data[i + steps].v2 = (i + 1) % steps + steps;
    }
}

void p_meshprimitives_raw_cone_part_hull(pCloud *out_points, pCloud *out_opt_normals,
                                         vec3 start_point, vec3 extend,
                                         float start_radius, float end_radius, float vertex_density) {
    mat4 pose = mat4_pose_from_ray(start_point, extend);

    float length = vec3_norm(extend);
    int steps = calc_steps(fmaxf(start_radius, end_radius), vertex_density);

    float beta = atanf(fabsf(start_radius - end_radius) / length);

    *out_points = p_cloud_new_empty(steps * 2 * 3);
    if (out_opt_normals)
        *out_opt_normals = p_cloud_new_empty(steps * 2 * 3);

    vec4 points[steps * 2 * 3];
    vec4 normals[steps * 2 * 3];
    for (int i = 0; i < steps; i++) {
        float alpha = (float) M_PI * 2 * i / steps;
        float alpha_1 = (float) M_PI * 2 * (i + 1) / steps;
        // 1A
        points[i * 3 + 0].x = start_radius * cosf(alpha);
        points[i * 3 + 0].y = start_radius * sinf(alpha);
        points[i * 3 + 0].z = 0;
        points[i * 3 + 0].w = 1;
        normals[i * 3 + 0] = polar_angles_to_normal(alpha, beta);

        // 1B
        points[i * 3 + 1].x = start_radius * cosf(alpha_1);
        points[i * 3 + 1].y = start_radius * sinf(alpha_1);
        points[i * 3 + 1].z = 0;
        points[i * 3 + 1].w = 1;
        normals[i * 3 + 1] = polar_angles_to_normal(alpha_1, beta);

        // 1C
        points[i * 3 + 2].x = end_radius * cosf(alpha);
        points[i * 3 + 2].y = end_radius * sinf(alpha);
        points[i * 3 + 2].z = length;
        points[i * 3 + 2].w = 1;
        normals[i * 3 + 2] = polar_angles_to_normal(alpha, beta);

        // 2A
        points[(i + steps) * 3 + 0].x = end_radius * cosf(alpha);
        points[(i + steps) * 3 + 0].y = end_radius * sinf(alpha);
        points[(i + steps) * 3 + 0].z = length;
        points[(i + steps) * 3 + 0].w = 1;
        normals[(i + steps) * 3 + 0] = polar_angles_to_normal(alpha, beta);

        // 2B
        points[(i + steps) * 3 + 1].x = start_radius * cosf(alpha_1);
        points[(i + steps) * 3 + 1].y = start_radius * sinf(alpha_1);
        points[(i + steps) * 3 + 1].z = 0;
        points[(i + steps) * 3 + 1].w = 1;
        normals[(i + steps) * 3 + 1] = polar_angles_to_normal(alpha_1, beta);

        // 2C
        points[(i + steps) * 3 + 2].x = end_radius * cosf(alpha_1);
        points[(i + steps) * 3 + 2].y = end_radius * sinf(alpha_1);
        points[(i + steps) * 3 + 2].z = length;
        points[(i + steps) * 3 + 2].w = 1;
        normals[(i + steps) * 3 + 2] = polar_angles_to_normal(alpha_1, beta);
    }

    for (int i = 0; i < steps * 2 * 3; i++)
        out_points->data[i] = mat4_mul_vec(pose, points[i]);

    if (out_opt_normals) {
        for (int i = 0; i < steps * 2 * 3; i++) {
            if(start_radius < end_radius)
                normals[i].z = -normals[i].z;   // bug?
            out_opt_normals->data[i] = mat4_mul_vec(pose, normals[i]);
        }
    }
}

void p_meshprimitives_cone_hull(pCloud *out_points, pMeshIndices *out_indices,
                                vec3 apex_point, vec3 extend,
                                float opening_angle_rad, float vertex_density) {
    float length = vec3_norm(extend);
    float radius = length * tanf(opening_angle_rad);
    p_meshprimitives_cone_part_hull(out_points, out_indices, apex_point, extend, 0, radius, vertex_density);
}

void p_meshprimitives_raw_cone_hull(pCloud *out_points, pCloud *out_opt_normals,
                                    vec3 apex_point, vec3 extend, float opening_angle_rad,
                                    float vertex_density) {
    float length = vec3_norm(extend);
    float radius = length * tanf(opening_angle_rad);
    p_meshprimitives_raw_cone_part_hull(out_points, out_opt_normals, apex_point, extend, 0, radius, vertex_density);
}

void p_meshprimitives_cone(pCloud *out_points, pMeshIndices *out_indices,
                           vec3 apex_point, vec3 extend, float opening_angle_rad, float vertex_density) {
    mat4 pose = mat4_pose_from_ray(apex_point, extend);

    float length = vec3_norm(extend);
    float radius = length * tanf(opening_angle_rad);
    int steps = calc_steps(radius, vertex_density);

    *out_points = p_cloud_new_empty(steps + 2);
    *out_indices = p_mesh_indices_new_empty(steps * 2);

    vec4 points[steps + 2];
    for (int i = 0; i < steps; i++) {
        float alpha = (float) M_PI * 2 * i / steps;
        points[i].x = radius * cosf(alpha);
        points[i].y = radius * sinf(alpha);
        points[i].z = length;
        points[i].w = 1;
    }
    points[steps] = vec4_unit_w();
    points[steps + 1] = (vec4) {{0, 0, length, 1}};

    for (int i = 0; i < steps + 2; i++)
        out_points->data[i] = mat4_mul_vec(pose, points[i]);

    for (int i = 0; i < steps; i++) {
        out_indices->data[i].v0 = steps;
        out_indices->data[i].v1 = (i + 1) % steps;
        out_indices->data[i].v2 = i;

        out_indices->data[i + steps].v0 = steps + 1;
        out_indices->data[i + steps].v1 = i;
        out_indices->data[i + steps].v2 = (i + 1) % steps;
    }
}

void p_meshprimitives_raw_cone(pCloud *out_points, pCloud *out_opt_normals,
                               vec3 apex_point, vec3 extend, float opening_angle_rad,
                               float vertex_density) {

    mat4 pose_top = mat4_pose_from_ray(vec3_add_vec(apex_point, extend), extend);


    float length = vec3_norm(extend);
    float radius = length * tanf(opening_angle_rad);

    pCloud hull_points, hull_normals;
    pCloud circle_points, circle_normals;
    p_meshprimitives_raw_cone_hull(&hull_points, &hull_normals, apex_point, extend, opening_angle_rad, vertex_density);
    p_meshprimitives_raw_circle(&circle_points, &circle_normals, pose_top, radius, vertex_density);

    assert(hull_points.size == hull_normals.size
           && circle_points.size == circle_normals.size);

    *out_points = p_cloud_concatenate(hull_points, circle_points);
    if (out_opt_normals)
        *out_opt_normals = p_cloud_concatenate(hull_normals, circle_normals);

    p_cloud_kill(&hull_points);
    p_cloud_kill(&hull_normals);
    p_cloud_kill(&circle_points);
    p_cloud_kill(&circle_normals);
}
