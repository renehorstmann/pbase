#include <stdio.h>

#include "pointc/types/vector.h"


void pc_vector_print(PcVector *self) {
    puts("pc_vector_print:");
    for (int i = 0; i < self->size; i++) {
        printf("%f\n", self->data[i]);
    }
}
