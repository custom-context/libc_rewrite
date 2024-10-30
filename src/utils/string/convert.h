#pragma once

#include <containers/dynamic/string/string.h>
#include <primitives/unsigned_types_aliases.h>
#include <utils/string/common.h>
#include <utils/convert.h>

#include <math.h>

#define DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(MODIFIER, NUMERIC_TYPE, STRING_TYPE)\
MODIFIER struct STRING_TYPE NAMESPACE_UTILS_STRING(CONVERT(NUMERIC_TYPE, STRING_TYPE))(NUMERIC_TYPE const* const value)

#define DEFINE_CONVERT_INTEGER_TYPE_TO_STRING_TYPE_WITH_MODIFIER(MODIFIER, NUMERIC_TYPE, STRING_TYPE)\
MODIFIER struct STRING_TYPE NAMESPACE_UTILS_STRING(CONVERT(NUMERIC_TYPE, STRING_TYPE))(NUMERIC_TYPE const* const value) {\
    ASSERT(value);\
    struct STRING_TYPE result;\
    TYPE_METHOD(STRING_TYPE, construct_at)(&result);\
    NUMERIC_TYPE temporary_value = *value;\
    if (!temporary_value) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const letter = '0';\
        TYPE_METHOD(STRING_TYPE, push_back)(&result, &letter);\
        return result;\
    }\
    bool is_negative = temporary_value < 0;\
    if (is_negative) {\
        temporary_value = -temporary_value;\
    }\
    while (temporary_value) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const letter = (STRUCT_SUBTYPE(STRING_TYPE, char_type))(temporary_value % 10) + '0';\
        TYPE_METHOD(STRING_TYPE, push_back)(&result, &letter);\
        temporary_value /= 10;\
    }\
    if (is_negative) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const letter = '-';\
        TYPE_METHOD(STRING_TYPE, push_back)(&result, &letter);\
    }\
    /*reverse values*/\
    STRUCT_SUBTYPE(STRING_TYPE, size_type) const string_size = TYPE_METHOD(STRING_TYPE, size)(&result);\
    for (STRUCT_SUBTYPE(STRING_TYPE, size_type) index = 0u; index < string_size / 2; ++index) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const temp = *TYPE_METHOD(STRING_TYPE, at)(&result, index);\
        *TYPE_METHOD(STRING_TYPE, mut_at)(&result, index) = *TYPE_METHOD(STRING_TYPE, at)(&result, string_size - 1 - index);\
        *TYPE_METHOD(STRING_TYPE, mut_at)(&result, string_size - 1 - index) = temp;\
    }\
    return result;\
}

