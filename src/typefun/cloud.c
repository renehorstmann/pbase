#include <stdio.h>
#include <string.h>

#include "pointc/typefun/cloud.h"



void pc_cloud_print(PcCloud *self) {
    puts("pc_cloud_print:");
    for (int r = 0; r < self->rows; r++) {
        printf("row[%d]\n", r);
        for (int c = 0; c < self->cols; c++) {
            printf("%.2f %.2f %.2f %.2f\n",
                   self->data[r * self->cols + c][0],
                   self->data[r * self->cols + c][1],
                   self->data[r * self->cols + c][2],
                   self->data[r * self->cols + c][3]
            );
        }
    }
}

void pc_cloud_concatenate(PcCloud *out_concatenate, PcCloud a, PcCloud b) {
    pc_cloud_concatenate_v(out_concatenate, (PcCloud[]) {a, b}, 2);
}

void pc_cloud_concatenate_v(PcCloud *out_concatenate, const PcCloud *cloud_list, int n) {
    int points = 0;
    for(int i=0; i<n; i++)
        points += cloud_list[i].rows * cloud_list[i].cols;
    pc_cloud_init_empty(out_concatenate, 1, points);
    pc_vec4 *data = out_concatenate->data;
    for(int i=0; i<n; i++) {
        int size = cloud_list[i].rows * cloud_list[i].cols;
        memcpy(data, cloud_list[i].data, sizeof(pc_vec4) * size);
        data += size;
    }
}

void pc_cloud_apply_indices(PcCloud *out_cloud, PcCloud cloud, PcIndices indices) {
    pc_cloud_init_empty(out_cloud, 1, indices.size);

    for(int i=0; i<indices.size; i++)
        memcpy(out_cloud->data[i], cloud.data[indices.data[i]], sizeof(pc_vec4));
}
