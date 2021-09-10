#include "helper.h"
#include "pbase/mathc/sca/uint.h"
#include "pbase/mathc/bool.h"
#include "pbase/mathc/float.h"
#include "pbase/io/ply.h"

#define TYPE ivec3
#define CLASS IVec3Arr
#define FN_NAME ivec3arr

#include "pbase/rhc/dynarray.h"

//
// private
//

enum ply_format {
    PLY_FORMAT_ASCII,
    PLY_FORMAT_BINARY_LE,
    PLY_FORMAT_BINARY_BE
};

enum ply_types {
    PLY_TYPE_NONE,      // for list_type
    PLY_TYPE_CHAR,
    PLY_TYPE_UCHAR,
    PLY_TYPE_SHORT,
    PLY_TYPE_USHORT,
    PLY_TYPE_INT,
    PLY_TYPE_UINT,
    PLY_TYPE_FLOAT,
    PLY_TYPE_DOUBLE,
};

typedef struct {
    char name[32];
    enum ply_types type;
    enum ply_types list_type;
} PlyProperty_s;

typedef struct {
    char name[32];
    PlyProperty_s properties[16];
    int properties_num;
    int num;
} PlyElement_s;

typedef struct {
    enum ply_format format;
    pIoPlyComments comments;
    PlyElement_s elements[8];
    int elements_num;
} PlyHeader_s;


static Str_s ply_eat_type(Str_s s, enum ply_types *opt_type) {
    Str_s name;
    s = str_lstrip(s, ' ');
    s = str_eat_until(s, ' ', &name);
    s = str_eat(s, 1);
    if (opt_type) {
        *opt_type = PLY_TYPE_NONE;
        if (str_equals(name, strc("char"))
            || str_equals(name, strc("int8"))) {
            *opt_type = PLY_TYPE_CHAR;
        } else if (str_equals(name, strc("uchar"))
                   || str_equals(name, strc("uint8"))) {
            *opt_type = PLY_TYPE_UCHAR;
        } else if (str_equals(name, strc("short"))
                   || str_equals(name, strc("int16"))) {
            *opt_type = PLY_TYPE_SHORT;
        } else if (str_equals(name, strc("ushort"))
                   || str_equals(name, strc("uint16"))) {
            *opt_type = PLY_TYPE_USHORT;
        } else if (str_equals(name, strc("int"))
                   || str_equals(name, strc("int32"))) {
            *opt_type = PLY_TYPE_INT;
        } else if (str_equals(name, strc("uint"))
                   || str_equals(name, strc("uint32"))) {
            *opt_type = PLY_TYPE_UINT;
        } else if (str_equals(name, strc("float"))
                   || str_equals(name, strc("float32"))) {
            *opt_type = PLY_TYPE_FLOAT;
        } else if (str_equals(name, strc("double"))
                   || str_equals(name, strc("float64"))) {
            *opt_type = PLY_TYPE_DOUBLE;
        }
    }
    return s;
}

static size_t ply_type_size(enum ply_types type) {
    switch (type) {
        case PLY_TYPE_CHAR:
        case PLY_TYPE_UCHAR:
            return 1;
        case PLY_TYPE_SHORT:
        case PLY_TYPE_USHORT:
            return 2;
        case PLY_TYPE_INT:
        case PLY_TYPE_UINT:
        case PLY_TYPE_FLOAT:
            return 4;
        case PLY_TYPE_DOUBLE:
            return 8;
        default:
            log_error("p_io_ply_load failed to get property num, invalid property");
    }
    return 0;
}

static int ply_property_list_num(const PlyProperty_s *self, Str_s property_data) {
    int64_t size = 0;
    if (self->list_type == PLY_TYPE_CHAR) {
        int8_t num;
        str_eat_int8_binary_le(property_data, &num);
        size = num;
    } else if (self->list_type == PLY_TYPE_UCHAR) {
        uint8_t num;
        str_eat_uint8_binary_le(property_data, &num);
        size = num;
    } else if (self->list_type == PLY_TYPE_SHORT) {
        int16_t num;
        str_eat_int16_binary_le(property_data, &num);
        size = num;
    } else if (self->list_type == PLY_TYPE_USHORT) {
        uint16_t num;
        str_eat_uint16_binary_le(property_data, &num);
        size = num;
    } else if (self->list_type == PLY_TYPE_INT) {
        int32_t num;
        str_eat_int32_binary_le(property_data, &num);
        size = num;
    } else if (self->list_type == PLY_TYPE_INT) {
        uint32_t num;
        str_eat_uint32_binary_le(property_data, &num);
        size = num;
    } else {
        log_error("p_io_load_ply failed, unsupported type as list num type");
        p_error_set("Could not parse ply data");
        return 0;
    }
    if (size <= 0) {
        log_error("p_io_load_ply failed, unsupported list num (must be >0) : %i", size);
        p_error_set("Could not parse ply data");
    }
    return size;
}

