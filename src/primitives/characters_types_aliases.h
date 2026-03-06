#pragma once

#include <stdint.h>
#include <wchar.h>

typedef uint8_t char8;
typedef uint16_t char16;
typedef uint32_t char32;
typedef uint64_t char64;
DECLARE_STRUCT_SUBTYPE(char8, value_type, char8);
DECLARE_STRUCT_SUBTYPE(char16, value_type, char16);
DECLARE_STRUCT_SUBTYPE(char32, value_type, char32);
DECLARE_STRUCT_SUBTYPE(char64, value_type, char64);

typedef wchar_t wchar;
DECLARE_STRUCT_SUBTYPE(wchar, value_type, wchar);

#if defined(_WIN32)
// windows character type
    #include <tchar.h>
    typedef TCHAR winchar;
    DECLARE_STRUCT_SUBTYPE(winchar, value_type, winchar);
#endif

#if defined(_WIN32) && defined(_UNICODE)
    #define OS_CHAR_TYPE wchar
#else
    // utf-8 oriented character type
    #define OS_CHAR_TYPE char
#endif
DECLARE_STRUCT_SUBTYPE(OS_CHAR_TYPE, value_type, OS_CHAR_TYPE);
