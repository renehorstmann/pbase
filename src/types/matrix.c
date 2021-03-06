#include <stdio.h>
#include <string.h>

#include "pbase/rhc/alloc.h"
#include "pbase/types/matrix.h"


/** Creates a new Matrix structure with empty data (malloc) */
pMatrix p_matrix_new_empty(int cols, int rows) {
    pMatrix self = {0};
    self.data = p_rhc_malloc(cols * rows * sizeof *self.data);
    self.cols = cols;
    self.rows = rows;
    return self;
}

/** Creates a new Matrix structure with all zeros (calloc) */
pMatrix p_matrix_new_zeros(int cols, int rows) {
    pMatrix self = p_matrix_new_empty(cols, rows);
    memset(self.data, 0, self.cols * self.rows * sizeof *self.data);
    return self;
}

/** Frees a Matrix structure */
void p_matrix_kill(pMatrix *self) {
    if(!p_matrix_valid(*self))
        return;
    p_rhc_free(self->data);
    *self = (pMatrix) {0};
}


/** Prints all elements to stdout */
void p_matrix_print(pMatrix self) {
    if(!p_matrix_valid(self)) {
        puts("p_matrix_print: invalid");
        return;
    }
    puts("p_matrix_print:");
    for(int r = 0; r < self.rows; r++) {
        for(int c = 0; c < self.cols; c++) {
            printf("%f ", self.data[r*self.cols + c]);
        }
        printf("\n");
    }
}
