#pragma once

#include <primitives/primitives.h>
#include <utils/string/common.h>
#include <utils/convert.h>
#include <primitives/optional.h>

extern char32 NAMESPACE_UTILS_STRING(CONVERT(utf8_c_codepoints, unicode_character))(char const* const codepoints, uint8* const count_codepoints_read);
extern char32 NAMESPACE_UTILS_STRING(CONVERT(utf8_codepoints, unicode_character))(char8 const* const codepoints, uint8* const count_codepoints_read);
extern char32 NAMESPACE_UTILS_STRING(CONVERT(utf16_codepoints, unicode_character))(char16 const* const codepoints, uint8* const count_codepoints_read);

#define utils__string__convert__utf_codepoints_to_unicode_character(CODEPOINTS, CODEPOINTS_READ) _Generic((CODEPOINTS),\
    char const*: NAMESPACE_UTILS_STRING(CONVERT(utf8_c_codepoints, unicode_character)),\
    char*: NAMESPACE_UTILS_STRING(CONVERT(utf8_c_codepoints, unicode_character)),\
    char8 const*: NAMESPACE_UTILS_STRING(CONVERT(utf8_codepoints, unicode_character)),\
    char8*: NAMESPACE_UTILS_STRING(CONVERT(utf8_codepoints, unicode_character)),\
    char16 const*: NAMESPACE_UTILS_STRING(CONVERT(utf16_codepoints, unicode_character)),\
    char16*: NAMESPACE_UTILS_STRING(CONVERT(utf16_codepoints, unicode_character))\
)(CODEPOINTS, CODEPOINTS_READ)


extern struct OPTIONAL_TYPE(char32) NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c_buffer, unicode_character))(char const buffer[const static 6], usize buffer_size);
extern struct OPTIONAL_TYPE(char32) NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c8_buffer, unicode_character))(char8 const buffer[const static 6], usize buffer_size);
extern struct OPTIONAL_TYPE(char32) NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c16_buffer, unicode_character))(char16 const buffer[const static 6], usize buffer_size);

#define utils__string__convert__unicode_character_buffer_to_unicode_character(BUFFER, BUFFER_SIZE) _Generic((BUFFER),\
    char const*: NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c_buffer, unicode_character)),\
    char*: NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c_buffer, unicode_character)),\
    char8 const*: NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c8_buffer, unicode_character)),\
    char8*: NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c8_buffer, unicode_character)),\
    char16 const*: NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c16_buffer, unicode_character)),\
    char16*: NAMESPACE_UTILS_STRING(CONVERT(unicode_character_c16_buffer, unicode_character))\
)(BUFFER, BUFFER_SIZE)


extern uint8 NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf8_c_codepoints))(char32 unicode_character, char utf8_buffer[static 4]);
extern uint8 NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf8_codepoints))(char32 unicode_character, char8 utf8_buffer[static 4]);
extern uint8 NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf16_codepoints))(char32 unicode_character, char16 utf16_buffer[static 2]);

#define utils__string__convert__unicode_character_to_utf_codepoints(UNICODE_CHARACTER, CODEPOINTS_BUFFER) _Generic((CODEPOINTS_BUFFER),\
    char const*   : NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf8_c_codepoints)),\
    char*         : NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf8_c_codepoints)),\
    char8 const*  : NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf8_codepoints)),\
    char8*        : NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf8_codepoints)),\
    char16 const* : NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf16_codepoints)),\
    char16*       : NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf16_codepoints))\
)(UNICODE_CHARACTER, CODEPOINTS_BUFFER)


