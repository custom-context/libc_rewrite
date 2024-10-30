#include "convert.h"

#include <primitives/limits.h>

char32 NAMESPACE_UTILS_STRING(CONVERT(utf8_c_codepoints, unicode_character))(char const* const codepoints, uint8* const count_codepoints_read) {
    STATIC_ASSERT(sizeof(char) == sizeof(char8));
    return NAMESPACE_UTILS_STRING(CONVERT(utf8_codepoints, unicode_character))((char8 const*)codepoints, count_codepoints_read);
}

char32 NAMESPACE_UTILS_STRING(CONVERT(utf8_codepoints, unicode_character))(char8 const* const codepoints, uint8* const count_codepoints_read) {
    ASSERT(codepoints);
    // codepoints[0] == 0xxxxxxx
    if (!(codepoints[0] & (1 << 7))) {
        if (count_codepoints_read) {
            *count_codepoints_read = 1;
        }
        return codepoints[0] & 0x7F;
    }
    // codepoints[0] == 1xxxxxxx
    ASSERT((codepoints[0] & (1 << 6)));
    if (!(codepoints[0] & (1 << 6))) {
        // string[0] == 10xxxxxx
        if (count_codepoints_read) {
            *count_codepoints_read = MAX_VALUE(uint8);
        }
        return 0;
    }
    // codepoints[0] == 11xxxxxx
    ASSERT((codepoints[1] & (1 << 7)));
    ASSERT(!(codepoints[1] & (1 << 6)));
    if (!((codepoints[1] & (1 << 7)) && !(codepoints[1] & (1 << 6)))) {
        // codepoints[1] != 10xxxxxx
        if (count_codepoints_read) {
            *count_codepoints_read = MAX_VALUE(uint8);
        }
        return 0;
    }
    // codepoints[1] == 10xxxxxx
    if (!(codepoints[0] & (1 << 5))) {
        // codepoints[0] == 110xxxxx
        if (count_codepoints_read) {
            *count_codepoints_read = 2;
        }
        return
            ((char32)(codepoints[0] & 0x1F) << 6) |
            (codepoints[1] & 0x3F);
    }
    // codepoints[0] == 111xxxxx
    ASSERT((codepoints[2] & (1 << 7)));
    ASSERT(!(codepoints[2] & (1 << 6)));
    if (!((codepoints[2] & (1 << 7)) && !(codepoints[2] & (1 << 6)))) {
        // codepoints[2] != 10xxxxxx
        if (count_codepoints_read) {
            *count_codepoints_read = MAX_VALUE(uint8);
        }
        return 0;
    }
    // codepoints[2] == 10xxxxxx
    if (!(codepoints[0] & (1 << 4))) {
        // codepoints[0] == 1110xxxx
        if (count_codepoints_read) {
            *count_codepoints_read = 3;
        }
        return
            ((char32)(codepoints[0] & 0xF) << 12) |
            ((char32)(codepoints[1] & 0x3F) << 6) |
            (codepoints[2] & 0x3F);
    }
    // codepoints[0] == 1111xxxx
    ASSERT((codepoints[3] & (1 << 7)));
    ASSERT(!(codepoints[3] & (1 << 6)));
    if (!((codepoints[3] & (1 << 7)) && !(codepoints[3] & (1 << 6)))) {
        // codepoints[3] != 10xxxxxx
        if (count_codepoints_read) {
            *count_codepoints_read = MAX_VALUE(uint8);
        }
        return 0;
    }
    // codepoints[3] == 10xxxxxx
    ASSERT(!(codepoints[0] & (1 << 3)));
    if ((codepoints[0] & (1 << 3))) {
        // codepoints[0] == 11111xxx
        if (count_codepoints_read) {
            *count_codepoints_read = MAX_VALUE(uint8);
        }
        return 0;
    }
    // codepoints[0] == 11110xxx
    return
        ((char32)(codepoints[0] & 0x7) << 18) |
        ((char32)(codepoints[1] & 0x3F) << 6) |
        ((char32)(codepoints[2] & 0x3F) << 6) |
        (codepoints[3] & 0x3F);
}

