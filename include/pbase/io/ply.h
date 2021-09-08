#ifndef PBASE_IO_PLY_H
#define PBASE_IO_PLY_H

#include "pbase/error.h"
#include "pbase/types/cloud.h"
#include "pbase/types/meshindices.h"

#define P_IO_PLY_COMMENT_MAX_LENGTH 128
#define P_IO_PLY_MAX_COMMENTS 8

typedef char pIoPlyComments[P_IO_PLY_MAX_COMMENTS][P_IO_PLY_COMMENT_MAX_LENGTH];


/** Saves a ply file with the given input (all valid members are saved) */
pError p_io_save_ply(pCloud points, pCloud normals, pCloud colors, pMeshIndices indices,
                     const char *file, bool ascii, const pIoPlyComments opt_comments);


/** Loads a ply file. If a member is not available, it will be set to an invalid state */
pError p_io_load_ply(pCloud *out_opt_points, pCloud *out_opt_normals, pCloud *out_opt_colors,
                     pMeshIndices *out_opt_indices,
                     const char *file, pIoPlyComments opt_out_comments);


//
// wrapper
//

/** Saves points to a ply file */
pError p_io_save_points_ply(pCloud points, const char *file, bool ascii);

/** Loads points from a ply file */
pError p_io_load_points_ply(pCloud *out_points, const char *file);


/** Saves points with normals to a ply file */
pError p_io_save_point_normals_ply(pCloud points, pCloud normals, const char *file, bool ascii);

/** Loads points with normals from a ply file */
pError p_io_load_point_normals_ply(pCloud *out_points, pCloud *out_normals, const char *file);


/** Saves points with colors  to a ply file */
pError p_io_save_points_colored_ply(pCloud points, pCloud colors, const char *file, bool ascii);

/** Loads points with colors from a ply file */
pError p_io_load_points_colored_ply(pCloud *out_points, pCloud *out_colors, const char *file);


/** Saves points with normals and colors to a ply file */
pError p_io_save_point_normals_colored_ply(pCloud points, pCloud normals, pCloud colors,
                                           const char *file, bool ascii);

/** Loads points with normals and colors from a ply file */
pError p_io_load_point_normals_colored_ply(pCloud *out_points, pCloud *out_normals, pCloud *out_colors,
                                           const char *file);


/** Saves a ply mesh */
pError p_io_save_mesh_ply(pCloud points, pMeshIndices indices, const char *file, bool ascii);

/** Loads a ply mesh */
pError p_io_load_mesh_ply(pCloud *out_points, pMeshIndices *out_indices, const char *file);


/** Saves a ply mesh with point normals */
pError p_io_save_mesh_normals_ply(pCloud points, pCloud normals, pMeshIndices indices,
                                  const char *file, bool ascii);

/** Loads a ply mesh with point normals */
pError p_io_load_mesh_normals_ply(pCloud *out_points, pCloud *out_normals, pMeshIndices *out_indices,
                                  const char *file);


/** Saves a ply mesh with colors */
pError p_io_save_mesh_colored_ply(pCloud points, pCloud colors, pMeshIndices indices, const char *file, bool ascii);

/** Loads a ply mesh with colors */
pError p_io_load_mesh_colored_ply(pCloud *out_points, pCloud *out_colors, pMeshIndices *out_indices, const char *file);


/** Saves a ply mesh with point normals and colors */
pError p_io_save_mesh_normals_colored_ply(pCloud points, pCloud normals, pCloud colors, pMeshIndices indices,
                                          const char *file, bool ascii);

/** Loads a ply mesh with point normals and colors */
pError p_io_load_mesh_normals_colored_ply(pCloud *out_points, pCloud *out_normals, pCloud *out_colors,
                                          pMeshIndices *out_indices,
                                          const char *file);


#endif //PBASE_IO_PLY_H
