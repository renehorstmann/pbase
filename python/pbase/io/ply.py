import numpy as np
import ctypes as ct
from typing import Tuple, List, Optional

from .. import mathctypes
from .. import bindingbase as bb
from .. import types as t
from .. import error

from .. import plib

# /** Saves points to a ply file */
# pError p_io_save_points_ply(pCloud points, const char *file, bool ascii);
plib.p_io_save_points_ply.argtypes = [t.pCloud, bb.c_char_p, bb.c_bool]
plib.p_io_save_points_ply.restype = error.pError


def save_points_ply(points: np.ndarray, file: str, ascii: bool):
    '''
    Saves points to a ply file
    '''
    err = plib.p_io_save_points_ply(t.cast_into_pCloud(points),
                                    file.encode(), ascii)
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads points from a ply file */
# pError p_io_load_points_ply(pCloud *out_points, const char *file);
plib.p_io_load_points_ply.argtypes = [t.pCloud_p, bb.c_char_p]
plib.p_io_load_points_ply.restype = error.pError


def load_points_ply(file: str) \
        -> t.NpCloud:
    '''
    Loads points from a ply file

    :returns: out_points
    '''
    out_points = t.pCloud()
    err = plib.p_io_load_points_ply(bb.ref(out_points), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pCloud(out_points)


# /** Saves points with normals to a ply file */
# pError p_io_save_point_normals_ply(pCloud points, pCloud normals, const char *file, bool ascii);
plib.p_io_save_point_normals_ply.argtypes = [t.pCloud, t.pCloud, bb.c_char_p, bb.c_bool]
plib.p_io_save_point_normals_ply.restype = error.pError


def save_point_normals_ply(points: np.ndarray, normals: np.ndarray, file: str, ascii: bool):
    '''
    Saves points with normals to a ply file
    '''
    err = plib.p_io_save_point_normals_ply(t.cast_into_pCloud(points), t.cast_into_pCloud(normals),
                                           file.encode(), ascii)
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads points with normals from a ply file */
# pError p_io_load_point_normals_ply(pCloud *out_points, pCloud *out_normals, const char *file);
plib.p_io_load_point_normals_ply.argtypes = [t.pCloud_p, t.pCloud_p, bb.c_char_p]
plib.p_io_load_point_normals_ply.restype = error.pError


def load_point_normals_ply(file: str) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Loads points with normals from a ply file

    :returns: out_points, out_normals
    '''
    out_points = t.pCloud()
    out_normals = t.pCloud()
    err = plib.p_io_load_point_normals_ply(bb.ref(out_points), bb.ref(out_normals), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_normals)


# /** Saves points with colors  to a ply file */
# pError p_io_save_points_colored_ply(pCloud points, pCloud colors, const char *file, bool ascii);
plib.p_io_save_points_colored_ply.argtypes = [t.pCloud, t.pCloud, bb.c_char_p, bb.c_bool]
plib.p_io_save_points_colored_ply.restype = error.pError


def save_points_colored_ply(points: np.ndarray, colors: np.ndarray, file: str, ascii: bool):
    '''
    Saves points with colors  to a ply file
    '''
    err = plib.p_io_save_points_colored_ply(t.cast_into_pCloud(points), t.cast_into_pCloud(colors),
                                            file.encode(), ascii)
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads points with colors from a ply file */
# pError p_io_load_points_colored_ply(pCloud *out_points, pCloud *out_colors, const char *file);
plib.p_io_load_points_colored_ply.argtypes = [t.pCloud_p, t.pCloud_p, bb.c_char_p]
plib.p_io_load_points_colored_ply.restype = error.pError


def load_points_colored_ply(file: str) \
        -> Tuple[t.NpCloud, t.NpCloud]:
    '''
    Loads points with colors from a ply file

    :returns: out_points, out_colors
    '''
    out_points = t.pCloud()
    out_colors = t.pCloud()
    err = plib.p_io_load_points_colored_ply(bb.ref(out_points), bb.ref(out_colors), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_colors)


# /** Saves points with normals and colors to a ply file */
# pError p_io_save_point_normals_colored_ply(pCloud points, pCloud normals, pCloud colors,
#                                            const char *file, bool ascii);
plib.p_io_save_point_normals_colored_ply.argtypes = [t.pCloud, t.pCloud, t.pCloud, bb.c_char_p, bb.c_bool]
plib.p_io_save_point_normals_colored_ply.restype = error.pError


def save_point_normals_colored_ply(points: np.ndarray, normals: np.ndarray, colors: np.ndarray, file: str, ascii: bool):
    '''
    Saves points with normals and colors to a ply file
    '''
    err = plib.p_io_save_point_normals_colored_ply(t.cast_into_pCloud(points),
                                                   t.cast_into_pCloud(normals),
                                                   t.cast_into_pCloud(colors),
                                                   file.encode(), ascii)
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads points with normals and colors from a ply file */
# pError p_io_load_point_normals_colored_ply(pCloud *out_points, pCloud *out_normals, pCloud *out_colors,
#                                            const char *file);
plib.p_io_load_point_normals_colored_ply.argtypes = [t.pCloud_p, t.pCloud_p, t.pCloud_p, bb.c_char_p]
plib.p_io_load_point_normals_colored_ply.restype = error.pError


def load_point_normals_colored_ply(file: str) \
        -> Tuple[t.NpCloud, t.NpCloud, t.NpCloud]:
    '''
    Loads points with normals and colors from a ply file

    :returns: out_points, out_normals, out_colors
    '''
    out_points = t.pCloud()
    out_normals = t.pCloud()
    out_colors = t.pCloud()
    err = plib.p_io_load_point_normals_colored_ply(bb.ref(out_points),
                                                   bb.ref(out_normals),
                                                   bb.ref(out_colors),
                                                   file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_normals), t.cast_from_pCloud(out_colors)


# /** Saves a ply mesh */
# pError p_io_save_mesh_ply(pCloud points, pMeshIndices indices, const char *file, bool ascii);
plib.p_io_save_mesh_ply.argtypes = [t.pCloud, t.pMeshIndices, bb.c_char_p, bb.c_bool]
plib.p_io_save_mesh_ply.restype = error.pError


def save_mesh_ply(points: np.ndarray, indices: np.ndarray, file: str, ascii: bool):
    '''
    Saves a ply mesh
    '''
    err = plib.p_io_save_mesh_ply(t.cast_into_pCloud(points), t.cast_into_pMeshIndices(indices),
                                  file.encode(), ascii)
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads a ply mesh */
# pError p_io_load_mesh_ply(pCloud *out_points, pMeshIndices *out_indices, const char *file);
plib.p_io_load_mesh_ply.argtypes = [t.pCloud_p, t.pMeshIndices_p, bb.c_char_p]
plib.p_io_load_mesh_ply.restype = error.pError


def load_mesh_ply(file: str) \
        -> Tuple[t.NpCloud, t.NpMeshIndices]:
    '''
    Loads a ply mesh

    :returns: out_points, out_indices
    '''
    out_points = t.pCloud()
    out_opt_indices = t.pMeshIndices()
    err = plib.p_io_load_mesh_ply(bb.ref(out_points), bb.ref(out_opt_indices), file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pCloud(out_points), t.cast_from_pMeshIndices(out_opt_indices)


# /** Saves a ply mesh with point normals */
# pError p_io_save_mesh_normals_ply(pCloud points, pCloud normals, pMeshIndices indices,
#                                   const char *file, bool ascii);
plib.p_io_save_mesh_normals_ply.argtypes = [t.pCloud, t.pCloud, t.pMeshIndices, bb.c_char_p, bb.c_bool]
plib.p_io_save_mesh_normals_ply.restype = error.pError


def save_mesh_normals_ply(points: np.ndarray, normals: np.ndarray, indices: np.ndarray, file: str, ascii: bool):
    '''
    Saves a ply mesh with point normals
    '''
    err = plib.p_io_save_mesh_normals_ply(t.cast_into_pCloud(points),
                                          t.cast_into_pCloud(normals),
                                          t.cast_into_pMeshIndices(indices),
                                          file.encode(), ascii)
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads a ply mesh with point normals */
# pError p_io_load_mesh_normals_ply(pCloud *out_points, pCloud *out_normals, pMeshIndices *out_indices,
#                                   const char *file);
plib.p_io_load_mesh_normals_ply.argtypes = [t.pCloud_p, t.pCloud_p, t.pMeshIndices_p, bb.c_char_p]
plib.p_io_load_mesh_normals_ply.restype = error.pError


def load_mesh_normals_ply(file: str) \
        -> Tuple[t.NpCloud, t.NpCloud, t.NpMeshIndices]:
    '''
    Loads a ply mesh with point normals

    :returns: out_points, out_normals, out_indices
    '''
    out_points = t.pCloud()
    out_normals = t.pCloud()
    out_opt_indices = t.pMeshIndices()
    err = plib.p_io_load_mesh_normals_ply(bb.ref(out_points),
                                          bb.ref(out_normals),
                                          bb.ref(out_opt_indices),
                                          file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_normals), t.cast_from_pMeshIndices(out_opt_indices)


# /** Saves a ply mesh with colors */
# pError p_io_save_mesh_colored_ply(pCloud points, pCloud colors, pMeshIndices indices, const char *file, bool ascii);
plib.p_io_save_mesh_colored_ply.argtypes = [t.pCloud, t.pCloud, t.pMeshIndices, bb.c_char_p, bb.c_bool]
plib.p_io_save_mesh_colored_ply.restype = error.pError


def save_mesh_colored_ply(points: np.ndarray, colors: np.ndarray, indices: np.ndarray, file: str, ascii: bool):
    '''
    Saves a ply mesh with colors
    '''
    err = plib.p_io_save_mesh_colored_ply(t.cast_into_pCloud(points),
                                          t.cast_into_pCloud(colors),
                                          t.cast_into_pMeshIndices(indices),
                                          file.encode(), ascii)
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads a ply mesh with colors */
# pError p_io_load_mesh_colored_ply(pCloud *out_points, pCloud *out_colors, pMeshIndices *out_indices, const char *file);
plib.p_io_load_mesh_colored_ply.argtypes = [t.pCloud_p, t.pCloud_p, t.pMeshIndices_p, bb.c_char_p]
plib.p_io_load_mesh_colored_ply.restype = error.pError


def load_mesh_colored_ply(file: str) \
        -> Tuple[t.NpCloud, t.NpCloud, t.NpMeshIndices]:
    '''
    Loads a ply mesh with colors

    :returns: out_points, out_colors, out_indices
    '''
    out_points = t.pCloud()
    out_colors = t.pCloud()
    out_opt_indices = t.pMeshIndices()
    err = plib.p_io_load_mesh_colored_ply(bb.ref(out_points),
                                          bb.ref(out_colors),
                                          bb.ref(out_opt_indices),
                                          file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_colors), t.cast_from_pMeshIndices(out_opt_indices)


# /** Saves a ply mesh with point normals and colors */
# pError p_io_save_mesh_normals_colored_ply(pCloud points, pCloud normals, pCloud colors, pMeshIndices indices,
#                                           const char *file, bool ascii);
plib.p_io_save_mesh_normals_colored_ply.argtypes = [t.pCloud, t.pCloud, t.pCloud, t.pMeshIndices, bb.c_char_p,
                                                    bb.c_bool]
plib.p_io_save_mesh_normals_colored_ply.restype = error.pError


def save_mesh_normals_colored_ply(points: np.ndarray, normals: np.ndarray, colors: np.ndarray, indices: np.ndarray,
                                  file: str, ascii: bool):
    '''
    Saves a ply mesh with point normals and colors
    '''
    err = plib.p_io_save_mesh_normals_colored_ply(t.cast_into_pCloud(points),
                                                  t.cast_into_pCloud(normals),
                                                  t.cast_into_pCloud(colors),
                                                  t.cast_into_pMeshIndices(indices),
                                                  file.encode(), ascii)
    if err is not None:
        raise RuntimeError(err.decode())


# /** Loads a ply mesh with point normals and colors */
# pError p_io_load_mesh_normals_colored_ply(pCloud *out_points, pCloud *out_normals, pCloud *out_colors,
#                                           pMeshIndices *out_indices,
#                                           const char *file);
plib.p_io_load_mesh_normals_colored_ply.argtypes = [t.pCloud_p, t.pCloud_p, t.pCloud_p, t.pMeshIndices_p, bb.c_char_p]
plib.p_io_load_mesh_normals_colored_ply.restype = error.pError


def load_mesh_normals_colored_ply(file: str) \
        -> Tuple[t.NpCloud, t.NpCloud, t.NpCloud, t.NpMeshIndices]:
    '''
    Loads a ply mesh with point normals and colors

    :returns: out_points, out_normals, out_colors, out_indices
    '''
    out_points = t.pCloud()
    out_normals = t.pCloud()
    out_colors = t.pCloud()
    out_opt_indices = t.pMeshIndices()
    err = plib.p_io_load_mesh_normals_colored_ply(bb.ref(out_points),
                                                  bb.ref(out_normals),
                                                  bb.ref(out_colors),
                                                  bb.ref(out_opt_indices),
                                                  file.encode())
    if err is not None:
        raise RuntimeError(err.decode())
    return t.cast_from_pCloud(out_points), t.cast_from_pCloud(out_normals), t.cast_from_pCloud(
        out_colors), t.cast_from_pMeshIndices(out_opt_indices)