#define DEFINE_CONVERT_FLOAT_TYPE_TO_STRING_TYPE_WITH_MODIFIER(MODIFIER, NUMERIC_TYPE, STRING_TYPE)\
MODIFIER struct STRING_TYPE NAMESPACE_UTILS_STRING(CONVERT(NUMERIC_TYPE, STRING_TYPE))(NUMERIC_TYPE const* const value) {\
    ASSERT(value);\
    struct STRING_TYPE result;\
    TYPE_METHOD(STRING_TYPE, construct_at)(&result);\
    NUMERIC_TYPE temporary_value = *value;\
    if ((NUMERIC_TYPE)fabs((double)temporary_value) < EPSILON(NUMERIC_TYPE)) {\
        TYPE_METHOD(STRING_TYPE, push_back)(&result, &(STRUCT_SUBTYPE(STRING_TYPE, char_type)){'0'});\
        return result;\
    }\
    bool is_negative = temporary_value < 0;\
    if (is_negative) {\
        temporary_value = -temporary_value;\
    }\
    /* get integer part */\
    while ((NUMERIC_TYPE)floor((double)temporary_value) > 0) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const letter = (STRUCT_SUBTYPE(STRING_TYPE, char_type))(temporary_value - (NUMERIC_TYPE)floor((double)temporary_value / 10) * 10) + '0';\
        TYPE_METHOD(STRING_TYPE, push_back)(&result, &letter);\
        temporary_value /= 10;\
    }\
    if (is_negative) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const letter = '-';\
        TYPE_METHOD(STRING_TYPE, push_back)(&result, &letter);\
    }\
    /*reverse values*/\
    STRUCT_SUBTYPE(STRING_TYPE, size_type) const string_size = TYPE_METHOD(STRING_TYPE, size)(&result);\
    for (STRUCT_SUBTYPE(STRING_TYPE, size_type) index = 0u; index < string_size / 2; ++index) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const temp = *TYPE_METHOD(STRING_TYPE, at)(&result, index);\
        *TYPE_METHOD(STRING_TYPE, mut_at)(&result, index) = *TYPE_METHOD(STRING_TYPE, at)(&result, string_size - 1 - index);\
        *TYPE_METHOD(STRING_TYPE, mut_at)(&result, string_size - 1 - index) = temp;\
    }\
    if (!string_size || (string_size == 1 && is_negative)) {\
        TYPE_METHOD(STRING_TYPE, push_back)(&result, &(STRUCT_SUBTYPE(STRING_TYPE, char_type)){'0'});\
    }\
    temporary_value = is_negative ? -*value : *value;\
    temporary_value = temporary_value - (NUMERIC_TYPE)floor((double)temporary_value);\
    if ((NUMERIC_TYPE)fabs((double)temporary_value) >= EPSILON(NUMERIC_TYPE)) {\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const letter = '.';\
        TYPE_METHOD(STRING_TYPE, push_back)(&result, &letter);\
    }\
    /* get decimal part */\
    enum {\
        max_count_zeroes_in_a_row__float = 3,\
        max_count_zeroes_in_a_row__double = 5,\
        max_count_nines_in_a_row__float = 3,\
        max_count_nines_in_a_row__double = 5\
    };\
    uint16 count_zeroes_in_a_row = 0u, count_nines_in_a_row = 0u;\
    while ((NUMERIC_TYPE)fabs((double)temporary_value) >= EPSILON(NUMERIC_TYPE)) {\
        temporary_value *= 10;\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const digit = (STRUCT_SUBTYPE(STRING_TYPE, char_type))(floor((double)temporary_value));\
        temporary_value -= (NUMERIC_TYPE)floor((double)temporary_value);\
        if (!digit) {\
            while (count_nines_in_a_row) {\
                TYPE_METHOD(STRING_TYPE, push_back)(&result, &(STRUCT_SUBTYPE(STRING_TYPE, char_type)){'9'});\
                --count_nines_in_a_row;\
            }\
            ++count_zeroes_in_a_row;\
            if (count_zeroes_in_a_row >= CONCAT3(max_count_zeroes_in_a_row, __, NUMERIC_TYPE)) {\
                break;\
            }\
            continue;\
        }\
        while (count_zeroes_in_a_row) {\
            TYPE_METHOD(STRING_TYPE, push_back)(&result, &(STRUCT_SUBTYPE(STRING_TYPE, char_type)){'0'});\
            --count_zeroes_in_a_row;\
        }\
        if (digit == 9) {\
            ++count_nines_in_a_row;\
            if (count_nines_in_a_row >= CONCAT3(max_count_nines_in_a_row, __, NUMERIC_TYPE)) {\
                STRUCT_SUBTYPE(STRING_TYPE, char_type)* prev_value = TYPE_METHOD(STRING_TYPE, mut_at)(&result, TYPE_METHOD(STRING_TYPE, size)(&result) - 1u);\
                if (*prev_value == (STRUCT_SUBTYPE(STRING_TYPE, char_type))('.')) {\
                    prev_value = TYPE_METHOD(STRING_TYPE, mut_at)(&result, TYPE_METHOD(STRING_TYPE, size)(&result) - 2u);\
                }\
                *prev_value += 1u;\
                break;\
            }\
            continue;\
        }\
        while (count_nines_in_a_row) {\
            TYPE_METHOD(STRING_TYPE, push_back)(&result, &(STRUCT_SUBTYPE(STRING_TYPE, char_type)){'9'});\
            --count_nines_in_a_row;\
        }\
        STRUCT_SUBTYPE(STRING_TYPE, char_type) const letter = digit + '0';\
        TYPE_METHOD(STRING_TYPE, push_back)(&result, &letter);\
    }\
    return result;\
}

DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, char, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, uchar, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, short, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, ushort, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, int, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, uint, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, long, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, ulong, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, llong, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, ullong, STRING_TYPE());

DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, usize, STRING_TYPE());

DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, float, STRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, double, STRING_TYPE());

DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, char, WSTRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, uchar, WSTRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, short, WSTRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, ushort, WSTRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, int, WSTRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, uint, WSTRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, long, WSTRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, ulong, WSTRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, llong, WSTRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, ullong, WSTRING_TYPE());

DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, usize, WSTRING_TYPE());

DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, float, WSTRING_TYPE());
DECLARE_CONVERT_NUMERIC_TYPE_TO_STRING_TYPE_WITH_MODIFIER(extern, double, WSTRING_TYPE());
