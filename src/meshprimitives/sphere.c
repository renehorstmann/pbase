#include "pbase/meshprimitives.h"
#include "helper.h"


void p_meshprimitives_sphere(pCloud *out_points, pMeshIndices *out_indices,
                             vec3 mid_point, float radius, float vertex_density) {
    mat4 pose = mat4_eye();
    pose.col[3].xyz = mid_point;

    int steps = calc_steps(radius, vertex_density);
    int row_steps = steps;

    *out_points = p_cloud_new_empty(row_steps * steps * 2);
    *out_indices = p_mesh_indices_new_empty(row_steps * steps * 2);

    // the sphere is made of steps rows of cone parts
    float row_height = 2 * radius / row_steps;
    for (int row = 0; row < row_steps; row++) {
        int index_offset = row_steps * steps * 2;
        vec4 *row_points = &out_points->data[index_offset];
        ivec3 *row_indices = &out_indices->data[index_offset];

        float bottom_z = row_height * row - radius;
        float top_z = bottom_z + row_height;

        // should never be sqrt(<0) but to make sure, max(0, _ ) is used to round up errors to 0
        float bottom_radius = sqrtf(fmaxf(0, radius * radius - bottom_z * bottom_z));
        float top_radius = sqrtf(fmaxf(0, radius * radius - top_z * top_z));

        vec4 points[steps * 2];
        for (int i = 0; i < steps; i++) {
            float alpha = (float) M_PI * 2 * i / steps;
            points[i].x = bottom_radius * cosf(alpha);
            points[i].y = bottom_radius * sinf(alpha);
            points[i].z = bottom_z;
            points[i].w = 1;

            points[i + steps].x = top_radius * cosf(alpha);
            points[i + steps].y = top_radius * sinf(alpha);
            points[i + steps].z = top_z;
            points[i + steps].w = 1;
        }

        for (int i = 0; i < steps * 2; i++)
            row_points[i] = mat4_mul_vec(pose, points[i]);


        for (int i = 0; i < steps; i++) {
            row_indices[i].v0 = index_offset + i;
            row_indices[i].v1 = index_offset + (i + 1) % steps;
            row_indices[i].v2 = index_offset + i + steps;

            row_indices[i + steps].v0 = index_offset + i + steps;
            row_indices[i + steps].v1 = index_offset + (i + 1) % steps;
            row_indices[i + steps].v2 = index_offset + (i + 1) % steps + steps;
        }
    }
}


