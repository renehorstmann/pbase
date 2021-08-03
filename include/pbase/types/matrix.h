#ifndef PBASE_TYPES_MATRIX_H
#define PBASE_TYPES_MATRIX_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h> // size_t
#include <stdbool.h>

/**
* Matrix data type.
*/
typedef struct {
    float *restrict data;
    size_t cols, rows;
} pMatrix;


/** Returns true if the matrix is in a valid state */
static bool p_matrix_valid(pMatrix self) {
    return self.data  && self.cols>0&& self.rows>0;
}

/** Returns an invalid Matrix */
static pMatrix p_matrix_new_invalid() {
    return (pMatrix) {0};
}

/** Creates a new Matrix structure with empty data (malloc) */
pMatrix p_matrix_new_empty(size_t cols, size_t rows);

/** Creates a new Matrix structure with all zeros (calloc) */
pMatrix p_matrix_new_zeros(size_t cols, size_t rows);

/** Frees a Matrix structure */
void p_matrix_kill(pMatrix *self);


/** Prints all elements to stdout */
void p_matrix_print(pMatrix self);



#ifdef __cplusplus
}
#endif
#endif //PBASE_TYPES_MATRIX_H
