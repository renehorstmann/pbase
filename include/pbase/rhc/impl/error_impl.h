#ifndef P_RHC_ERROR_IMPL_H
#define P_RHC_ERROR_IMPL_H
#ifdef P_RHC_IMPL

#include <stdio.h>
#include <stdarg.h>
#include <signal.h>
#include "../error.h"

//
// options
//

#ifndef P_RHC_ERROR_ASSUME_SIGNAL
#define P_RHC_ERROR_ASSUME_SIGNAL SIGABRT
#endif

#ifndef P_RHC_ERROR_ASSUME_MAX_FORMATED_MSG_SIZE
#define P_RHC_ERROR_ASSUME_MAX_FORMATED_MSG_SIZE 4096
#endif


//
// data
//

_Thread_local const char *p_rhc_error;

//
// functions
//


void p_rhc_assume_impl_(const char *expression, const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char msg[P_RHC_ERROR_ASSUME_MAX_FORMATED_MSG_SIZE];
    vsnprintf(msg, P_RHC_ERROR_ASSUME_MAX_FORMATED_MSG_SIZE, format, args);
    va_end(args);
#ifdef NDEBUG
    fprintf(stderr, "An assumption in the program failed: %s\n", msg);
#else
    fprintf(stderr, "Assumption failed: %s at %s:%d %s\n", expression, file, line, msg);
#endif
    raise(P_RHC_ERROR_ASSUME_SIGNAL);
}

#endif //P_RHC_IMPL
#endif //P_RHC_ERROR_IMPL_H
