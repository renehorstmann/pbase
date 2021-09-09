#include <stdio.h>

#include "pbase/pbase.h"

int main() {
    puts("start");

    pCloud points;
    pMeshIndices indices;
    p_io_load_mesh_ply(&points, &indices, "../python/test.ply");
    p_error_check();
    puts("loaded");

    p_io_save_mesh_ply(points, indices, "test_io_ascii.ply", true);
    p_error_check();
    puts("saved_ascii");
    p_io_save_mesh_ply(points, indices, "test_io_binary.ply", false);
    p_error_check();
    puts("saved_binary");

    puts("fin");
}