char32 NAMESPACE_UTILS_STRING(CONVERT(utf16_codepoints, unicode_character))(char16 const* const codepoints, uint8* const count_codepoints_read) {
    ASSERT(codepoints);
    if (0xD800 <= codepoints[0] && codepoints[0] < 0xDC00) {
        if (count_codepoints_read) {
            *count_codepoints_read = 2;
        }
        return
            (((char32)(codepoints[0] & 0x3FF) << 10) |
            ((char32)(codepoints[1] & 0x3FF))) +
            0x10000;
    }
    if (count_codepoints_read) {
        *count_codepoints_read = 1;
    }
    return codepoints[0];
}

static uint8 hex_character_to_integer(char16 character);
static OPTIONAL_TYPE(char16) hex_u8_sequence_to_utf16_character(char8 const buffer[const static 6]);
static OPTIONAL_TYPE(char16) hex_u16_sequence_to_utf16_character(char16 const buffer[const static 6]);

#define hex_sequence_to_utf16_character(BUFFER) _Generic((BUFFER),\
    char8 const* : hex_u8_sequence_to_utf16_character,\
    char8*       : hex_u8_sequence_to_utf16_character,\
    char16 const*: hex_u16_sequence_to_utf16_character,\
    char16*      : hex_u16_sequence_to_utf16_character\
)(BUFFER)

struct OPTIONAL_TYPE(char32) NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c_buffer, unicode_character))(char const buffer[const static 6], usize buffer_size) {
    STATIC_ASSERT(sizeof(char) == sizeof(char8));
    return NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c8_buffer, unicode_character))((char8 const*)buffer, buffer_size);
}

struct OPTIONAL_TYPE(char32) NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c8_buffer, unicode_character))(char8 const buffer[const static 6], usize buffer_size) {
    struct OPTIONAL_TYPE(char32) result;
    if (buffer_size < 6u) {
        TYPE_METHOD(OPTIONAL_TYPE(char32), construct_at)(&result);
        return result;
    }

    char16 surrogate_pair_part1;
    {
        struct OPTIONAL_TYPE(char16) surrogate_pair_part1_opt = hex_sequence_to_utf16_character(buffer);
        if (!TYPE_METHOD(OPTIONAL_TYPE(char16), has_value)(&surrogate_pair_part1_opt)) {
            TYPE_METHOD(OPTIONAL_TYPE(char32), construct_at)(&result);
            return result;
        }
        surrogate_pair_part1 = *TYPE_METHOD(OPTIONAL_TYPE(char16), value)(&surrogate_pair_part1_opt);
    }

    if (surrogate_pair_part1 < 0xD800 || surrogate_pair_part1 > 0xDC00) {
        char32 result_value = surrogate_pair_part1;
        TYPE_METHOD(OPTIONAL_TYPE(char32), construct_copy_from_value_at)(&result, &result_value);
        return result;
    }

    if (buffer_size < 12u) {
        TYPE_METHOD(OPTIONAL_TYPE(char32), construct_at)(&result);
        return result;
    }

    char16 surrogate_pair_part2;
    {
        struct OPTIONAL_TYPE(char16) surrogate_pair_part2_opt = hex_sequence_to_utf16_character(buffer + 6u);
        if (!TYPE_METHOD(OPTIONAL_TYPE(char16), has_value)(&surrogate_pair_part2_opt)) {
            TYPE_METHOD(OPTIONAL_TYPE(char32), construct_at)(&result);
            return result;
        }
        surrogate_pair_part2 = *TYPE_METHOD(OPTIONAL_TYPE(char16), value)(&surrogate_pair_part2_opt);
    }

