#include "helper.h"
#include "pbase/mathc/sca/uint.h"
#include "pbase/io/ply.h"

#define TYPE ivec3
#define CLASS IVec3Arr
#define FN_NAME ivec3arr
#include "pbase/rhc/dynarray.h"

//
// private
//

Str_s get_ply_data(Str_s ply_full) {
    Str_s s = str_eat_until_str(ply_full, strc("end_header"), NULL);
    s = str_eat_until(s, '\n', NULL);
    s = str_eat(s, 1);  // '\n'
    return s;
}

enum ply_format {
    PLY_FORMAT_ASCII,
    PLY_FORMAT_BINARY_LE,
    PLY_FORMAT_BINARY_BE
};

typedef struct {
    enum ply_format format;
    size_t vertex_size;
    bool points;
    bool normals;
    bool colors;
    size_t indices_size;
    bool indices_unsigned;
    pIoPlyComments comments;
} PlyHeader;

static bool ply_header_valid(PlyHeader self) {
    return self.vertex_size > 0 || self.indices_size > 0;
}

static PlyHeader parse_header(Str_s data) {
    // to print in C style (3.14, instead of 3,14 on some machines)
    setlocale(LC_ALL, "C");

    Str_s s = data;
    PlyHeader header = {0};
    int header_comments = 0;

    s = str_eat_str(s, strc("ply"));
    s = str_lstrip(s, ' ');
    if (str_begins_with(s, strc("format ascii 1.0")))
        header.format = PLY_FORMAT_ASCII;
    else if (str_begins_with(s, strc("format binary_little_endian 1.0")))
        header.format = PLY_FORMAT_BINARY_LE;
    else if (str_begins_with(s, strc("format binary_big_endian 1.0")))
        header.format = PLY_FORMAT_BINARY_BE;
    else {
        log_error("p_io_load_ply failed, wrong format or ply indicator");
        p_error_set("Could not parse ply header");
        return (PlyHeader) {0};
    }

    s = str_eat_until(s, '\n', NULL);

    // comments
    for (;;) {
        s = str_lstrip(s, ' ');
        if (str_begins_with(s, strc("comment "))) {
            if (header_comments < P_IO_PLY_MAX_COMMENTS) {
                s = str_eat_str(s, strc("comment "));
                Str_s comment;
                str_eat_until(s, '\n', &comment);
                // strncpy does not set '\0'...
                strncpy(header.comments[header_comments++], comment.data,
                        usca_min(comment.size, P_IO_PLY_COMMENT_MAX_LENGTH - 1));
            }
            s = str_eat_until(s, '\n', NULL);
        } else {
            break;
        }
    }

    // vertex element
    s = str_lstrip(s, ' ');
    if (str_begins_with(s, strc("element vertex "))) {
        s = str_eat_str(s, strc("element vertex "));
        uint64_t num;
        s = str_eat_uint64_ascii(s, &num);
        header.vertex_size = num;

        // points
        s = str_lstrip(s, ' ');
        if (str_begins_with(s, strc("property float x"))
            || str_begins_with(s, strc("property float32 x"))) {
            s = str_eat_until(s, '\n', NULL);

            s = str_lstrip(s, ' ');
            if (!str_begins_with(s, strc("property float y"))
                && !str_begins_with(s, strc("property float32 y"))) {
                log_error("p_io_load_ply failed, got x but not y");
                p_error_set("Could not parse ply header");
                return (PlyHeader) {0};
            }
            s = str_eat_until(s, '\n', NULL);

            s = str_lstrip(s, ' ');
            if (!str_begins_with(s, strc("property float z"))
                && !str_begins_with(s, strc("property float32 z"))) {
                log_error("p_io_load_ply failed, got xy but not z");
                p_error_set("Could not parse ply header");
                return (PlyHeader) {0};
            }
            s = str_eat_until(s, '\n', NULL);

            header.points = true;
        }

        // normals
        s = str_lstrip(s, ' ');
        if (str_begins_with(s, strc("property float nx"))
            || str_begins_with(s, strc("property float32 nx"))) {
            s = str_eat_until(s, '\n', NULL);

            s = str_lstrip(s, ' ');
            if (!str_begins_with(s, strc("property float ny"))
                && !str_begins_with(s, strc("property float32 ny"))) {
                log_error("p_io_load_ply failed, got nx but not ny");
                p_error_set("Could not parse ply header");
                return (PlyHeader) {0};
            }
            s = str_eat_until(s, '\n', NULL);

            s = str_lstrip(s, ' ');
            if (!str_begins_with(s, strc("property float nz"))
                && !str_begins_with(s, strc("property float32 nz"))) {
                log_error("p_io_load_ply failed, got nx ny but not nz");
                p_error_set("Could not parse ply header");
                return (PlyHeader) {0};
            }
            s = str_eat_until(s, '\n', NULL);

            header.normals = true;
        }

        // colors
        s = str_lstrip(s, ' ');
        if (str_begins_with(s, strc("property uchar r"))
            || str_begins_with(s, strc("property uint8 r"))
            || str_begins_with(s, strc("property uchar r"))
            || str_begins_with(s, strc("property uint8 red"))) {
            s = str_eat_until(s, '\n', NULL);

            s = str_lstrip(s, ' ');
            if (!str_begins_with(s, strc("property uchar g"))
                && !str_begins_with(s, strc("property uint8 g"))
                && !str_begins_with(s, strc("property uchar green"))
                && !str_begins_with(s, strc("property uint8 green"))) {
                log_error("p_io_load_ply failed, got red but not green");
                p_error_set("Could not parse ply header");
                return (PlyHeader) {0};
            }
            s = str_eat_until(s, '\n', NULL);

            s = str_lstrip(s, ' ');
            if (!str_begins_with(s, strc("property uchar b"))
                && !str_begins_with(s, strc("property uint8 b"))
                && !str_begins_with(s, strc("property uchar blue"))
                && !str_begins_with(s, strc("property uint8 blue"))) {
                log_error("p_io_load_ply failed, got red green but not blue");
                p_error_set("Could not parse ply header");
                return (PlyHeader) {0};
            }
            s = str_eat_until(s, '\n', NULL);

            header.colors = true;
        }

        if (!header.points && !header.normals && !header.colors) {
            log_error("p_io_load_ply failed, got vertex element with no valid properties");
            p_error_set("Could not parse ply header");
            return (PlyHeader) {0};
        }
    }

    // face element
    s = str_lstrip(s, ' ');
    if (str_begins_with(s, strc("element face "))) {
        s = str_eat_str(s, strc("element face "));
        uint64_t num;
        s = str_eat_uint64_ascii(s, &num);
        header.indices_size = num;

        s = str_lstrip(s, ' ');
        if (str_begins_with(s, strc("property list uchar uint "))
            || str_begins_with(s, strc("property list uint8 uint32 "))) {
            header.indices_unsigned = true;
        } else if (str_begins_with(s, strc("property list uchar int "))
                   || str_begins_with(s, strc("property list uint8 int32 "))) {
            header.indices_unsigned = false;
        }

        s = str_eat_until(s, '\n', NULL);
    }

    s = str_lstrip(s, ' ');
    s = str_eat_str(s, strc("end_header"));

    if (!str_valid(s)) {
        log_error("p_io_load_ply failed to parse header");
        p_error_set("Could not parse ply header");
        return (PlyHeader) {0};
    }

    return header;
}


