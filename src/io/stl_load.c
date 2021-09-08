#include "helper.h"
#include "pbase/io/stl.h"

#define TYPE vec4
#define CLASS Vec4Arr
#define FN_NAME vec4arr
#include "pbase/rhc/dynarray.h"

//
// private
//

pError parse_ascii(pCloud *out_points, Str_s data) {
    if(!str_begins_with(data, strc("solid"))) {
        return p_error_set("Not an ascii STL file");
    }

    // to print in C style (3.14, instead of 3,14 on some machines)
    setlocale(LC_ALL, "C");

    Str_s s = data;
    s = str_eat_until(s, '\n', NULL);

    Vec4Arr arr = vec4arr_new(128);

    bool valid = false;
    for(;;) {
        s = str_lstrip(s, ' ');

        if(str_begins_with(s, strc("endsolid"))) {
            valid = true;
            break;
        }

        s = str_eat_str(s, strc("facet normal"));
        vec3 normal;
        s = eat_vec3_ascii(s, &normal);
        s = str_lstrip(s, ' ');
        s = str_eat_str(s, strc("outer loop"));
        vec3 a, b, c;
        for(int abc=0; abc<3; abc++) {
            s = str_lstrip(s, ' ');
            s = str_eat_str(s, strc("vertex"));
            s = eat_vec3_ascii(s, (vec3*[]){&a, &b, &c}[abc]);
        }
        s = str_lstrip(s, ' ');
        s = str_eat_str(s, strc("endloop"));
        s = str_lstrip(s, ' ');
        s = str_eat_str(s, strc("endfacet"));

        if(str_valid(s)) {
            vec3 calced_normal = triangle_normal(a, b, c);
            vec4arr_push(&arr, (vec4) {{a.x, a.y, a.z, 1}});
            if(vec3_dot(normal, calced_normal) > 0) {
                vec4arr_push(&arr, (vec4) {{b.x, b.y, b.z, 1}});
                vec4arr_push(&arr, (vec4) {{c.x, c.y, c.z, 1}});
            } else {
                vec4arr_push(&arr, (vec4) {{c.x, c.y, c.z, 1}});
                vec4arr_push(&arr, (vec4) {{b.x, b.y, b.z, 1}});
            }
        } else {
            break;
        }
    }

    if(valid) {
        // move
        out_points->data = arr.array;
        out_points->size = arr.size;
    } else {
        vec4arr_kill(&arr);
        *out_points = p_cloud_new_invalid();
        p_error_set("Failed to parse stl file");
    }

    return p_error();
}

pError parse_binary(pCloud *out_points, Str_s data) {
    if(str_begins_with(data, strc("solid"))) {
        return p_error_set("Not a binary STL file");
    }

    Str_s s = data;
    s = str_eat(s, 80); // Header

    // stl is little endian
    uint32_t triangles;
    s = str_eat_uint32_binary_le(s, &triangles);

    if(!str_valid(s) || triangles == 0)
        return p_error_set("Failed to parse stl file");

    *out_points = p_cloud_new_empty(triangles*3);

    for(uint32_t t=0; t<triangles; t++) {
        vec3 normal, a, b, c;
        s = eat_vec3_le(s, &normal);
        s = eat_vec3_le(s, &a);
        s = eat_vec3_le(s, &b);
        s = eat_vec3_le(s, &c);
        uint16_t attr_byte_cnt;
        s = str_eat_uint16_binary_le(s, &attr_byte_cnt);  // Attribute byte count

        if(!str_valid(s) || attr_byte_cnt != 0) {
            p_error_set("Failed to parse stl file");
            break;
        }

        vec3 calced_normal = triangle_normal(a, b, c);
        out_points->data[t*3+0] = (vec4) {{a.x, a.y, a.z, 1}};
        if(vec3_dot(normal, calced_normal) > 0) {
            out_points->data[t*3+1] = (vec4) {{b.x, b.y, b.z, 1}};
            out_points->data[t*3+2] = (vec4) {{c.x, c.y, c.z, 1}};
        } else {
            out_points->data[t*3+1] = (vec4) {{c.x, c.y, c.z, 1}};
            out_points->data[t*3+2] = (vec4) {{b.x, b.y, b.z, 1}};
        }
    }

    if(p_error()) {
        p_cloud_kill(out_points);
    }

    return p_error();
}


//
// public
//

pError p_io_load_mesh_stl(pCloud *out_points, pMeshIndices *out_opt_indices, const char *file) {
    String data = file_read(file, true);

    if(!string_valid(data)) {
        log_warn("p_io_load_mesh_stl failed, could not read file: %s", file);
        assert(p_error());  // should be set by file_read
        return p_error();
    }

    bool ascii;
    if(str_begins_with(data.str, strc("solid"))) {
        ascii = true;
    } else {
        ascii = false;
        string_kill(&data);
        data = file_read(file, false);
    }

    if(ascii)
        parse_ascii(out_points, data.str);
    else
        parse_binary(out_points, data.str);

    string_kill(&data);

    if(out_opt_indices) {
        *out_opt_indices = p_mesh_indices_new_count_up(out_points->size/3);
    }

    return p_error();
}
