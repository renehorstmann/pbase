#include <assert.h>
#include <string.h>
#include "pbase/rhc/allocator.h"
#include "pbase/rhc/log.h"
#include "pbase/types.h"

#include "pbase/mathc/mathc.h"


pCloud p_cloud_new_empty(size_t size) {
    pCloud self = {0};
    self.data = p_rhc_malloc_raising(size * sizeof *self.data);
    self.size = size;
    return self;
}

pCloud p_cloud_new_zeros(size_t size) {
    pCloud self = p_cloud_new_empty(size);
    memset(self.data, 0, self.size * sizeof *self.data);
    return self;
}

pCloud p_cloud_new_zeros_1(size_t size) {
    pCloud self = p_cloud_new_zeros(size);
    for(int i=0; i<self.size; i++) {
        self.data[i].w = 1;
    }
    return self;
}

void p_cloud_kill(pCloud *self) {
    p_rhc_free(self->data);
    *self = (pCloud) {0};
}



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
    for(int i=0; i<size; i++) {
        self.data[i] = start;
        start += step;
    }
    return self;
}

void p_indices_kill(pIndices *self) {
    p_rhc_free(self->data);
    *self = (pIndices) {0};
}
