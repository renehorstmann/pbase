#ifndef PBASE_TYPEFUN_CLOUD_H
#define PBASE_TYPEFUN_CLOUD_H
#ifdef __cplusplus
extern "C" {
#endif

#include "pointc/types.h"


/** Prints the whole Cloud data to stdout */
void pc_cloud_print(PcCloud *self);

/** Concatenates two point clouds together */
void pc_cloud_concatenate(PcCloud *out_concatenate, PcCloud a, PcCloud b);

/** Concatenates a list/vector of point clouds together */
void pc_cloud_concatenate_v(PcCloud *out_concatenate, const PcCloud *cloud_list, int n);

/** Applies indices on cloud, so that all not used points are removed */
void pc_cloud_apply_indices(PcCloud *out_cloud, PcCloud cloud, PcIndices indices);


#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPEFUN_CLOUD_H
