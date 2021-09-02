#include "pbase/meshprimitives.h"
#include "helper.h"

void p_meshprimitives_plane(pCloud *out_points, pMeshIndices *out_indices,
                            mat4 pose, float width, float height) {
    *out_points = p_cloud_new_empty(4);
    *out_indices = p_mesh_indices_new_empty(2);

    width /= 2;
    height /= 2;

    vec4 points[4] = {
            {{-width, -height, 0, 1}},
            {{-width, +height, 0, 1}},
            {{+width, -height, 0, 1}},
            {{+width, +height, 0, 1}}
    };

    for (int i = 0; i < 4; i++)
        out_points->data[i] = mat4_mul_vec(pose, points[i]);

    out_indices->data[0] = (ivec3) {{2, 1, 0}};
    out_indices->data[1] = (ivec3) {{1, 2, 3}};
}

void p_meshprimitives_raw_plane(pCloud *out_points, pCloud *out_opt_normals,
                                mat4 pose, float width, float height) {
    pCloud points;
    pMeshIndices indices;
    p_meshprimitives_plane(&points, &indices, pose, width, height);

    if (out_opt_normals)
        mesh_expand_point_normals(out_points, out_opt_normals, points, indices);
    else
        *out_points = mesh_expand_cloud(points, indices);

    p_cloud_kill(&points);
    p_mesh_indices_kill(&indices);
}


void p_meshprimitives_box(pCloud *out_points, pMeshIndices *out_indices,
                          mat4 pose, float width, float height, float extend) {
    *out_points = p_cloud_new_empty(8);
    *out_indices = p_mesh_indices_new_empty(12);

    width /= 2;
    height /= 2;
    extend /= 2;

    vec4 points[8] = {
            {{-width, -height, -extend, 1}},
            {{-width, +height, -extend, 1}},
            {{+width, -height, -extend, 1}},
            {{+width, +height, -extend, 1}},
            {{-width, -height, +extend, 1}},
            {{-width, +height, +extend, 1}},
            {{+width, -height, +extend, 1}},
            {{+width, +height, +extend, 1}}
    };

    for (int i = 0; i < 8; i++)
        out_points->data[i] = mat4_mul_vec(pose, points[i]);

    // bottom
    out_indices->data[0] = (ivec3) {{0, 1, 2}};
    out_indices->data[1] = (ivec3) {{3, 2, 1}};

    // top
    out_indices->data[2] = (ivec3) {{6, 5, 4}};
    out_indices->data[3] = (ivec3) {{5, 6, 7}};

    // left
    out_indices->data[4] = (ivec3) {{4, 1, 0}};
    out_indices->data[5] = (ivec3) {{1, 4, 5}};

    // right
    out_indices->data[6] = (ivec3) {{2, 3, 6}};
    out_indices->data[7] = (ivec3) {{7, 6, 3}};

    // front
    out_indices->data[8] = (ivec3) {{0, 2, 4}};
    out_indices->data[9] = (ivec3) {{6, 4, 2}};

    // back
    out_indices->data[10] = (ivec3) {{5, 3, 1}};
    out_indices->data[11] = (ivec3) {{3, 5, 7}};
}


void p_meshprimitives_raw_box(pCloud *out_points, pCloud *out_opt_normals,
                              mat4 pose, float width, float height, float extend) {
    pCloud points;
    pMeshIndices indices;
    p_meshprimitives_box(&points, &indices, pose, width, height, extend);

    if (out_opt_normals)
        mesh_expand_point_normals(out_points, out_opt_normals, points, indices);
    else
        *out_points = mesh_expand_cloud(points, indices);

    p_cloud_kill(&points);
    p_mesh_indices_kill(&indices);
}


void p_meshprimitives_circle(pCloud *out_points, pMeshIndices *out_indices,
                             mat4 pose, float radius, float vertex_density) {
    int steps = calc_steps(radius, vertex_density);

    *out_points = p_cloud_new_empty(steps + 1);
    *out_indices = p_mesh_indices_new_empty(steps);

    vec4 points[steps + 1];
    points[0] = vec4_unit_w();
    for (int i = 1; i < steps + 1; i++) {
        float alpha = (float) M_PI * 2 * (i - 1) / steps;
        points[i].x = radius * cosf(alpha);
        points[i].y = radius * sinf(alpha);
        points[i].z = 0;
        points[i].w = 1;
    }

    for (int i = 0; i < steps + 1; i++)
        out_points->data[i] = mat4_mul_vec(pose, points[i]);

    for (int i = 0; i < steps; i++) {
        out_indices->data[i].v0 = 0;
        out_indices->data[i].v1 = i + 1;
        out_indices->data[i].v2 = i + 2;
    }
    out_indices->data[steps - 1].v2 = 1;
}

void p_meshprimitives_raw_circle(pCloud *out_points, pCloud *out_opt_normals,
                                 mat4 pose, float radius, float vertex_density) {
    pCloud points;
    pMeshIndices indices;
    p_meshprimitives_circle(&points, &indices, pose, radius, vertex_density);

    if (out_opt_normals)
        mesh_expand_point_normals(out_points, out_opt_normals, points, indices);
    else
        *out_points = mesh_expand_cloud(points, indices);

    p_cloud_kill(&points);
    p_mesh_indices_kill(&indices);
}

