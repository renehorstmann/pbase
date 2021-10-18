#include <stdio.h>
#include <string.h>
#include <float.h>

#include "pbase/rhc/alloc.h"
#include "pbase/mathc/sca/int.h"
#include "pbase/mathc/vec/vec4.h"
#include "pbase/types/cloud.h"


pCloud p_cloud_new_empty(int size) {
    pCloud self = {0};
    self.data = p_rhc_malloc(size * sizeof *self.data);
    self.size = size;
    return self;
}

pCloud p_cloud_new_zeros(int size) {
    pCloud self = p_cloud_new_empty(size);
    memset(self.data, 0, self.size * sizeof *self.data);
    return self;
}

pCloud p_cloud_new_zeros_1(int size) {
    pCloud self = p_cloud_new_zeros(size);
    for(int i=0; i<self.size; i++) {
        self.data[i].w = 1;
    }
    return self;
}

void p_cloud_kill(pCloud *self) {
    if(!p_cloud_valid(*self))
        return;
    p_rhc_free(self->data);
    *self = (pCloud) {0};
}

void p_cloud_print(pCloud self) {
    if(!p_cloud_valid(self)) {
        puts("p_cloud_print: invalid");
        return;
    }
    puts("p_cloud_print:");
    for(int i = 0; i < self.size; i++) {
        printf("%.2f %.2f %.2f %.2f\n",
               self.data[i].x,
               self.data[i].y,
               self.data[i].z,
               self.data[i].w
        );
    }
}

pCloud p_cloud_concatenate(pCloud a, pCloud b) {
    return p_cloud_concatenate_v((pCloud[]) {a, b}, 2);
}

pCloud p_cloud_concatenate_v(const pCloud *cloud_list, int n) {
    int size = 0;
    for(int i=0; i<n; i++)
        size += cloud_list[i].size;
    pCloud self = p_cloud_new_empty(size);
    vec4 *data = self.data;
    for(int i=0; i<n; i++) {
        size = cloud_list[i].size;
        memcpy(data, cloud_list[i].data, size * sizeof *data);
        data += size;
    }
    return self;
}

pCloud p_cloud_apply_indices(pCloud self, pIndices indices) {
    pCloud ret = p_cloud_new_empty(indices.size);
    for(int i=0; i<indices.size; i++) {
        int index = isca_mod_positive(indices.data[i], self.size);
        ret.data[i] = self.data[index];
    }
    return ret;
}

vec4 p_cloud_min(pCloud self) {
    vec4 min = vec4_set(FLT_MAX);
    for(int i=0; i<self.size; i++) {
        for(int xyzw=0; xyzw<4; xyzw++) {
            if(min.v[xyzw] > self.data[i].v[xyzw])
                min.v[xyzw] = self.data[i].v[xyzw];
        }
    }
    return min;
}

vec4 p_cloud_max(pCloud self) {
    vec4 max = vec4_set(-FLT_MAX);
    for(int i=0; i<self.size; i++) {
        for(int xyzw=0; xyzw<4; xyzw++) {
            if(max.v[xyzw] < self.data[i].v[xyzw])
                max.v[xyzw] = self.data[i].v[xyzw];
        }
    }
    return max;
}
