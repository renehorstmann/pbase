#ifndef PBASE_TYPES_INDICESLIST_H
#define PBASE_TYPES_INDICESLIST_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h> // size_t
#include <stdbool.h>
#include "indices.h"

/**
 * IndicesList data type.
 * A list of Indices
 */
typedef struct {
    pIndices *list;
    size_t size;
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
pIndicesList p_indices_list_new(size_t size);

/** Frees a IndicesList structure */
void p_indices_list_kill(pIndicesList *self);

/** Appends an Indices object to the list and returns its reference */
pIndices *p_indices_list_append(pIndicesList *self);


#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPES_INDICESLIST_H
