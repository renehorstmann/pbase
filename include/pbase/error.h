#ifndef PBASE_ERROR_H
#define PBASE_ERROR_H

#include "stddef.h"

typedef const char *pError;

/** returns the error code/text p_rhc_error */
pError p_error();

/**
 * Sets and returns the error code/text p_rhc_error.
 * If error is set to NULL, it will clear the error
 * If p_rhc_error is not NULL (and error!=NULL), it will log a warning.
 */
pError p_error_set(pError error);

/** calls assume(!p_error(), "%s", p_error()) to print the error message as assumption note */
void p_error_check();

/**
 * Returns p_error(), but also runs assume(p_error(), "p_error_assume failed!");
 * useful for if(function_may_return_error) { return p_error_assume(); }
 */
pError p_error_assume();

#endif //PBASE_ERROR_H
