#include <stdio.h>

#include "pbase/pbase.h"
#include "pbase/mathc/mathc.h"


int main() {
    puts("start");

    p_error_set("lol");
    p_error_set("hey");
    p_error_set("ho");

    pCloud points;
    pMeshIndices indices;
    p_meshprimitives_box(&points, &indices, mat4_eye(), 100, 50, 10);

    puts("fin");
}
