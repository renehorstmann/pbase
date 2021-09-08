#include <stdio.h>
#include <stdlib.h>
#include "pbase/io/io.h"
#include "helper.h"


static void stl() {
    vec4 data_cloud[4] = {
            {{0,  0,  0, 1}},
            {{10, 0,  0, 1}},
            {{0,  10, 0, 1}},
            {{10, 10, 0, 1}}
    };
    ivec3 data_indices[2] = {
            {{0, 1, 2}},
            {{2, 1, 3}}
    };
    vec4 data_cloud_unpacked[6] = {
            {{0,  0,  0, 1}},
            {{10, 0,  0, 1}},
            {{0,  10, 0, 1}},
            {{0,  10, 0, 1}},
            {{10, 0,  0, 1}},
            {{10, 10, 0, 1}}
    };


    pCloud save_points = {data_cloud, 4};
    pMeshIndices save_indices = {data_indices, 2};

    p_io_save_mesh_stl(save_points, save_indices, "test_io_ascii.stl", true);
    if (p_error()) {
        printf("p_io_save_mesh_stl ascii failed, %s", p_error());
        exit(1);
    }

    p_io_save_mesh_stl(save_points, save_indices, "test_io_binary.stl", false);
    if (p_error()) {
        printf("p_io_save_mesh_stl binary failed, %s", p_error());
        exit(1);
    }


    pCloud load_points;
    pMeshIndices load_indices;
    p_io_load_mesh_stl(&load_points, &load_indices, "test_io_ascii.stl");
    if (p_error()) {
        printf("p_io_load_mesh_stl ascii failed, %s", p_error());
        exit(1);
    }
    if (!equals_cloud(load_points, (pCloud) {data_cloud_unpacked, 6})) {
        printf("p_io_load_mesh_stl ascii failed, loaded cloud is wrong");
        exit(1);
    }
    p_cloud_kill(&load_points);
    p_mesh_indices_kill(&load_indices);

    p_io_load_mesh_stl(&load_points, &load_indices, "test_io_binary.stl");
    if (p_error()) {
        printf("p_io_load_mesh_stl binary failed, %s", p_error());
        exit(1);
    }
    if (!equals_cloud(load_points, (pCloud) {data_cloud_unpacked, 6})) {
        printf("p_io_load_mesh_stl binary failed, loaded cloud is wrong");
        exit(1);
    }
    p_cloud_kill(&load_points);
    p_mesh_indices_kill(&load_indices);
}


static void ply() {
    vec4 data_cloud[4] = {
            {{0,  0,  0, 1}},
            {{10, 0,  0, 1}},
            {{0,  10, 0, 1}},
            {{10, 10, 0, 1}}
    };
    vec4 data_normals[4] = {
            {{-0.5, -0.5, 0.7071, 0}},
            {{0.5,  -0.5, 0.7071, 0}},
            {{-0.5, 0.5,  0.7071, 0}},
            {{0.5,  0.5,  0.7071, 0}}
    };
    vec4 data_colors[4] = {
            {{1, 0, 0, 1}},
            {{0, 1, 0, 1}},
            {{0, 0, 1, 1}},
            {{1, 1, 1, 1}}
    };
    ivec3 data_indices[2] = {
            {{0, 1, 2}},
            {{2, 1, 3}}
    };


    pCloud save_points = {data_cloud, 4};
    pCloud save_normals = {data_normals, 4};
    pCloud save_colors = {data_colors, 4};
    pMeshIndices save_indices = {data_indices, 2};

    p_io_save_mesh_normals_colored_ply(save_points, save_normals, save_colors, save_indices,
                                       "test_io_ascii.ply", true);
    if (p_error()) {
        printf("p_io_save_mesh_normals_colored_ply ascii failed, %s", p_error());
        exit(1);
    }

    p_io_save_mesh_normals_colored_ply(save_points, save_normals, save_colors, save_indices,
                                       "test_io_binary.ply", true);
    if (p_error()) {
        printf("p_io_save_mesh_normals_colored_ply binary failed, %s", p_error());
        exit(1);
    }


    pCloud load_points;
    pCloud load_normals;
    pCloud load_colors;
    pMeshIndices load_indices;
    p_io_load_mesh_normals_colored_ply(&load_points, &load_normals, &load_colors, &load_indices, "test_io_ascii.ply");
    if (p_error()) {
        printf("p_io_load_mesh_normals_colored_ply ascii failed, %s", p_error());
        exit(1);
    }
    if (!equals_cloud(load_points, save_points)
        || !equals_cloud(load_normals, save_normals)
        || !equals_cloud(load_colors, save_colors)
        || !equals_mesh_indices(load_indices, save_indices)) {
        printf("p_io_load_mesh_normals_colored_ply ascii failed, loaded data is wrong");
        exit(1);
    }
    p_cloud_kill(&load_points);
    p_cloud_kill(&load_normals);
    p_cloud_kill(&load_colors);
    p_mesh_indices_kill(&load_indices);

    p_io_load_mesh_normals_colored_ply(&load_points, &load_normals, &load_colors, &load_indices, "test_io_binary.ply");
    if (p_error()) {
        printf("p_io_load_mesh_normals_colored_ply binary failed, %s", p_error());
        exit(1);
    }
    if (!equals_cloud(load_points, save_points)
        || !equals_cloud(load_normals, save_normals)
        || !equals_cloud(load_colors, save_colors)
        || !equals_mesh_indices(load_indices, save_indices)) {
        printf("p_io_load_mesh_normals_colored_ply binary failed, loaded data is wrong");
        exit(1);
    }
    p_cloud_kill(&load_points);
    p_cloud_kill(&load_normals);
    p_cloud_kill(&load_colors);
    p_mesh_indices_kill(&load_indices);
}

int main() {
    stl();
    ply();

}
