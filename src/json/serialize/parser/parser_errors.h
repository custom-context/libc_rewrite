#pragma once

#include <json/serialize/lexer/lexer_token.h>
#include <json/common.h>

#include <containers/dynamic/string/string.h>
#include <containers/static/string_view/string_view.h>

#define JSON_PARSER_ERROR_TYPE() NAMESPACE_JSON(parser_error)
#define JSON_PARSER_ERROR_METHOD(METHOD) TYPE_METHOD(JSON_PARSER_ERROR_TYPE(), METHOD)

typedef struct JSON_PARSER_ERROR_TYPE() {
    struct STRING_TYPE() message;
    struct JSON_LEXER_TOKEN_TYPE() token;
} JSON_PARSER_ERROR_TYPE();

struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(construct_custom_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE() const* const token);

struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(construct_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this);
struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(construct_copy_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_PARSER_ERROR_TYPE() const* const source);
struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(construct_move_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_PARSER_ERROR_TYPE()* const source);
struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(assign_copy_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_PARSER_ERROR_TYPE() const* const source);
struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(assign_move_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_PARSER_ERROR_TYPE()* const source);
void
    JSON_PARSER_ERROR_METHOD(swap)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_PARSER_ERROR_TYPE()* const source);
void* JSON_PARSER_ERROR_METHOD(destroy_at)(struct JSON_PARSER_ERROR_TYPE()* const this);

struct CSTRING_VIEW_TYPE() JSON_PARSER_ERROR_METHOD(message)(struct JSON_PARSER_ERROR_TYPE() const* const this);
