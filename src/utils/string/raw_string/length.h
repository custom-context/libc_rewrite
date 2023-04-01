#pragma once

#include "common.h"
#include <primitives/primitives.h>

#define DECLARE_RAW_STRING_LENGTH_FUNCTION_WITH_MODIFIER(MODIFIER, CHAR_TYPE)\
MODIFIER usize RAW_STRING_FUNCTION(CHAR_TYPE, length)(CHAR_TYPE const* const string)

#define DECLARE_RAW_STRING_LENGTH_FUNCTION(CHAR_TYPE)\
    DECLARE_RAW_STRING_LENGTH_FUNCTION_WITH_MODIFIER(, CHAR_TYPE)
#define DECLARE_EXTERNAL_RAW_STRING_LENGTH_FUNCTION(CHAR_TYPE)\
    DECLARE_RAW_STRING_LENGTH_FUNCTION_WITH_MODIFIER(extern, CHAR_TYPE)
#define DECLARE_INTERNAL_RAW_STRING_LENGTH_FUNCTION(CHAR_TYPE)\
    DECLARE_RAW_STRING_LENGTH_FUNCTION_WITH_MODIFIER(static, CHAR_TYPE)

#define DEFINE_RAW_STRING_LENGTH_FUNCTION_WITH_MODIFIER(MODIFIER, CHAR_TYPE)\
MODIFIER usize RAW_STRING_FUNCTION(CHAR_TYPE, length)(CHAR_TYPE const* const string) {\
    usize length = 0u;\
    while (string[length] != '\0') {\
        ++length;\
    }\
    return length;\
}

#define DEFINE_RAW_STRING_LENGTH_FUNCTION(CHAR_TYPE)\
    DEFINE_RAW_STRING_LENGTH_FUNCTION_WITH_MODIFIER(, CHAR_TYPE)
#define DEFINE_INTERNAL_RAW_STRING_LENGTH_FUNCTION(CHAR_TYPE)\
    DEFINE_RAW_STRING_LENGTH_FUNCTION_WITH_MODIFIER(static, CHAR_TYPE)


DECLARE_EXTERNAL_RAW_STRING_LENGTH_FUNCTION(char);
DECLARE_EXTERNAL_RAW_STRING_LENGTH_FUNCTION(char8);
DECLARE_EXTERNAL_RAW_STRING_LENGTH_FUNCTION(char16);
DECLARE_EXTERNAL_RAW_STRING_LENGTH_FUNCTION(char32);
DECLARE_EXTERNAL_RAW_STRING_LENGTH_FUNCTION(char64);

DECLARE_EXTERNAL_RAW_STRING_LENGTH_FUNCTION(wchar);

#if defined(_WIN32)
    DECLARE_EXTERNAL_RAW_STRING_LENGTH_FUNCTION(winchar);
#endif
