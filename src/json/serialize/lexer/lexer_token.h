#pragma once

#include <json/common.h>
#include <containers/dynamic/string/string.h>

#define JSON_LEXER_TOKEN_ENUM_TYPE() NAMESPACE_JSON(ENUM_TYPE(token))
#define JSON_LEXER_TOKEN_ENUM_VALUE(VALUE) ENUM_VALUE(JSON_LEXER_TOKEN_ENUM_TYPE(), VALUE)

typedef enum JSON_LEXER_TOKEN_ENUM_TYPE() {
    JSON_LEXER_TOKEN_ENUM_VALUE(UNKNOWN),
    JSON_LEXER_TOKEN_ENUM_VALUE(WHITESPACE),
    JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_BEGIN),
    JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_END),
    JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_BEGIN),
    JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_END),
    JSON_LEXER_TOKEN_ENUM_VALUE(NULL_LITERAL),
    JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL),
    JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL),
    JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL),
    JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR),
    JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR),
} JSON_LEXER_TOKEN_ENUM_TYPE();

#define JSON_LEXER_TOKEN_TYPE() NAMESPACE_JSON(token)
#define JSON_LEXER_TOKEN_METHOD(METHOD) TYPE_METHOD(JSON_LEXER_TOKEN_TYPE(), METHOD)

typedef struct JSON_LEXER_TOKEN_TYPE() {
    union {
        bool boolean; // for boolean literals
        double number; // for number literals
        struct STRING_TYPE() string; // for string literals
    };
    enum JSON_LEXER_TOKEN_ENUM_TYPE() token_type;
    usize position;
} JSON_LEXER_TOKEN_TYPE();

struct JSON_LEXER_TOKEN_TYPE()*
    JSON_LEXER_TOKEN_METHOD(construct_at)(
        struct JSON_LEXER_TOKEN_TYPE()* const this);
struct JSON_LEXER_TOKEN_TYPE()*
    JSON_LEXER_TOKEN_METHOD(construct_copy_at)(
        struct JSON_LEXER_TOKEN_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE() const* const source);
struct JSON_LEXER_TOKEN_TYPE()*
    JSON_LEXER_TOKEN_METHOD(construct_move_at)(
        struct JSON_LEXER_TOKEN_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE()* const source);
struct JSON_LEXER_TOKEN_TYPE()*
    JSON_LEXER_TOKEN_METHOD(assign_copy_at)(
        struct JSON_LEXER_TOKEN_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE() const* const source);
struct JSON_LEXER_TOKEN_TYPE()*
    JSON_LEXER_TOKEN_METHOD(assign_move_at)(
        struct JSON_LEXER_TOKEN_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE()* const source);
void
    JSON_LEXER_TOKEN_METHOD(swap)(
        struct JSON_LEXER_TOKEN_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE()* const source);
void* JSON_LEXER_TOKEN_METHOD(destroy_at)(struct JSON_LEXER_TOKEN_TYPE()* const this);
