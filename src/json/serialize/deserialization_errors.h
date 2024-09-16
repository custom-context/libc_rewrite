#pragma once

#include <json/common.h>
#include <containers/dynamic/string/string.h>
#include <containers/static/string_view/string_view.h>
#include "lexer/lexer_errors.h"
#include "parser/parser_errors.h"

#define JSON_DESERIALIZATION_ERROR_TYPE() NAMESPACE_JSON(deserialization_error)
#define JSON_DESERIALIZATION_ERROR_METHOD(METHOD) TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), METHOD)

typedef struct JSON_DESERIALIZATION_ERROR_TYPE() {
    struct STRING_TYPE() message;
} JSON_DESERIALIZATION_ERROR_TYPE();

struct JSON_DESERIALIZATION_ERROR_TYPE()*
    JSON_DESERIALIZATION_ERROR_METHOD(construct_from_lexer_error_at)(
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const this,
        struct JSON_LEXER_ERROR_TYPE() const* const perror);

struct JSON_DESERIALIZATION_ERROR_TYPE()*
    JSON_DESERIALIZATION_ERROR_METHOD(construct_from_parser_error_at)(
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const this,
        struct CSTRING_VIEW_TYPE() const source_view,
        struct JSON_PARSER_ERROR_TYPE() const* const perror);

struct JSON_DESERIALIZATION_ERROR_TYPE()*
    JSON_DESERIALIZATION_ERROR_METHOD(construct_at)(
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const this);
struct JSON_DESERIALIZATION_ERROR_TYPE()*
    JSON_DESERIALIZATION_ERROR_METHOD(construct_copy_at)(
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const this,
        struct JSON_DESERIALIZATION_ERROR_TYPE() const* const source);
struct JSON_DESERIALIZATION_ERROR_TYPE()*
    JSON_DESERIALIZATION_ERROR_METHOD(construct_move_at)(
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const this,
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const source);
void* JSON_DESERIALIZATION_ERROR_METHOD(destroy_at)(struct JSON_DESERIALIZATION_ERROR_TYPE()* const this);

struct CSTRING_VIEW_TYPE() JSON_DESERIALIZATION_ERROR_METHOD(message)(struct JSON_DESERIALIZATION_ERROR_TYPE() const* const this);
