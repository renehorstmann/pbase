#include <stdio.h>
#include <stdlib.h>
#include "pbase/io/stl.h"
#include "helper.h"


static void stl() {
    vec4 data_cloud[4] = {
            {{0, 0, 0, 1}},
            {{10, 0, 0, 1}},
            {{0, 10, 0, 1}},
            {{10, 10, 0, 1}}
    };
    ivec3 data_indices[2] = {
            {{0, 1, 2}},
            {{2, 1, 3}}
    };
    vec4 data_cloud_unpacked[6] = {
            {{0, 0, 0, 1}},
            {{10, 0, 0, 1}},
            {{0, 10, 0, 1}},
            {{0, 10, 0, 1}},
            {{10, 0, 0, 1}},
            {{10, 10, 0, 1}}
    };


    pCloud save_points = {data_cloud, 4};
    pMeshIndices save_indices = {data_indices, 2};

    p_io_save_mesh_stl(save_points, save_indices, "test_io_ascii.stl", true);
    if(p_error()) {
        printf("p_io_save_mesh_stl ascii failed, %s", p_error());
        exit(1);
    }

    p_io_save_mesh_stl(save_points, save_indices, "test_io_binary.stl", false);
    if(p_error()) {
        printf("p_io_save_mesh_stl binary failed, %s", p_error());
        exit(1);
    }


    pCloud load_points;
    p_io_load_mesh_stl(&load_points, "test_io_ascii.stl");
    if(p_error()) {
        printf("p_io_load_mesh_stl ascii failed, %s", p_error());
        exit(1);
    }
    if(!equals_cloud(load_points, (pCloud) {data_cloud_unpacked, 6})) {
        printf("p_io_load_mesh_stl ascii failed, loaded cloud is wrong");
        exit(1);
    }
    p_cloud_kill(&load_points);

    p_io_load_mesh_stl(&load_points, "test_io_binary.stl");
    if(p_error()) {
        printf("p_io_load_mesh_stl binary failed, %s", p_error());
        exit(1);
    }
    if(!equals_cloud(load_points, (pCloud) {data_cloud_unpacked, 6})) {
        printf("p_io_load_mesh_stl binary failed, loaded cloud is wrong");
        exit(1);
    }
    p_cloud_kill(&load_points);



}

int main() {
    stl();

}
