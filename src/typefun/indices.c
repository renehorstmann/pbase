#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "pointc/mathc/float.h"
#include "pointc/typefun/indices.h"


void pc_indices_print(PcIndices *self) {
    puts("pc_indices_print:");
    for (int i = 0; i < self->size; i++) {
        printf("%d\n", self->data[i]);
    }
}

static int comp(const void *elem1, const void *elem2) {
    int f = *((int *) elem1);
    int s = *((int *) elem2);
    if (f > s) return 1;
    if (f < s) return -1;
    return 0;
}

void pc_indices_sort(PcIndices *self) {
    qsort(self->data, self->size, sizeof(int), comp);
}

void pc_indices_as_set(PcIndices *self) {
    pc_indices_sort(self);
    if (self->size <= 1)
        return;

    int from_index = 1; // first element cant be skipped
    int to_index = 0;
    for (; from_index < self->size; from_index++) {
        assert(to_index < from_index);
        if (self->data[to_index] != self->data[from_index])
            self->data[++to_index] = self->data[from_index];
    }
    self->size = to_index + 1; //size = last_index+1
}

void pc_indices_set_diff(PcIndices *self, PcIndices remove) {
    if (remove.size <= 0 || self->size <= 0)
        return;
    int from_index = 0;
    int to_index = 0;
    int remove_index = 0;
    for (; from_index < self->size; from_index++) {
        int from = self->data[from_index];
        while (remove_index < remove.size
               && from > remove.data[remove_index])
            remove_index++;

        if (from < remove.data[remove_index] || remove_index >= remove.size)
            self->data[to_index++] = from;
    }
    self->size = to_index; //size = to_index = last_index+1
}

void pc_indices_add_offset(PcIndices *self, int offset) {
    for (int i = 0; i < self->size; i++)
        self->data[i] += offset;
}

void pc_indices_concatenate(PcIndices *out_concatenate, PcIndices a, PcIndices b) {
    pc_indices_concatenate_v(out_concatenate, (PcIndices[]) {a, b}, 2);
}

void pc_indices_concatenate_v(PcIndices *out_concatenate, const PcIndices *indices_list, int n) {
    int indices = 0;
    for (int i = 0; i < n; i++)
        indices += indices_list[i].size;
    pc_indices_init_empty(out_concatenate, indices);
    int *data = out_concatenate->data;
    for (int i = 0; i < n; i++) {
        int size = indices_list[i].size;
        memcpy(data, indices_list[i].data, sizeof(int) * size);
        data += size;
    }
}
