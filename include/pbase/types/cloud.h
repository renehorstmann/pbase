#ifndef PBASE_TYPES_CLOUD_H
#define PBASE_TYPES_CLOUD_H

#include <stdbool.h>
#include "pbase/mathc/types/float.h"
#include "indices.h"

/**
 * Point cloud data type.
 * Each point consists of a vec4 (x, y, z, w)
 */
typedef struct {
    vec4 *restrict data;
    int size;
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
pCloud p_cloud_new_empty(int size);

/** Creates a new Cloud structure with all zeros (calloc) */
pCloud p_cloud_new_zeros(int size);

/** Creates a new Cloud structure with all zeros but .w=1 */
pCloud p_cloud_new_zeros_1(int size);

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

/** Returns the minimum values for x, y, z, w */
vec4 p_cloud_min(pCloud self);

/** Returns the maximum values for x, y, z, w */
vec4 p_cloud_max(pCloud self);

#endif //PBASE_TYPES_CLOUD_H
