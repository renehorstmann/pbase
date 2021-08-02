#ifndef PBASE_TYPEFUN_MESHINDICES_H
#define PBASE_TYPEFUN_MESHINDICES_H
#ifdef __cplusplus
extern "C" {
#endif

#include "pointc/types.h"


/** Prints all mesh indices to stdout */
void pc_mesh_indices_print(PcMeshIndices *self);

/** adds an offset to each index */
void pc_mesh_indices_add_offset(PcMeshIndices *self, int offset);

/** Concatenates two mesh indices together */
void pc_mesh_indices_concatenate(PcMeshIndices *out_concatenate, PcMeshIndices a, PcMeshIndices b);

/** Concatenates a list/vector of mesh indices together */
void pc_mesh_indices_concatenate_v(PcMeshIndices *out_concatenate, const PcMeshIndices *mesh_indices_list, int n);

/** Applies indices on a mesh, so that all not used triangles are removed */
void pc_mesh_indices_apply_indices(PcMeshIndices *out_mesh, PcMeshIndices mesh, PcIndices indices);



#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPEFUN_MESHINDICES_H
