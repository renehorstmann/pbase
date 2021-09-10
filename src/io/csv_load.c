#include <locale.h>
#include "pbase/rhc/string.h"
#include "pbase/rhc/str_parse.h"
#include "pbase/rhc/file.h"
#include "pbase/io/csv.h"

#define TYPE float
#define CLASS FltArr
#define FN_NAME fltarr
#include "pbase/rhc/dynarray.h"

static const char *delimiters = "\t,:;|";


static void replace_delimiters_with_spaces(Str_s data) {
    for(int i=0; i<strlen(delimiters); i++) {
        str_replace(data, delimiters[i], ' ');
    }
}

pError parse_indices_list(pIndicesList *out_list, Str_s data) {

}

pError parse_matrix(pMatrix *out_mat, Str_s data) {
    // to print in C style (3.14, instead of 3,14 on some machines)
    setlocale(LC_ALL, "C");

    FltArr arr = fltarr_new(32);
    int rows = 0;
    int cols = 0;
    for(;;) {
        Str_s line;
        data = str_eat_until(data, '\n', &line);
        data = str_eat(data, 1);
        if(str_empty(data))
            break;

        line = str_lstrip(line, ' ');

        int rowcols = 0;
        while(!str_empty(line)) {
            float val;
            line = str_eat_float_ascii(line, &val);
            line = str_lstrip(line, ' ');
            if(!str_valid(line)) {
                log_error("p_io_load_csv failed to parse float value");
                p_error_set("Failed to parse csv file");
                goto CLEAN_UP;
            }
            fltarr_push(&arr, val);
            rowcols++;
        };

        if(rowcols>0) {
            rows++;
            if(cols <= 0)
                cols = rowcols;
            else if(cols != rowcols) {
                log_error("p_io_load_csv matrix has cols with different sizes");
                p_error_set("Failed to parse csv file");
                goto CLEAN_UP;
            }
        }
    }

    // move
    *out_mat = (pMatrix) {.data=arr.array, .cols=cols, .rows=rows};
    arr = fltarr_new_invalid();

    CLEAN_UP:
    fltarr_kill(&arr);
    return p_error();
}

pError p_io_load_indices_list_csv(pIndicesList *out_list, const char *file) {
    if(!str_ends_with(strc(file), strc(".csv")) && !str_ends_with(strc(file), strc(".CSV"))) {
        log_warn("p_io_load_csv: file does not end with .csv: %s", file);
    }

    String data = file_read(file, true);

    if(!string_valid(data)) {
        log_warn("p_io_load_csv failed, could not read file: %s", file);
        return p_error_assume();
    }

    replace_delimiters_with_spaces(data.str);
    parse_indices_list(out_list, data.str);

    string_kill(&data);
    return p_error();
}

pError p_io_load_matrix_csv(pMatrix *out_mat, const char *file) {
    if(!str_ends_with(strc(file), strc(".csv")) && !str_ends_with(strc(file), strc(".CSV"))) {
        log_warn("p_io_load_csv: file does not end with .csv: %s", file);
    }

    String data = file_read(file, true);

    if(!string_valid(data)) {
        log_warn("p_io_load_csv failed, could not read file: %s", file);
        return p_error_assume();
    }

    replace_delimiters_with_spaces(data.str);
    parse_matrix(out_mat, data.str);

    string_kill(&data);
    return p_error();
}
