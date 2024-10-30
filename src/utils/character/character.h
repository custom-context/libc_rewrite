#pragma once

#include "common.h"

#include <primitives/characters_types_aliases.h>
#include <primitives/bool_type_alias.h>

extern bool NAMESPACE_UTILS_CHARACTER(is_char_digit)(char character);
extern bool NAMESPACE_UTILS_CHARACTER(is_char8_digit)(char8 character);
extern bool NAMESPACE_UTILS_CHARACTER(is_char16_digit)(char16 character);
extern bool NAMESPACE_UTILS_CHARACTER(is_char32_digit)(char32 character);

#define utils__character__is_digit(CHARACTER) _Generic((CHARACTER),\
    char32: NAMESPACE_UTILS_CHARACTER(is_char32_digit),\
    char16: NAMESPACE_UTILS_CHARACTER(is_char16_digit),\
    char8 : NAMESPACE_UTILS_CHARACTER(is_char8_digit),\
    char  : NAMESPACE_UTILS_CHARACTER(is_char_digit)\
)(CHARACTER)
