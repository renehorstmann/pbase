#include <stdio.h>

#include "pbase/pbase.h"

int main() {
    puts("start");

    pCloud points;
    pMeshIndices indices;
    p_io_load_mesh_stl(&points, &indices, "test_io_stl_giraffebinary.stl");
    puts("loaded");

    p_io_save_mesh_ply(points, indices, "test_io_ascii.ply", true);
    puts("saved_ascii");
    p_error_check();
    p_io_save_mesh_ply(points, indices, "test_io_binary.ply", false);
    puts("saved_binary");
    p_error_check();

    puts("fin");
}
