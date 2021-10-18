#include <stdio.h>
#include <string.h>

#include "pbase/rhc/alloc.h"
#include "pbase/mathc/sca/int.h"
#include "pbase/mathc/vec/ivec3.h"
#include "pbase/types/meshindices.h"


pMeshIndices p_mesh_indices_new_empty(int size) {
    pMeshIndices self = {0};
    self.data = p_rhc_malloc(size * sizeof *self.data);
    self.size = size;
    return self;
}

pMeshIndices p_mesh_indices_new_zeros(int size) {
    pMeshIndices self = p_mesh_indices_new_empty(size);
    memset(self.data, 0, self.size * sizeof *self.data);
    return self;
}

pMeshIndices p_mesh_indices_new_count_up(int size) {
    pMeshIndices self = p_mesh_indices_new_empty(size);
    for(int i=0; i<self.size; i++) {
        self.data[i].v0 = i*3;
        self.data[i].v1 = i*3 + 1;
        self.data[i].v2 = i*3 + 2;
    }
    return self;
}

void p_mesh_indices_kill(pMeshIndices *self) {
    if(!p_mesh_indices_valid(*self))
        return;
    p_rhc_free(self->data);
    *self = (pMeshIndices) {0};
}


void p_mesh_indices_print(pMeshIndices self) {
    if(!p_mesh_indices_valid(self)) {
        puts("p_mesh_indices_print: invalid");
        return;
    }
    puts("p_mesh_indices_print:");
    for(int i = 0; i < self.size; i++) {
        printf("%d %d %d\n", self.data[i].v0, self.data[i].v1, self.data[i].v2);
    }
}

void p_mesh_indices_add_offset(pMeshIndices *self, int offset) {
    for(int i=0; i<self->size; i++) {
        for(int abc=0; abc<3; abc++)
            self->data[i].v[abc] += offset;
    }
}

pMeshIndices p_mesh_indices_concatenate(pMeshIndices a, pMeshIndices b) {
    return p_mesh_indices_concatenate_v((pMeshIndices[]) {a, b}, 2);
}

pMeshIndices p_mesh_indices_concatenate_v(const pMeshIndices *mesh_indices_list, int n) {
    int size = 0;
    for(int i=0; i<n; i++)
        size += mesh_indices_list[i].size;
    pMeshIndices self = p_mesh_indices_new_empty(size);
    ivec3 *data = self.data;
    for(int i=0; i<n; i++) {
        size = mesh_indices_list[i].size;
        memcpy(data, mesh_indices_list[i].data, size * sizeof *self.data);
        data += size;
    }
    return self;
}


pMeshIndices p_mesh_indices_apply_indices(pMeshIndices self, pIndices indices) {
    pMeshIndices ret = p_mesh_indices_new_empty(indices.size);
    for(int i=0; i<indices.size; i++) {
        int index = isca_mod_positive(indices.data[i], self.size);
        ret.data[i] = self.data[index];
    }
    return ret;
}


ivec3 p_mesh_indices_min(pMeshIndices self) {
    ivec3 min = ivec3_set(INT_MAX);
    for(int i=0; i<self.size; i++) {
        for(int abc=0; abc < 3; abc++) {
            if(min.v[abc] > self.data[i].v[abc])
                min.v[abc] = self.data[i].v[abc];
        }
    }
    return min;
}

ivec3 p_mesh_indices_max(pMeshIndices self) {
    ivec3 max = ivec3_set(INT_MIN);
    for(int i=0; i<self.size; i++) {
        for(int abc=0; abc < 3; abc++) {
            if(max.v[abc] < self.data[i].v[abc])
                max.v[abc] = self.data[i].v[abc];
        }
    }
    return max;
}

bool p_mesh_indices_check_in_range(pMeshIndices self, int min_incl, int max_excl) {
    assert(min_incl < max_excl);
    ivec3 min_indices = p_mesh_indices_min(self);
    int min = min_indices.v[ivec3_min_index(min_indices)];
    if(min < min_incl)
        return false;
    ivec3 max_indices = p_mesh_indices_max(self);
    int max = max_indices.v[ivec3_min_index(max_indices)];
    return max < max_excl;
}

