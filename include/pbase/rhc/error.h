#ifndef RHC_ERROR_H
#define RHC_ERROR_H


//
// data
//

extern _Thread_local const char *p_rhc_error;

//
// functions
//

// set and return p_rhc_error
static const char *error(const char *err) {
    return p_rhc_error = err;
}

// assert like function, that also uses formatting print to stderr.
// Calls raise(SIG_ABRT).
// If NDEBUG is defined, only msg will get displayed (without expression, file and line infos)
#define assume(EX, ...) \
(void)((EX) || (p_rhc_assume_impl_ (#EX, __FILE__, __LINE__, __VA_ARGS__),0))

void p_rhc_assume_impl_(const char *expression, const char *file, int line, const char *format, ...);


#endif //RHC_ERROR_H
