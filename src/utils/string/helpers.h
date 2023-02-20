#pragma once

#include "raw_string_helpers.h"

#include <primitives/unsigned_types_aliases.h>

#include <containers/string.h>

#include <utils/common.h>
#ifndef NAMESPACE_UTILS_STRING
    #define NAMESPACE_UTILS_STRING(NAME) NAMESPACE_UTILS(CONCAT3(string, __, NAME))
#endif
#ifndef RAW_STRING_FUNCTION
    #define RAW_STRING_FUNCTION(CHAR_TYPE, NAME) NAMESPACE_UTILS_STRING(TYPE_METHOD(CONCAT3(raw_string, _, CHAR_TYPE), length))
#endif

#define CONVERT_FUNCTION(FROM_TYPE, TO_TYPE) CONCAT5(FROM_TYPE, _, to, _, TO_TYPE)
#define COMPARE_FUNCTION(NAME1, NAME2) CONCAT7(compare, __, NAME1, _, with, _, NAME2)

#define DECLARE_NUMERIC_TYPE_TO_STRING_TYPE(NUMERIC_TYPE, CHAR_TYPE)\
struct SPECIALIZED_STRING_TYPE(CHAR_TYPE) NAMESPACE_UTILS_STRING(CONVERT_FUNCTION(NUMERIC_TYPE, SPECIALIZED_STRING_TYPE(CHAR_TYPE)))(NUMERIC_TYPE value)
#define IMPLEMENT_NUMERIC_TYPE_TO_STRING_TYPE(NUMERIC_TYPE, CHAR_TYPE)\
struct SPECIALIZED_STRING_TYPE(CHAR_TYPE) NAMESPACE_UTILS_STRING(CONVERT_FUNCTION(NUMERIC_TYPE, SPECIALIZED_STRING_TYPE(CHAR_TYPE)))(NUMERIC_TYPE value) {\
    struct SPECIALIZED_STRING_TYPE(CHAR_TYPE) result;\
    SPECIALIZED_STRING_METHOD(CHAR_TYPE, construct_at)(&result);\
    if (!value) {\
        CHAR_TYPE const letter = '0';\
        SPECIALIZED_STRING_METHOD(CHAR_TYPE, push_back)(&result, &letter);\
        return result;\
    }\
    if (value < 0) {\
        CHAR_TYPE const letter = '-';\
        SPECIALIZED_STRING_METHOD(CHAR_TYPE, push_back)(&result, &letter);\
        value = -value;\
    }\
    while (value) {\
        CHAR_TYPE const letter = value % 10 + '0';\
        SPECIALIZED_STRING_METHOD(CHAR_TYPE, push_back)(&result, &letter);\
        value /= 10;\
    }\
    /*reverse values*/\
    uint const string_size = SPECIALIZED_STRING_METHOD(CHAR_TYPE, size)(&result);\
    for (uint index = 0u; index < string_size / 2; ++index) {\
        CHAR_TYPE const temp = *SPECIALIZED_STRING_METHOD(CHAR_TYPE, at)(&result, index);\
        *SPECIALIZED_STRING_METHOD(CHAR_TYPE, mut_at)(&result, index) = *SPECIALIZED_STRING_METHOD(CHAR_TYPE, at)(&result, string_size - 1 - index);\
        *SPECIALIZED_STRING_METHOD(CHAR_TYPE, mut_at)(&result, string_size - 1 - index) = temp;\
    }\
    return result;\
}\

#define DECLARE_NUMERIC_TYPE_TO_STRING(NUMERIC_TYPE) DECLARE_NUMERIC_TYPE_TO_STRING_TYPE(NUMERIC_TYPE, char)
#define IMPLEMENT_NUMERIC_TYPE_TO_STRING(NUMERIC_TYPE) IMPLEMENT_NUMERIC_TYPE_TO_STRING_TYPE(NUMERIC_TYPE, char)

#define DECLARE_COMPARE_STRING_TYPE_WITH_BUFFER(CHAR_TYPE)\
int NAMESPACE_UTILS_STRING(COMPARE_FUNCTION(SPECIALIZED_STRING_TYPE(CHAR_TYPE), buffer))(struct SPECIALIZED_STRING_TYPE(CHAR_TYPE) const* const this, uint buffer_size, CHAR_TYPE const* const buffer)
#define IMPLEMENT_COMPARE_STRING_TYPE_WITH_BUFFER(CHAR_TYPE)\
int NAMESPACE_UTILS_STRING(COMPARE_FUNCTION(SPECIALIZED_STRING_TYPE(CHAR_TYPE), buffer))(struct SPECIALIZED_STRING_TYPE(CHAR_TYPE) const* const this, uint buffer_size, CHAR_TYPE const* const buffer) {\
    uint const string_size = SPECIALIZED_STRING_METHOD(CHAR_TYPE, size)(this);\
    if (string_size < buffer_size) {\
        return -1;\
    }\
    if (string_size > buffer_size) {\
        return 1;\
    }\
    for (uint index = 0u; index < string_size; ++index) {\
        CHAR_TYPE const * const value = SPECIALIZED_STRING_METHOD(CHAR_TYPE, at)(this, index);\
        if (*value < buffer[index]) {\
            return -1;\
        }\
        if (*value > buffer[index]) {\
            return 1;\
        }\
    }\
    return 0;\
}\

#define DECLARE_COMPARE_STRING_WITH_BUFFER() DECLARE_COMPARE_STRING_TYPE_WITH_BUFFER(char)
#define IMPLEMENT_COMPARE_STRING_WITH_BUFFER() IMPLEMENT_COMPARE_STRING_TYPE_WITH_BUFFER(char)