void p_meshprimitives_raw_sphere(pCloud *out_points, pCloud *out_opt_normals,
                                 vec3 mid_point, float radius, float vertex_density) {
    mat4 pose = mat4_eye();
    pose.col[3].xyz = mid_point;

    int steps = calc_steps(radius, vertex_density);
    int row_steps = steps;

    *out_points = p_cloud_new_empty(row_steps * steps * 2 * 3);
    if (out_opt_normals)
        *out_opt_normals = p_cloud_new_empty(row_steps * steps * 2 * 3);

    // the sphere is made of steps rows of cone parts
    float row_height = 2 * radius / row_steps;
    for (int row = 0; row < row_steps; row++) {
        int index_offset = row * row_steps * 2 * 3;
        vec4 *row_points = &out_points->data[index_offset];
        vec4 *row_normals = out_opt_normals ? &out_opt_normals->data[index_offset] : NULL;

        float bottom_z = row_height * row - radius;
        float top_z = bottom_z + row_height;

        // should never be sqrt(<0) but to make sure, max(0, _ ) is used to round up errors to 0
        float bottom_radius = sqrtf(fmaxf(0, radius * radius - bottom_z * bottom_z));
        float top_radius = sqrtf(fmaxf(0, radius * radius - top_z * top_z));

        float bottom_beta = atan2f(bottom_z, bottom_radius);
        float top_beta = atan2f(top_z, top_radius);

        vec4 points[steps * 2 * 3];
        vec4 normals[steps * 2 * 3];
        for (int i = 0; i < steps; i++) {
            float alpha = (float) M_PI * 2 * i / steps;
            float alpha_1 = (float) M_PI * 2 * (i + 1) / steps;
            // 1A
            points[i * 3 + 0].x = bottom_radius * cosf(alpha);
            points[i * 3 + 0].y = bottom_radius * sinf(alpha);
            points[i * 3 + 0].z = bottom_z;
            points[i * 3 + 0].w = 1;
            normals[i * 3 + 0] = polar_angles_to_normal(alpha, bottom_beta);

            // 1B
            points[i * 3 + 1].x = bottom_radius * cosf(alpha_1);
            points[i * 3 + 1].y = bottom_radius * sinf(alpha_1);
            points[i * 3 + 1].z = bottom_z;
            points[i * 3 + 1].w = 1;
            normals[i * 3 + 1] = polar_angles_to_normal(alpha_1, bottom_beta);

            // 1C
            points[i * 3 + 2].x = top_radius * cosf(alpha);
            points[i * 3 + 2].y = top_radius * sinf(alpha);
            points[i * 3 + 2].z = top_z;
            points[i * 3 + 2].w = 1;
            normals[i * 3 + 2] = polar_angles_to_normal(alpha, top_beta);

            // 2A
            points[(i + steps) * 3 + 0].x = top_radius * cosf(alpha);
            points[(i + steps) * 3 + 0].y = top_radius * sinf(alpha);
            points[(i + steps) * 3 + 0].z = top_z;
            points[(i + steps) * 3 + 0].w = 1;
            normals[(i + steps) * 3 + 0] = polar_angles_to_normal(alpha, top_beta);

            // 2B
            points[(i + steps) * 3 + 1].x = bottom_radius * cosf(alpha_1);
            points[(i + steps) * 3 + 1].y = bottom_radius * sinf(alpha_1);
            points[(i + steps) * 3 + 1].z = bottom_z;
            points[(i + steps) * 3 + 1].w = 1;
            normals[(i + steps) * 3 + 1] = polar_angles_to_normal(alpha_1, bottom_beta);

            // 2C
            points[(i + steps) * 3 + 2].x = top_radius * cosf(alpha_1);
            points[(i + steps) * 3 + 2].y = top_radius * sinf(alpha_1);
            points[(i + steps) * 3 + 2].z = top_z;
            points[(i + steps) * 3 + 2].w = 1;
            normals[(i + steps) * 3 + 2] = polar_angles_to_normal(alpha_1, top_beta);
        }

        for (int i = 0; i < steps * 2 * 3; i++)
            row_points[i] = mat4_mul_vec(pose, points[i]);

        if (out_opt_normals) {
            for (int i = 0; i < steps * 2 * 3; i++)
                row_normals[i] = mat4_mul_vec(pose, normals[i]);
        }
    }
}


