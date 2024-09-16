#include "deserialize.h"

#include <json/serialize/serialize.h>
#include <json/value/value.h>
#include <primitives/limits.h>
#include <utils/format.h>

// struct STRING_TYPE() NAMESPACE_JSON(serialize)(struct JSON_VALUE_TYPE() const* const json);
// struct RESULT_TYPE(JSON_VALUE_TYPE(), JSON_DESERIALIZATION_ERROR_TYPE()) NAMESPACE_JSON(deserialize)(struct CSTRING_VIEW_TYPE() const string_view);


IMPLEMENT_TYPE_TESTS(json_deserialize) {
    #define DeserializationResultType RESULT_TYPE(JSON_VALUE_TYPE(), JSON_DESERIALIZATION_ERROR_TYPE())
    #define DeserializationResultMethod(METHOD) RESULT_METHOD(JSON_VALUE_TYPE(), JSON_DESERIALIZATION_ERROR_TYPE(), METHOD)

    TEST_BLOCK("check base json value deserialization (from empty object)") {
        char const c_string_value[] = "{}";

        // deserialize json_value from c_string_value
        struct CSTRING_VIEW_TYPE() string_view_value;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&string_view_value, c_string_value);

        struct DeserializationResultType deserialized_json_value_result =
            NAMESPACE_JSON(deserialize)(string_view_value);

        CHECK(DeserializationResultMethod(has_value)(&deserialized_json_value_result));

        struct JSON_VALUE_TYPE()* const pdeserialized_json_value =
            DeserializationResultMethod(value)(&deserialized_json_value_result);

        // serialize deserialized json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(pdeserialized_json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(c_string_value) / sizeof(*c_string_value) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            c_string_value));

        // cleanup
        STRING_METHOD(destroy_at)(&serialized_json_value);
        DeserializationResultMethod(destroy_at)(&deserialized_json_value_result);
        CSTRING_VIEW_METHOD(destroy_at)(&string_view_value);
    }
    TEST_BLOCK("check base json value deserialization (from empty array)") {
        char const c_string_value[] = "[]";

        // deserialize json_value from c_string_value
        struct CSTRING_VIEW_TYPE() string_view_value;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&string_view_value, c_string_value);

        struct DeserializationResultType deserialized_json_value_result =
            NAMESPACE_JSON(deserialize)(string_view_value);

        CHECK(DeserializationResultMethod(has_value)(&deserialized_json_value_result));

        struct JSON_VALUE_TYPE()* const pdeserialized_json_value =
            DeserializationResultMethod(value)(&deserialized_json_value_result);

        // serialize deserialized json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(pdeserialized_json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(c_string_value) / sizeof(*c_string_value) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            c_string_value));

        // cleanup
        STRING_METHOD(destroy_at)(&serialized_json_value);
        DeserializationResultMethod(destroy_at)(&deserialized_json_value_result);
        CSTRING_VIEW_METHOD(destroy_at)(&string_view_value);
    }
    TEST_BLOCK("check base json value deserialization (from non-empty array)") {
        char const c_string_value[] = "[1,2,null,true,123.56]";

        // deserialize json_value from c_string_value
        struct CSTRING_VIEW_TYPE() string_view_value;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&string_view_value, c_string_value);

        struct DeserializationResultType deserialized_json_value_result =
            NAMESPACE_JSON(deserialize)(string_view_value);

        CHECK(DeserializationResultMethod(has_value)(&deserialized_json_value_result));

        struct JSON_VALUE_TYPE()* const pdeserialized_json_value =
            DeserializationResultMethod(value)(&deserialized_json_value_result);

        // serialize deserialized json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(pdeserialized_json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(c_string_value) / sizeof(*c_string_value) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            c_string_value));

        // cleanup
        STRING_METHOD(destroy_at)(&serialized_json_value);
        DeserializationResultMethod(destroy_at)(&deserialized_json_value_result);
        CSTRING_VIEW_METHOD(destroy_at)(&string_view_value);
    }
    TEST_BLOCK("check base json value deserialization (from non-empty object)") {
        // WARNING: values must be sorted by key due object container type (binary tree)
        char const c_string_value[] = "{\"boolean_literal\":true,\"null_literal\":null,\"number_literal\":1283.5324,\"string_literal\":\"somestring\u5F61\"}";

        // deserialize json_value from c_string_value
        struct CSTRING_VIEW_TYPE() string_view_value;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&string_view_value, c_string_value);

        struct DeserializationResultType deserialized_json_value_result =
            NAMESPACE_JSON(deserialize)(string_view_value);

        CHECK(DeserializationResultMethod(has_value)(&deserialized_json_value_result));

        struct JSON_VALUE_TYPE()* const pdeserialized_json_value =
            DeserializationResultMethod(value)(&deserialized_json_value_result);

        // serialize deserialized json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(pdeserialized_json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(c_string_value) / sizeof(*c_string_value) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            c_string_value));

        // cleanup
        STRING_METHOD(destroy_at)(&serialized_json_value);
        DeserializationResultMethod(destroy_at)(&deserialized_json_value_result);
        CSTRING_VIEW_METHOD(destroy_at)(&string_view_value);
    }
    TEST_BLOCK("check base json value deserialization (from array with sub-objects & sub-arrays)") {
        // WARNING: values must be sorted by key due object container type (binary tree)
        char const c_string_value[] =
            "[{\"0bool\":true,\"1another_literal\":null,\"2number_literal\":1283.5324},null,\"$%Sdt923#%^91-)(hfd\",{},[\"sda\rsb\",false,{\"5ter\tminal\":\"sdagd#@%@\",\"6as d  -  48t\":124.355}]]";

        // deserialize json_value from c_string_value
        struct CSTRING_VIEW_TYPE() string_view_value;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&string_view_value, c_string_value);

        struct DeserializationResultType deserialized_json_value_result =
            NAMESPACE_JSON(deserialize)(string_view_value);

        CHECK(DeserializationResultMethod(has_value)(&deserialized_json_value_result));
        if (!DeserializationResultMethod(has_value)(&deserialized_json_value_result)) {
            struct JSON_DESERIALIZATION_ERROR_TYPE()* const perror = DeserializationResultMethod(error)(&deserialized_json_value_result);
            struct CSTRING_VIEW_TYPE() message = JSON_DESERIALIZATION_ERROR_METHOD(message)(perror);
            LOG_DEBUG_FORMAT("%s\n", message.buffer);
            CSTRING_VIEW_METHOD(destroy_at)(&message);
        }

        struct JSON_VALUE_TYPE()* const pdeserialized_json_value =
            DeserializationResultMethod(value)(&deserialized_json_value_result);

        // serialize deserialized json value
        struct STRING_TYPE() serialized_json_value = NAMESPACE_JSON(serialize)(pdeserialized_json_value);

        CHECK(STRING_METHOD(size)(&serialized_json_value) == sizeof(c_string_value) / sizeof(*c_string_value) - 1u);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(
            TYPE_METHOD(JSON__string_type, data)(&serialized_json_value),
            c_string_value));

        // cleanup
        STRING_METHOD(destroy_at)(&serialized_json_value);
        DeserializationResultMethod(destroy_at)(&deserialized_json_value_result);
        CSTRING_VIEW_METHOD(destroy_at)(&string_view_value);
    }
}
