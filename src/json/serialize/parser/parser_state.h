#pragma once

#include <json/common.h>

#define JSON_PARSER_STATE_ENUM_TYPE() NAMESPACE_JSON(ENUM_TYPE(parser_state))
#define JSON_PARSER_STATE_ENUM_VALUE(VALUE) ENUM_VALUE(JSON_PARSER_STATE_ENUM_TYPE(), VALUE)

typedef enum JSON_PARSER_STATE_ENUM_TYPE() {
    JSON_PARSER_STATE_ENUM_VALUE(NONE) = 0,
    JSON_PARSER_STATE_ENUM_VALUE(ARRAY_EXPRESSION),
    JSON_PARSER_STATE_ENUM_VALUE(OBJECT_EXPRESSION),
    JSON_PARSER_STATE_ENUM_VALUE(KEY_VALUE_EXPRESSION),
    JSON_PARSER_STATE_ENUM_VALUE(KEY_VALUE_AWAIT_FOR_VALUE_EXPRESSION),
    JSON_PARSER_STATE_ENUM_VALUE(VALUE_EXPRESSION),
} JSON_PARSER_STATE_ENUM_TYPE();
