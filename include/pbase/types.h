#ifndef PBASE_TYPES_H
#define PBASE_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

// restrict
#ifdef __cplusplus
#define restrict __restrict
#endif

#include <stddef.h>
#include <stdbool.h>
#include "mathc/types/float.h"
#include "mathc/types/int.h"

/**
 * Point cloud data type.
 * Each point consists of a vec4 (x, y, z, w)
 */
typedef struct {
    vec4 *restrict data;
    size_t size;
} pCloud;


// Returns true if the cloud is in a valid state
static bool p_cloud_valid(pCloud self) {
    return self.data && self.size>0;
}

// Returns an invalid Cloud
static pCloud p_cloud_new_invalid() {
    return (pCloud) {0};
}

// Creates a new Cloud structure with empty data (malloc)
pCloud p_cloud_new_empty(size_t size);

// Creates a new Cloud structure with all zeros (calloc)
pCloud p_cloud_new_zeros(size_t size);

// Creates a new Cloud structure with all zeros but .w=1
pCloud p_cloud_new_zeros_1(size_t size);

// Frees a Cloud structure
void p_cloud_kill(pCloud *self);



/**
 * Indices data type.
 */
typedef struct {
    int *restrict data;
    size_t size;
} pIndices;

// Returns true if the indices is in a valid state
static bool p_indices_valid(pIndices self) {
    return self.data && self.size>0;
}

// Returns invalid Indices
static pIndices p_indices_new_invalid() {
    return (pIndices) {0};
}

// Creates a new Indices structure with empty data (malloc)
pIndices p_indices_new_empty(size_t size);

// Creates a new Indices structure with all zeros (calloc)
pIndices p_indices_new_zeros(size_t size);

// Creates a range as Indices
pIndices p_indices_new_range(int start, int end, int step);

// Frees a Cloud structure
void p_indices_kill(pIndices *self);


#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPES_H