static void parse_ascii(pCloud *out_opt_points, pCloud *out_opt_normals, pCloud *out_opt_colors,
                        pMeshIndices *out_opt_indices,
                        PlyHeader header, Str_s data) {
    // to print in C style (3.14, instead of 3,14 on some machines)
    setlocale(LC_ALL, "C");

    Str_s s = get_ply_data(data);
    for (size_t i = 0; i < header.vertex_size; i++) {
        if(header.points) {
            vec3 point;
            s = eat_vec3_ascii(s, &point);
            if(out_opt_points) {
                out_opt_points->data[i].xyz = point;
                out_opt_points->data[i].w = 1;
            }
        }
        if(header.normals) {
            vec3 normal;
            s = eat_vec3_ascii(s, &normal);
            if(out_opt_normals) {
                out_opt_normals->data[i].xyz = normal;
                out_opt_normals->data[i].w = 0;
            }
        }
        if(header.colors) {
            ucvec3 color;
            s = eat_ucvec3_ascii(s, &color);
            if(out_opt_colors) {
                out_opt_colors->data[i].rgb = vec3_cast_from_uchar_1(color.v);
                out_opt_colors->data[i].a = 1;
            }
        }
    }

    if(!out_opt_indices)
        return;

    if(header.indices_size==0)
        *out_opt_indices = p_mesh_indices_new_invalid();

    IVec3Arr arr = ivec3arr_new(header.indices_size);

    for(size_t i=0; i<header.indices_size; i++) {
        uint8_t list_size;
        s = str_eat_uint8_ascii(s, &list_size);
        if(!str_valid(s) || list_size<3 || list_size>4) {
            log_error("p_io_load_ply failed to parse indices list_size");
            p_error_set("Could not parse ply data");
            goto CLEAN_UP;
        }
        if(list_size == 3) {
            ivec3 triangle;
            s = eat_ivec3_ascii(s, &triangle);
            ivec3arr_push(&arr, triangle);
        } else {
            ivec4 quad;
            s = eat_ivec4_ascii(s, &quad);
            ivec3 a = quad.xyz;
            ivec3 b = {{quad.x, quad.z, quad.w}};
            ivec3arr_push(&arr, a);
            ivec3arr_push(&arr, b);
        }
    }

    out_opt_indices->data = arr.array;
    out_opt_indices->size = arr.size;
    arr.array = NULL;

    CLEAN_UP:
    ivec3arr_kill(&arr);
}

