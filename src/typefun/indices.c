#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "pbase/typefun/indices.h"


void p_indices_print(pIndices self) {
    puts("p_indices_print:");
    for (int i = 0; i < self.size; i++) {
        printf("%d\n", self.data[i]);
    }
}

static int comp(const void *elem1, const void *elem2) {
    int f = *((int *) elem1);
    int s = *((int *) elem2);
    if (f > s) return 1;
    if (f < s) return -1;
    return 0;
}

void p_indices_sort(pIndices *self) {
    qsort(self->data, self->size, sizeof(int), comp);
}

void p_indices_as_set(pIndices *self) {
    p_indices_sort(self);
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

void p_indices_set_diff(pIndices *self, pIndices remove) {
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

void p_indices_add_offset(pIndices *self, int offset) {
    for (int i = 0; i < self->size; i++)
        self->data[i] += offset;
}

pIndices p_indices_concatenate(pIndices a, pIndices b) {
    return p_indices_concatenate_v((pIndices[]) {a, b}, 2);
}

pIndices p_indices_concatenate_v(const pIndices *indices_list, int n) {
    size_t size = 0;
    for (int i = 0; i < n; i++)
        size += indices_list[i].size;
    pIndices self = p_indices_new_empty(size);
    int *data = self.data;
    for (int i = 0; i < n; i++) {
        size = indices_list[i].size;
        memcpy(data, indices_list[i].data, sizeof(int) * size);
        data += size;
    }
    return self;
}


pIndices p_indices_apply_indices(pIndices self, pIndices indices) {
    pIndices ret = p_indices_new_empty(indices.size);
    for(int i=0; i<indices.size; i++) {
        ret.data[i] = self.data[indices.data[i]];
    }
    return ret;
}