static size_t ply_property_list_size(const PlyProperty_s *self, Str_s property_data) {
    int num = ply_property_list_num(self, property_data);
    return ply_type_size(self->list_type) + num * ply_type_size(self->type);
}

static size_t ply_property_size(const PlyProperty_s *self, Str_s property_data) {
    if (self->list_type)
        return ply_property_list_size(self, property_data);
    return ply_type_size(self->type);
}

static size_t ply_element_single_size(const PlyElement_s *self, Str_s element_data) {
    Str_s s = element_data;
    for (int p = 0; p < self->properties_num; p++) {
        s = str_eat(s, ply_property_size(&self->properties[p], s));
    }
    return s.data - element_data.data;
}

static size_t ply_element_size(const PlyElement_s *self, Str_s element_data) {
    Str_s s = element_data;
    for (int i = 0; i < self->num; i++) {
        s = str_eat(s, ply_element_single_size(self, s));
    }
    return s.data - element_data.data;
}

static size_t ply_header_size(const PlyHeader_s *self, Str_s header_data) {
    Str_s s = header_data;
    for (int i = 0; i < self->elements_num; i++) {
        s = str_eat(s, ply_element_size(&self->elements[i], s));
    }
    return s.data - header_data.data;
}

Str_s ply_get_data(Str_s ply_full) {
    Str_s s = str_eat_until_str(ply_full, strc("end_header"), NULL);
    s = str_eat_until(s, '\n', NULL);
    s = str_eat(s, 1);  // '\n'
    return s;
}

static PlyHeader_s ply_parse_header(Str_s data) {
    // to print in C style (3.14, instead of 3,14 on some machines)
    setlocale(LC_ALL, "C");

    Str_s s = data;
    PlyHeader_s header = {0};

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
        return (PlyHeader_s) {0};
    }
    s = str_eat_until(s, '\n', NULL);

    int comments_num = 0;
    PlyElement_s *current_element = NULL;
    for (;;) {
        if (!str_valid(s)) {
            log_error("p_io_ply_load failed, parse not finished");
            p_error_set("Failed to parse ply header");
            return (PlyHeader_s) {0};
        }
        Str_s line;
        s = str_eat_until(s, '\n', &line);
        s = str_eat(s, 1);
        line = str_strip(line, ' ');

        if (str_empty(line))
            continue;

        if (str_begins_with(line, strc("end_header"))) {
            break;
        }

        if (str_begins_with(line, strc("comment "))) {
            line = str_eat_str(line, strc("comment "));
            if (comments_num < P_IO_PLY_MAX_COMMENTS) {
                line.size = usca_max(line.size, P_IO_PLY_COMMENT_MAX_LENGTH - 1);
                strncpy(header.comments[comments_num++], line.data, line.size);
            }
            continue;
        }

        if (str_begins_with(line, strc("element "))) {
            if (header.elements_num >= sizeof header.elements / sizeof *header.elements) {
                log_error("p_io_ply_load failed, max elements reached!");
                p_error_set("Failed to parse ply header");
                return (PlyHeader_s) {0};
            }
            current_element = &header.elements[header.elements_num++];

            line = str_eat_str(line, strc("element "));
            line = str_lstrip(line, ' ');
            Str_s name;
            line = str_eat_until(line, ' ', &name);
            name.size = usca_min(name.size, sizeof current_element->name - 1);
            strncpy(current_element->name, name.data, name.size);
            line = str_lstrip(line, ' ');
            uint64_t size;
            line = str_eat_uint64_ascii(line, &size);
            current_element->num = size;

            if (!line.data) {
                log_error("p_io_ply_load failed to parse element num");
                p_error_set("Failed to parse ply header");
                return (PlyHeader_s) {0};
            }
            continue;
        }

        if (str_begins_with(line, strc("property list "))) {
            if (!current_element) {
                log_error("p_io_ply_load failed, property list before element");
                p_error_set("Failed to parse ply header");
                return (PlyHeader_s) {0};
            }
            if (current_element->properties_num >=
                sizeof current_element->properties / sizeof *current_element->properties) {
                log_error("p_io_ply_load failed, max elements reached!");
                p_error_set("Failed to parse ply header");
                return (PlyHeader_s) {0};
            }
            PlyProperty_s *property = &current_element->properties[current_element->properties_num++];
            line = str_eat_str(line, strc("property list "));
            line = ply_eat_type(line, &property->list_type);
            line = ply_eat_type(line, &property->type);
            Str_s name;
            line = str_lstrip(line, ' ');
            line = str_eat_until(line, ' ', &name);
            name.size = usca_min(name.size, sizeof property->name - 1);
            strncpy(property->name, name.data, name.size);

            if (!line.data) {
                log_error("p_io_ply_load failed to parse property list");
                p_error_set("Failed to parse ply header");
                return (PlyHeader_s) {0};
            }
            continue;
        }

        if (str_begins_with(line, strc("property "))) {
            if (!current_element) {
                log_error("p_io_ply_load failed, property before element");
                p_error_set("Failed to parse ply header");
                return (PlyHeader_s) {0};
            }
            if (current_element->properties_num >=
                sizeof current_element->properties / sizeof *current_element->properties) {
                log_error("p_io_ply_load failed, max elements reached!");
                p_error_set("Failed to parse ply header");
                return (PlyHeader_s) {0};
            }
            PlyProperty_s *property = &current_element->properties[current_element->properties_num++];
            line = str_eat_str(line, strc("property "));
            property->list_type = PLY_TYPE_NONE;
            line = ply_eat_type(line, &property->type);
            Str_s name;
            line = str_lstrip(line, ' ');
            line = str_eat_until(line, ' ', &name);
            name.size = usca_min(name.size, sizeof property->name - 1);
            strncpy(property->name, name.data, name.size);

            if (!line.data) {
                log_error("p_io_ply_load failed to parse property");
                p_error_set("Failed to parse ply header");
                return (PlyHeader_s) {0};
            }
            continue;
        }

        log_error("p_io_ply_load failed to parse header, unknown line keyword");
        p_error_set("Failed to parse ply header");
        return (PlyHeader_s) {0};
    }

    return header;
}

