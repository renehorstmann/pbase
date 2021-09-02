#ifndef PBASE_MESHPRIMITIVES_HELPER_H
#define PBASE_MESHPRIMITIVES_HELPER_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "pbase/mathc/float.h"
#include "pbase/mathc/utils/rotation.h"
#include "pbase/types/cloud.h"
#include "pbase/types/meshindices.h"

static int calc_steps(float radius, float vertex_density) {
    float u = (float) M_PI * 2 * radius;
    int steps = (int) (u / vertex_density);
    if (steps < 5)
        steps = 5;
    return steps;
}

/**
 * Surface normal for a point normal from angles.
 * @param alpha: x-y angle
 * @param beta: (x|y)-z angle
 */
static vec4 polar_angles_to_normal(float alpha, float beta) {
    vec4 out_normal;
    out_normal.x = cosf(beta) * cosf(alpha);
    out_normal.y = cosf(beta) * sinf(alpha);
    out_normal.z = sinf(beta);
    out_normal.w = 0;
    return out_normal;
}

static pCloud mesh_expand_cloud(pCloud mesh_points, pMeshIndices mesh_indices) {
    pCloud out_expanded = p_cloud_new_empty(mesh_indices.size * 3);

    for (int t = 0; t < mesh_indices.size; t++) {
        for (int abc = 0; abc < 3; abc++)
            out_expanded.data[t * 3 + abc] = mesh_points.data[mesh_indices.data[t].v[abc]];
    }
    return out_expanded;
}

static pCloud mesh_face_normals(pCloud points, pMeshIndices indices) {
    pCloud out_normals = p_cloud_new_empty(indices.size);
    for (int t = 0; t < indices.size; t++) {
        vec4 *normal = &out_normals.data[t];
        int index_a = indices.data[t].v0;
        int index_b = indices.data[t].v1;
        int index_c = indices.data[t].v2;
        vec3 ab = vec3_sub_vec(points.data[index_b].xyz, points.data[index_a].xyz);
        vec3 ac = vec3_sub_vec(points.data[index_c].xyz, points.data[index_a].xyz);
        normal->xyz = vec3_cross(ab, ac);
        normal->xyz = vec3_normalize(normal->xyz);
        normal->w = 0;
    }
    return out_normals;
}


static void mesh_expand_point_normals(pCloud *out_points, pCloud *out_normals,
                               pCloud mesh_points, pMeshIndices mesh_indices) {
    pCloud triangle_normals = mesh_face_normals(mesh_points, mesh_indices);

    // allocate out_ clouds
    *out_points = p_cloud_new_empty(mesh_indices.size * 3);
    *out_normals = p_cloud_new_empty(mesh_indices.size * 3);

    for (int t = 0; t < mesh_indices.size; t++) {
        for (int abc = 0; abc < 3; abc++) {
            out_points->data[t * 3 + abc] = mesh_points.data[mesh_indices.data[t].v[abc]];
            out_normals->data[t * 3 + abc] = triangle_normals.data[t];
        }
    }

    p_cloud_kill(&triangle_normals);
}


#endif //PBASE_MESHPRIMITIVES_HELPER_H