void p_meshprimitives_half_sphere_hull(pCloud *out_points, pMeshIndices *out_indices,
                                       mat4 pose, float radius, float vertex_density) {
    int steps = calc_steps(radius, vertex_density);
    int row_steps = steps / 2;

    *out_points = p_cloud_new_empty(row_steps * steps * 2);
    *out_indices = p_mesh_indices_new_empty(row_steps * steps * 2);

    // the sphere is made of steps rows of cone parts
    float row_height = 2 * radius / steps;
    for (int row = 0; row < row_steps; row++) {
        int index_offset = row * steps * 2;
        vec4 *row_points = &out_points->data[index_offset];
        ivec3 *row_indices = &out_indices->data[index_offset];

        float bottom_z = row_height * row;
        float top_z = bottom_z + row_height;

        // should never be sqrt(<0) but to make sure, max(0, _ ) is used to round up errors to 0
        float bottom_radius = sqrtf(fmaxf(0, radius * radius - bottom_z * bottom_z));
        float top_radius = sqrtf(fmaxf(0, radius * radius - top_z * top_z));

        vec4 points[steps * 2];
        for (int i = 0; i < steps; i++) {
            float alpha = (float) M_PI * 2 * i / steps;
            points[i].x = bottom_radius * cosf(alpha);
            points[i].y = bottom_radius * sinf(alpha);
            points[i].z = bottom_z;
            points[i].w = 1;

            points[i + steps].x = top_radius * cosf(alpha);
            points[i + steps].y = top_radius * sinf(alpha);
            points[i + steps].z = top_z;
            points[i + steps].w = 1;
        }

        for (int i = 0; i < steps * 2; i++)
            row_points[i] = mat4_mul_vec(pose, points[i]);


        for (int i = 0; i < steps; i++) {
            row_indices[i].v0 = index_offset + i;
            row_indices[i].v1 = index_offset + (i + 1) % steps;
            row_indices[i].v2 = index_offset + i + steps;

            row_indices[i + steps].v0 = index_offset + i + steps;
            row_indices[i + steps].v1 = index_offset + (i + 1) % steps;
            row_indices[i + steps].v2 = index_offset + (i + 1) % steps + steps;
        }
    }
}

void p_meshprimitives_raw_half_sphere_hull(pCloud *out_points, pCloud *out_opt_normals,
                                           mat4 pose, float radius, float vertex_density) {
    int steps = calc_steps(radius, vertex_density);
    int row_steps = steps / 2;

    *out_points = p_cloud_new_empty(row_steps * steps * 2 * 3);
    if (out_opt_normals)
        *out_opt_normals = p_cloud_new_empty(row_steps * steps * 2 * 3);

    // the sphere is made of steps rows of cone parts
    float row_height = 2 * radius / steps;
    for (int row = 0; row < row_steps; row++) {
        int index_offset = row * steps * 2 * 3;
        vec4 *row_points = &out_points->data[index_offset];
        vec4 *row_normals = out_opt_normals ? &out_opt_normals->data[index_offset] : NULL;

        float bottom_z = row_height * row;
        float top_z = bottom_z + row_height;

        // should never be sqrt(<0) but to make sure, max(0, _ ) is used to round up errors to 0
        float bottom_radius = sqrtf(fmaxf(0, radius * radius - bottom_z * bottom_z));
        float top_radius = sqrtf(fmaxf(0, radius * radius - top_z * top_z));

        float bottom_beta = atan2f(bottom_z, bottom_radius);
        float top_beta = atan2f(top_z, top_radius);

        vec4 points[steps * 2 * 3];
        vec4 normals[steps * 2 * 3];
        for (int i = 0; i < steps; i++) {
            float alpha = (float) M_PI * 2 * i / steps;
            float alpha_1 = (float) M_PI * 2 * (i + 1) / steps;
            // 1A
            points[i * 3 + 0].x = bottom_radius * cosf(alpha);
            points[i * 3 + 0].y = bottom_radius * sinf(alpha);
            points[i * 3 + 0].z = bottom_z;
            points[i * 3 + 0].w = 1;
            normals[i * 3 + 0] = polar_angles_to_normal(alpha, bottom_beta);

            // 1B
            points[i * 3 + 1].x = bottom_radius * cosf(alpha_1);
            points[i * 3 + 1].y = bottom_radius * sinf(alpha_1);
            points[i * 3 + 1].z = bottom_z;
            points[i * 3 + 1].w = 1;
            normals[i * 3 + 1] = polar_angles_to_normal(alpha_1, bottom_beta);

            // 1C
            points[i * 3 + 2].x = top_radius * cosf(alpha);
            points[i * 3 + 2].y = top_radius * sinf(alpha);
            points[i * 3 + 2].z = top_z;
            points[i * 3 + 2].w = 1;
            normals[i * 3 + 2] = polar_angles_to_normal(alpha, top_beta);

            // 2A
            points[(i + steps) * 3 + 0].x = top_radius * cosf(alpha);
            points[(i + steps) * 3 + 0].y = top_radius * sinf(alpha);
            points[(i + steps) * 3 + 0].z = top_z;
            points[(i + steps) * 3 + 0].w = 1;
            normals[(i + steps) * 3 + 0] = polar_angles_to_normal(alpha, top_beta);

            // 2B
            points[(i + steps) * 3 + 1].x = bottom_radius * cosf(alpha_1);
            points[(i + steps) * 3 + 1].y = bottom_radius * sinf(alpha_1);
            points[(i + steps) * 3 + 1].z = bottom_z;
            points[(i + steps) * 3 + 1].w = 1;
            normals[(i + steps) * 3 + 1] = polar_angles_to_normal(alpha_1, bottom_beta);

            // 2C
            points[(i + steps) * 3 + 2].x = top_radius * cosf(alpha_1);
            points[(i + steps) * 3 + 2].y = top_radius * sinf(alpha_1);
            points[(i + steps) * 3 + 2].z = top_z;
            points[(i + steps) * 3 + 2].w = 1;
            normals[(i + steps) * 3 + 2] = polar_angles_to_normal(alpha_1, top_beta);
        }

        for (int i = 0; i < steps * 2 * 3; i++)
            row_points[i] = mat4_mul_vec(pose, points[i]);

        if (out_opt_normals) {
            for (int i = 0; i < steps * 2 * 3; i++)
                row_normals[i] = mat4_mul_vec(pose, normals[i]);
        }
    }
}


