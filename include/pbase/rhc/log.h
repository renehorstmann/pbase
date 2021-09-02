#ifndef P_RHC_LOG_H
#define P_RHC_LOG_H

#include <stdbool.h>

//
// Options:
//

#ifndef P_RHC_LOG_DEFAULT_FILE
#define P_RHC_LOG_DEFAULT_FILE stdout
#endif


// use the following definition to stop using colors (not in sdl...)
// #define P_RHC_LOG_DO_NOT_USE_COLOR

// use the following definition to stop printing time and file info
// #define P_RHC_LOG_DO_NOT_PRINT_TIME_FILE


enum p_rhc_log_level {
    P_RHC_LOG_TRACE, P_RHC_LOG_DEBUG, P_RHC_LOG_INFO, P_RHC_LOG_WARN, P_RHC_LOG_ERROR, P_RHC_LOG_WTF, P_RHC_LOG_NUM_LEVELS
};

#define log_trace(...) p_rhc_log_base_(P_RHC_LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)

#define log_debug(...) p_rhc_log_base_(P_RHC_LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)

#define log_info(...)  p_rhc_log_base_(P_RHC_LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)

#define log_warn(...)  p_rhc_log_base_(P_RHC_LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)

#define log_error(...) p_rhc_log_base_(P_RHC_LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)

#define log_wtf(...)   p_rhc_log_base_(P_RHC_LOG_WTF, __FILE__, __LINE__, __VA_ARGS__)


void p_rhc_log_set_min_level(enum p_rhc_log_level level);

void p_rhc_log_set_quiet(bool set);

void p_rhc_log_base_(enum p_rhc_log_level level, const char *file, int line, const char *format, ...);

#endif //P_RHC_LOG