    char32 result_value = (((char32)surrogate_pair_part1 & 0x3FF) << 10 | ((char32)surrogate_pair_part2 & 0x3FF)) + 0x10000;
    TYPE_METHOD(OPTIONAL_TYPE(char32), construct_copy_from_value_at)(&result, &result_value);
    return result;
}

struct OPTIONAL_TYPE(char32) NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c16_buffer, unicode_character))(char16 const buffer[const static 6], usize buffer_size) {
    struct OPTIONAL_TYPE(char32) result;
    if (buffer_size < 6u) {
        TYPE_METHOD(OPTIONAL_TYPE(char32), construct_at)(&result);
        return result;
    }

    char16 surrogate_pair_part1;
    {
        struct OPTIONAL_TYPE(char16) surrogate_pair_part1_opt = hex_sequence_to_utf16_character(buffer);
        if (!TYPE_METHOD(OPTIONAL_TYPE(char16), has_value)(&surrogate_pair_part1_opt)) {
            TYPE_METHOD(OPTIONAL_TYPE(char32), construct_at)(&result);
            return result;
        }
        surrogate_pair_part1 = *TYPE_METHOD(OPTIONAL_TYPE(char16), value)(&surrogate_pair_part1_opt);
    }

    if (surrogate_pair_part1 < 0xD800 || surrogate_pair_part1 > 0xDC00) {
        char32 result_value = surrogate_pair_part1;
        TYPE_METHOD(OPTIONAL_TYPE(char32), construct_copy_from_value_at)(&result, &result_value);
        return result;
    }

    if (buffer_size < 12u) {
        TYPE_METHOD(OPTIONAL_TYPE(char32), construct_at)(&result);
        return result;
    }

    char16 surrogate_pair_part2;
    {
        struct OPTIONAL_TYPE(char16) surrogate_pair_part2_opt = hex_sequence_to_utf16_character(buffer + 6u);
        if (!TYPE_METHOD(OPTIONAL_TYPE(char16), has_value)(&surrogate_pair_part2_opt)) {
            TYPE_METHOD(OPTIONAL_TYPE(char32), construct_at)(&result);
            return result;
        }
        surrogate_pair_part2 = *TYPE_METHOD(OPTIONAL_TYPE(char16), value)(&surrogate_pair_part2_opt);
    }

    char32 result_value = (((char32)surrogate_pair_part1 & 0x3FF) << 10 | ((char32)surrogate_pair_part2 & 0x3FF)) + 0x10000;
    TYPE_METHOD(OPTIONAL_TYPE(char32), construct_copy_from_value_at)(&result, &result_value);
    return result;
}

static uint8 hex_character_to_integer(char16 character) {
    if ('0' <= character && character <= '9') {
        return (uint8)(character - '0');
    }
    if ('a' <= character && character <= 'z') {
        return (uint8)(character - 'a' + 10u);
    }
    if ('A' <= character && character <= 'Z') {
        return (uint8)(character - 'A' + 10u);
    }
    return MAX_VALUE(uint8);
}

static OPTIONAL_TYPE(char16) hex_u8_sequence_to_utf16_character(char8 const buffer[const static 6]) {
    struct OPTIONAL_TYPE(char16) result;
    ASSERT(buffer[0u] == '\\');
    ASSERT(buffer[1u] == 'u');
    if (buffer[0u] != '\\' && buffer[1u] != 'u') {
        TYPE_METHOD(OPTIONAL_TYPE(char16), construct_at)(&result);
        return result;
    }
    char16 result_value = 0u;
    uint8 value;
    for (uint8 i = 0u; i < 4; ++i) {
        value = hex_character_to_integer(buffer[2u + i]);
        if (value == MAX_VALUE(uint8)) {
            TYPE_METHOD(OPTIONAL_TYPE(char16), construct_at)(&result);
            return result;
        }
        result_value |= (char16)(value << ((3 - i) << 2));
    }
    TYPE_METHOD(OPTIONAL_TYPE(char16), construct_copy_from_value_at)(&result, &result_value);
    return result;
}

