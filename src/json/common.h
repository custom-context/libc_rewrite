#pragma once

#include <utils/macros.h>

#define NAMESPACE_JSON(NAME) NAMESPACE(json, NAME)

#define JSON_ENUM_TYPE()\
    NAMESPACE_JSON(ENUM_TYPE(json))

#define JSON_ENUM_VALUE(VALUE)\
    ENUM_VALUE(NAMESPACE_JSON(ENUM_TYPE(json)), VALUE)

typedef enum JSON_ENUM_TYPE() {
    JSON_ENUM_VALUE(null),
    JSON_ENUM_VALUE(boolean),
    JSON_ENUM_VALUE(number),
    JSON_ENUM_VALUE(string),
    JSON_ENUM_VALUE(array),
    JSON_ENUM_VALUE(object)
} JSON_ENUM_TYPE();
