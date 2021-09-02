#ifndef PBASE_ERROR_H
#define PBASE_ERROR_H


/** returns the error code/text p_rhc_error */
const char *p_error();

/**
 * Sets and returns the error code/text p_rhc_error.
 * If error is set to NULL, it will clear the error
 * If p_rhc_error is not NULL (and error!=NULL), it will log a warning.
 */
const char *p_error_set(const char *error);

#endif //PBASE_ERROR_H
