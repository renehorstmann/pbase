#include <stdlib.h>

#include "pointc/typefun/indiceslist.h"


PcIndices *pc_indices_list_append(PcIndicesList *self) {
    self->list = realloc(self->list, ++self->size * sizeof(PcIndices));
    if (!self->list)
        return NULL;
    return &self->list[self->size - 1];
}


