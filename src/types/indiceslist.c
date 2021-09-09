#include <stdlib.h>
#include <string.h>

#include "pbase/rhc/allocator.h"

#include "pbase/types/indiceslist.h"

pIndicesList p_indices_list_new(int size) {
    pIndicesList self = {0};
    self.list = p_rhc_malloc_raising(size * sizeof *self.list);
    self.size = size;
    memset(self.list, 0, size * sizeof *self.list);
    return self;
}

void p_indices_list_kill(pIndicesList *self) {
    if(!p_indices_list_valid(*self))
        return;
    p_rhc_free(self->list);
    *self = (pIndicesList) {0};
}

pIndices *p_indices_list_append(pIndicesList *self) {
    self->list = p_rhc_realloc_raising(self->list, ++self->size * sizeof *self->list);
    if (!self->list)
        return self->size--, NULL;
    return &self->list[self->size - 1];
}


