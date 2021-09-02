#include <stdio.h>

#include "pbase/pbase.h"
#include "pbase/mathc/mathc.h"


int main() {
    puts("start");

    pCloud points;
    pMeshIndices indices;
    p_meshprimitives_box(&points, &indices, mat4_eye(), 100, 50, 10);

    puts("fin");
}
