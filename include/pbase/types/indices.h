#ifndef PBASE_TYPES_INDICES_H
#define PBASE_TYPES_INDICES_H

#include <stdbool.h>

/**
 * Indices data type.
 */
typedef struct {
    int *restrict data;
    int size;
} pIndices;

/** Returns true if the indices is in a valid state */
static bool p_indices_valid(pIndices self) {
    return self.data && self.size>0;
}

/** Returns invalid Indices */
static pIndices p_indices_new_invalid() {
    return (pIndices) {0};
}

/** Creates a new Indices structure with empty data (malloc) */
pIndices p_indices_new_empty(int size);

/** Creates a new Indices structure with all zeros (calloc) */
pIndices p_indices_new_zeros(int size);

/** Creates a range as Indices */
pIndices p_indices_new_range(int start, int end, int step);

/** Frees a Cloud structure */
void p_indices_kill(pIndices *self);



/** Prints all indices to stdout */
void p_indices_print(pIndices self);

/** Sorts the internal indices list in ascending order */
void p_indices_sort(pIndices *self);

/** Deletes all duplicate indices (result will be sorted) */
void p_indices_as_set(pIndices *self);

/**
 * Removes all indices of the (sorted) set remove from the (sorted) set self.
 * @param self: must be a sorted set.
 * @param remove: must be a sorted set.
 */
void p_indices_set_diff(pIndices *self, pIndices remove);

/** Adds an offset to each index */
void p_indices_add_offset(pIndices *self, int offset);

/** Concatenates two indices together, into the new pIndices out_concatenate. */
pIndices p_indices_concatenate(pIndices a, pIndices b);

/** Concatenates a list/vector of indices together, into the new pIndices out_concatenate. */
pIndices p_indices_concatenate_v(const pIndices *indices_list, int n);

/** Applies indices on indices, so that all not used indices are removed */
pIndices p_indices_apply_indices(pIndices self, pIndices indices);

/** returns the smallest index */
int p_indices_min(pIndices self);

/** returns the biggest index */
int p_indices_max(pIndices self);

#endif //PBASE_TYPES_INDICES_H
