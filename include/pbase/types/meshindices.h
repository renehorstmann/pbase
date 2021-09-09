#ifndef PBASE_TYPES_MESHINDICES_H
#define PBASE_TYPES_MESHINDICES_H


#include <stdbool.h>
#include "pbase/mathc/types/int.h"
#include "indices.h"

/**
 * MeshIndices data type.
 */
typedef struct {
    ivec3 *restrict data;
    int size;
} pMeshIndices;

/** Returns true if the mesh indices are in a valid state */
static bool p_mesh_indices_valid(pMeshIndices self) {
    return self.data && self.size>0;
}

/** Returns invalid MeshIndices */
static pMeshIndices p_mesh_indices_new_invalid() {
    return (pMeshIndices) {0};
}

/** Creates a new MeshIndices structure with empty data (malloc) */
pMeshIndices p_mesh_indices_new_empty(int size);

/** Creates a new MeshIndices structure with all zeros (calloc) */
pMeshIndices p_mesh_indices_new_zeros(int size);

/** Creates a new MeshIndices structure with incrementing points (0, 1, 2), (3, 4, 5), ... */
pMeshIndices p_mesh_indices_new_count_up(int size);

/** Frees a MeshIndices structure */
void p_mesh_indices_kill(pMeshIndices *self);


/** Prints all mesh indices to stdout */
void p_mesh_indices_print(pMeshIndices self);

/** adds an offset to each index */
void p_mesh_indices_add_offset(pMeshIndices *self, int offset);

/** Concatenates two mesh indices together */
pMeshIndices p_mesh_indices_concatenate(pMeshIndices a, pMeshIndices b);

/** Concatenates a list/vector of mesh indices together */
pMeshIndices p_mesh_indices_concatenate_v(const pMeshIndices *mesh_indices_list, int n);

/** Applies indices on a self, so that all not used triangles are removed */
pMeshIndices p_mesh_indices_apply_indices(pMeshIndices self, pIndices indices);

/** Returns the minimum values for v0, v1, v2 */
ivec3 p_mesh_indices_min(pMeshIndices self);

/** Returns the maximum values for v0, v1, v2 */
ivec3 p_mesh_indices_max(pMeshIndices self);

#endif //PBASE_TYPES_MESHINDICES_H
