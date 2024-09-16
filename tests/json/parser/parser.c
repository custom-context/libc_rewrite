#include "parser.h"

#include <json/serialize/parser/parser.h>
#include <json/serialize/lexer/lexer.h>
#include <json/serialize/serialize.h>
#include <json/value/value.h>

#include <primitives/limits.h>
#include <utils/format.h>

IMPLEMENT_TYPE_TESTS(json_parser) {
    TEST_BLOCK("check base json value deserialization (from empty object)") {
        char const target_raw_string[] = "{}";
        struct JSON_PARSER_TYPE() parser;
        JSON_PARSER_METHOD(construct_at)(&parser);
        struct OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE()) parser_error_opt;
        // source_view construction
        struct CSTRING_VIEW_TYPE() source_view;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&source_view, target_raw_string);

        // tokenize value
        struct JSON_LEXER_TYPE() lexer; JSON_LEXER_METHOD(construct_from_value_at)(&lexer, source_view);
        struct JSON_LEXER_TYPE() lexer_end = JSON_LEXER_METHOD(end)(&lexer);
        struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) token_or_error;

        { // '{' // JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_BEGIN)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE()* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_BEGIN));
            parser_error_opt = JSON_PARSER_METHOD(push_move_token)(&parser, ptoken);
            CHECK(!OPTIONAL_METHOD(JSON_PARSER_ERROR_TYPE(), has_value)(&parser_error_opt));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // '}' // JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_END)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE()* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_END));
            parser_error_opt = JSON_PARSER_METHOD(push_move_token)(&parser, ptoken);
            CHECK(!OPTIONAL_METHOD(JSON_PARSER_ERROR_TYPE(), has_value)(&parser_error_opt));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // end of sequence
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(!RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            CHECK(JSON_LEXER_METHOD(are_equals)(&lexer, &lexer_end));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }

        struct JSON_PARSER_AST_TYPE()* pastree = JSON_PARSER_METHOD(mut_abstract_syntax_tree)(&parser);
        struct JSON_VALUE_TYPE() json_value = JSON_PARSER_AST_METHOD(shrink_to_value)(pastree);

        CHECK(JSON_VALUE_METHOD(type)(&json_value) == JSON_ENUM_VALUE(object));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const* const json_object =
            JSON_VALUE_METHOD(as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type))(&json_value);

        CHECK(TYPE_METHOD(JSON__object_type, size)(json_object) == 0u);

        // cleanup
        JSON_LEXER_METHOD(destroy_at)(&lexer_end);
        JSON_LEXER_METHOD(destroy_at)(&lexer);
        CSTRING_VIEW_METHOD(destroy_at)(&source_view);
        JSON_PARSER_METHOD(destroy_at)(&parser);
    }
    TEST_BLOCK("check base json value deserialization (from empty array)") {
        char const target_raw_string[] = "[]";
        struct JSON_PARSER_TYPE() parser;
        JSON_PARSER_METHOD(construct_at)(&parser);
        struct OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE()) parser_error_opt;
        // source_view construction
        struct CSTRING_VIEW_TYPE() source_view;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&source_view, target_raw_string);

        // tokenize value
        struct JSON_LEXER_TYPE() lexer; JSON_LEXER_METHOD(construct_from_value_at)(&lexer, source_view);
        struct JSON_LEXER_TYPE() lexer_end = JSON_LEXER_METHOD(end)(&lexer);
        struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) token_or_error;

        { // '[' // JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_BEGIN)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE()* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_BEGIN));
            parser_error_opt = JSON_PARSER_METHOD(push_move_token)(&parser, ptoken);
            CHECK(!OPTIONAL_METHOD(JSON_PARSER_ERROR_TYPE(), has_value)(&parser_error_opt));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ']' // JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_END)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE()* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_END));
            parser_error_opt = JSON_PARSER_METHOD(push_move_token)(&parser, ptoken);
            CHECK(!OPTIONAL_METHOD(JSON_PARSER_ERROR_TYPE(), has_value)(&parser_error_opt));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // end of sequence
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(!RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            CHECK(JSON_LEXER_METHOD(are_equals)(&lexer, &lexer_end));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }

        struct JSON_PARSER_AST_TYPE()* pastree = JSON_PARSER_METHOD(mut_abstract_syntax_tree)(&parser);
        struct JSON_VALUE_TYPE() json_value = JSON_PARSER_AST_METHOD(shrink_to_value)(pastree);

        CHECK(JSON_VALUE_METHOD(type)(&json_value) == JSON_ENUM_VALUE(array));
        JSON__array_type const* const json_object =
            JSON_VALUE_METHOD(as)(JSON__array_type)(&json_value);

        CHECK(TYPE_METHOD(JSON__array_type, size)(json_object) == 0u);

        // cleanup
        JSON_LEXER_METHOD(destroy_at)(&lexer_end);
        JSON_LEXER_METHOD(destroy_at)(&lexer);
        CSTRING_VIEW_METHOD(destroy_at)(&source_view);
        JSON_PARSER_METHOD(destroy_at)(&parser);
    }
}
