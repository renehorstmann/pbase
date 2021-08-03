#ifndef PBASE_TYPES_INDICESLIST_H
#define PBASE_TYPES_INDICESLIST_H
#ifdef __cplusplus
extern "C" {
#endif

#include "pointc/types.h"


/** Appends an Indices object to the list and returns its reference */
PcIndices *pc_indices_list_append(PcIndicesList *self);


#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPES_INDICESLIST_H
