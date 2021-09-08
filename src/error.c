#include "pbase/rhc/error.h"
#include "pbase/rhc/log.h"
#include "pbase/error.h"

pError p_error() {
    return p_rhc_error;
}

pError p_error_set(pError error) {
    if(error && p_rhc_error)
        log_warn("p_error_set overrides error!\n  \\-> prev error: %s\n  \\-> new error : %s", p_rhc_error, error);
    return p_rhc_error = error;
}

void p_error_check() {
    assume(!p_error(), "%s", p_error());
}
