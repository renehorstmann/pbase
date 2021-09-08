#ifndef PBASE_IO_HELPER_H
#define PBASE_IO_HELPER_H

#include <assert.h>
#include <locale.h>
#include "pbase/rhc/string.h"
#include "pbase/rhc/str_parse.h"
#include "pbase/rhc/file.h"
#include "pbase/mathc/vec/vec3.h"
#include "pbase/mathc/vec/ucvec4.h"
#include "pbase/mathc/int.h"
#include "pbase/mathc/types/uint.h"

static vec3 triangle_normal(vec3 a, vec3 b, vec3 c) {
    return vec3_normalize(vec3_cross(vec3_sub_vec(b, a), vec3_sub_vec(c, a)));
}

static void append_vec3(String *s, vec3 v) {
    char buffer[128];
    snprintf(buffer, 128, "%f %f %f", v.x, v.y, v.z);
    string_append(s, strc(buffer));
}

static Str_s eat_vec3_ascii(Str_s s, vec3 *out_v) {
    s = str_eat_float_ascii(s, &out_v->x);
    s = str_eat_float_ascii(s, &out_v->y);
    s = str_eat_float_ascii(s, &out_v->z);
    return s;
}

static Str_s eat_ucvec3_ascii(Str_s s, ucvec3 *out_v) {
    s = str_eat_uint8_ascii(s, &out_v->x);
    s = str_eat_uint8_ascii(s, &out_v->y);
    s = str_eat_uint8_ascii(s, &out_v->z);
    return s;
}

static Str_s eat_ivec3_ascii(Str_s s, ivec3 *out_v) {
    s = str_eat_int32_ascii(s, &out_v->x);
    s = str_eat_int32_ascii(s, &out_v->y);
    s = str_eat_int32_ascii(s, &out_v->z);
    return s;
}

static Str_s eat_ivec4_ascii(Str_s s, ivec4 *out_v) {
    s = str_eat_int32_ascii(s, &out_v->x);
    s = str_eat_int32_ascii(s, &out_v->y);
    s = str_eat_int32_ascii(s, &out_v->z);
    s = str_eat_int32_ascii(s, &out_v->w);
    return s;
}

static Str_s eat_vec3_le(Str_s s, vec3 *out_v) {
    s = str_eat_float_binary_le(s, &out_v->x);
    s = str_eat_float_binary_le(s, &out_v->y);
    s = str_eat_float_binary_le(s, &out_v->z);
    return s;
}

static Str_s eat_vec3_be(Str_s s, vec3 *out_v) {
    s = str_eat_float_binary_be(s, &out_v->x);
    s = str_eat_float_binary_be(s, &out_v->y);
    s = str_eat_float_binary_be(s, &out_v->z);
    return s;
}

static Str_s eat_ucvec3_le(Str_s s, ucvec3 *out_v) {
    s = str_eat_uint8_binary_le(s, &out_v->x);
    s = str_eat_uint8_binary_le(s, &out_v->y);
    s = str_eat_uint8_binary_le(s, &out_v->z);
    return s;
}

static Str_s eat_ucvec3_be(Str_s s, ucvec3 *out_v) {
    s = str_eat_uint8_binary_be(s, &out_v->x);
    s = str_eat_uint8_binary_be(s, &out_v->y);
    s = str_eat_uint8_binary_be(s, &out_v->z);
    return s;
}

static Str_s eat_ivec3_le(Str_s s, ivec3 *out_v) {
    s = str_eat_int32_binary_le(s, &out_v->x);
    s = str_eat_int32_binary_le(s, &out_v->y);
    s = str_eat_int32_binary_le(s, &out_v->z);
    return s;
}

static Str_s eat_ivec3_be(Str_s s, ivec3 *out_v) {
    s = str_eat_int32_binary_be(s, &out_v->x);
    s = str_eat_int32_binary_be(s, &out_v->y);
    s = str_eat_int32_binary_be(s, &out_v->z);
    return s;
}

static Str_s eat_uvec3_le(Str_s s, uvec3 *out_v) {
    s = str_eat_uint32_binary_le(s, &out_v->x);
    s = str_eat_uint32_binary_le(s, &out_v->y);
    s = str_eat_uint32_binary_le(s, &out_v->z);
    return s;
}

static Str_s eat_uvec3_be(Str_s s, uvec3 *out_v) {
    s = str_eat_uint32_binary_be(s, &out_v->x);
    s = str_eat_uint32_binary_be(s, &out_v->y);
    s = str_eat_uint32_binary_be(s, &out_v->z);
    return s;
}

static Str_s eat_ivec4_le(Str_s s, ivec4 *out_v) {
    s = str_eat_int32_binary_le(s, &out_v->x);
    s = str_eat_int32_binary_le(s, &out_v->y);
    s = str_eat_int32_binary_le(s, &out_v->z);
    s = str_eat_int32_binary_le(s, &out_v->w);
    return s;
}

static Str_s eat_ivec4_be(Str_s s, ivec4 *out_v) {
    s = str_eat_int32_binary_be(s, &out_v->x);
    s = str_eat_int32_binary_be(s, &out_v->y);
    s = str_eat_int32_binary_be(s, &out_v->z);
    s = str_eat_int32_binary_be(s, &out_v->w);
    return s;
}

static Str_s eat_uvec4_le(Str_s s, uvec4 *out_v) {
    s = str_eat_uint32_binary_le(s, &out_v->x);
    s = str_eat_uint32_binary_le(s, &out_v->y);
    s = str_eat_uint32_binary_le(s, &out_v->z);
    s = str_eat_uint32_binary_le(s, &out_v->w);
    return s;
}

static Str_s eat_uvec4_be(Str_s s, uvec4 *out_v) {
    s = str_eat_uint32_binary_be(s, &out_v->x);
    s = str_eat_uint32_binary_be(s, &out_v->y);
    s = str_eat_uint32_binary_be(s, &out_v->z);
    s = str_eat_uint32_binary_be(s, &out_v->w);
    return s;
}

static Str_s feed_vec3_le(Str_s str, vec3 v) {
    str = str_feed_float_binary_le(str, v.x);
    str = str_feed_float_binary_le(str, v.y);
    str = str_feed_float_binary_le(str, v.z);
    return str;
}

static Str_s feed_ivec3_le(Str_s str, ivec3 v) {
    str = str_feed_int32_binary_le(str, v.x);
    str = str_feed_int32_binary_le(str, v.y);
    str = str_feed_int32_binary_le(str, v.z);
    return str;
}

static Str_s feed_ucvec3_le(Str_s str, ucvec3 v) {
    str = str_feed_uint8_binary_le(str, v.x);
    str = str_feed_uint8_binary_le(str, v.y);
    str = str_feed_uint8_binary_le(str, v.z);
    return str;
}

static Str_s feed_ucvec4_le(Str_s str, ucvec4 v) {
    str = str_feed_uint8_binary_le(str, v.x);
    str = str_feed_uint8_binary_le(str, v.y);
    str = str_feed_uint8_binary_le(str, v.z);
    str = str_feed_uint8_binary_le(str, v.w);
    return str;
}

#endif //PBASE_IO_HELPER_H