static void parse_binary_le(pCloud *out_opt_points, pCloud *out_opt_normals, pCloud *out_opt_colors,
                            pMeshIndices *out_opt_indices,
                            PlyHeader header, Str_s data) {
    Str_s s = get_ply_data(data);

    for (size_t i = 0; i < header.vertex_size; i++) {
        if(header.points) {
            vec3 point;
            s = eat_vec3_le(s, &point);
            if(out_opt_points) {
                out_opt_points->data[i].xyz = point;
                out_opt_points->data[i].w = 1;
            }
        }
        if(header.normals) {
            vec3 normal;
            s = eat_vec3_le(s, &normal);
            if(out_opt_normals) {
                out_opt_normals->data[i].xyz = normal;
                out_opt_normals->data[i].w = 0;
            }
        }
        if(header.colors) {
            ucvec3 color;
            s = eat_ucvec3_le(s, &color);
            if(out_opt_colors) {
                out_opt_colors->data[i].rgb = vec3_cast_from_uchar_1(color.v);
                out_opt_colors->data[i].a = 1;
            }
        }
    }

    if(!out_opt_indices)
        return;

    if(header.indices_size==0)
        *out_opt_indices = p_mesh_indices_new_invalid();

    IVec3Arr arr = ivec3arr_new(header.indices_size);

    for(size_t i=0; i<header.indices_size; i++) {
        uint8_t list_size;
        s = str_eat_uint8_binary_le(s, &list_size);
        if(!str_valid(s) || list_size<3 || list_size>4) {
            log_error("p_io_load_ply failed to parse indices list_size");
            p_error_set("Could not parse ply data");
            goto CLEAN_UP;
        }
        if(list_size == 3) {
            ivec3 triangle;
            if(header.indices_unsigned) {
                uvec3 ut;
                s = eat_uvec3_le(s, &ut);
                triangle = ivec3_cast_from_unsigned(ut.v);
            } else {
                s = eat_ivec3_le(s, &triangle);
            }
            ivec3arr_push(&arr, triangle);
        } else {
            ivec4 quad;
            if(header.indices_unsigned) {
                uvec4 ut;
                s = eat_uvec4_le(s, &ut);
                quad = ivec4_cast_from_unsigned(ut.v);
            } else {
                s = eat_ivec4_le(s, &quad);
            }
            ivec3 a = quad.xyz;
            ivec3 b = {{quad.x, quad.z, quad.w}};
            ivec3arr_push(&arr, a);
            ivec3arr_push(&arr, b);
        }
    }

    out_opt_indices->data = arr.array;
    out_opt_indices->size = arr.size;
    arr.array = NULL;

    CLEAN_UP:
    ivec3arr_kill(&arr);
}

