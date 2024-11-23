#include "macros.h"

#include <stdio.h>
#include <stdarg.h>

// ingore usage of format string for errprintf function usage
#if !defined(__has_warning) || __has_warning("-Wformat-nonliteral")
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif
int errprintf(const char* restrict format, ...) {
    int ret;
    va_list args;
    va_start(args, format);
    ret = vfprintf(stderr, format, args);
    va_end(args);
    return ret;
}
#if !defined(__has_warning) || __has_warning("-Wformat-nonliteral")
    #pragma clang diagnostic pop
#endif