static Str_s ply_parse_type(String *s, Str_s data, enum ply_types type, enum ply_format format) {
    if(p_error())
        return str_new_invalid();
    assume(format == PLY_FORMAT_ASCII || format == PLY_FORMAT_BINARY_LE || format == PLY_FORMAT_BINARY_BE, "wtf");
    char buffer[64];
    Str_s push = {buffer, 64};
    if (type == PLY_TYPE_CHAR) {
        int8_t val;
        if (format == PLY_FORMAT_ASCII)
            data = str_eat_int8_ascii(data, &val);
        else if (format == PLY_FORMAT_BINARY_BE)
            data = str_eat_int8_binary_be(data, &val);
        else
            data = str_eat_int8_binary_le(data, &val);
        str_feed_int8_binary_le(push, val);
        push.size = 1;
    } else if (type == PLY_TYPE_UCHAR) {
        uint8_t val;
        if (format == PLY_FORMAT_ASCII)
            data = str_eat_uint8_ascii(data, &val);
        else if (format == PLY_FORMAT_BINARY_BE)
            data = str_eat_uint8_binary_be(data, &val);
        else
            data = str_eat_uint8_binary_le(data, &val);
        str_feed_uint8_binary_le(push, val);
        push.size = 1;
    } else if (type == PLY_TYPE_SHORT) {
        int16_t val;
        if (format == PLY_FORMAT_ASCII)
            data = str_eat_int16_ascii(data, &val);
        else if (format == PLY_FORMAT_BINARY_BE)
            data = str_eat_int16_binary_be(data, &val);
        else
            data = str_eat_int16_binary_le(data, &val);
        str_feed_int16_binary_le(push, val);
        push.size = 2;
    } else if (type == PLY_TYPE_USHORT) {
        uint16_t val;
        if (format == PLY_FORMAT_ASCII)
            data = str_eat_uint16_ascii(data, &val);
        else if (format == PLY_FORMAT_BINARY_BE)
            data = str_eat_uint16_binary_be(data, &val);
        else
            data = str_eat_uint16_binary_le(data, &val);
        str_feed_uint16_binary_le(push, val);
        push.size = 2;
    } else if (type == PLY_TYPE_INT) {
        int32_t val;
        if (format == PLY_FORMAT_ASCII)
            data = str_eat_int32_ascii(data, &val);
        else if (format == PLY_FORMAT_BINARY_BE)
            data = str_eat_int32_binary_be(data, &val);
        else
            data = str_eat_int32_binary_le(data, &val);
        str_feed_int32_binary_le(push, val);
        push.size = 4;
    } else if (type == PLY_TYPE_UINT) {
        uint32_t val;
        if (format == PLY_FORMAT_ASCII)
            data = str_eat_uint32_ascii(data, &val);
        else if (format == PLY_FORMAT_BINARY_BE)
            data = str_eat_uint32_binary_be(data, &val);
        else
            data = str_eat_uint32_binary_le(data, &val);
        str_feed_uint32_binary_le(push, val);
        push.size = 4;
    } else if (type == PLY_TYPE_FLOAT) {
        float val;
        if (format == PLY_FORMAT_ASCII)
            data = str_eat_float_ascii(data, &val);
        else if (format == PLY_FORMAT_BINARY_BE)
            data = str_eat_float_binary_be(data, &val);
        else
            data = str_eat_float_binary_le(data, &val);
        str_feed_float_binary_le(push, val);
        push.size = 4;
    } else if (type == PLY_TYPE_DOUBLE) {
        double val;
        data = str_eat_double_ascii(data, &val);
        if (format == PLY_FORMAT_ASCII)
            data = str_eat_double_ascii(data, &val);
        else if (format == PLY_FORMAT_BINARY_BE)
            data = str_eat_double_binary_be(data, &val);
        else
            data = str_eat_double_binary_le(data, &val);
        str_feed_double_binary_le(push, val);
        push.size = 8;
    } else {
        log_error("p_io_load_ply failed to parse unknown type");
        p_error_set("Could not parse ply data");
        return data;
    }
    string_append(s, push);
    return data;
}

