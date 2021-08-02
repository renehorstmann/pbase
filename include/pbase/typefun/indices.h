#ifndef PBASE_TYPEFUN_INDICES_H
#define PBASE_TYPEFUN_INDICES_H
#ifdef __cplusplus
extern "C" {
#endif

#include "../types.h"


// Prints all indices to stdout
void p_indices_print(pIndices self);

// Sorts the internal indices list in ascending order
void p_indices_sort(pIndices *self);

// Deletes all duplicate indices (result will be sorted)
void p_indices_as_set(pIndices *self);

/**
 * Removes all indices of the (sorted) set remove from the (sorted) set self.
 * @param self: must be a sorted set.
 * @param remove: must be a sorted set.
 */
void p_indices_set_diff(pIndices *self, pIndices remove);

// Adds an offset to each index
void p_indices_add_offset(pIndices *self, int offset);

// Concatenates two indices together, into the new pIndices out_concatenate.
pIndices p_indices_concatenate(pIndices a, pIndices b);

// Concatenates a list/vector of indices together, into the new pIndices out_concatenate.
pIndices p_indices_concatenate_v(const pIndices *indices_list, int n);

// Applies indices on indices, so that all not used indices are removed
pIndices p_indices_apply_indices(pIndices self, pIndices indices);



#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPEFUN_INDICES_H
