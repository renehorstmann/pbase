#ifndef PBASE_ERROR_H
#define PBASE_ERROR_H

typedef const char *pError;

/** returns the error code/text p_rhc_error */
pError p_error();

/**
 * Sets and returns the error code/text p_rhc_error.
 * If error is set to NULL, it will clear the error
 * If p_rhc_error is not NULL (and error!=NULL), it will log a warning.
 */
pError p_error_set(pError error);

#endif //PBASE_ERROR_H
