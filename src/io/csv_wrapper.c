#include "pbase/rhc/log.h"
#include "pbase/io/csv.h"


pError p_io_save_indices_csv(pIndices indices, const char *file) {
    pIndicesList list = {&indices, 1};
    return p_io_save_indices_list_csv(list, file);
}


pError p_io_load_indices_csv(pIndices *out_indices, const char *file) {
    pIndicesList list;
    if(p_io_load_indices_list_csv(&list, file)) {
        return p_error_assume();
    }
    if(list.size != 1 || !p_indices_valid(list.list[0])) {
        log_error("p_io_load_indices_csv failed, expected an incides list with only a single Indices member");
        p_error_set("p_io_load_csv failed");
    } else {
        *out_indices = list.list[0];
        list.owns_indices = false;
    }
    p_indices_list_kill(&list);
    return p_error();
}


pError p_io_save_vector_csv(pVector vector, const char *file) {
    pMatrix mat = {vector.data, vector.size, 1};
    return p_io_save_matrix_csv(mat, file);
}


pError p_io_load_vector_csv(pVector *out_vector, const char *file) {
    pMatrix mat;
    if(p_io_load_matrix_csv(&mat, file)) {
        return p_error_assume();
    }
    if(mat.rows != 1 && mat.cols != 1) {
        log_error("p_io_load_vector_csv failed, expected a vector from a matrix with rows or cols == 1");
        p_matrix_kill(&mat);
        return p_error_set("p_io_load_csv failed");
    }
    *out_vector = (pVector) {mat.data, mat.rows * mat.cols};
    mat = p_matrix_new_invalid();
    return NULL;
}

