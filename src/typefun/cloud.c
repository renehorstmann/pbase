#include <stdio.h>
#include <string.h>

#include "pbase/mathc/sca/int.h"
#include "pbase/typefun/cloud.h"


void p_cloud_print(pCloud self) {
    if(!p_cloud_valid(self)) {
        puts("p_cloud_print: invalid");
        return;
    }
    puts("p_cloud_print:");
    for (int i = 0; i < self.size; i++) {
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
    size_t size = 0;
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