void p_meshprimitives_half_sphere(pCloud *out_points, pMeshIndices *out_indices,
                                  mat4 pose, float radius, float vertex_density) {

    // circle_pose is pose with z (and y) flipped
    mat4 circle_pose = pose;
    circle_pose.col[1].xyz = vec3_neg(pose.col[1].xyz);
    circle_pose.col[2].xyz = vec3_neg(pose.col[2].xyz);

    pCloud hull_points;
    pMeshIndices hull_indices;
    pCloud circle_points;
    pMeshIndices circle_indices;

    p_meshprimitives_half_sphere_hull(&hull_points, &hull_indices, pose, radius, vertex_density);
    p_meshprimitives_circle(&circle_points, &circle_indices, circle_pose, radius, vertex_density);

    p_mesh_indices_add_offset(&circle_indices, hull_points.size);

    *out_points = p_cloud_concatenate(hull_points, circle_points);
    *out_indices = p_mesh_indices_concatenate(hull_indices, circle_indices);

    p_cloud_kill(&hull_points);
    p_mesh_indices_kill(&hull_indices);
    p_cloud_kill(&circle_points);
    p_mesh_indices_kill(&circle_indices);
}

void p_meshprimitives_raw_half_sphere(pCloud *out_points, pCloud *out_opt_normals,
                                      mat4 pose, float radius, float vertex_density) {

    // circle_pose is pose with z (and y) flipped
    mat4 circle_pose = pose;
    circle_pose.col[1].xyz = vec3_neg(pose.col[1].xyz);
    circle_pose.col[2].xyz = vec3_neg(pose.col[2].xyz);

    pCloud hull_points, hull_normals;
    pCloud circle_points, circle_normals;

    p_meshprimitives_raw_half_sphere_hull(&hull_points, &hull_normals, pose, radius, vertex_density);
    p_meshprimitives_raw_circle(&circle_points, &circle_normals, circle_pose, radius, vertex_density);

    *out_points = p_cloud_concatenate(hull_points, circle_points);
    if (out_opt_normals)
        *out_opt_normals = p_cloud_concatenate(hull_normals, circle_normals);

    p_cloud_kill(&hull_points);
    p_cloud_kill(&hull_normals);
    p_cloud_kill(&circle_points);
    p_cloud_kill(&circle_normals);
}
