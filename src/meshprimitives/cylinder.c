#include "pbase/meshprimitives.h"
#include "helper.h"

void p_meshprimitives_cylinder_hull(pCloud *out_points, pMeshIndices *out_indices,
                                    vec3 start_point, vec3 extend, float radius, float vertex_density) {
    mat4 pose = mat4_pose_from_ray(start_point, extend);

    float length = vec3_norm(extend);
    int steps = calc_steps(radius, vertex_density);

    *out_points = p_cloud_new_empty(steps * 2);
    *out_indices = p_mesh_indices_new_empty(steps * 2);

    vec4 points[steps * 2];
    for (int i = 0; i < steps; i++) {
        float alpha = (float) M_PI * 2 * i / steps;
        points[i].x = radius * cosf(alpha);
        points[i].y = radius * sinf(alpha);
        points[i].z = 0;
        points[i].w = 1;

        points[i + steps].x = radius * cosf(alpha);
        points[i + steps].y = radius * sinf(alpha);
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


void p_meshprimitives_raw_cylinder_hull(pCloud *out_points, pCloud *out_opt_normals,
                                        vec3 start_point, vec3 extend, float radius,
                                        float vertex_density) {
    mat4 pose = mat4_pose_from_ray(start_point, extend);

    float length = vec3_norm(extend);
    int steps = calc_steps(radius, vertex_density);

    *out_points = p_cloud_new_empty(steps * 2 * 3);
    if (out_opt_normals)
        *out_opt_normals = p_cloud_new_empty(steps * 2 * 3);

    vec4 points[steps * 2 * 3];
    vec4 normals[steps * 2 * 3];
    for (int i = 0; i < steps; i++) {
        float alpha = (float) M_PI * 2 * i / steps;
        float alpha_1 = (float) M_PI * 2 * (i + 1) / steps;
        // 1A
        points[i * 3 + 0].x = radius * cosf(alpha);
        points[i * 3 + 0].y = radius * sinf(alpha);
        points[i * 3 + 0].z = 0;
        points[i * 3 + 0].w = 1;
        normals[i * 3 + 0] = (vec4) {{cosf(alpha), sinf(alpha), 0, 0}};

        // 1B
        points[i * 3 + 1].x = radius * cosf(alpha_1);
        points[i * 3 + 1].y = radius * sinf(alpha_1);
        points[i * 3 + 1].z = 0;
        points[i * 3 + 1].w = 1;
        normals[i * 3 + 1] = (vec4) {{cosf(alpha_1), sinf(alpha_1), 0, 0}};

        // 1C
        points[i * 3 + 2].x = radius * cosf(alpha);
        points[i * 3 + 2].y = radius * sinf(alpha);
        points[i * 3 + 2].z = length;
        points[i * 3 + 2].w = 1;
        normals[i * 3 + 2] = (vec4) {{cosf(alpha), sinf(alpha), 0, 0}};

        // 2A
        points[(i + steps) * 3 + 0].x = radius * cosf(alpha);
        points[(i + steps) * 3 + 0].y = radius * sinf(alpha);
        points[(i + steps) * 3 + 0].z = length;
        points[(i + steps) * 3 + 0].w = 1;
        normals[(i + steps) * 3 + 0] = (vec4) {{cosf(alpha), sinf(alpha), 0, 0}};

        // 2B
        points[(i + steps) * 3 + 1].x = radius * cosf(alpha_1);
        points[(i + steps) * 3 + 1].y = radius * sinf(alpha_1);
        points[(i + steps) * 3 + 1].z = 0;
        points[(i + steps) * 3 + 1].w = 1;
        normals[(i + steps) * 3 + 1] = (vec4) {{cosf(alpha_1), sinf(alpha_1), 0, 0}};

        // 2C
        points[(i + steps) * 3 + 2].x = radius * cosf(alpha_1);
        points[(i + steps) * 3 + 2].y = radius * sinf(alpha_1);
        points[(i + steps) * 3 + 2].z = length;
        points[(i + steps) * 3 + 2].w = 1;
        normals[(i + steps) * 3 + 2] = (vec4) {{cosf(alpha_1), sinf(alpha_1), 0, 0}};
    }

    for (int i = 0; i < steps * 2 * 3; i++)
        out_points->data[i] = mat4_mul_vec(pose, points[i]);

    if (out_opt_normals) {
        for (int i = 0; i < steps * 2 * 3; i++)
            out_opt_normals->data[i] = mat4_mul_vec(pose, normals[i]);
    }
}


void p_meshprimitives_cylinder(pCloud *out_points, pMeshIndices *out_indices,
                               vec3 start_point, vec3 extend, float radius, float vertex_density) {
    mat4 pose = mat4_pose_from_ray(start_point, extend);

    float length = vec3_norm(extend);
    int steps = calc_steps(radius, vertex_density);

    *out_points = p_cloud_new_empty(steps * 2 + 2);
    *out_indices = p_mesh_indices_new_empty(steps * 4);

    vec4 points[steps * 2 + 2];
    for (int i = 0; i < steps; i++) {
        float alpha = (float) M_PI * 2 * i / steps;
        points[i].x = radius * cosf(alpha);
        points[i].y = radius * sinf(alpha);
        points[i].z = 0;
        points[i].w = 1;

        points[i + steps].x = radius * cosf(alpha);
        points[i + steps].y = radius * sinf(alpha);
        points[i + steps].z = length;
        points[i + steps].w = 1;
    }
    // bottom + top middle
    points[steps * 2] = (vec4) {{0, 0, 0, 1}};
    points[steps * 2 + 1] = (vec4) {{0, 0, length, 1}};

    for (int i = 0; i < steps * 2 + 2; i++)
        out_points->data[i] = mat4_mul_vec(pose, points[i]);


    for (int i = 0; i < steps; i++) {
        out_indices->data[i].v0 = i;
        out_indices->data[i].v1 = (i + 1) % steps;
        out_indices->data[i].v2 = i + steps;

        out_indices->data[i + steps].v0 = i + steps;
        out_indices->data[i + steps].v1 = (i + 1) % steps;
        out_indices->data[i + steps].v2 = (i + 1) % steps + steps;

        out_indices->data[i + steps * 2].v0 = steps * 2; // bottom middle
        out_indices->data[i + steps * 2].v1 = (i + 1) % steps;
        out_indices->data[i + steps * 2].v2 = i;

        out_indices->data[i + steps * 3].v0 = steps * 2 + 1; // top middle
        out_indices->data[i + steps * 3].v1 = i + steps;
        out_indices->data[i + steps * 3].v2 = (i + 1) % steps + steps;
    }
}


void p_meshprimitives_raw_cylinder(pCloud *out_points, pCloud *out_opt_normals,
                                   vec3 start_point, vec3 extend, float radius,
                                   float vertex_density) {

    mat4 pose_top = mat4_pose_from_ray(vec3_add_vec(start_point, extend), extend);
    mat4 pose_bottom = mat4_pose_from_ray(start_point, vec3_neg(extend));

    pCloud hull_points, hull_normals;
    pCloud circle_top_points, circle_top_normals;
    pCloud circle_bottom_points, circle_bottom_normals;
    p_meshprimitives_raw_cylinder_hull(&hull_points, &hull_normals, start_point, extend, radius, vertex_density);
    p_meshprimitives_raw_circle(&circle_top_points, &circle_top_normals, pose_top, radius, vertex_density);
    p_meshprimitives_raw_circle(&circle_bottom_points, &circle_bottom_normals, pose_bottom, radius, vertex_density);

    *out_points = p_cloud_concatenate_v(
            (pCloud[]) {hull_points, circle_top_points, circle_bottom_points},
            3);
    if (out_opt_normals)
        *out_opt_normals = p_cloud_concatenate_v(
                (pCloud[]) {hull_normals, circle_top_normals, circle_bottom_normals},
                3);

    p_cloud_kill(&hull_points);
    p_cloud_kill(&hull_normals);
    p_cloud_kill(&circle_top_points);
    p_cloud_kill(&circle_top_normals);
    p_cloud_kill(&circle_bottom_points);
    p_cloud_kill(&circle_bottom_normals);
}

