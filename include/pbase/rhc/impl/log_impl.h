#ifndef P_RHC_LOG_IMPL_H
#define P_RHC_LOG_IMPL_H
#ifdef P_RHC_IMPL

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../allocator.h"
#include "../log.h"

#define P_RHC_LOG_MAX_LENGTH 4096     // Should be the same as SDL's log max

static struct {
    enum p_rhc_log_level level;
    bool quiet;
} p_rhc_log_L;


#ifdef OPTION_SDL
static SDL_LogPriority p_rhc_log_sdl_priority(enum p_rhc_log_level level) {
    switch(level) {
        case P_RHC_LOG_TRACE:
            return SDL_LOG_PRIORITY_VERBOSE;
        case P_RHC_LOG_DEBUG:
            return SDL_LOG_PRIORITY_DEBUG;
        case P_RHC_LOG_INFO:
            return SDL_LOG_PRIORITY_INFO;
        case P_RHC_LOG_WARN:
            return SDL_LOG_PRIORITY_WARN;
        case P_RHC_LOG_ERROR:
            return SDL_LOG_PRIORITY_ERROR;
        case P_RHC_LOG_WTF:
        default:
            return SDL_LOG_PRIORITY_CRITICAL;
    }
}
#endif

#ifndef P_RHC_LOG_DO_NOT_USE_COLOR
static const char *p_rhc_log_src_level_colors_[] = {
        "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};
#endif

static const char *p_rhc_log_src_level_names_[] = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "WTF"
};

void p_rhc_log_set_min_level(enum p_rhc_log_level level) {
#ifdef OPTION_SDL
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, p_rhc_log_sdl_priority(level));
#endif
    p_rhc_log_L.level = level;
}

void p_rhc_log_set_quiet(bool set) {
    p_rhc_log_L.quiet = set;
}

#ifdef OPTION_SDL
void p_rhc_log_base_(enum p_rhc_log_level level, const char *file, int line, const char *format, ...) {
    if (level < p_rhc_log_L.level || p_rhc_log_L.quiet) {
        return;
    }
    va_list args;

#ifdef P_RHC_LOG_DO_NOT_PRINT_TIME_FILE
    va_start(args, format);
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, p_rhc_log_sdl_priority(level), format, args);
    va_end(args);
#else
    /* Get current time */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);


    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';

    char msg_format[P_RHC_LOG_MAX_LENGTH];
    snprintf(msg_format, P_RHC_LOG_MAX_LENGTH, "%s %s:%d: %s", buf, file, line, format);
    va_start(args, format);
    SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, p_rhc_log_sdl_priority(level), msg_format, args);
    va_end(args);
#endif
}

#else //!OPTION_SDL

void p_rhc_log_base_(enum p_rhc_log_level level, const char *file, int line, const char *format, ...) {
    if (level < p_rhc_log_L.level || p_rhc_log_L.quiet) {
        return;
    }
    va_list args;

    char msg_format[P_RHC_LOG_MAX_LENGTH];

#ifdef P_RHC_LOG_DO_NOT_PRINT_TIME_FILE

#ifdef P_RHC_LOG_DO_NOT_USE_COLOR
    snprintf(msg_format, P_RHC_LOG_MAX_LENGTH, "%-5s: %s\n", p_rhc_log_src_level_names_[level], format);
#else
    snprintf(msg_format, P_RHC_LOG_MAX_LENGTH, "%s%-5s\x1b[0m\x1b[90m:\x1b[0m %s\n",
            p_rhc_log_src_level_colors_[level], p_rhc_log_src_level_names_[level], format);
#endif
    va_start(args, format);
    vfprintf(P_RHC_LOG_DEFAULT_FILE, msg_format, args);
    va_end(args);
    fflush(P_RHC_LOG_DEFAULT_FILE);

#else //!P_RHC_LOG_DO_NOT_PRINT_TIME_FILE

    /* Get current time */
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    /* Log to P_RHC_DEFAULT_FILE (stdout) */
    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", lt)] = '\0';


#ifdef P_RHC_LOG_DO_NOT_USE_COLOR
    snprintf(msg_format, P_RHC_LOG_MAX_LENGTH, "%s %-5s %s:%d: %s\n",
            buf, p_rhc_log_src_level_names_[level], file, line, format);
#else
    snprintf(msg_format, P_RHC_LOG_MAX_LENGTH, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m %s\n",
            buf, p_rhc_log_src_level_colors_[level], p_rhc_log_src_level_names_[level], file, line, format);
#endif
    va_start(args, format);
    vfprintf(P_RHC_LOG_DEFAULT_FILE, msg_format, args);
    va_end(args);
    fflush(P_RHC_LOG_DEFAULT_FILE);
#endif //P_RHC_LOG_DO_NOT_PRINT_TIME_FILE

}
#endif //OPTION_SDL

#endif //P_RHC_IMPL
#endif //P_RHC_LOG_IMPL_H
