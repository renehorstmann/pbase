#include <stdio.h>

#include "pbase/pbase.h"

int main() {
    puts("start");

    pCloud points;
    p_io_load_stl(&points, "test_io_stl_giraffebinary.stl");

    pMeshIndices indices = p_mesh_indices_new_count_up(points.size/3);
    p_io_save_stl(points, indices, "giraffe_ascii.stl", true);

    puts("fin");
}