static OPTIONAL_TYPE(char16) hex_u16_sequence_to_utf16_character(char16 const buffer[const static 6]) {
    struct OPTIONAL_TYPE(char16) result;
    ASSERT(buffer[0u] == '\\');
    ASSERT(buffer[1u] == 'u');
    if (buffer[0u] != '\\' && buffer[1u] != 'u') {
        TYPE_METHOD(OPTIONAL_TYPE(char16), construct_at)(&result);
        return result;
    }
    char16 result_value = 0u;
    uint8 value;
    for (uint8 i = 0u; i < 4; ++i) {
        value = hex_character_to_integer(buffer[2u + i]);
        if (value == MAX_VALUE(uint8)) {
            TYPE_METHOD(OPTIONAL_TYPE(char16), construct_at)(&result);
            return result;
        }
        result_value |= (char16)(value << ((3 - i) << 2));
    }
    TYPE_METHOD(OPTIONAL_TYPE(char16), construct_copy_from_value_at)(&result, &result_value);
    return result;
}

uint8 NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf8_c_codepoints))(char32 unicode_character, char utf8_buffer[static 4]) {
    STATIC_ASSERT(sizeof(char) == sizeof(char8));
    return NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf8_codepoints))(unicode_character, (char8*)utf8_buffer);
}

uint8 NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf8_codepoints))(char32 unicode_character, char8 utf8_buffer[static 4]) {
    ASSERT(unicode_character <= 0x10FFFF);
    if (unicode_character <= 0x7F) {
        utf8_buffer[0u] = (char8)unicode_character;                          /* 0xxx'xxxx */
        return 1;
    }
    if (unicode_character <= 0x7FF) {
        utf8_buffer[0u] = 0xC0 | (char8)(unicode_character >> 6);            /* 110x'xxxx */
        utf8_buffer[1u] = 0x80 | (char8)(unicode_character & 0x3F);          /* 10xx'xxxx */
        return 2u;
    }
    if (unicode_character <= 0xFFFF) {
        utf8_buffer[0u] = 0xE0 | (char8)(unicode_character >> 12);           /* 1110'xxxx */
        utf8_buffer[1u] = 0x80 | (char8)((unicode_character >> 6) & 0x3F);   /* 10xx'xxxx */
        utf8_buffer[2u] = 0x80 | (char8)(unicode_character & 0x3F);          /* 10xx'xxxx */
        return 3u;
    }
    if (unicode_character <= 0x10FFFF) {
        utf8_buffer[0u] = 0xF0 | (char8)(unicode_character >> 18);           /* 1111'0xxx */
        utf8_buffer[1u] = 0x80 | (char8)((unicode_character >> 12) & 0x3F);  /* 10xx'xxxx */
        utf8_buffer[2u] = 0x80 | (char8)((unicode_character >> 6) & 0x3F);   /* 10xx'xxxx */
        utf8_buffer[3u] = 0x80 | (char8)(unicode_character & 0x3F);          /* 10xx'xxxx */
        return 4u;
    }
    return 0u;
}

uint8 NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf16_codepoints))(char32 unicode_character, char16 utf16_buffer[static 2]) {
    ASSERT(unicode_character <= 0x10FFFF);
    if (unicode_character <= 0x0FFFF) {
        utf16_buffer[0u] = (char16)unicode_character;
        return 1u;
    }

    if (unicode_character <= 0x10FFFF) { // unicode_character: 0x010000 – 0x10FFFF
        unicode_character -= 0x010000;   // unicode_character: 0x000000 – 0x0FFFFF
        utf16_buffer[0u] = (char16)((unicode_character >> 10) & 0x3FF) + 0xD800;
        utf16_buffer[1u] = (char16)(unicode_character & 0x3FF) + 0xDC00;
        return 2u;
    }

    return 0u;
}
