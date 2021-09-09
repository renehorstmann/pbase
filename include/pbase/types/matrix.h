#ifndef PBASE_TYPES_MATRIX_H
#define PBASE_TYPES_MATRIX_H

#include <stdbool.h>

/**
* Matrix data type.
*/
typedef struct {
    float *restrict data;
    int cols, rows;
} pMatrix;


/** Returns true if the matrix is in a valid state */
static bool p_matrix_valid(pMatrix self) {
    return self.data  && self.cols>0 && self.rows>0;
}

/** Returns an invalid Matrix */
static pMatrix p_matrix_new_invalid() {
    return (pMatrix) {0};
}

/** Creates a new Matrix structure with empty data (malloc) */
pMatrix p_matrix_new_empty(int cols, int rows);

/** Creates a new Matrix structure with all zeros (calloc) */
pMatrix p_matrix_new_zeros(int cols, int rows);

/** Frees a Matrix structure */
void p_matrix_kill(pMatrix *self);


/** Prints all elements to stdout */
void p_matrix_print(pMatrix self);


#endif //PBASE_TYPES_MATRIX_H
