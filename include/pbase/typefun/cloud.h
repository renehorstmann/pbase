#ifndef PBASE_TYPEFUN_CLOUD_H
#define PBASE_TYPEFUN_CLOUD_H
#ifdef __cplusplus
extern "C" {
#endif

#include "../types.h"


// Prints the whole cloud data to stdout
void p_cloud_print(pCloud self);

// Concatenates two point clouds together
pCloud p_cloud_concatenate(pCloud a, pCloud b);

// Concatenates a list/vector of point clouds together
pCloud p_cloud_concatenate_v(const pCloud *cloud_list, int n);

// Applies indices on cloud, so that all not used points are removed
pCloud p_cloud_apply_indices(pCloud self, pIndices indices);





#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPEFUN_CLOUD_H
