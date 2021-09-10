#include <stddef.h>
#include "pbase/rhc/log.h"
#include "pbase/io/ply.h"


pError p_io_save_points_ply(pCloud points, const char *file, bool ascii) {
    return p_io_save_ply(points, p_cloud_new_invalid(), p_cloud_new_invalid(), p_mesh_indices_new_invalid(),
                         file, ascii, NULL);
}


pError p_io_load_points_ply(pCloud *out_points, const char *file) {
    if (p_io_load_ply(out_points, NULL, NULL, NULL, file, NULL))
        return p_error_assume();
    if (!p_cloud_valid(*out_points)) {
        log_error("p_io_load_points_ply failed to load all members");
        return "Failed to load all members of the ply file";
    }
    return NULL;
}


pError p_io_save_point_normals_ply(pCloud points, pCloud normals, const char *file, bool ascii) {
    return p_io_save_ply(points, normals, p_cloud_new_invalid(), p_mesh_indices_new_invalid(),
                         file, ascii, NULL);
}

pError p_io_load_point_normals_ply(pCloud *out_points, pCloud *out_normals, const char *file) {
    if (p_io_load_ply(out_points, out_normals, NULL, NULL, file, NULL))
        return p_error_assume();
    if (!p_cloud_valid(*out_points) || !p_cloud_valid(*out_normals)) {
        log_error("p_io_load_point_normals_ply failed to load all members");
        return "Failed to load all members of the ply file";
    }
    return NULL;
}


pError p_io_save_points_colored_ply(pCloud points, pCloud colors, const char *file, bool ascii) {
    return p_io_save_ply(points, p_cloud_new_invalid(), colors, p_mesh_indices_new_invalid(),
                         file, ascii, NULL);
}

pError p_io_load_points_colored_ply(pCloud *out_points, pCloud *out_colors, const char *file) {
    if (p_io_load_ply(out_points, NULL, out_colors, NULL, file, NULL))
        return p_error_assume();
    if (!p_cloud_valid(*out_points) || !p_cloud_valid(*out_colors)) {
        log_error("p_io_load_points_colored_ply failed to load all members");
        return "Failed to load all members of the ply file";
    }
    return NULL;
}


pError p_io_save_point_normals_colored_ply(pCloud points, pCloud normals, pCloud colors,
                                           const char *file, bool ascii) {
    return p_io_save_ply(points, normals, colors, p_mesh_indices_new_invalid(),
                         file, ascii, NULL);
}

pError p_io_load_point_normals_colored_ply(pCloud *out_points, pCloud *out_normals, pCloud *out_colors,
                                           const char *file) {
    if (p_io_load_ply(out_points, out_normals, out_colors, NULL, file, NULL))
        return p_error_assume();
    if (!p_cloud_valid(*out_points) || !p_cloud_valid(*out_normals) || !p_cloud_valid(*out_colors)) {
        log_error("p_io_load_point_normals_colored_ply failed to load all members");
        return "Failed to load all members of the ply file";
    }
    return NULL;
}


pError p_io_save_mesh_ply(pCloud points, pMeshIndices indices, const char *file, bool ascii) {
    return p_io_save_ply(points, p_cloud_new_invalid(), p_cloud_new_invalid(), indices,
                         file, ascii, NULL);
}

pError p_io_load_mesh_ply(pCloud *out_points, pMeshIndices *out_indices, const char *file) {
    if (p_io_load_ply(out_points, NULL, NULL, out_indices, file, NULL))
        return p_error_assume();
    if (!p_cloud_valid(*out_points) || !p_mesh_indices_valid(*out_indices)) {
        log_error("p_io_load_mesh_ply failed to load all members");
        return "Failed to load all members of the ply file";
    }
    return NULL;
}


pError p_io_save_mesh_normals_ply(pCloud points, pCloud normals, pMeshIndices indices,
                                  const char *file, bool ascii) {
    return p_io_save_ply(points, normals, p_cloud_new_invalid(), indices,
                         file, ascii, NULL);
}

pError p_io_load_mesh_normals_ply(pCloud *out_points, pCloud *out_normals, pMeshIndices *out_indices,
                                  const char *file) {
    if (p_io_load_ply(out_points, out_normals, NULL, out_indices, file, NULL))
        return p_error_assume();
    if (!p_cloud_valid(*out_points) || !p_cloud_valid(*out_normals) || !p_mesh_indices_valid(*out_indices)) {
        log_error("p_io_load_mesh_normals_ply failed to load all members");
        return "Failed to load all members of the ply file";
    }
    return NULL;
}


pError p_io_save_mesh_colored_ply(pCloud points, pCloud colors, pMeshIndices indices, const char *file, bool ascii) {
    return p_io_save_ply(points, p_cloud_new_invalid(), colors, indices,
                         file, ascii, NULL);
}

pError p_io_load_mesh_colored_ply(pCloud *out_points, pCloud *out_colors, pMeshIndices *out_indices, const char *file) {
    if (p_io_load_ply(out_points, NULL, out_colors, out_indices, file, NULL))
        return p_error_assume();
    if (!p_cloud_valid(*out_points) || !p_cloud_valid(*out_colors) || !p_mesh_indices_valid(*out_indices)) {
        log_error("p_io_load_mesh_colored_ply failed to load all members");
        return "Failed to load all members of the ply file";
    }
    return NULL;
}


pError p_io_save_mesh_normals_colored_ply(pCloud points, pCloud normals, pCloud colors, pMeshIndices indices,
                                          const char *file, bool ascii) {
    return p_io_save_ply(points, normals, colors, indices,
                         file, ascii, NULL);
}

pError p_io_load_mesh_normals_colored_ply(pCloud *out_points, pCloud *out_normals, pCloud *out_colors,
                                          pMeshIndices *out_indices,
                                          const char *file) {
    if (p_io_load_ply(out_points, out_normals, out_colors, out_indices, file, NULL))
        return p_error_assume();
    if (!p_cloud_valid(*out_points) || !p_cloud_valid(*out_normals) || !p_cloud_valid(*out_colors)
        || !p_mesh_indices_valid(*out_indices)) {
        log_error("p_io_load_mesh_normals_colored_ply failed to load all members");
        return "Failed to load all members of the ply file";
    }
    return NULL;
}
