#pragma once
#include <utils/common.h>

#define NAMESPACE_UTILS_STRING(NAME) NAMESPACE_UTILS(CONCAT3(string, __, NAME))

#define STRING_FUNCTION(STRING_TYPE, NAME)\
    NAMESPACE_UTILS_STRING(TYPE_METHOD(CONCAT3(STRING_TYPE, _, fn), NAME))
