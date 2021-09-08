#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pbase/rhc/allocator.h"

#include "pbase/mathc/sca/int.h"
#include "pbase/types/indices.h"


pIndices p_indices_new_empty(size_t size) {
    pIndices self = {0};
    self.data = p_rhc_malloc_raising(size * sizeof *self.data);
    self.size = size;
    return self;
}

pIndices p_indices_new_zeros(size_t size) {
    pIndices self = p_indices_new_empty(size);
    memset(self.data, 0, self.size * sizeof *self.data);
    return self;}

pIndices p_indices_new_range(int start, int end, int step) {
    if(start == end || step == 0)
        return p_indices_new_invalid();
    assert(step != 0);
    int diff = end - start;
    size_t size = abs(diff / step);
    pIndices self = p_indices_new_empty(size);
    if((step > 0 && end < start) || (step < 0 && end > start))
        start = end;
    for(size_t i=0; i<size; i++) {
        self.data[i] = start;
        start += step;
    }
    return self;
}

void p_indices_kill(pIndices *self) {
    if(!p_indices_valid(*self))
        return;
    p_rhc_free(self->data);
    *self = (pIndices) {0};
}


void p_indices_print(pIndices self) {
    if(!p_indices_valid(self)) {
        puts("p_indices_print: invalid");
        return;
    }
    puts("p_indices_print:");
    for(size_t i = 0; i < self.size; i++) {
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
    if(!self || !p_indices_valid(*self))
        return;
    qsort(self->data, self->size, sizeof(int), comp);
}

void p_indices_as_set(pIndices *self) {
    if(!self || !p_indices_valid(*self))
        return;
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
    if(!self || !p_indices_valid(*self) || !p_indices_valid(remove))
        return;
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
    if(!self || !p_indices_valid(*self))
        return;
    for(size_t i = 0; i < self->size; i++)
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
    for(size_t i=0; i<indices.size; i++) {
        int index = isca_mod_positive(indices.data[i], self.size);
        ret.data[i] = self.data[index];
    }
    return ret;
}

int p_indices_min(pIndices self) {
    int min = INT_MAX;
    for(size_t i=0; i<self.size; i++) {
        if(min > self.data[i])
            min = self.data[i];
    }
    return min;
}

int p_indices_max(pIndices self) {
    int max = INT_MAX;
    for(size_t i=0; i<self.size; i++) {
        if(max < self.data[i])
            max = self.data[i];
    }
    return max;
}
