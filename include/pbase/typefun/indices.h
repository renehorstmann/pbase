#ifndef PBASE_TYPEFUN_INDICES_H
#define PBASE_TYPEFUN_INDICES_H
#ifdef __cplusplus
extern "C" {
#endif

#include "pointc/types.h"


/** Prints all indices to stdout */
void pc_indices_print(PcIndices *self);

/** Sorts the internal indices list in ascending order */
void pc_indices_sort(PcIndices *self);

/** Deletes all duplicate indices (result will be sorted) */
void pc_indices_as_set(PcIndices *self);

/**
 * Removes all indices of the (sorted) set remove from the (sorted) set self.
 * @param self: must be a sorted set.
 * @param remove: must be a sorted set.
 */
void pc_indices_set_diff(PcIndices *self, PcIndices remove);

/** adds an offset to each index */
void pc_indices_add_offset(PcIndices *self, int offset);

/** Concatenates two indices together, into the new PcIndices out_concatenate. */
void pc_indices_concatenate(PcIndices *out_concatenate, PcIndices a, PcIndices b);

/** Concatenates a list/vector of indices together, into the new PcIndices out_concatenate. */
void pc_indices_concatenate_v(PcIndices *out_concatenate, const PcIndices *indices_list, int n);




#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPEFUN_INDICES_H
