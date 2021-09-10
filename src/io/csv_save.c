#include <locale.h>
#include "pbase/rhc/string.h"
#include "pbase/rhc/file.h"
#include "pbase/io/csv.h"


String generate_indices_list(pIndicesList list) {
    if(!p_indices_list_valid(list)) {
        log_error("p_io_save_csv failed, invalid parameters");
        p_error_set("Invalid parameters");
        return string_new_invalid();
    }

    // to print in C style (3.14, instead of 3,14 on some machines)
    setlocale(LC_ALL, "C");

    String data = string_new(512);
    String *s = &data;

    char buffer[128];
    for(int i=0; i<list.size; i++) {
        const pIndices *indices = &list.list[i];
        if(!p_indices_valid(*indices)) {
            log_warn("p_io_save_csv got an invalid list at list[%i]", i);
            continue;
        }
        for(int idx=0; indices->size; idx++) {
            snprintf(buffer, 128, idx==indices->size-1? "%i" : "%i,", indices->data[idx]);
            string_append(s, strc(buffer));
        }
        string_push(s, '\n');
    }

    return data;
}

String generate_matrix(pMatrix mat) {
    if(!p_matrix_valid(mat)) {
        log_error("p_io_save_csv failed, invalid parameters");
        p_error_set("Invalid parameters");
        return string_new_invalid();
    }

    // to print in C style (3.14, instead of 3,14 on some machines)
    setlocale(LC_ALL, "C");

    String data = string_new(512);
    String *s = &data;

    char buffer[128];
    for(int r=0; r < mat.rows; r++) {
        for(int c=0; mat.cols; c++) {
            snprintf(buffer, 128, c == mat.cols - 1 ? "%f" : "%f,", mat.data[r*mat.cols + c]);
            string_append(s, strc(buffer));
        }
        string_push(s, '\n');
    }

    return data;
}


pError p_io_save_indices_list_csv(pIndicesList list, const char *file) {
    if(!str_ends_with(strc(file), strc(".csv")) && !str_ends_with(strc(file), strc(".CSV"))) {
        log_warn("p_io_save_indices_list_csv: file does not end with .csv: %s", file);
    }

    String data = generate_indices_list(list);

    if(!file_write(file, data.str, true)) {
        log_error("p_io_save_csv failed to write file");
        p_error_assume();
    }

    string_kill(&data);
    return p_error();
}


pError p_io_save_matrix_csv(pMatrix mat, const char *file) {
    if(!str_ends_with(strc(file), strc(".csv")) && !str_ends_with(strc(file), strc(".CSV"))) {
        log_warn("p_io_save_matrix_csv: file does not end with .csv: %s", file);
    }

    String data = generate_matrix(mat);

    if(!file_write(file, data.str, true)) {
        log_error("p_io_save_csv failed to write file");
        p_error_assume();
    }

    string_kill(&data);
    return p_error();
}
