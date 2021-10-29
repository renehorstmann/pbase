#ifndef RHC_ALLOCATOR_H
#define RHC_ALLOCATOR_H

#include "types.h"

//
// Options
//
#ifndef RHC_DEFAULT_ALLOCATOR
#define RHC_DEFAULT_ALLOCATOR p_rhc_allocator_new()
#endif

//
// Functions
//

// malloc
void *p_rhc_malloc_try(size_t size);

// calloc
void *p_rhc_calloc_try(size_t size);

// realloc
void *p_rhc_realloc_try(void *memory, size_t size);

// free
void p_rhc_free(void *memory);

// malloc + assume
void *p_rhc_malloc(size_t size);

// calloc + assume
void *p_rhc_calloc(size_t size);

// realloc + assume
void *p_rhc_realloc(void *memory, size_t size);


// uses p_rhc_malloc, p_rhc_realloc, p_rhc_free
Allocator_i p_rhc_allocator_new_try();

// uses p_rhc_malloc_raising, p_rhc_realloc_raising, p_rhc_free
Allocator_i p_rhc_allocator_new();

// does nothing, but is valid
// malloc, realloc will return NULL
Allocator_i p_rhc_allocator_new_empty_try();

// will always raise a signal, but is valid
// if the signal is catched and ignored, NULL is returned
Allocator_i p_rhc_allocator_new_empty();


#endif //RHC_ALLOCATOR_H
