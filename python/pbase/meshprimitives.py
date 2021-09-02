import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from . import types as t
from . import mathctypes as mt
from . import bindingbase as bb

from . import plib

# /**
#  * Makes a mesh that represents the given plane (pose in center).
#  */
# void p_meshprimitives_plane(pCloud *out_points, pMeshIndices *out_indices,
#                             mat4 pose, float width, float height);
plib.p_meshprimitives_plane.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                        mt.mat4, bb.c_float, bb.c_float]


def plane(pose: mt.Array, width: float, height: float) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given plane (pose in center).

    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_plane(bb.ref(out_points), bb.ref(out_indices),
                                mt.cast_array_mat4(pose), width, height)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given plane (pose in center).
#  */
# void p_meshprimitives_raw_plane(pCloud *out_points, pCloud *out_opt_normals,
#                                 mat4 pose, float width, float height);
plib.p_meshprimitives_raw_plane.argtypes = [t.pCloud_p, t.pCloud_p,
                                            mt.mat4, bb.c_float, bb.c_float]


def raw_plane(pose: mt.Array, width: float, height: float) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given plane (pose in center).

    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_plane(bb.ref(out_points), bb.ref(out_opt_normals),
                                    mt.cast_array_mat4(pose), width, height)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given box (pose in center).
#  */
# void p_meshprimitives_box(pCloud *out_points, pMeshIndices *out_indices,
#                           mat4 pose, float width, float height, float extend);
plib.p_meshprimitives_box.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                      mt.mat4, bb.c_float, bb.c_float, bb.c_float]


def box(pose: mt.Array, width: float, height: float, extend: float) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given box (pose in center).

    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_box(bb.ref(out_points), bb.ref(out_indices),
                              mt.cast_array_mat4(pose), width, height, extend)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given box (pose in center).
#  */
# void p_meshprimitives_raw_box(pCloud *out_points, pCloud *out_opt_normals,
#                               mat4 pose, float width, float height, float extend);
plib.p_meshprimitives_raw_box.argtypes = [t.pCloud_p, t.pCloud_p,
                                          mt.mat4, bb.c_float, bb.c_float, bb.c_float]


def raw_box(pose: mt.Array, width: float, height: float, extend: float) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given box (pose in center).

    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_box(bb.ref(out_points), bb.ref(out_opt_normals),
                                  mt.cast_array_mat4(pose), width, height, extend)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given circle (pose in center).
#  * @param vertex_density=2.5f: defines the line length (circle arc length)
#  */
# void p_meshprimitives_circle(pCloud *out_points, pMeshIndices *out_indices,
#                              mat4 pose, float radius, float vertex_density);
plib.p_meshprimitives_circle.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                         mt.mat4, bb.c_float, bb.c_float]