static void parse_binary_be(pCloud *out_opt_points, pCloud *out_opt_normals, pCloud *out_opt_colors,
                            pMeshIndices *out_opt_indices,
                            PlyHeader header, Str_s data) {
    Str_s s = get_ply_data(data);

    for (size_t i = 0; i < header.vertex_size; i++) {
        if(header.points) {
            vec3 point;
            s = eat_vec3_be(s, &point);
            if(out_opt_points) {
                out_opt_points->data[i].xyz = point;
                out_opt_points->data[i].w = 1;
            }
        }
        if(header.normals) {
            vec3 normal;
            s = eat_vec3_be(s, &normal);
            if(out_opt_normals) {
                out_opt_normals->data[i].xyz = normal;
                out_opt_normals->data[i].w = 0;
            }
        }
        if(header.colors) {
            ucvec3 color;
            s = eat_ucvec3_be(s, &color);
            if(out_opt_colors) {
                out_opt_colors->data[i].rgb = vec3_cast_from_uchar_1(color.v);
                out_opt_colors->data[i].a = 1;
            }
        }
    }

    if(!out_opt_indices)
        return;

    if(header.indices_size==0)
        *out_opt_indices = p_mesh_indices_new_invalid();

    IVec3Arr arr = ivec3arr_new(header.indices_size);

    for(size_t i=0; i<header.indices_size; i++) {
        uint8_t list_size;
        s = str_eat_uint8_binary_be(s, &list_size);
        if(!str_valid(s) || list_size<3 || list_size>4) {
            log_error("p_io_load_ply failed to parse indices list_size");
            p_error_set("Could not parse ply data");
            goto CLEAN_UP;
        }
        if(list_size == 3) {
            ivec3 triangle;
            if(header.indices_unsigned) {
                uvec3 ut;
                s = eat_uvec3_be(s, &ut);
                triangle = ivec3_cast_from_unsigned(ut.v);
            } else {
                s = eat_ivec3_be(s, &triangle);
            }
            ivec3arr_push(&arr, triangle);
        } else {
            ivec4 quad;
            if(header.indices_unsigned) {
                uvec4 ut;
                s = eat_uvec4_be(s, &ut);
                quad = ivec4_cast_from_unsigned(ut.v);
            } else {
                s = eat_ivec4_be(s, &quad);
            }
            ivec3 a = quad.xyz;
            ivec3 b = {{quad.x, quad.z, quad.w}};
            ivec3arr_push(&arr, a);
            ivec3arr_push(&arr, b);
        }
    }

    out_opt_indices->data = arr.array;
    out_opt_indices->size = arr.size;
    arr.array = NULL;

    CLEAN_UP:
    ivec3arr_kill(&arr);
}


//
// public
//

pError p_io_load_ply(pCloud *out_opt_points, pCloud *out_opt_normals, pCloud *out_opt_colors,
                     pMeshIndices *out_opt_indices,
                     const char *file, pIoPlyComments opt_out_comments) {
    String data = file_read(file, true);

    if (!string_valid(data)) {
        log_warn("p_io_load_ply failed, could not read file: %s", file);
        assert(p_error());  // should be set by file_read
        return p_error();
    }

    PlyHeader header = parse_header(data.str);
    if (!ply_header_valid(header)) {
        assert(p_error());  // should be set by parse_header
        return p_error();
    }

    if (opt_out_comments) {
        memcpy(opt_out_comments, header.comments, sizeof header.comments);
    }

    if(out_opt_points) {
        if(header.points)
            *out_opt_points = p_cloud_new_empty(header.vertex_size);
        else
            *out_opt_points = p_cloud_new_invalid();
    }

    if(out_opt_normals) {
        if(header.normals)
            *out_opt_normals = p_cloud_new_empty(header.vertex_size);
        else
            *out_opt_normals = p_cloud_new_invalid();
    }

    if(out_opt_colors) {
        if(header.colors)
            *out_opt_colors = p_cloud_new_empty(header.vertex_size);
        else
            *out_opt_colors = p_cloud_new_invalid();
    }

    switch (header.format) {
        case PLY_FORMAT_ASCII:
            parse_ascii(out_opt_points, out_opt_normals, out_opt_colors, out_opt_indices,
                        header, data.str);
            break;
        case PLY_FORMAT_BINARY_LE:
            parse_binary_le(out_opt_points, out_opt_normals, out_opt_colors, out_opt_indices,
                            header, data.str);
            break;
        case PLY_FORMAT_BINARY_BE:
            parse_binary_be(out_opt_points, out_opt_normals, out_opt_colors, out_opt_indices,
                            header, data.str);
            break;
        default:
            assume(false, "wtf");
    }

    string_kill(&data);
    return p_error();
}
