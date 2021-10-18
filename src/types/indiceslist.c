#include <stdlib.h>
#include <string.h>

#include "pbase/rhc/alloc.h"

#include "pbase/types/indiceslist.h"

pIndicesList p_indices_list_new(int size) {
    pIndicesList self = {0};
    self.list = p_rhc_malloc(size * sizeof *self.list);
    self.size = size;
    self.owns_indices = true;
    memset(self.list, 0, size * sizeof *self.list);
    return self;
}

void p_indices_list_kill(pIndicesList *self) {
    if(!p_indices_list_valid(*self))
        return;
    if(self->owns_indices) {
        for (int i = 0; i < self->size; i++) {
            p_indices_kill(&self->list[i]);
        }
    }
    p_rhc_free(self->list);
    *self = (pIndicesList) {0};
}

pIndices *p_indices_list_append(pIndicesList *self) {
    self->list = p_rhc_realloc(self->list, ++self->size * sizeof *self->list);
    if (!self->list)
        return self->size--, NULL;
    return &self->list[self->size - 1];
}