def circle(pose: mt.Array, radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given circle (pose in center).

    :param vertex_density=2.5f: defines the line length (circle arc length)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_circle(bb.ref(out_points), bb.ref(out_indices),
                                 mt.cast_array_mat4(pose), radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given circle (pose in center).
#  * @param vertex_density=2.5f: defines the line length (circle arc length)
#  */
# void p_meshprimitives_raw_circle(pCloud *out_points, pCloud *out_opt_normals,
#                                  mat4 pose, float radius, float vertex_density);
plib.p_meshprimitives_raw_circle.argtypes = [t.pCloud_p, t.pCloud_p,
                                             mt.mat4, bb.c_float, bb.c_float]


def raw_circle(pose: mt.Array, radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given circle (pose in center).

    :param vertex_density=2.5f: defines the line length (circle arc length)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_circle(bb.ref(out_points), bb.ref(out_opt_normals),
                                     mt.cast_array_mat4(pose), radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given cylinder hull.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_cylinder_hull(pCloud *out_points, pMeshIndices *out_indices,
#                                     vec3 start_point, vec3 extend, float radius, float vertex_density);
plib.p_meshprimitives_cylinder_hull.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                                mt.vec3, mt.vec3, bb.c_float, bb.c_float]


def cylinder_hull(start_point: mt.Array, extend: mt.Array, radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given cylinder hull.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_cylinder_hull(bb.ref(out_points), bb.ref(out_indices),
                                        mt.cast_array_vec3(start_point), mt.cast_array_vec3(extend),
                                        radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given cylinder hull.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_cylinder_hull(pCloud *out_points, pCloud *out_opt_normals,
#                                         vec3 start_point, vec3 extend,
#                                         float radius, float vertex_density);
plib.p_meshprimitives_raw_cylinder_hull.argtypes = [t.pCloud_p, t.pCloud_p,
                                                    mt.vec3, mt.vec3,
                                                    bb.c_float, bb.c_float]


def raw_cylinder_hull(start_point: mt.Array, extend: mt.Array,
                      radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given cylinder hull.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_cylinder_hull(bb.ref(out_points), bb.ref(out_opt_normals),
                                            mt.cast_array_vec3(start_point), mt.cast_array_vec3(extend),
                                            radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given cylinder.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_cylinder(pCloud *out_points, pMeshIndices *out_indices,
#                                vec3 start_point, vec3 extend, float radius, float vertex_density);
plib.p_meshprimitives_cylinder.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                           mt.vec3, mt.vec3, bb.c_float, bb.c_float]


def cylinder(start_point: mt.Array, extend: mt.Array, radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given cylinder.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_cylinder(bb.ref(out_points), bb.ref(out_indices),
                                   mt.cast_array_vec3(start_point), mt.cast_array_vec3(extend),
                                   radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given cylinder.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_cylinder(pCloud *out_points, pCloud *out_opt_normals,
#                                    vec3 start_point, vec3 extend,
#                                    float radius, float vertex_density);
plib.p_meshprimitives_raw_cylinder.argtypes = [t.pCloud_p, t.pCloud_p,
                                               mt.vec3, mt.vec3,
                                               bb.c_float, bb.c_float]


def raw_cylinder(start_point: mt.Array, extend: mt.Array,
                 radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given cylinder.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_cylinder(bb.ref(out_points), bb.ref(out_opt_normals),
                                       mt.cast_array_vec3(start_point), mt.cast_array_vec3(extend),
                                       radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given cone part hull.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_cone_part_hull(pCloud *out_points, pMeshIndices *out_indices,
#                                      vec3 start_point, vec3 extend,
#                                      float start_radius, float end_radius, float vertex_density);
plib.p_meshprimitives_cone_part_hull.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                                 mt.vec3, mt.vec3,
                                                 bb.c_float, bb.c_float, bb.c_float]


def cone_part_hull(start_point: mt.Array, extend: mt.Array,
                   start_radius: float, end_radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given cone part hull.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_cone_part_hull(bb.ref(out_points), bb.ref(out_indices),
                                         mt.cast_array_vec3(start_point), mt.cast_array_vec3(extend),
                                         start_radius, end_radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given cone part hull.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_cone_part_hull(pCloud *out_points, pCloud *out_opt_normals,
#                                          vec3 start_point, vec3 extend,
#                                          float start_radius, float end_radius, float vertex_density);
plib.p_meshprimitives_raw_cone_part_hull.argtypes = [t.pCloud_p, t.pCloud_p,
                                                     mt.vec3, mt.vec3,
                                                     bb.c_float, bb.c_float, bb.c_float]


def raw_cone_part_hull(start_point: mt.Array, extend: mt.Array,
                       start_radius: float, end_radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given cone part hull.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_cone_part_hull(bb.ref(out_points), bb.ref(out_opt_normals),
                                             mt.cast_array_vec3(start_point), mt.cast_array_vec3(extend),
                                             start_radius, end_radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given cone.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_cone_hull(pCloud *out_points, pMeshIndices *out_indices,
#                                 vec3 apex_point, vec3 extend,
#                                 float opening_angle_rad, float vertex_density);
plib.p_meshprimitives_cone_hull.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                            mt.vec3, mt.vec3,
                                            bb.c_float, bb.c_float]


def cone_hull(start_point: mt.Array, extend: mt.Array,
              opening_angle_rad: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given cone.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_cone_hull(bb.ref(out_points), bb.ref(out_indices),
                                    mt.cast_array_vec3(start_point), mt.cast_array_vec3(extend),
                                    opening_angle_rad, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given cone.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_cone_hull(pCloud *out_points, pCloud *out_opt_normals,
#                                     vec3 apex_point, vec3 extend,
#                                     float opening_angle_rad, float vertex_density);
plib.p_meshprimitives_raw_cone_hull.argtypes = [t.pCloud_p, t.pCloud_p,
                                                mt.vec3, mt.vec3,
                                                bb.c_float, bb.c_float]


def raw_cone_hull(start_point: mt.Array, extend: mt.Array,
                  opening_angle_rad: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given cone.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_cone_hull(bb.ref(out_points), bb.ref(out_opt_normals),
                                        mt.cast_array_vec3(start_point), mt.cast_array_vec3(extend),
                                        opening_angle_rad, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given cone.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_cone(pCloud *out_points, pMeshIndices *out_indices,
#                            vec3 apex_point, vec3 extend, float opening_angle_rad, float vertex_density);
plib.p_meshprimitives_cone.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                       mt.vec3, mt.vec3, bb.c_float, bb.c_float]


def cone(start_point: mt.Array, extend: mt.Array, opening_angle_rad: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given cone.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_cone(bb.ref(out_points), bb.ref(out_indices),
                               mt.cast_array_vec3(start_point), mt.cast_array_vec3(extend),
                               opening_angle_rad, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given cone.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_cone(pCloud *out_points, pCloud *out_opt_normals,
#                                vec3 apex_point, vec3 extend,
#                                float opening_angle_rad, float vertex_density);
plib.p_meshprimitives_raw_cone.argtypes = [t.pCloud_p, t.pCloud_p,
                                           mt.vec3, mt.vec3,
                                           bb.c_float, bb.c_float]


def raw_cone(start_point: mt.Array, extend: mt.Array,
             opening_angle_rad: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given cone.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_cone(bb.ref(out_points), bb.ref(out_opt_normals),
                                   mt.cast_array_vec3(start_point), mt.cast_array_vec3(extend),
                                   opening_angle_rad, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given sphere.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_sphere(pCloud *out_points, pMeshIndices *out_indices,
#                              vec3 mid_point, float radius, float vertex_density);
plib.p_meshprimitives_sphere.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                         mt.vec3, bb.c_float, bb.c_float]


def sphere(mid_point: mt.Array, radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given sphere.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_sphere(bb.ref(out_points), bb.ref(out_indices),
                                 mt.cast_array_vec3(mid_point), radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given sphere.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_sphere(pCloud *out_points, pCloud *out_opt_normals,
#                                  vec3 mid_point, float radius, float vertex_density);
plib.p_meshprimitives_raw_sphere.argtypes = [t.pCloud_p, t.pCloud_p,
                                             mt.vec3, bb.c_float, bb.c_float]


def raw_sphere(mid_point: mt.Array, radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given sphere.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_sphere(bb.ref(out_points), bb.ref(out_opt_normals),
                                     mt.cast_array_vec3(mid_point), radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given half sphere hull in z direction.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_half_sphere_hull(pCloud *out_points, pMeshIndices *out_indices,
#                                        mat4 pose, float radius, float vertex_density);
plib.p_meshprimitives_half_sphere_hull.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                                   mt.mat4, bb.c_float, bb.c_float]


def half_sphere_hull(pose: mt.Array, radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given half sphere hull in z direction.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_half_sphere_hull(bb.ref(out_points), bb.ref(out_indices),
                                           mt.cast_array_mat4(pose), radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given half sphere hull in z direction.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_half_sphere_hull(pCloud *out_points, pCloud *out_opt_normals,
#                                            mat4 pose, float radius, float vertex_density);
plib.p_meshprimitives_raw_half_sphere_hull.argtypes = [t.pCloud_p, t.pCloud_p,
                                                       mt.mat4, bb.c_float, bb.c_float]


def raw_half_sphere_hull(pose: mt.Array, radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given half sphere hull in z direction.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_half_sphere_hull(bb.ref(out_points), bb.ref(out_opt_normals),
                                               mt.cast_array_mat4(pose), radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given half sphere in z direction.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_half_sphere(pCloud *out_points, pMeshIndices *out_indices,
#                                   mat4 pose, float radius, float vertex_density);
plib.p_meshprimitives_half_sphere.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                              mt.mat4, bb.c_float, bb.c_float]


def half_sphere(pose: mt.Array, radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given half sphere in z direction.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_half_sphere(bb.ref(out_points), bb.ref(out_indices),
                                      mt.cast_array_mat4(pose), radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given half sphere in z direction.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_half_sphere(pCloud *out_points, pCloud *out_opt_normals,
#                                       mat4 pose, float radius, float vertex_density);
plib.p_meshprimitives_raw_half_sphere.argtypes = [t.pCloud_p, t.pCloud_p,
                                                  mt.mat4, bb.c_float, bb.c_float]


def raw_half_sphere(pose: mt.Array, radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given half sphere in z direction.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_half_sphere(bb.ref(out_points), bb.ref(out_opt_normals),
                                          mt.cast_array_mat4(pose), radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given arrow (build by cone and cylinder).
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_arrow_custom(pCloud *out_points, pMeshIndices *out_indices,
#                                    vec3 apex_point, vec3 extend,
#                                    float arrowhead_opening_angle_rad, float arrowhead_length,
#                                    float radius, float vertex_density);
plib.p_meshprimitives_arrow_custom.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                               mt.vec3, mt.vec3,
                                               bb.c_float, bb.c_float,
                                               bb.c_float, bb.c_float]


def arrow_custom(apex_point: mt.Array, extend: mt.Array,
                 arrowhead_opening_angle_rad: float, arrowhead_length: float,
                 radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given arrow (build by cone and cylinder).

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_arrow_custom(bb.ref(out_points), bb.ref(out_indices),
                                       mt.cast_array_vec3(apex_point), mt.cast_array_vec3(extend),
                                       arrowhead_opening_angle_rad, arrowhead_length,
                                       radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given arrow (build by cone and cylinder).
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_arrow_custom(pCloud *out_points, pCloud *out_opt_normals,
#                                        vec3 apex_point, vec3 extend,
#                                        float arrowhead_opening_angle_rad, float arrowhead_length,
#                                        float radius, float vertex_density);
plib.p_meshprimitives_raw_arrow_custom.argtypes = [t.pCloud_p, t.pCloud_p,
                                                   mt.vec3, mt.vec3,
                                                   bb.c_float, bb.c_float,
                                                   bb.c_float, bb.c_float]


def raw_arrow_custom(apex_point: mt.Array, extend: mt.Array,
                     arrowhead_opening_angle_rad: float, arrowhead_length: float,
                     radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given arrow (build by cone and cylinder).

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_arrow_custom(bb.ref(out_points), bb.ref(out_opt_normals),
                                           mt.cast_array_vec3(apex_point), mt.cast_array_vec3(extend),
                                           arrowhead_opening_angle_rad, arrowhead_length,
                                           radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given arrow (build by cone and cylinder).
#  * The opening angle will be 30Â° and the arrowhead_length will be so, that cone_radius = 2*radius.
#  * The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_arrow(pCloud *out_points, pMeshIndices *out_indices,
#                             vec3 apex_point, vec3 extend,
#                             float radius, float vertex_density);
plib.p_meshprimitives_arrow.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                        mt.vec3, mt.vec3,
                                        bb.c_float, bb.c_float]


def arrow(apex_point: mt.Array, extend: mt.Array,
          radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given arrow (build by cone and cylinder).
    The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
    The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_arrow(bb.ref(out_points), bb.ref(out_indices),
                                mt.cast_array_vec3(apex_point), mt.cast_array_vec3(extend),
                                radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given arrow (build by cone and cylinder).
#  * The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
#  * The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_arrow(pCloud *out_points, pCloud *out_opt_normals,
#                                 vec3 apex_point, vec3 extend,
#                                 float radius, float vertex_density);
plib.p_meshprimitives_raw_arrow.argtypes = [t.pCloud_p, t.pCloud_p,
                                            mt.vec3, mt.vec3,
                                            bb.c_float, bb.c_float]


def raw_arrow(apex_point: mt.Array, extend: mt.Array,
              radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given arrow (build by cone and cylinder).
    The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
    The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_arrow(bb.ref(out_points), bb.ref(out_opt_normals),
                                    mt.cast_array_vec3(apex_point), mt.cast_array_vec3(extend),
                                    radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)


# /**
#  * Makes a mesh that represents the given arrow (build by cone and cylinder).
#  * The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
#  * The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_arrow_swapped(pCloud *out_points, pMeshIndices *out_indices,
#                                     vec3 end_point, vec3 extend,
#                                     float radius, float vertex_density);
plib.p_meshprimitives_arrow_swapped.argtypes = [t.pCloud_p, t.pMeshIndices_p,
                                                mt.vec3, mt.vec3,
                                                bb.c_float, bb.c_float]


def arrow_swapped(apex_point: mt.Array, extend: mt.Array,
                  radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Makes a mesh that represents the given arrow (build by cone and cylinder).
    The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
    The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_indices = t.pMeshIndices()
    plib.p_meshprimitives_arrow_swapped(bb.ref(out_points), bb.ref(out_indices),
                                        mt.cast_array_vec3(apex_point), mt.cast_array_vec3(extend),
                                        radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_indices)


# /**
#  * Makes a raw mesh (each 3 point normals = triangle) that represents the given arrow (build by cone and cylinder).
#  * The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
#  * The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.
#  * @param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
#  */
# void p_meshprimitives_raw_arrow_swapped(pCloud *out_points, pCloud *out_opt_normals,
#                                         vec3 end_point, vec3 extend,
#                                         float radius, float vertex_density);
plib.p_meshprimitives_raw_arrow_swapped.argtypes = [t.pCloud_p, t.pCloud_p,
                                                    mt.vec3, mt.vec3,
                                                    bb.c_float, bb.c_float]


def raw_arrow_swapped(apex_point: mt.Array, extend: mt.Array,
                      radius: float, vertex_density: float = 2.5) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Makes a raw mesh (each 3 point normals = triangle) that represents the given arrow (build by cone and cylinder).
    The opening angle will be 30° and the arrowhead_length will be so, that cone_radius = 2*radius.
    The cylinder length must be at least arrowhead_length/2, if not, the radius will be set to fit it.

    :param vertex_density=2.5f: defines the triangle sizes/widths (same as p_meshprimitives_circle)
    :return: out_points, out_opt_normals
    '''
    out_points = t.pCloud()
    out_opt_normals = t.pCloud()
    plib.p_meshprimitives_raw_arrow_swapped(bb.ref(out_points), bb.ref(out_opt_normals),
                                            mt.cast_array_vec3(apex_point), mt.cast_array_vec3(extend),
                                            radius, vertex_density)
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_opt_normals)
