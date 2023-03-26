#pragma once

#include <stdint.h>
#include <wchar.h>

typedef uint8_t char8;
typedef uint16_t char16;
typedef uint32_t char32;
typedef uint64_t char64;

typedef wchar_t wchar;

#if defined(_WIN32)
// windows character type
    #include <tchar.h>
    typedef TCHAR winchar;

    #define OS_CHAR_TYPE winchar
#else
// utf-8 oriented character type
    #define OS_CHAR_TYPE char
#endif
