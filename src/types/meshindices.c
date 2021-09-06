#include <stdio.h>
#include <string.h>

#include "pbase/rhc/allocator.h"
#include "pbase/mathc/sca/int.h"
#include "pbase/types/meshindices.h"


pMeshIndices p_mesh_indices_new_empty(size_t size) {
    pMeshIndices self = {0};
    self.data = p_rhc_malloc_raising(size * sizeof *self.data);
    self.size = size;
    return self;
}

pMeshIndices p_mesh_indices_new_zeros(size_t size) {
    pMeshIndices self = p_mesh_indices_new_empty(size);
    memset(self.data, 0, self.size * sizeof *self.data);
    return self;
}

pMeshIndices p_mesh_indices_new_count_up(size_t size) {
    pMeshIndices self = p_mesh_indices_new_empty(size);
    for(size_t i=0; i<self.size; i++) {
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
    for(size_t i = 0; i < self.size; i++) {
        printf("%d %d %d\n", self.data[i].v0, self.data[i].v1, self.data[i].v2);
    }
}

void p_mesh_indices_add_offset(pMeshIndices *self, int offset) {
    for(size_t i=0; i<self->size; i++) {
        for(int abc=0; abc<3; abc++)
            self->data[i].v[abc] += offset;
    }
}

pMeshIndices p_mesh_indices_concatenate(pMeshIndices a, pMeshIndices b) {
    return p_mesh_indices_concatenate_v((pMeshIndices[]) {a, b}, 2);
}

pMeshIndices p_mesh_indices_concatenate_v(const pMeshIndices *mesh_indices_list, int n) {
    size_t size = 0;
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
    for(size_t i=0; i<indices.size; i++) {
        int index = isca_mod_positive(indices.data[i], self.size);
        ret.data[i] = self.data[index];
    }
    return ret;
}
