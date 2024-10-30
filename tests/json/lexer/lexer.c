#include "lexer.h"

#include <json/serialize/lexer/lexer.h>
#include <json/serialize/serialize.h>
#include <json/value/value.h>

#include <primitives/limits.h>
#include <utils/format.h>

IMPLEMENT_TYPE_TESTS(json_lexer) {
    TEST_BLOCK("check base json value tokenization (from null)") {
        char const target_value_raw_string[] = "null";
        JSON_ENUM_TYPE() const target_json_value_type = JSON_ENUM_VALUE(null);
        JSON_LEXER_TOKEN_ENUM_TYPE() const target_token_literal = JSON_LEXER_TOKEN_ENUM_VALUE(NULL_LITERAL);

        // construct json value as null-value
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_at)(&json_value);

        // check correct json value construction
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == target_json_value_type);

        // serialize json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(&json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(target_value_raw_string) / sizeof(char) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            target_value_raw_string));

        // tokenize value
        struct CSTRING_VIEW_TYPE() target_view;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&target_view, target_value_raw_string);

        struct JSON_LEXER_TYPE() lexer;
        JSON_LEXER_METHOD(construct_from_value_at)(&lexer, target_view);

        struct JSON_LEXER_TYPE() lexer_end = JSON_LEXER_METHOD(end)(&lexer);

        struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) token_or_error;
        
        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
        CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
        struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
        CHECK(ptoken->token_type == target_token_literal);
        RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);

        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
        CHECK(!RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
        CHECK(JSON_LEXER_METHOD(are_equals)(&lexer, &lexer_end));
        RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);

        // cleanup
        JSON_LEXER_METHOD(destroy_at)(&lexer_end);
        JSON_LEXER_METHOD(destroy_at)(&lexer);
        TYPE_METHOD(CSTRING_VIEW_TYPE(), destroy_at)(&target_view);
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&serialized_json_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json value serialization (from boolean [false])") {
        char const target_value_raw_string[] = "false";
        bool const value = false;
        JSON_ENUM_TYPE() const target_json_value_type = JSON_ENUM_VALUE(boolean);
        JSON_LEXER_TOKEN_ENUM_TYPE() const target_token_literal = JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL);

        // construct json value as boolean value
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_boolean_at)(&json_value, value);

        // check correct json value construction
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == target_json_value_type);

        // serialize json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(&json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(target_value_raw_string) / sizeof(char) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            target_value_raw_string));

        // tokenize value
        struct CSTRING_VIEW_TYPE() target_view;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&target_view, target_value_raw_string);

        struct JSON_LEXER_TYPE() lexer;
        JSON_LEXER_METHOD(construct_from_value_at)(&lexer, target_view);

        struct JSON_LEXER_TYPE() lexer_end = JSON_LEXER_METHOD(end)(&lexer);

        struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) token_or_error;
        
        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
        CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
        struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
        CHECK(ptoken->token_type == target_token_literal);
        CHECK(ptoken->boolean == value);
        RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);

        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
        CHECK(!RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
        CHECK(JSON_LEXER_METHOD(are_equals)(&lexer, &lexer_end));
        RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);

        // cleanup
        JSON_LEXER_METHOD(destroy_at)(&lexer_end);
        JSON_LEXER_METHOD(destroy_at)(&lexer);
        TYPE_METHOD(CSTRING_VIEW_TYPE(), destroy_at)(&target_view);
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&serialized_json_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json value serialization (from boolean [true])") {
        char const target_value_raw_string[] = "true";
        bool const value = true;
        JSON_ENUM_TYPE() const target_json_value_type = JSON_ENUM_VALUE(boolean);
        JSON_LEXER_TOKEN_ENUM_TYPE() const target_token_literal = JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL);

        // construct json value as boolean value
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_boolean_at)(&json_value, value);

        // check correct json value construction
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == target_json_value_type);

        // serialize json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(&json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(target_value_raw_string) / sizeof(char) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            target_value_raw_string));

        // tokenize value
        struct CSTRING_VIEW_TYPE() target_view;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&target_view, target_value_raw_string);

        struct JSON_LEXER_TYPE() lexer;
        JSON_LEXER_METHOD(construct_from_value_at)(&lexer, target_view);

        struct JSON_LEXER_TYPE() lexer_end = JSON_LEXER_METHOD(end)(&lexer);

        struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) token_or_error;
        
        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
        CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
        struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
        CHECK(ptoken->token_type == target_token_literal);
        CHECK(ptoken->boolean == value);
        RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);

        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
        CHECK(!RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
        CHECK(JSON_LEXER_METHOD(are_equals)(&lexer, &lexer_end));
        RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);

        // cleanup
        JSON_LEXER_METHOD(destroy_at)(&lexer_end);
        JSON_LEXER_METHOD(destroy_at)(&lexer);
        TYPE_METHOD(CSTRING_VIEW_TYPE(), destroy_at)(&target_view);
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&serialized_json_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json value serialization (from number)") {
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) const value = 23.6319e+2;
        char const target_value_raw_string[] = "2363.19";
        JSON_ENUM_TYPE() const target_json_value_type = JSON_ENUM_VALUE(number);
        JSON_LEXER_TOKEN_ENUM_TYPE() const target_token_literal = JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL);

        // construct json value as boolean value
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_number_at)(&json_value, value);

        // check correct json value construction
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == target_json_value_type);

        // serialize json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(&json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(target_value_raw_string) / sizeof(char) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            target_value_raw_string));

        // tokenize value
        struct CSTRING_VIEW_TYPE() target_view;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&target_view, target_value_raw_string);

        struct JSON_LEXER_TYPE() lexer;
        JSON_LEXER_METHOD(construct_from_value_at)(&lexer, target_view);

        struct JSON_LEXER_TYPE() lexer_end = JSON_LEXER_METHOD(end)(&lexer);

        struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) token_or_error;

        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
        CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
        struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
        CHECK(ptoken->token_type == target_token_literal);
        CHECK(fabs(ptoken->number - value) < EPSILON(double));
        RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);

        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
        CHECK(!RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
        CHECK(JSON_LEXER_METHOD(are_equals)(&lexer, &lexer_end));
        RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);

        // cleanup
        JSON_LEXER_METHOD(destroy_at)(&lexer_end);
        JSON_LEXER_METHOD(destroy_at)(&lexer);
        TYPE_METHOD(CSTRING_VIEW_TYPE(), destroy_at)(&target_view);
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&serialized_json_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }

    TEST_BLOCK("check base json value serialization (from string)") {
        char const target_value_raw_string[] = "@#%UHSND Qtgsdfu\nhw4w22j\u1353wsrwse^)323\\\t";
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) value = NAMESPACE_UTILS(cformat)("\"%s\"", target_value_raw_string);
        JSON_ENUM_TYPE() const target_json_value_type = JSON_ENUM_VALUE(string);
        JSON_LEXER_TOKEN_ENUM_TYPE() const target_token_literal = JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL);

        // construct json value as boolean value
        struct JSON_VALUE_TYPE() json_value;
        {
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) tmp;
            TYPE_METHOD(JSON__string_type, construct_from_c_string_at)(&tmp, target_value_raw_string);
            TYPE_METHOD(JSON_VALUE_TYPE(), construct_move_from_string_at)(&json_value, &tmp);
            TYPE_METHOD(JSON__string_type, destroy_at)(&tmp);
        }

        // check correct json value construction
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == target_json_value_type);

        // serialize json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(&json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == TYPE_METHOD(JSON__string_type, size)(&value));
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            TYPE_METHOD(JSON__string_type, data)(&value)));

        // tokenize value
        struct CSTRING_VIEW_TYPE() target_view;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&target_view, TYPE_METHOD(JSON__string_type, data)(&serialized_json_value));

        struct JSON_LEXER_TYPE() lexer;
        JSON_LEXER_METHOD(construct_from_value_at)(&lexer, target_view);

        struct JSON_LEXER_TYPE() lexer_end = JSON_LEXER_METHOD(end)(&lexer);

        struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) token_or_error;

        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
        CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
        struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
        CHECK(ptoken->token_type == target_token_literal);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&ptoken->string),
            target_value_raw_string));
        RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);

        token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
        CHECK(!RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
        CHECK(JSON_LEXER_METHOD(are_equals)(&lexer, &lexer_end));
        RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);

        // cleanup
        JSON_LEXER_METHOD(destroy_at)(&lexer_end);
        JSON_LEXER_METHOD(destroy_at)(&lexer);
        TYPE_METHOD(CSTRING_VIEW_TYPE(), destroy_at)(&target_view);
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&serialized_json_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
        TYPE_METHOD(JSON__string_type, destroy_at)(&value);
    }
    TEST_BLOCK("check base json value serialization (from array)") {
        char const source_value[] = "[1, 2.03e-13, \"$asd#^dff1\", null, true]";
        struct CSTRING_VIEW_TYPE() source_view;
        // source_view construction
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&source_view, source_value);

        // tokenize value
        struct JSON_LEXER_TYPE() lexer; JSON_LEXER_METHOD(construct_from_value_at)(&lexer, source_view);
        struct JSON_LEXER_TYPE() lexer_end = JSON_LEXER_METHOD(end)(&lexer);
        struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) token_or_error;

        { // '[' // JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_BEGIN)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_BEGIN));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // '1' // JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL));
            CHECK(fabs(ptoken->number - 1) < EPSILON(double));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ',' // JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // '2.03e-13' // JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL));
            CHECK(fabs(ptoken->number - 2.03e-13) < EPSILON(double));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ',' // JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // "$asd#^dff1" // JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL));
            CHECK(!RAW_STRING_FUNCTION(char, compare)("$asd#^dff1", TYPE_METHOD(JSON__string_type, data)(&ptoken->string)));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ',' // JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // null // JSON_LEXER_TOKEN_ENUM_VALUE(NULL_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(NULL_LITERAL));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ',' // JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // true // JSON_LEXER_TOKEN_ENUM_VALUE(TRUE_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL));
            CHECK(ptoken->boolean == true);
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ']' // JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_END)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_END));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // end of sequence
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(!RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            CHECK(JSON_LEXER_METHOD(are_equals)(&lexer, &lexer_end));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }

        // cleanup
        JSON_LEXER_METHOD(destroy_at)(&lexer_end);
        JSON_LEXER_METHOD(destroy_at)(&lexer);
        CSTRING_VIEW_METHOD(destroy_at)(&source_view);
    }
    TEST_BLOCK("check base json value serialization (from object)") {
        char const source_value[] = "{\n\t\"integer_value\": 1,\n\t\"float_value\": 2.03e-13, \n\t\"string_value\": \"$asd#^dff1\",\n\t\"null_value\": null,\n\t\"boolean_value\": true\n}";
        struct CSTRING_VIEW_TYPE() source_view;
        // source_view construction
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&source_view, source_value);

        // tokenize value
        struct JSON_LEXER_TYPE() lexer; JSON_LEXER_METHOD(construct_from_value_at)(&lexer, source_view);
        struct JSON_LEXER_TYPE() lexer_end = JSON_LEXER_METHOD(end)(&lexer);
        struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE()) token_or_error;

        { // '{' // JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_BEGIN)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_BEGIN));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // "integer_value" // JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL));
            CHECK(!RAW_STRING_FUNCTION(char, compare)("integer_value", TYPE_METHOD(JSON__string_type, data)(&ptoken->string)));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ':' // JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // '1' // JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL));
            CHECK(fabs(ptoken->number - 1) < EPSILON(double));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ',' // JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // "float_value" // JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL));
            CHECK(!RAW_STRING_FUNCTION(char, compare)("float_value", TYPE_METHOD(JSON__string_type, data)(&ptoken->string)));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ':' // JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // '2.03e-13' // JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL));
            CHECK(fabs(ptoken->number - 2.03e-13) < EPSILON(double));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ',' // JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // "string_value" // JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL));
            CHECK(!RAW_STRING_FUNCTION(char, compare)("string_value", TYPE_METHOD(JSON__string_type, data)(&ptoken->string)));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ':' // JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // "$asd#^dff1" // JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL));
            CHECK(!RAW_STRING_FUNCTION(char, compare)("$asd#^dff1", TYPE_METHOD(JSON__string_type, data)(&ptoken->string)));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ',' // JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // "null_value" // JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL));
            CHECK(!RAW_STRING_FUNCTION(char, compare)("null_value", TYPE_METHOD(JSON__string_type, data)(&ptoken->string)));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ':' // JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // null // JSON_LEXER_TOKEN_ENUM_VALUE(NULL_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(NULL_LITERAL));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ',' // JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // "boolean_value" // JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL));
            CHECK(!RAW_STRING_FUNCTION(char, compare)("boolean_value", TYPE_METHOD(JSON__string_type, data)(&ptoken->string)));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // ':' // JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // true // JSON_LEXER_TOKEN_ENUM_VALUE(TRUE_LITERAL)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL));
            CHECK(ptoken->boolean == true);
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // '}' // JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_END)
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            struct JSON_LEXER_TOKEN_TYPE() const* const ptoken = RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), value)(&token_or_error);
            CHECK(ptoken->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_END));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }
        { // end of sequence
            token_or_error = JSON_LEXER_METHOD(get_next_token)(&lexer);
            CHECK(!RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), has_value)(&token_or_error));
            CHECK(JSON_LEXER_METHOD(are_equals)(&lexer, &lexer_end));
            RESULT_METHOD(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE(), destroy_at)(&token_or_error);
        }

        // cleanup
        JSON_LEXER_METHOD(destroy_at)(&lexer_end);
        JSON_LEXER_METHOD(destroy_at)(&lexer);
        CSTRING_VIEW_METHOD(destroy_at)(&source_view);
    }
}
