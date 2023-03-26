#pragma once

#include "common.h"
#include <primitives/unsigned_types_aliases.h>
#include <primitives/characters_types_aliases.h>

#define DECLARE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(MODIFIER, CHAR_TYPE)\
MODIFIER int RAW_STRING_FUNCTION(CHAR_TYPE, compare)(CHAR_TYPE const* string1, CHAR_TYPE const* string2)

#define DECLARE_RAW_STRING_COMPARE_FUNCTION(CHAR_TYPE)\
    DECLARE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(, CHAR_TYPE)

#define DEFINE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(MODIFIER, CHAR_TYPE)\
MODIFIER int RAW_STRING_FUNCTION(CHAR_TYPE, compare)(CHAR_TYPE const* string1, CHAR_TYPE const* string2) {\
    ASSERT(string1);\
    ASSERT(string2);\
    while (*string1 != '\0' || *string2 != '\0') {\
        if (*string1 > *string2) {\
            return 1;\
        }\
        if (*string1 < *string2) {\
            return -1;\
        }\
        ++string1;\
        ++string2;\
    }\
    if (*string1 != '\0') {\
        return 1;\
    }\
    if (*string2 != '\0') {\
        return -1;\
    }\
    return 0;\
}

#define DEFINE_RAW_STRING_COMPARE_FUNCTION(CHAR_TYPE)\
    DEFINE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(, CHAR_TYPE)

DECLARE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(extern, char);
DECLARE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(extern, char8);
DECLARE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(extern, char16);
DECLARE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(extern, char32);
DECLARE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(extern, char64);

DECLARE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(extern, wchar);

#if defined(_WIN32)
    DECLARE_RAW_STRING_COMPARE_FUNCTION_WITH_MODIFIER(extern, winchar);
#endif
