#pragma once

#include "length.h"
#include "compare.h"

// define OS_STRING_LITERAL
#if defined(_WIN32)
    #define OS_STRING_LITERAL(STR) _TEXT(STR)
#else
    #define OS_STRING_LITERAL(STR) STR
#endif
