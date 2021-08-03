#ifndef PBASE_TYPES_MESHINDICES_H
#define PBASE_TYPES_MESHINDICES_H
#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h> // size_t
#include <stdbool.h>
#include "pbase/mathc/types/int.h"
#include "indices.h"

/**
 * MeshIndices data type.
 */
typedef struct {
    ivec3 *restrict data;
    size_t size;
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
pMeshIndices p_mesh_indices_new_empty(size_t size);

/** Creates a new MeshIndices structure with all zeros (calloc) */
pMeshIndices p_mesh_indices_new_zeros(size_t size);

/** Creates a new MeshIndices structure with incrementing points (0, 1, 2), (3, 4, 5), ... */
pMeshIndices p_mesh_indices_new_count_up(size_t size);

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



#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPES_MESHINDICES_H
