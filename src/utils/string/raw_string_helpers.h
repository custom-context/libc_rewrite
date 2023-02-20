#pragma once

#include <primitives/unsigned_types_aliases.h>
#include <primitives/characters_types_aliases.h>
#include <utils/common.h>

#ifndef NAMESPACE_UTILS_STRING
    #define NAMESPACE_UTILS_STRING(NAME) NAMESPACE_UTILS(CONCAT3(string, __, NAME))
#endif
#ifndef RAW_STRING_FUNCTION
    #define RAW_STRING_FUNCTION(CHAR_TYPE, NAME) NAMESPACE_UTILS_STRING(TYPE_METHOD(CONCAT3(raw_string, _, CHAR_TYPE), length))
#endif
#define DECLARE_RAW_STRING_LENGTH_FUNCTION(CHAR_TYPE)\
extern uint RAW_STRING_FUNCTION(CHAR_TYPE, length)(CHAR_TYPE const* const string)

#define DEFINE_RAW_STRING_LENGTH_FUNCTION(CHAR_TYPE)\
uint RAW_STRING_FUNCTION(CHAR_TYPE, length)(CHAR_TYPE const* const string) {\
    uint length = 0u;\
    while (string[length] != '\0') {\
        ++length;\
    }\
    return length;\
}

DECLARE_RAW_STRING_LENGTH_FUNCTION(char);
DECLARE_RAW_STRING_LENGTH_FUNCTION(char8);
DECLARE_RAW_STRING_LENGTH_FUNCTION(char16);
DECLARE_RAW_STRING_LENGTH_FUNCTION(char32);
DECLARE_RAW_STRING_LENGTH_FUNCTION(char64);
