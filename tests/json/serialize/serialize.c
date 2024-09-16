#include "serialize.h"

#include <json/serialize/serialize.h>
#include <json/value/value.h>
#include <primitives/limits.h>
#include <utils/format.h>

// struct STRING_TYPE() NAMESPACE_JSON(serialize)(struct JSON_VALUE_TYPE() const* const json);
// struct RESULT_TYPE(JSON_VALUE_TYPE(), JSON_DESERIALIZATION_ERROR_TYPE()) NAMESPACE_JSON(deserialize)(struct CSTRING_VIEW_TYPE() const string_view);


IMPLEMENT_TYPE_TESTS(json_serialize) {
    TEST_BLOCK("check base json value serialization (from null)") {
        // construct json value as null-value
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_at)(&json_value);

        // check correct json value construction
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(null));

        // serialize json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(&json_value);
        char const target_value_raw_string[] = "null";

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(target_value_raw_string) / sizeof(char) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            target_value_raw_string));

        // cleanup
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&serialized_json_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json value serialization (from boolean [true])") {
        char const target_value_raw_string[] = "true";
        bool const value = true;

        // construct json value as boolean value
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_boolean_at)(&json_value, value);

        // check correct json value construction
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(boolean));

        // serialize json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(&json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(target_value_raw_string) / sizeof(char) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            target_value_raw_string));

        // cleanup
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&serialized_json_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json value serialization (from number)") {
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) const value = -2312.533;
        char const target_value_raw_string[] = "-2312.533";

        // construct json value as boolean value
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_number_at)(&json_value, value);

        // check correct json value construction
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(number));

        // serialize json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(&json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(target_value_raw_string) / sizeof(char) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            target_value_raw_string));

        // cleanup
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&serialized_json_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json value serialization (from string)") {
        char const target_value_raw_string[] = "#!%cgfh^sUHYE(FW#@!ert$@$gdHSLFHCv@><CSA35";
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) target_value;
        TYPE_METHOD(JSON__string_type, construct_from_c_string_at)(&target_value, target_value_raw_string);

        // copy construct json value
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_move_from_value_at)(&json_value, &target_value);

        // check correct json value construction
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(string));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const)(&json_value);

        CHECK(value_ptr);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_value_raw_string, TYPE_METHOD(JSON__string_type, data)(value_ptr)));

        // serialize json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(&json_value);
        struct STRING_TYPE() formatted_target_value = NAMESPACE_UTILS(format)("\"%s\"", target_value_raw_string);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == STRING_METHOD(size)(&formatted_target_value));
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            STRING_METHOD(data)(&formatted_target_value)));

        // cleanup
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&formatted_target_value);
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&serialized_json_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
        TYPE_METHOD(JSON__string_type, destroy_at)(&target_value);
    }
}
