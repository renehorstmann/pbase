#ifndef PBASE_TYPES_CLOUD_H
#define PBASE_TYPES_CLOUD_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h> // size_t
#include <stdbool.h>
#include "pbase/mathc/types/float.h"
#include "indices.h"

/**
 * Point cloud data type.
 * Each point consists of a vec4 (x, y, z, w)
 */
typedef struct {
    vec4 *restrict data;
    size_t size;
} pCloud;


/** Returns true if the cloud is in a valid state */
static bool p_cloud_valid(pCloud self) {
    return self.data && self.size>0;
}

/** Returns an invalid Cloud */
static pCloud p_cloud_new_invalid() {
    return (pCloud) {0};
}

/** Creates a new Cloud structure with empty data (malloc) */
pCloud p_cloud_new_empty(size_t size);

/** Creates a new Cloud structure with all zeros (calloc) */
pCloud p_cloud_new_zeros(size_t size);

/** Creates a new Cloud structure with all zeros but .w=1 */
pCloud p_cloud_new_zeros_1(size_t size);

/** Frees a Cloud structure */
void p_cloud_kill(pCloud *self);


/** Prints the whole cloud data to stdout */
void p_cloud_print(pCloud self);

/** Concatenates two point clouds together */
pCloud p_cloud_concatenate(pCloud a, pCloud b);

/** Concatenates a list/vector of point clouds together */
pCloud p_cloud_concatenate_v(const pCloud *cloud_list, int n);

/** Applies indices on cloud, so that all not used points are removed */
pCloud p_cloud_apply_indices(pCloud self, pIndices indices);


#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPES_CLOUD_H
