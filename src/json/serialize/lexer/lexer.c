#include "lexer.h"

DEFINE_RESULT_TYPE_METHODS_WITH_COMMON_MODIFIER(,JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE())

DEFINE_OPTIONAL_STATIC_METHODS(JSON_LEXER_TOKEN_TYPE())

struct JSON_LEXER_TYPE()*
    JSON_LEXER_METHOD(construct_from_value_at)(
        struct JSON_LEXER_TYPE()* const this,
        struct CSTRING_VIEW_TYPE() const source) {
    ASSERT(this);
    JSON_LEXER_TOKEN_METHOD(PRIVATE(initialize_token_mapping_table))();
    this->source = source;
    this->source_index = 0u;
    return this;
}

void* JSON_LEXER_METHOD(destroy_at)(struct JSON_LEXER_TYPE()* const this) {
    ASSERT(this);
    CSTRING_VIEW_METHOD(destroy_at)(&this->source);
    return this;
}

struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) JSON_LEXER_METHOD(get_next_token)(struct JSON_LEXER_TYPE()* const this) {
    ASSERT(this);

    struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) result;

    usize const start_index = this->source_index;
    for (usize count_bytes_read_by_parsing; this->source_index < TYPE_METHOD(CSTRING_VIEW_TYPE(), size)(&this->source); this->source_index += count_bytes_read_by_parsing) {
        struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) value_opt = JSON_LEXER_METHOD(PRIVATE(try_map_lexeme_to_token))(this, &count_bytes_read_by_parsing);

        // if no token was read => error occured while reading -> return error
        if (!OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), has_value)(&value_opt)) {
            struct JSON_LEXER_ERROR_TYPE() error;
            JSON_LEXER_ERROR_METHOD(construct_custom_at)(&error, this->source, this->source_index, start_index - this->source_index);

            TYPE_METHOD(RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()), construct_move_from_error_at)(&result, &error);

            JSON_LEXER_ERROR_METHOD(destroy_at)(&error);
            OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), destroy_at)(&value_opt);
            return result;
        }

        // continue reading if white space occured:
        if (OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), value)(&value_opt)->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(WHITESPACE)) {
            OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), destroy_at)(&value_opt);
            continue;
        }

        // return token on success
        struct JSON_LEXER_TOKEN_TYPE() token;
        JSON_LEXER_TOKEN_METHOD(construct_move_at)(&token, OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), mut_value)(&value_opt));

        TYPE_METHOD(RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()), construct_move_from_value_at)(&result, &token);

        JSON_LEXER_TOKEN_METHOD(destroy_at)(&token);
        OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), destroy_at)(&value_opt);
        this->source_index += count_bytes_read_by_parsing;
        return result;
    }

    // if token was not returned => we are reached end of source string -> return error
    struct JSON_LEXER_ERROR_TYPE() error;
    JSON_LEXER_ERROR_METHOD(construct_custom_at)(&error, this->source, this->source_index, start_index - this->source_index);
    TYPE_METHOD(RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()), construct_move_from_error_at)(&result, &error);
    return result;
}

struct JSON_LEXER_TYPE() JSON_LEXER_METHOD(end)(struct JSON_LEXER_TYPE() const* const this) {
    ASSERT(this);
    struct JSON_LEXER_TYPE() result;
    result.source = this->source;
    result.source_index = TYPE_METHOD(CSTRING_VIEW_TYPE(), size)(&this->source);
    return result;
}

bool JSON_LEXER_METHOD(are_equals)(struct JSON_LEXER_TYPE() const* const this, struct JSON_LEXER_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    return
        this->source.buffer == source->source.buffer &&
        this->source.size == source->source.size &&
        this->source_index == source->source_index;
}
