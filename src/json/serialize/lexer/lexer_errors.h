#pragma once

#include <json/common.h>
#include <containers/dynamic/string/string.h>
#include <containers/static/string_view/string_view.h>

#define JSON_LEXER_ERROR_TYPE() NAMESPACE_JSON(lexer_error)
#define JSON_LEXER_ERROR_METHOD(METHOD)\
TYPE_METHOD(JSON_LEXER_ERROR_TYPE(), METHOD)

typedef struct JSON_LEXER_ERROR_TYPE() {
    struct STRING_TYPE() message;
} JSON_LEXER_ERROR_TYPE();

struct JSON_LEXER_ERROR_TYPE()*
    JSON_LEXER_ERROR_METHOD(construct_custom_at)(
        struct JSON_LEXER_ERROR_TYPE()* const this,
        struct CSTRING_VIEW_TYPE() substring, usize position, usize size);
struct JSON_LEXER_ERROR_TYPE()*
    JSON_LEXER_ERROR_METHOD(construct_at)(
        struct JSON_LEXER_ERROR_TYPE()* const this);
struct JSON_LEXER_ERROR_TYPE()*
    JSON_LEXER_ERROR_METHOD(construct_copy_at)(
        struct JSON_LEXER_ERROR_TYPE()* const this,
        struct JSON_LEXER_ERROR_TYPE() const* const source);
struct JSON_LEXER_ERROR_TYPE()*
    JSON_LEXER_ERROR_METHOD(construct_move_at)(
        struct JSON_LEXER_ERROR_TYPE()* const this,
        struct JSON_LEXER_ERROR_TYPE()* const source);
void* JSON_LEXER_ERROR_METHOD(destroy_at)(struct JSON_LEXER_ERROR_TYPE()* const this);

struct CSTRING_VIEW_TYPE() JSON_LEXER_ERROR_METHOD(message)(struct JSON_LEXER_ERROR_TYPE() const* const this);
