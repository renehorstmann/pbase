#include "pbase/meshprimitives.h"
#include "helper.h"

void p_meshprimitives_arrow_custom(pCloud *out_points, pMeshIndices *out_indices,
                                   vec3 apex_point, vec3 extend,
                                   float arrowhead_opening_angle_rad, float arrowhead_length,
                                   float radius, float vertex_density) {
    pCloud cone_points;
    pMeshIndices cone_indices;
    pCloud cylinder_points;
    pMeshIndices cylinder_indices;

    float length = vec3_norm(extend);
    vec3 cone_extend = vec3_scale(extend, arrowhead_length / length);
    vec3 cylinder_extend = vec3_scale(extend, (length - arrowhead_length) / length);
    vec3 cylinder_start = vec3_add_vec(apex_point, cone_extend);

    p_meshprimitives_cone(&cone_points, &cone_indices, apex_point, cone_extend,
                          arrowhead_opening_angle_rad, vertex_density);
    p_meshprimitives_cylinder(&cylinder_points, &cylinder_indices, cylinder_start, cylinder_extend,
                              radius, vertex_density);

    p_mesh_indices_add_offset(&cylinder_indices, cone_points.size);

    *out_points = p_cloud_concatenate(cone_points, cylinder_points);
    *out_indices = p_mesh_indices_concatenate(cone_indices, cylinder_indices);

    p_cloud_kill(&cone_points);
    p_mesh_indices_kill(&cone_indices);
    p_cloud_kill(&cylinder_points);
    p_mesh_indices_kill(&cylinder_indices);
}

void p_meshprimitives_raw_arrow_custom(pCloud *out_points, pCloud *out_opt_normals,
                                       vec3 apex_point, vec3 extend,
                                       float arrowhead_opening_angle_rad, float arrowhead_length,
                                       float radius, float vertex_density) {
    pCloud cone_points, cone_normals;
    pCloud cylinder_points, cylinder_normals;

    float length = vec3_norm(extend);
    vec3 cone_extend = vec3_scale(extend, arrowhead_length / length);
    vec3 cylinder_extend = vec3_scale(extend, (length - arrowhead_length) / length);
    vec3 cylinder_start = vec3_add_vec(apex_point, cone_extend);

    p_meshprimitives_raw_cone(&cone_points, &cone_normals, apex_point, cone_extend,
                              arrowhead_opening_angle_rad, vertex_density);
    p_meshprimitives_raw_cylinder(&cylinder_points, &cylinder_normals, cylinder_start, cylinder_extend,
                                  radius, vertex_density);

    *out_points = p_cloud_concatenate(cone_points, cylinder_points);
    if (out_opt_normals)
        *out_opt_normals = p_cloud_concatenate(cone_normals, cylinder_normals);

    p_cloud_kill(&cone_points);
    p_cloud_kill(&cone_normals);
    p_cloud_kill(&cylinder_points);
    p_cloud_kill(&cylinder_normals);
}


//
// simple versions
//
#include <stdio.h>

void p_meshprimitives_arrow(pCloud *out_points, pMeshIndices *out_indices,
                            vec3 apex_point, vec3 extend,
                            float radius, float vertex_density) {
    const float opening_angle_rad = 15 * M_PI / 180.0;

    float length = vec3_norm(extend);
    float arrowhead_length = 2 * radius / tanf(opening_angle_rad);
    float cylinder_length = length - arrowhead_length;
    if (cylinder_length < arrowhead_length / 2) {
        cylinder_length = length / 3;
        arrowhead_length = length - cylinder_length;
        radius = (arrowhead_length * tanf(opening_angle_rad)) / 2;
    }

    p_meshprimitives_arrow_custom(out_points, out_indices, apex_point, extend,
                                  opening_angle_rad, arrowhead_length, radius, vertex_density);
}


void p_meshprimitives_raw_arrow(pCloud *out_points, pCloud *out_opt_normals,
                                vec3 apex_point, vec3 extend,
                                float radius, float vertex_density) {
    const float opening_angle_rad = 15 * M_PI / 180.0;

    float length = vec3_norm(extend);
    float arrowhead_length = 2 * radius / tanf(opening_angle_rad);
    float cylinder_length = length - arrowhead_length;
    if (cylinder_length < arrowhead_length / 2) {
        cylinder_length = length / 3;
        arrowhead_length = length - cylinder_length;
        radius = (arrowhead_length * tanf(opening_angle_rad)) / 2;
    }

    p_meshprimitives_raw_arrow_custom(out_points, out_opt_normals, apex_point, extend,
                                      opening_angle_rad, arrowhead_length, radius, vertex_density);
}


void p_meshprimitives_arrow_swapped(pCloud *out_points, pMeshIndices *out_indices,
                                    vec3 end_point, vec3 extend,
                                    float radius, float vertex_density) {
    vec3 apex_point = vec3_add_vec(end_point, extend);
    vec3 swapped_extend = vec3_neg(extend);
    p_meshprimitives_arrow(out_points, out_indices, apex_point, swapped_extend, radius, vertex_density);
}

void p_meshprimitives_raw_arrow_swapped(pCloud *out_points, pCloud *out_opt_normals,
                                        vec3 end_point, vec3 extend,
                                        float radius, float vertex_density) {
    vec3 apex_point = vec3_add_vec(end_point, extend);
    vec3 swapped_extend = vec3_neg(extend);
    p_meshprimitives_raw_arrow(out_points, out_opt_normals, apex_point, swapped_extend, radius, vertex_density);
}
