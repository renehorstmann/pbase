#ifndef P_RHC_ALLOCATOR_H
#define P_RHC_ALLOCATOR_H

#include "types.h"

//
// Options
//
#ifndef P_RHC_STRING_DEFAULT_ALLOCATOR
#define P_RHC_STRING_DEFAULT_ALLOCATOR allocator_new_raising()
#endif

#ifndef P_RHC_DYNARRAY_DEFAULT_ALLOCATOR
#define P_RHC_DYNARRAY_DEFAULT_ALLOCATOR allocator_new_raising()
#endif

#ifndef P_RHC_HASHMAP_DEFAULT_ALLOCATOR
#define P_RHC_HASHMAP_DEFAULT_ALLOCATOR allocator_new_raising()
#endif

//
// Functions
//

// malloc
void *p_rhc_malloc(size_t size);

// realloc
void *p_rhc_realloc(void *memory, size_t size);

// free
void p_rhc_free(void *memory);

// malloc + assume
void *p_rhc_malloc_raising(size_t size);

// realloc + assume
void *p_rhc_realloc_raising(void *memory, size_t size);


// uses p_rhc_malloc, p_rhc_realloc, p_rhc_free
Allocator_s allocator_new_default();

// uses p_rhc_malloc_raising, p_rhc_realloc_raising, p_rhc_free
Allocator_s allocator_new_raising();

// does nothing, but is valid
// malloc, realloc will return NULL
Allocator_s allocator_new_empty();

// will always raise a signal, but is valid
// if the signal is catched and ignored, NULL is returned
Allocator_s allocator_new_empty_raising();


#endif //P_RHC_ALLOCATOR_H