static Str_s ply_parse_property_list(String *s, Str_s data, const PlyProperty_s *self, enum ply_format format) {
    if(p_error())
        return str_new_invalid();
    Str_s list_data = ply_parse_type(s, data, self->list_type, format);
    Str_s parsed_list_num = str_eat(s->str, s->size - ply_type_size(self->list_type));
    int num = ply_property_list_num(self, parsed_list_num);
    for (int i = 0; i < num; i++) {
        list_data = ply_parse_type(s, list_data, self->type, format);
    }
    return list_data;
}

static Str_s ply_parse_property(String *s, Str_s data, const PlyProperty_s *self, enum ply_format format) {
    if(p_error())
        return str_new_invalid();
    if (self->list_type) {
        return ply_parse_property_list(s, data, self, format);
    }
    return ply_parse_type(s, data, self->type, format);
}

static Str_s ply_parse_element(String *s, Str_s data, const PlyElement_s *self, enum ply_format format) {
    if(p_error())
        return str_new_invalid();
    for (int i = 0; i < self->num; i++) {
        for (int p = 0; p < self->properties_num; p++) {
            data = ply_parse_property(s, data, &self->properties[p], format);
        }
    }
    return data;
}

static void ply_parse_data(String *s, Str_s data, const PlyHeader_s *self) {
    for (int i = 0; i < self->elements_num; i++) {
        data = ply_parse_element(s, data, &self->elements[i], self->format);
    }
}

static float ply_grep_type_as_float(Str_s data, enum ply_types type) {
    if (type == PLY_TYPE_CHAR) {
        int8_t val;
        data = str_eat_int8_binary_le(data, &val);
        return (float) val / INT8_MAX;
    } else if (type == PLY_TYPE_UCHAR) {
        uint8_t val;
        data = str_eat_uint8_binary_le(data, &val);
        return (float) val / UINT8_MAX;
    } else if (type == PLY_TYPE_SHORT) {
        int16_t val;
        data = str_eat_int16_binary_le(data, &val);
        return (float) val / INT16_MAX;
    } else if (type == PLY_TYPE_USHORT) {
        uint16_t val;
        data = str_eat_uint16_binary_le(data, &val);
        return (float) val / UINT16_MAX;
    } else if (type == PLY_TYPE_INT) {
        int32_t val;
        data = str_eat_int32_binary_le(data, &val);
        return (float) val / INT32_MAX;
    } else if (type == PLY_TYPE_UINT) {
        uint32_t val;
        data = str_eat_uint32_binary_le(data, &val);
        return (float) val / UINT32_MAX;
    } else if (type == PLY_TYPE_FLOAT) {
        float val;
        data = str_eat_float_binary_le(data, &val);
        return val;
    } else if (type == PLY_TYPE_DOUBLE) {
        double val;
        data = str_eat_double_binary_le(data, &val);
        return (float) val;
    }
    return NAN;
}

