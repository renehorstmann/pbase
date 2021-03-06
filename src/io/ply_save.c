#include "helper.h"
#include "pbase/io/ply.h"

//
// private
//

static bool check_clouds_valid(pCloud points, pCloud normals, pCloud colors) {
    if (p_cloud_valid(points) && p_cloud_valid(normals) && points.size != normals.size) {
        return false;
    }
    if (p_cloud_valid(points) && p_cloud_valid(colors) && points.size != colors.size) {
        return false;
    }
    if (p_cloud_valid(normals) && p_cloud_valid(colors) && normals.size != colors.size) {
        return false;
    }
    return true;
}

static int get_vertex_size(pCloud points, pCloud normals, pCloud colors) {
    int vertex_size = 0;
    if (p_cloud_valid(points))
        vertex_size = points.size;
    else if (p_cloud_valid(normals))
        vertex_size = normals.size;
    else if (p_cloud_valid(colors))
        vertex_size = colors.size;
    return vertex_size;
}


static String generate_header(pCloud points, pCloud normals, pCloud colors, pMeshIndices indices,
                              bool ascii, bool color_alpha, const pIoPlyComments opt_comments) {
    String data = string_new(512);
    String *s = &data;

    // to print in C style (3.14, instead of 3,14 on some machines)
    setlocale(LC_ALL, "C");

    string_append(s, strc("ply\n"));
    if (ascii) {
        string_append(s, strc("format ascii 1.0\n"));
    } else {
        string_append(s, strc("format binary_little_endian 1.0\n"));
    }

    if (!opt_comments) {
        string_append(s, strc("comment PLY generated by pbase_io_ply\n"));
    } else {
        for (int i = 0; i < P_IO_PLY_MAX_COMMENTS; i++) {
            if (*opt_comments[i]) {
                string_append(s, strc("comment "));
                string_append(s, strc(opt_comments[i]));
                string_push(s, '\n');
            }
        }
    }

    int vertex_size = get_vertex_size(points, normals, colors);
    if (vertex_size > 0) {
        char buf[32];
        snprintf(buf, 32, "%i", vertex_size);
        string_append(s, strc("element vertex "));
        string_append(s, strc(buf));
        string_push(s, '\n');

        if (p_cloud_valid(points)) {
            string_append(s, strc("property float x\nproperty float y\nproperty float z\n"));
        }
        if (p_cloud_valid(normals)) {
            string_append(s, strc("property float nx\nproperty float ny\nproperty float nz\n"));
        }
        if (p_cloud_valid(colors)) {
            string_append(s, strc("property uchar red\nproperty uchar green\nproperty uchar blue\n"));
            if (color_alpha)
                string_append(s, strc("property uchar alpha\n"));
        }
    }

    if (p_mesh_indices_valid(indices)) {
        char buf[32];
        snprintf(buf, 32, "%i", indices.size);
        string_append(s, strc("element face "));
        string_append(s, strc(buf));
        string_push(s, '\n');

        string_append(s, strc("property list uchar int vertex_indices\n"));
    }

    string_append(s, strc("end_header\n"));

    return data;
}


static String generate_ascii(pCloud points, pCloud normals, pCloud colors, pMeshIndices indices,
                             bool color_alpha, const pIoPlyComments opt_comments) {
    // to print in C style (3.14, instead of 3,14 on some machines)
    setlocale(LC_ALL, "C");

    String data = generate_header(points, normals, colors, indices, true, color_alpha, opt_comments);
    String *s = &data;

    int vertex_size = get_vertex_size(points, normals, colors);
    for (int i = 0; i < vertex_size; i++) {
        char buf[256];
        if (p_cloud_valid(points)) {
            snprintf(buf, 256, "%f %f %f ", points.data[i].x, points.data[i].y, points.data[i].z);
            string_append(s, strc(buf));
        }
        if (p_cloud_valid(normals)) {
            snprintf(buf, 256, "%f %f %f ", normals.data[i].x, normals.data[i].y, normals.data[i].z);
            string_append(s, strc(buf));
        }
        if (p_cloud_valid(colors)) {
            ucvec4 col = ucvec4_cast_from_float_1(colors.data[i].v);
            if (color_alpha)
                snprintf(buf, 256, "%i %i %i %i ", col.r, col.g, col.b, col.a);
            else
                snprintf(buf, 256, "%i %i %i ", col.r, col.g, col.b);
            string_append(s, strc(buf));
        }
        string_push(s, '\n');
    }

    for (int i = 0; i < indices.size; i++) {
        char buf[256];
        snprintf(buf, 256, "3 %i %i %i\n", indices.data[i].v0, indices.data[i].v1, indices.data[i].v2);
        string_append(s, strc(buf));
    }

    return data;
}

static String generate_binary(pCloud points, pCloud normals, pCloud colors, pMeshIndices indices,
                              bool color_alpha, const pIoPlyComments opt_comments) {
    String header = generate_header(points, normals, colors, indices, false, color_alpha, opt_comments);

    size_t data_size = 0;

    int vertex_size = get_vertex_size(points, normals, colors);
    if (p_cloud_valid(points))
        data_size += vertex_size * (3 * 4); // vec3
    if (p_cloud_valid(normals))
        data_size += vertex_size * (3 * 4); // vec3
    if (p_cloud_valid(colors))
        data_size += vertex_size * (3 * 1); // ucvec3
    if (p_mesh_indices_valid(indices))
        data_size += indices.size * (1 + (3 * 4));  // uchar + ivec3

    String data = string_new(data_size);
    data.size = data_size;
    Str_s s = data.str;

    for (int i = 0; i < vertex_size; i++) {
        if (p_cloud_valid(points)) {
            s = feed_vec3_le(s, points.data[i].xyz);
        }
        if (p_cloud_valid(normals)) {
            s = feed_vec3_le(s, normals.data[i].xyz);
        }
        if (p_cloud_valid(colors)) {
            ucvec4 col = ucvec4_cast_from_float_1(colors.data[i].v);
            if (color_alpha)
                s = feed_ucvec4_le(s, col);
            else
                s = feed_ucvec3_le(s, col.rgb);
        }
    }

    for (int i = 0; i < indices.size; i++) {
        s = str_feed_uint8_binary_le(s, 3);
        s = feed_ivec3_le(s, indices.data[i]);
    }

    if (s.data != data.data + data_size || s.size != 0) {
        log_error("p_io_ply failed to generate binary");
    }

    string_append(&header, data.str);
    string_kill(&data);
    return header;
}


//
// public
//

pError p_io_save_ply(pCloud points, pCloud normals, pCloud colors, pMeshIndices indices,
                     const char *file, bool ascii, const pIoPlyComments opt_comments) {
    if(!str_ends_with(strc(file), strc(".ply")) && !str_ends_with(strc(file), strc(".PLY"))) {
        log_warn("p_io_save_ply: file does not end with .ply: %s", file);
    }

    if (!check_clouds_valid(points, normals, colors)) {
        log_error("p_io_save_ply failed to generate file");
        return p_error_set("Invalid parameters");
    }

    bool color_alpha = false;
    if (p_cloud_valid(colors) && p_cloud_min(colors).a < 1) {
        color_alpha = true;
    }

    String data;
    if (ascii)
        data = generate_ascii(points, normals, colors, indices, color_alpha, opt_comments);
    else
        data = generate_binary(points, normals, colors, indices, color_alpha, opt_comments);

    if (!file_write(file, data.str, ascii)) {
        log_error("p_io_save_ply failed to write file");
        p_error_assume();  // should be set by file_write
    }

    string_kill(&data);
    return p_error();
}


