#pragma once

#include <containers/dynamic/string/string.h>
#include <primitives/unsigned_types_aliases.h>
#include <utils/string/common.h>
#include <utils/convert.h>

#define DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(MODIFIER, NUMERIC_TYPE, STRING_TYPE)\
MODIFIER void NAMESPACE_UTILS_STRING(CONVERT(NUMERIC_TYPE, STRING_TYPE))(NUMERIC_TYPE const* const value, struct STRING_TYPE* const result)

#define DEFINE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(MODIFIER, NUMERIC_TYPE, STRING_TYPE)\
MODIFIER void NAMESPACE_UTILS_STRING(CONVERT(NUMERIC_TYPE, STRING_TYPE))(NUMERIC_TYPE const* const value, struct STRING_TYPE* const result) {\
    ASSERT(value);\
    ASSERT(result);\
    NUMERIC_TYPE temporary_value = *value;\
    if (!temporary_value) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const letter = '0';\
        TYPE_METHOD(STRING_TYPE, push_back)(result, &letter);\
        return;\
    }\
    if (temporary_value < 0) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const letter = '-';\
        TYPE_METHOD(STRING_TYPE, push_back)(result, &letter);\
        temporary_value = -temporary_value;\
    }\
    while (temporary_value) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const letter = temporary_value % 10 + '0';\
        TYPE_METHOD(STRING_TYPE, push_back)(result, &letter);\
        temporary_value /= 10;\
    }\
    /*reverse values*/\
    STRUCT_SUBTYPE(STRING_TYPE, size_type) const string_size = TYPE_METHOD(STRING_TYPE, size)(result);\
    for (STRUCT_SUBTYPE(STRING_TYPE, size_type) index = 0u; index < string_size / 2; ++index) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const temp = *TYPE_METHOD(STRING_TYPE, at)(result, index);\
        *TYPE_METHOD(STRING_TYPE, mut_at)(result, index) = *TYPE_METHOD(STRING_TYPE, at)(result, string_size - 1 - index);\
        *TYPE_METHOD(STRING_TYPE, mut_at)(result, string_size - 1 - index) = temp;\
    }\
}

DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, char, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, uchar, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, short, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, ushort, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, int, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, uint, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, long, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, ulong, STRING_TYPE());