static float ply_grep_type_as_int(Str_s data, enum ply_types type) {
    if (type == PLY_TYPE_CHAR) {
        int8_t val;
        data = str_eat_int8_binary_le(data, &val);
        return val;
    } else if (type == PLY_TYPE_UCHAR) {
        uint8_t val;
        data = str_eat_uint8_binary_le(data, &val);
        return val;
    } else if (type == PLY_TYPE_SHORT) {
        int16_t val;
        data = str_eat_int16_binary_le(data, &val);
        return val;
    } else if (type == PLY_TYPE_USHORT) {
        uint16_t val;
        data = str_eat_uint16_binary_le(data, &val);
        return val;
    } else if (type == PLY_TYPE_INT) {
        int32_t val;
        data = str_eat_int32_binary_le(data, &val);
        return val;
    } else if (type == PLY_TYPE_UINT) {
        uint32_t val;
        data = str_eat_uint32_binary_le(data, &val);
        return val;
    } else if (type == PLY_TYPE_FLOAT) {
        float val;
        data = str_eat_float_binary_le(data, &val);
        return val;
    } else if (type == PLY_TYPE_DOUBLE) {
        double val;
        data = str_eat_double_binary_le(data, &val);
        return val;
    }
    return NAN;
}

static pCloud ply_data_grep_cloud(const PlyHeader_s *header, Str_s data, const char *element_name,
                                  const char *x, const char *y, const char *z, const char *opt_w, float init_w) {
    int element_pos = -1;
    for (int i = 0; i < header->elements_num; i++) {
        if (strcmp(element_name, header->elements[i].name) == 0) {
            element_pos = i;
            break;
        }
    }
    if (element_pos < 0)
        return p_cloud_new_invalid();

    const PlyElement_s *element = &header->elements[element_pos];

    ivec3 xyz_pos = ivec3_set(-1);
    int w_pos = -1;
    for (int p = 0; p < element->properties_num; p++) {
        for (int xyz = 0; xyz < 3; xyz++) {
            if (strcmp((const char *[]) {x, y, z}[xyz], element->properties[p].name) == 0) {
                xyz_pos.v[xyz] = p;
            }
        }
        if (opt_w && strcmp(opt_w, element->properties[p].name) == 0) {
            w_pos = p;
        }
    }
    if (bvec3_any(ivec3_less_than(xyz_pos, 0)))
        return p_cloud_new_invalid();


    // element offset
    for (int i = 0; i < element_pos; i++) {
        size_t size = ply_element_size(element, data);
        data = str_eat(data, size);
    }

    pCloud self = p_cloud_new_empty(element->num);
    for (int i = 0; i < self.size; i++) {
        for (int xyz = 0; xyz < 3; xyz++) {
            const PlyProperty_s *property = &element->properties[xyz_pos.v[xyz]];
            Str_s p_data = data;
            for (int p = 0; p < xyz_pos.v[xyz]; p++) {
                p_data = str_eat(p_data, ply_property_size(&element->properties[p], p_data));
            }
            self.data[i].v[xyz] = ply_grep_type_as_float(p_data, property->type);
        }
        if (w_pos < 0) {
            self.data[i].w = init_w;
        } else {
            const PlyProperty_s *property = &element->properties[w_pos];
            Str_s p_data = data;
            for (int p = 0; p < w_pos; p++) {
                p_data = str_eat(p_data, ply_property_size(&element->properties[p], p_data));
            }
            self.data[i].w = ply_grep_type_as_float(p_data, property->type);
        }

        data = str_eat(data, ply_element_single_size(element, data));
    }
    return self;
}

