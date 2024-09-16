#include "parser_errors.h"
#include <utils/format.h>
#include <utils/string/convert.h>

static char const* convert_token_type_to_string(enum JSON_LEXER_TOKEN_ENUM_TYPE());
static struct STRING_TYPE() convert_token_value_to_string(struct JSON_LEXER_TOKEN_TYPE() const* const token);

struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(construct_custom_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE() const* const token) {
    ASSERT(this);
    ASSERT(token);

    JSON_LEXER_TOKEN_METHOD(construct_copy_at)(&this->token, token);

    struct STRING_TYPE() token_string_repr = convert_token_value_to_string(token);
    this->message =
        NAMESPACE_UTILS(format)(
            "Error occured while parsing expression from json string. "
            "position=%zu, "
            "token_type=\"%s\", "
            "token_value='%s'.",
            token->position,
            convert_token_type_to_string(token->token_type),
            STRING_METHOD(data)(&token_string_repr)
        );

    STRING_METHOD(destroy_at)(&token_string_repr);
    return this;
}
struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(construct_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this) {
    ASSERT(this);
    JSON_LEXER_TOKEN_METHOD(construct_at)(&this->token);
    TYPE_METHOD(STRING_TYPE(), construct_at)(&this->message);
    return this;
}
struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(construct_copy_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_PARSER_ERROR_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    JSON_LEXER_TOKEN_METHOD(construct_copy_at)(&this->token, &source->token);
    TYPE_METHOD(STRING_TYPE(), construct_copy_at)(&this->message, &source->message);
    return this;
}
struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(construct_move_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_PARSER_ERROR_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    JSON_LEXER_TOKEN_METHOD(construct_move_at)(&this->token, &source->token);
    TYPE_METHOD(STRING_TYPE(), construct_move_at)(&this->message, &source->message);
    return this;
}
struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(assign_copy_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_PARSER_ERROR_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    struct JSON_PARSER_ERROR_TYPE() temporary;
    JSON_PARSER_ERROR_METHOD(construct_copy_at)(&temporary, source);
    JSON_PARSER_ERROR_METHOD(swap)(this, &temporary);
    JSON_PARSER_ERROR_METHOD(destroy_at)(&temporary);
    return this;
}
struct JSON_PARSER_ERROR_TYPE()*
    JSON_PARSER_ERROR_METHOD(assign_move_at)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_PARSER_ERROR_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    struct JSON_PARSER_ERROR_TYPE() temporary;
    JSON_PARSER_ERROR_METHOD(construct_move_at)(&temporary, source);
    JSON_PARSER_ERROR_METHOD(swap)(this, &temporary);
    JSON_PARSER_ERROR_METHOD(destroy_at)(&temporary);
    return this;
}
void
    JSON_PARSER_ERROR_METHOD(swap)(
        struct JSON_PARSER_ERROR_TYPE()* const this,
        struct JSON_PARSER_ERROR_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    JSON_LEXER_TOKEN_METHOD(swap)(&this->token, &source->token);
    STRING_METHOD(swap)(&this->message, &source->message);
}
void* JSON_PARSER_ERROR_METHOD(destroy_at)(struct JSON_PARSER_ERROR_TYPE()* const this) {
    ASSERT(this);
    JSON_LEXER_TOKEN_METHOD(destroy_at)(&this->token);
    TYPE_METHOD(STRING_TYPE(), destroy_at)(&this->message);
    return this;
}

struct CSTRING_VIEW_TYPE() JSON_PARSER_ERROR_METHOD(message)(struct JSON_PARSER_ERROR_TYPE() const* const this) {
    ASSERT(this);
    struct CSTRING_VIEW_TYPE() result;
    TYPE_METHOD(CSTRING_VIEW_TYPE(), construct_from_buffer_at)(&result,
        TYPE_METHOD(STRING_TYPE(), data)(&this->message),
        TYPE_METHOD(STRING_TYPE(), size)(&this->message));
    return result;
}

static char const* convert_token_type_to_string(enum JSON_LEXER_TOKEN_ENUM_TYPE() type) {
    switch (type) {
        case (JSON_LEXER_TOKEN_ENUM_VALUE(WHITESPACE)): return "WHITESPACE";
        case (JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_BEGIN)): return "OBJECT_BEGIN";
        case (JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_END)): return "OBJECT_END";
        case (JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_BEGIN)): return "ARRAY_BEGIN";
        case (JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_END)): return "ARRAY_END";
        case (JSON_LEXER_TOKEN_ENUM_VALUE(NULL_LITERAL)): return "NULL_LITERAL";
        case (JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL)): return "BOOLEAN_LITERAL";
        case (JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL)): return "NUMBER_LITERAL";
        case (JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)): return "STRING_LITERAL";
        case (JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR)): return "COMMA_SEPARATOR";
        case (JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR)): return "COLON_SEPARATOR";
        default: return "UNKNOWN";
    }
}

static struct STRING_TYPE() convert_token_value_to_string(struct JSON_LEXER_TOKEN_TYPE() const* const token) {
    struct STRING_TYPE() result;
    switch (token->token_type) {
        case (JSON_LEXER_TOKEN_ENUM_VALUE(WHITESPACE)): STRING_METHOD(construct_from_c_string_at)(&result, " "); break;
        case (JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_BEGIN)): STRING_METHOD(construct_from_c_string_at)(&result, "{"); break;
        case (JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_END)): STRING_METHOD(construct_from_c_string_at)(&result, "}"); break;
        case (JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_BEGIN)): STRING_METHOD(construct_from_c_string_at)(&result, "["); break;
        case (JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_END)):  STRING_METHOD(construct_from_c_string_at)(&result, "]"); break;
        case (JSON_LEXER_TOKEN_ENUM_VALUE(NULL_LITERAL)): STRING_METHOD(construct_from_c_string_at)(&result, "null"); break;
        case (JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL)): {
            STRING_METHOD(construct_from_c_string_at)(&result, (char*)(token->boolean ? "true" : "false"));
        } break;
        case (JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL)): {
            result = NAMESPACE_UTILS(format)("%ld", token->number);
        } break;
        case (JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)): {
            result = NAMESPACE_UTILS(format)("\"%s\"", STRING_METHOD(data)(&token->string));
        } break;
        case (JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR)): STRING_METHOD(construct_from_c_string_at)(&result, ","); break;
        case (JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR)): STRING_METHOD(construct_from_c_string_at)(&result, ":"); break;
        default: STRING_METHOD(construct_from_c_string_at)(&result, "UNKNOWN"); break;
    }
    return result;
}

