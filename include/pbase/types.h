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

/** Creates a new Cloud structure with empty data (malloc) */
pCloud p_cloud_new_empty(size_t size);

/** Creates a new Cloud structure with all zeros (calloc) */
pCloud p_cloud_new_zeros(size_t size);

/** Creates a new Cloud structure with all zeros but .w=1 */
pCloud p_cloud_new_zeros_1(size_t size);

/** Frees a Cloud structure */
void p_cloud_kill(pCloud *self);

vec3 p_cloud_sum(pCloud self, vec3 start);


#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPES_H
