#ifndef PBASE_HELPER_H
#define PBASE_HELPER_H

#include "pbase/mathc/int.h"
#include "pbase/mathc/float.h"
#include "pbase/types/cloud.h"
#include "pbase/types/meshindices.h"

bool equals_vec4(vec4 a, vec4 b) {
    return vec4_norm_1(vec4_sub_vec(a, b)) < 0.01;
}

bool equals_cloud(pCloud a, pCloud b) {
    if(!p_cloud_valid(a) || !p_cloud_valid(b) || a.size != b.size)
        return false;
    for(size_t i=0; i<a.size; i++) {
        if(!equals_vec4(a.data[i], b.data[i]))
            return false;
    }
    return true;
}

bool equals_mesh_indices(pMeshIndices a, pMeshIndices b) {
    if(!p_mesh_indices_valid(a) || !p_mesh_indices_valid(b) || a.size != b.size)
        return false;
    return memcmp(a.data, b.data, sizeof(*a.data) *a.size) == 0;
}

#endif //PBASE_HELPER_H
