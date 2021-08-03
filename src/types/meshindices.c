#include <stdio.h>
#include <string.h>

#include "pointc/types/meshindices.h"


void pc_mesh_indices_print(PcMeshIndices *self) {
    puts("pc_mesh_indices_print:");
    for (int i = 0; i < self->size; i++) {
        printf("%d %d %d\n", self->data[i][0], self->data[i][1], self->data[i][2]);
    }
}

void pc_mesh_indices_add_offset(PcMeshIndices *self, int offset) {
    for(int i=0; i<self->size; i++) {
        for(int abc=0; abc<3; abc++)
            self->data[i][abc] += offset;
    }
}

void pc_mesh_indices_concatenate(PcMeshIndices *out_concatenate, PcMeshIndices a, PcMeshIndices b) {
    pc_mesh_indices_concatenate_v(out_concatenate, (PcMeshIndices[]) {a, b}, 2);
}

void pc_mesh_indices_concatenate_v(PcMeshIndices *out_concatenate, const PcMeshIndices *mesh_indices_list, int n) {
    int indices = 0;
    for(int i=0; i<n; i++)
        indices += mesh_indices_list[i].size;
    pc_mesh_indices_init_empty(out_concatenate, indices);
    pc_ivec3 *data = out_concatenate->data;
    for(int i=0; i<n; i++) {
        int size = mesh_indices_list[i].size;
        memcpy(data, mesh_indices_list[i].data, sizeof(pc_ivec3) * size);
        data += size;
    }
}


void pc_mesh_indices_apply_indices(PcMeshIndices *out_mesh, PcMeshIndices mesh, PcIndices indices) {
    pc_mesh_indices_init_empty(out_mesh, indices.size);

    for(int i=0; i<indices.size; i++)
        memcpy(out_mesh->data[i], mesh.data[indices.data[i]], sizeof(pc_ivec3));
}
