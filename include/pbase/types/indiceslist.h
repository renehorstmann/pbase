#ifndef PBASE_TYPES_INDICESLIST_H
#define PBASE_TYPES_INDICESLIST_H

#include <stdbool.h>
#include "indices.h"

/**
 * IndicesList data type.
 * A list of Indices
 */
typedef struct {
    pIndices *list;
    int size;
    bool owns_indices;
} pIndicesList;

/** Returns true if the indices list is in a valid state */
static bool p_indices_list_valid(pIndicesList self) {
    return self.list && self.size>0;
}

/** Returns an invalid IndicesList */
static pIndicesList p_indices_list_new_invalid() {
    return (pIndicesList) {0};
}

/** Creates a new IndicesList structure with empty (to zero) PcIndices structs */
pIndicesList p_indices_list_new(int size);

/** Frees a IndicesList structure */
void p_indices_list_kill(pIndicesList *self);

/** Appends an Indices object to the list and returns its reference */
pIndices *p_indices_list_append(pIndicesList *self);

#endif //PBASE_TYPES_INDICESLIST_H