static pMeshIndices ply_data_grep_mesh_indices(const PlyHeader_s *header, Str_s data, const char *element_name,
                                         const char *list_name) {
    int element_pos = -1;
    for (int i = 0; i < header->elements_num; i++) {
        if (strcmp(element_name, header->elements[i].name) == 0) {
            element_pos = i;
            break;
        }
    }
    if (element_pos < 0)
        return p_mesh_indices_new_invalid();

    const PlyElement_s *element = &header->elements[element_pos];

    int list_pos = -1;
    for (int p = 0; p < element->properties_num; p++) {
        if (list_pos && strcmp(list_name, element->properties[p].name) == 0) {
            list_pos = p;
        }
    }
    if (list_pos < 0)
        return p_mesh_indices_new_invalid();


    // element offset
    for (int i = 0; i < element_pos; i++) {
        size_t size = ply_element_size(&header->elements[i], data);
        data = str_eat(data, size);
    }

    IVec3Arr arr = ivec3arr_new(element->num);
    for (int i = 0; i < element->num; i++) {
        const PlyProperty_s *property = &element->properties[list_pos];
        Str_s p_data = data;
        for (int p = 0; p < list_pos; p++) {
            p_data = str_eat(p_data, ply_property_size(&element->properties[p], p_data));
        }
        int list_size = ply_grep_type_as_int(p_data, property->list_type);
        p_data = str_eat(p_data, ply_type_size(property->list_type));
        if(list_size == 3) {
            ivec3 triangle;
            for(int abc=0; abc<3; abc++) {
                triangle.v[abc] = ply_grep_type_as_int(p_data, property->type);
                p_data = str_eat(p_data, ply_type_size(property->type));
            }
            ivec3arr_push(&arr, triangle);
        } else if(list_size == 4) {
            ivec4 quad;
            for(int abcd=0; abcd<4; abcd++) {
                quad.v[abcd] = ply_grep_type_as_int(p_data, property->type);
                p_data = str_eat(p_data, ply_type_size(property->type));
            }
            ivec3 a = quad.xyz;
            ivec3 b = {{quad.x, quad.z, quad.w}};
            ivec3arr_push(&arr, a);
            ivec3arr_push(&arr, b);
        } else {
            log_warn("p_io_load_ply invalid polygon size: %i", list_size);
        }
        data = str_eat(data, ply_element_single_size(element, data));
    }
    return (pMeshIndices) {arr.array, arr.size};
}


//
// public
//

pError p_io_load_ply(pCloud *out_opt_points, pCloud *out_opt_normals, pCloud *out_opt_colors,
                     pMeshIndices *out_opt_indices,
                     const char *file, pIoPlyComments opt_out_comments) {
    if(!str_ends_with(strc(file), strc(".ply")) && !str_ends_with(strc(file), strc(".PLY"))) {
        log_warn("p_io_load_ply: file does not end with .ply: %s", file);
    }


    String filedata = file_read(file, true);

    if (!string_valid(filedata)) {
        log_warn("p_io_load_ply failed, could not read file: %s", file);
        return p_error_assume();
    }

    String data = string_new(512);

    PlyHeader_s header = ply_parse_header(filedata.str);
    if (p_error())
        goto CLEAN_UP;

    if (opt_out_comments) {
        memcpy(opt_out_comments, header.comments, sizeof header.comments);
    }

    if(header.format != PLY_FORMAT_ASCII) {
        // reread as binary
        string_kill(&filedata);
        filedata = file_read(file, false);
    }

    Str_s fileplydata = ply_get_data(filedata.str);

    // converts data to little endian into the String
    ply_parse_data(&data, fileplydata, &header);
    if (p_error())
        goto CLEAN_UP;

    if (out_opt_points) {
        *out_opt_points = ply_data_grep_cloud(&header, data.str,
                                              "vertex", "x", "y", "z", NULL, 1);
    }
    if(out_opt_normals) {
        *out_opt_normals = ply_data_grep_cloud(&header, data.str,
                                               "vertex", "nx", "ny", "nz", NULL, 0);
    }
    if(out_opt_colors) {
        *out_opt_colors = ply_data_grep_cloud(&header, data.str,
                                              "vertex", "r", "g", "b", "a", 1);
        if (!p_cloud_valid(*out_opt_colors)) {
            *out_opt_colors = ply_data_grep_cloud(&header, data.str,
                                                  "vertex", "red", "green", "blue", "alpha", 1);
        }
    }
    if(out_opt_indices) {
        *out_opt_indices = ply_data_grep_mesh_indices(&header, data.str,
                                                      "face", "vertex_index");
        if(!p_mesh_indices_valid(*out_opt_indices)) {
            *out_opt_indices = ply_data_grep_mesh_indices(&header, data.str,
                                                          "face", "vertex_indices");
        }
    }

    CLEAN_UP:
    string_kill(&data);
    string_kill(&filedata);
    return p_error();
}
