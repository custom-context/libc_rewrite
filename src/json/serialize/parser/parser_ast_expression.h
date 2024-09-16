#pragma once

#include <json/common.h>

#define JSON_PARSER_EXPRESSION_ENUM_TYPE() NAMESPACE_JSON(ENUM_TYPE(parser_expression))
#define JSON_PARSER_EXPRESSION_ENUM_VALUE(VALUE) ENUM_VALUE(JSON_PARSER_EXPRESSION_ENUM_TYPE(), VALUE)

typedef enum JSON_PARSER_EXPRESSION_ENUM_TYPE() {
    JSON_PARSER_EXPRESSION_ENUM_VALUE(VALUE_TERMINAL),
    JSON_PARSER_EXPRESSION_ENUM_VALUE(ARRAY_EXPRESSION),
    JSON_PARSER_EXPRESSION_ENUM_VALUE(OBJECT_EXPRESSION),
    JSON_PARSER_EXPRESSION_ENUM_VALUE(KEY_VALUE_EXPRESSION),
} JSON_PARSER_EXPRESSION_ENUM_TYPE();
