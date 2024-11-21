#include "serialize.h"

#include "parser/parser.h"
#include "lexer/lexer.h"

struct STRING_TYPE() NAMESPACE_JSON(serialize)(struct JSON_VALUE_TYPE() const* const json) {
    return NAMESPACE_UTILS_STRING(CONVERT(JSON_VALUE_TYPE(), STRING_TYPE()))(json);
}

#define LEXER_RESULT_TYPE() RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE())
#define LEXER_RESULT_METHOD(METHOD) RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), METHOD)
#define DESERIALIZER_RESULT_TYPE() RESULT_TYPE(JSON_VALUE_TYPE(), JSON_DESERIALIZATION_ERROR_TYPE())
#define DESERIALIZER_RESULT_METHOD(METHOD) RESULT_METHOD(JSON_VALUE_TYPE(), JSON_DESERIALIZATION_ERROR_TYPE(), METHOD)

struct DESERIALIZER_RESULT_TYPE() NAMESPACE_JSON(deserialize)(struct CSTRING_VIEW_TYPE() const view) {
    // deserializer related structures:
    struct DESERIALIZER_RESULT_TYPE() result;
    struct JSON_DESERIALIZATION_ERROR_TYPE() deserialization_error;
    struct JSON_VALUE_TYPE() json_value;
    // lexer related structures:
    struct JSON_LEXER_TYPE() lexer; JSON_LEXER_METHOD(construct_from_value_at)(&lexer, view);
    struct JSON_LEXER_TYPE() lexer_end = JSON_LEXER_METHOD(end)(&lexer);
    struct LEXER_RESULT_TYPE() token_or_error;
    // parser related structures:
    struct JSON_PARSER_TYPE() parser; JSON_PARSER_METHOD(construct_at)(&parser);
    struct OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE()) parser_error;

    while (!JSON_LEXER_METHOD(are_equals)(&lexer, &lexer_end)) {
        // [construct] `token_or_error` is a raw copy and must be destructed at the end
        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);

        if (!LEXER_RESULT_METHOD(has_value)(&token_or_error)) {
            TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), construct_from_lexer_error_at)(
                &deserialization_error,
                LEXER_RESULT_METHOD(error)(&token_or_error)
            );

            DESERIALIZER_RESULT_METHOD(construct_move_from_error_at)(&result, &deserialization_error);

            TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), destroy_at)(&deserialization_error);
            LEXER_RESULT_METHOD(destroy_at)(&token_or_error);
            JSON_LEXER_METHOD(destroy_at)(&lexer);
            return result;
        }

        // [construct] `parser_error` is a raw copy and must be destructed at the end
        parser_error = JSON_PARSER_METHOD(push_move_token)(&parser, LEXER_RESULT_METHOD(mut_value)(&token_or_error));
        if (OPTIONAL_METHOD(JSON_PARSER_ERROR_TYPE(), has_value)(&parser_error)) {
            TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), construct_from_parser_error_at)(
                &deserialization_error,
                view,
                OPTIONAL_METHOD(JSON_PARSER_ERROR_TYPE(), value)(&parser_error)
            );

            DESERIALIZER_RESULT_METHOD(construct_move_from_error_at)(&result, &deserialization_error);

            TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), destroy_at)(&deserialization_error);
            OPTIONAL_METHOD(JSON_PARSER_ERROR_TYPE(), destroy_at)(&parser_error);
            LEXER_RESULT_METHOD(destroy_at)(&token_or_error);
            JSON_LEXER_METHOD(destroy_at)(&lexer);
            return result;
        }

        OPTIONAL_METHOD(JSON_PARSER_ERROR_TYPE(), destroy_at)(&parser_error);
        LEXER_RESULT_METHOD(destroy_at)(&token_or_error);
    }

    json_value = JSON_PARSER_AST_METHOD(shrink_to_value)(JSON_PARSER_METHOD(mut_abstract_syntax_tree)(&parser));

    DESERIALIZER_RESULT_METHOD(construct_move_from_value_at)(&result, &json_value);

    JSON_VALUE_METHOD(destroy_at)(&json_value);
    JSON_LEXER_METHOD(destroy_at)(&lexer);
    JSON_PARSER_METHOD(destroy_at)(&parser);
    return result;
}
