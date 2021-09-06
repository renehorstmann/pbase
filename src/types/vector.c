#include <stdio.h>
#include <string.h>

#include "pbase/rhc/allocator.h"
#include "pbase/types/vector.h"


/** Creates a new Vector structure with empty data (malloc) */
pVector p_vector_new_empty(size_t size) {
    pVector self = {0};
    self.data = p_rhc_malloc_raising(size * sizeof *self.data);
    self.size = size;
    return self;
}

/** Creates a new Vector structure with all zeros (calloc) */
pVector p_vector_new_zeros(size_t size) {
    pVector self = p_vector_new_empty(size);
    memset(self.data, 0, self.size * sizeof *self.data);
    return self;
}

/** Frees a Vector structure */
void p_vector_kill(pVector *self) {
    if(!p_vector_valid(*self))
        return;
    p_rhc_free(self->data);
    *self = (pVector) {0};
}


/** Prints all elements to stdout */
void p_vector_print(pVector self) {
    if(!p_vector_valid(self)) {
        puts("p_vector_print: invalid");
        return;
    }
    puts("pc_vector_print:");
    for(size_t i = 0; i < self.size; i++) {
        printf("%f\n", self.data[i]);
    }
}
