#include <stdio.h>

#include "pointc/types/matrix.h"


void pc_matrix_print(PcMatrix *self) {
    puts("pc_matrix_print:");
    for (int r = 0; r < self->rows; r++) {
        printf("row[%d]\n", r);
        for (int c = 0; c < self->cols; c++) {
            printf("%f\n", self->data[r * self->cols + c]);
        }
    }
}
