#include <stdio.h>
#include <stdlib.h>
#include <pbase/pbase.h>

int main(int argc, char **argv) {
    if (argc < 3 || argc > 4) {
        printf("Usage: %s <load_mesh.stl> <save_mesh.ply> [ascii=0]", argv[0]);
        exit(EXIT_FAILURE);
    }

    bool ascii = false;
    if(argc==4 && *argv[3]=='1') {
        puts("saving as ascii ply");
        ascii = true;
    }

    pCloud points;
    pMeshIndices indices;
    p_io_load_mesh_stl(&points, &indices, argv[1]);

    p_io_save_mesh_ply(points, indices, argv[2], ascii);

    if(p_error()) {
        printf("An error occured while converting: %s", p_error());
        exit(EXIT_FAILURE);
    }

    p_cloud_kill(&points);
    p_mesh_indices_kill(&indices);
    exit(EXIT_SUCCESS);
}
