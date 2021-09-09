#ifndef PBASE_TYPES_VECTOR_H
#define PBASE_TYPES_VECTOR_H

#include <stdbool.h>

/**
* Vector data type.
*/
typedef struct {
    float *restrict data;
    int size;
} pVector;


/** Returns true if the vector is in a valid state */
static bool p_vector_valid(pVector self) {
    return self.data && self.size>0;
}

/** Returns an invalid Vector */
static pVector p_vector_new_invalid() {
    return (pVector) {0};
}

/** Creates a new Vector structure with empty data (malloc) */
pVector p_vector_new_empty(int size);

/** Creates a new Vector structure with all zeros (calloc) */
pVector p_vector_new_zeros(int size);

/** Frees a Vector structure */
void p_vector_kill(pVector *self);


/** Prints all elements to stdout */
void p_vector_print(pVector self);


#endif //PBASE_TYPES_VECTOR_H
