#pragma once

#include <primitives/unsigned_types_aliases.h>
#include <primitives/characters_types_aliases.h>
#include <utils/macros.h>

#define DECLARE_C_STRING_LENGTH_FUNCTION(CHAR_TYPE)\
extern uint CONCAT5(utils__string__string, _, CHAR_TYPE ,_, length)(CHAR_TYPE const* const string)

#define DEFINE_C_STRING_LENGTH_FUNCTION(CHAR_TYPE)\
uint CONCAT5(utils__string__string, _, CHAR_TYPE ,_, length)(CHAR_TYPE const* const string) {\
    uint length = 0u;\
    while (string[length] != '\0') {\
        ++length;\
    }\
    return length;\
}

DECLARE_C_STRING_LENGTH_FUNCTION(char);
DECLARE_C_STRING_LENGTH_FUNCTION(char8);
DECLARE_C_STRING_LENGTH_FUNCTION(char16);
DECLARE_C_STRING_LENGTH_FUNCTION(char32);
DECLARE_C_STRING_LENGTH_FUNCTION(char64);
