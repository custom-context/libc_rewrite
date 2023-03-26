#pragma once

#include <utils/string/common.h>

#define RAW_STRING_FUNCTION(CHAR_TYPE, NAME)\
    NAMESPACE_UTILS_STRING(TYPE_METHOD(CONCAT3(raw_string, _, CHAR_TYPE), NAME))
