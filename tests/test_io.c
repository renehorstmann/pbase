#include <stdio.h>
#include <stdlib.h>
#include "pbase/io/io.h"
#include "helper.h"


static void csv_indices_list() {
    int list_a[] = {1, 2, 3, 4, 5};
    int list_b[] = {10, 20, 30};

    pIndicesList list = {(pIndices[]) {
            (pIndices) {list_a, 5},
            (pIndices) {list_b, 3}
    }, 2};


    p_io_save_indices_list_csv(list, "test_io_indices_list.csv");
    if (p_error()) {
        printf("p_io_save_indices_list_csv failed, %s", p_error());
        exit(1);
    }

}

static void csv_matrix() {
    mat4 data_matrix = {{
                                1.1, 2.2, 3.3, 4.4,
                                5.5, 6.6, 7.7, 8.8,
                                9.9, 10.10, 11.11, 12.12,
                                13.13, 14.14, 15.15, 16.16
                        }};

    pMatrix mat = {data_matrix.v, 4, 4};

    p_io_save_matrix_csv(mat, "test_io_matrix.csv");
    if (p_error()) {
        printf("p_io_save_matrix_csv failed, %s", p_error());
        exit(1);
    }

    pMatrix load_mat;
    p_io_load_matrix_csv(&load_mat, "test_io_matrix.csv");
    if (p_error()) {
        printf("p_io_load_matrix_csv failed, %s", p_error());
        exit(1);
    }
    if (!equals_matrix(mat, load_mat)) {
        printf("p_io_load_matrix_csv failed, loaded matrix is wrong");
        exit(1);
    }
    p_matrix_kill(&load_mat);
}

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
    csv_indices_list();
    csv_matrix();
    stl();
    ply();
}
