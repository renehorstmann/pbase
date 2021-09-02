#include "pbase/rhc/error.h"
#include "pbase/rhc/log.h"
#include "pbase/error.h"

const char *p_error() {
    return p_rhc_error;
}

const char *p_error_set(const char *error) {
    if(error && p_rhc_error)
        log_warn("p_error_set overrides error!\n  \\-> prev error: %s\n  \\-> new error : %s", p_rhc_error, error);
    return p_rhc_error = error;
}
