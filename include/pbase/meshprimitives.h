#ifndef PBASE_MESHPRIMITIVES_H
#define PBASE_MESHPRIMITIVES_H

#include "types/cloud.h"
#include "types/meshindices.h"

/**
 * Makes a mesh that represents the given plane (pose in center).
 */
void p_meshprimitives_plane(pCloud *out_points, pMeshIndices *out_indices,
                            mat4 pose, float width, float height);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given plane (pose in center).
 */
void p_meshprimitives_raw_plane(pCloud *out_points, pCloud *out_opt_normals,
                                mat4 pose, float width, float height);

/**
 * Makes a mesh that represents the given box (pose in center).
 */
void p_meshprimitives_box(pCloud *out_points, pMeshIndices *out_indices,
                          mat4 pose, float width, float height, float extend);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given box (pose in center).
 */
void p_meshprimitives_raw_box(pCloud *out_points, pCloud *out_opt_normals,
                              mat4 pose, float width, float height, float extend);

/**
 * Makes a mesh that represents the given circle (pose in center).
 * @param vertex_density=2.5f: defines the line length (circle arc length)
 */
void p_meshprimitives_circle(pCloud *out_points, pMeshIndices *out_indices,
                             mat4 pose, float radius, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given circle (pose in center).
 * @param vertex_density=2.5f: defines the line length (circle arc length)
 */
void p_meshprimitives_raw_circle(pCloud *out_points, pCloud *out_opt_normals,
                                 mat4 pose, float radius, float vertex_density);

/**
 * Makes a mesh that represents the given cylinder hull.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_cylinder_hull(pCloud *out_points, pMeshIndices *out_indices,
                                    vec3 start_point, vec3 extend, float radius, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given cylinder hull.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_cylinder_hull(pCloud *out_points, pCloud *out_opt_normals,
                                        vec3 start_point, vec3 extend,
                                        float radius, float vertex_density);

/**
 * Makes a mesh that represents the given cylinder.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_cylinder(pCloud *out_points, pMeshIndices *out_indices,
                               vec3 start_point, vec3 extend, float radius, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given cylinder.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_cylinder(pCloud *out_points, pCloud *out_opt_normals,
                                   vec3 start_point, vec3 extend,
                                   float radius, float vertex_density);

/**
 * Makes a mesh that represents the given cone part hull.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_cone_part_hull(pCloud *out_points, pMeshIndices *out_indices,
                                     vec3 start_point, vec3 extend,
                                     float start_radius, float end_radius, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given cone part hull.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_cone_part_hull(pCloud *out_points, pCloud *out_opt_normals,
                                         vec3 start_point, vec3 extend,
                                         float start_radius, float end_radius, float vertex_density);

/**
 * Makes a mesh that represents the given cone.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_cone_hull(pCloud *out_points, pMeshIndices *out_indices,
                                vec3 apex_point, vec3 extend,
                                float opening_angle_rad, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given cone.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_cone_hull(pCloud *out_points, pCloud *out_opt_normals,
                                    vec3 apex_point, vec3 extend,
                                    float opening_angle_rad, float vertex_density);

/**
 * Makes a mesh that represents the given cone.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_cone(pCloud *out_points, pMeshIndices *out_indices,
                           vec3 apex_point, vec3 extend, float opening_angle_rad, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given cone.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_cone(pCloud *out_points, pCloud *out_opt_normals,
                               vec3 apex_point, vec3 extend,
                               float opening_angle_rad, float vertex_density);

/**
 * Makes a mesh that represents the given sphere.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_sphere(pCloud *out_points, pMeshIndices *out_indices,
                             vec3 mid_point, float radius, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given sphere.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_sphere(pCloud *out_points, pCloud *out_opt_normals,
                                 vec3 mid_point, float radius, float vertex_density);

/**
 * Makes a mesh that represents the given half sphere hull in z direction.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_half_sphere_hull(pCloud *out_points, pMeshIndices *out_indices,
                                       mat4 pose, float radius, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given half sphere hull in z direction.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_half_sphere_hull(pCloud *out_points, pCloud *out_opt_normals,
                                           mat4 pose, float radius, float vertex_density);

/**
 * Makes a mesh that represents the given half sphere in z direction.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_half_sphere(pCloud *out_points, pMeshIndices *out_indices,
                                  mat4 pose, float radius, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given half sphere in z direction.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_half_sphere(pCloud *out_points, pCloud *out_opt_normals,
                                      mat4 pose, float radius, float vertex_density);


/**
 * Makes a mesh that represents the given arrow (build by cone and cylinder).
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_arrow_custom(pCloud *out_points, pMeshIndices *out_indices,
                                   vec3 apex_point, vec3 extend,
                                   float arrowhead_opening_angle_rad, float arrowhead_length,
                                   float radius, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given arrow (build by cone and cylinder).
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_arrow_custom(pCloud *out_points, pCloud *out_opt_normals,
                                       vec3 apex_point, vec3 extend,
                                       float arrowhead_opening_angle_rad, float arrowhead_length,
                                       float radius, float vertex_density);

/**
 * Makes a mesh that represents the given arrow (build by cone and cylinder).
 * The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
 * The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_arrow(pCloud *out_points, pMeshIndices *out_indices,
                            vec3 apex_point, vec3 extend,
                            float radius, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given arrow (build by cone and cylinder).
 * The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
 * The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_arrow(pCloud *out_points, pCloud *out_opt_normals,
                                vec3 apex_point, vec3 extend,
                                float radius, float vertex_density);


/**
 * Makes a mesh that represents the given arrow (build by cone and cylinder).
 * The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
 * The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_arrow_swapped(pCloud *out_points, pMeshIndices *out_indices,
                                    vec3 end_point, vec3 extend,
                                    float radius, float vertex_density);

/**
 * Makes a raw mesh (each 3 point normals = triangle) that represents the given arrow (build by cone and cylinder).
 * The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
 * The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.
 * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
 */
void p_meshprimitives_raw_arrow_swapped(pCloud *out_points, pCloud *out_opt_normals,
                                        vec3 end_point, vec3 extend,
                                        float radius, float vertex_density);

#endif //PBASE_MESHPRIMITIVES_H
