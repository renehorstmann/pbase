#ifndef PBASE_IO_CSV_H
#define PBASE_IO_CSV_H

#include "pbase/error.h"
#include "pbase/types/indices.h"
#include "pbase/types/indiceslist.h"
#include "pbase/types/vector.h"
#include "pbase/types/matrix.h"

/** Saves an IndicesList as .csv file */
pError p_io_save_indices_list_csv(pIndicesList list, const char *file);

/** Loads an IndicesList from a .csv file */
pError p_io_load_indices_list_csv(pIndicesList *out_list, const char *file);


/** Saves a Matrix as a .csv file */
pError p_io_save_matrix_csv(pMatrix mat, const char *file);

/** Loads a Matrix from a .csv file */
pError p_io_load_matrix_csv(pMatrix *out_mat, const char *file);


//
// wrapper
//

/** Saves Indices as .csv file */
pError p_io_save_indices_csv(pIndices indices, const char *file);

/** Loads Indices from a .csv file */
pError p_io_load_indices_csv(pIndices *out_indices, const char *file);

/** Saves a Vector as a .csv file */
pError p_io_save_vector_csv(pVector vec, const char *file);

/** Loads a Vector from a .csv file */
pError p_io_load_vector_csv(pVector *out_vec, const char *file);

#endif //PBASE_IO_CSV_H
