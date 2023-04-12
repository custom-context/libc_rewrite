#include "value.h"

#include <json/value/value.h>
#include <primitives/limits.h>

static struct JSON__string_type index_to_string_for_move_array_test(usize index);
static struct JSON__string_type index_to_string_for_copy_array_test(usize index);

static struct JSON__key_type index_to_object_key_for_move_object_test(usize index);
static struct JSON__key_type index_to_object_string_value_for_move_object_test(usize index);

IMPLEMENT_TYPE_TESTS(json_value) {
    TEST_BLOCK("check base json_value construction/destruction") {
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_at)(&json_value);
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(null));
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    // construct from type
    TEST_BLOCK("check base json_value construction from null type") {
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_type_at)(&json_value, JSON_ENUM_VALUE(null));
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(null));
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json_value construction from number type") {
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_type_at)(&json_value, JSON_ENUM_VALUE(number));
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(number));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(*value_ptr < EPSILON(double));
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json_value construction from string type") {
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_type_at)(&json_value, JSON_ENUM_VALUE(string));
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(string));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(!TYPE_METHOD(JSON__string_type, size)(value_ptr));
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json_value construction from array type") {
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_type_at)(&json_value, JSON_ENUM_VALUE(array));
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(array));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(!TYPE_METHOD(JSON__array_type, size)(value_ptr));
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json_value construction from object type") {
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_type_at)(&json_value, JSON_ENUM_VALUE(object));
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(object));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(!TYPE_METHOD(JSON__object_type, size)(value_ptr));
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    // construct from value
    TEST_BLOCK("check base json_value construction from number value") {
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) target_value = 2.52317;
        struct JSON_VALUE_TYPE() json_value;
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, target_value);
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(number));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(fabs(*value_ptr - target_value) < EPSILON(double));
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json_value construction from mutable string value") {
        char const* const target_value_raw_string = "uf9ph217fbhzxbdv8oq2";
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) target_value;
        TYPE_METHOD(JSON__string_type, construct_from_c_string_at)(&target_value, target_value_raw_string);
        struct JSON_VALUE_TYPE() json_value;
        // here move construction happens, 'couse target value passed as non-const
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, &target_value);
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(string));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_value_raw_string, TYPE_METHOD(JSON__string_type, data)(value_ptr)));
        TYPE_METHOD(JSON__string_type, destroy_at)(&target_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json_value construction from non-mutable string value") {
        char const* const target_value_raw_string = "jiadsjf89y39y9712p7g";
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) target_value;
        TYPE_METHOD(JSON__string_type, construct_from_c_string_at)(&target_value, target_value_raw_string);
        struct JSON_VALUE_TYPE() json_value;
        // here copy construction happens, 'couse target value passed as const
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, (STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const*)&target_value);
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(string));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_value_raw_string, TYPE_METHOD(JSON__string_type, data)(value_ptr)));
        TYPE_METHOD(JSON__string_type, destroy_at)(&target_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    /// array type
    TEST_BLOCK("check base json_value construction from mutable array value") {
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) target_value;
        TYPE_METHOD(JSON__array_type, construct_at)(&target_value);
        enum { count_elements = 34 };
        TYPE_METHOD(JSON__array_type, reserve)(&target_value, count_elements);
        struct JSON_VALUE_TYPE() json_value;
        for (usize i = 0; i < count_elements; ++i) {
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) str_value = index_to_string_for_move_array_test(i);
            TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, &str_value);
            TYPE_METHOD(JSON__array_type, push_back_by_moving)(&target_value, &json_value);
            TYPE_METHOD(JSON__string_type, destroy_at)(&str_value);
            TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
        }

        // here move construction happens, 'couse target value passed as non-const
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, &target_value);
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(array));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(TYPE_METHOD(JSON__array_type, size)(value_ptr) == count_elements);
        // compare each element
        for (usize i = 0; i < count_elements; ++i) {
            struct JSON_VALUE_TYPE() const* const json_array_element = TYPE_METHOD(JSON__array_type, at)(value_ptr, i);
            CHECK(json_array_element);
            CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(json_array_element) == JSON_ENUM_VALUE(string));

            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* json_array_element_value_ptr =
                TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const)(json_array_element);
            CHECK(json_array_element_value_ptr);

            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) target_str_value = index_to_string_for_move_array_test(i);

            CHECK(!RAW_STRING_FUNCTION(char, compare)(TYPE_METHOD(JSON__string_type, data)(&target_str_value), TYPE_METHOD(JSON__string_type, data)(json_array_element_value_ptr)));

            TYPE_METHOD(JSON__string_type, destroy_at)(&target_str_value);
        }
        
        TYPE_METHOD(JSON__array_type, destroy_at)(&target_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json_value construction from const array value") {
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) target_value;
        TYPE_METHOD(JSON__array_type, construct_at)(&target_value);
        enum { count_elements = 71 };
        TYPE_METHOD(JSON__array_type, reserve)(&target_value, count_elements);
        struct JSON_VALUE_TYPE() json_value;
        for (usize i = 0; i < count_elements; ++i) {
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) str_value = index_to_string_for_copy_array_test(i);
            TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, &str_value);
            TYPE_METHOD(JSON__array_type, push_back_by_moving)(&target_value, &json_value);
            TYPE_METHOD(JSON__string_type, destroy_at)(&str_value);
            TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
        }

        // here copy construction happens, 'couse target value passed as const
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, (STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const*)&target_value);
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(array));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(TYPE_METHOD(JSON__array_type, size)(value_ptr) == count_elements);
        // compare each element
        for (usize i = 0; i < count_elements; ++i) {
            struct JSON_VALUE_TYPE() const* const json_array_element = TYPE_METHOD(JSON__array_type, at)(value_ptr, i);
            CHECK(json_array_element);
            CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(json_array_element) == JSON_ENUM_VALUE(string));

            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* json_array_element_value_ptr =
                TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const)(json_array_element);
            CHECK(json_array_element_value_ptr);

            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) target_str_value = index_to_string_for_copy_array_test(i);

            CHECK(!RAW_STRING_FUNCTION(char, compare)(TYPE_METHOD(JSON__string_type, data)(&target_str_value), TYPE_METHOD(JSON__string_type, data)(json_array_element_value_ptr)));

            TYPE_METHOD(JSON__string_type, destroy_at)(&target_str_value);
        }
        
        TYPE_METHOD(JSON__array_type, destroy_at)(&target_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    /// object type
    TEST_BLOCK("check base json_value construction from mutable object value") {
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) target_value;
        TYPE_METHOD(JSON__object_type, construct_at)(&target_value);
        enum { count_elements = 394 };
        usize count_of_insertions = 0u;
        struct JSON_VALUE_TYPE() json_value;
        for (usize i = 0; i < count_elements; ++i) {
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) key_str = index_to_object_key_for_move_object_test(i);
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) value_str = index_to_object_string_value_for_move_object_test(i);
            TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, &value_str);
            struct PAIR_TYPE(JSON__object__iterator_type, bool) const result =
                TYPE_METHOD(JSON__object_type, insert_or_assign_with_key_move_value_move)(&target_value, &key_str, &json_value);
            count_of_insertions += result.second;

            TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
            TYPE_METHOD(JSON__string_type, destroy_at)(&value_str);
            TYPE_METHOD(JSON__string_type, destroy_at)(&key_str);
        }
        CHECK(TYPE_METHOD(JSON__object_type, size)(&target_value) == count_of_insertions);

        // here move construction happens, 'couse target value passed as non-const
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, &target_value);
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(object));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(TYPE_METHOD(JSON__object_type, size)(value_ptr) == count_of_insertions);
        // compare each element
        for (usize i = 0; i < count_elements; ++i) {
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) key_str = index_to_object_key_for_move_object_test(i);

            struct JSON_VALUE_TYPE() const* const json_object_element = TYPE_METHOD(JSON__object_type, at)(value_ptr, &key_str);
            CHECK(json_object_element);
            CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(json_object_element) == JSON_ENUM_VALUE(string));

            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* json_object_element_value_ptr =
                TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const)(json_object_element);
            CHECK(json_object_element_value_ptr);

            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) target_str_value = index_to_object_string_value_for_move_object_test(i);

            CHECK(!RAW_STRING_FUNCTION(char, compare)(TYPE_METHOD(JSON__string_type, data)(&target_str_value), TYPE_METHOD(JSON__string_type, data)(json_object_element_value_ptr)));

            TYPE_METHOD(JSON__string_type, destroy_at)(&target_str_value);
            TYPE_METHOD(JSON__string_type, destroy_at)(&key_str);
        }
        
        TYPE_METHOD(JSON__object_type, destroy_at)(&target_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
    TEST_BLOCK("check base json_value construction from const object value") {
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) target_value;
        TYPE_METHOD(JSON__object_type, construct_at)(&target_value);
        enum { count_elements = 394 };
        usize count_of_insertions = 0u;
        struct JSON_VALUE_TYPE() json_value;
        for (usize i = 0; i < count_elements; ++i) {
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) key_str = index_to_object_key_for_move_object_test(i);
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) value_str = index_to_object_string_value_for_move_object_test(i);
            TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, &value_str);
            struct PAIR_TYPE(JSON__object__iterator_type, bool) const result =
                TYPE_METHOD(JSON__object_type, insert_or_assign_with_key_move_value_move)(&target_value, &key_str, &json_value);
            count_of_insertions += result.second;

            TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
            TYPE_METHOD(JSON__string_type, destroy_at)(&value_str);
            TYPE_METHOD(JSON__string_type, destroy_at)(&key_str);
        }
        CHECK(TYPE_METHOD(JSON__object_type, size)(&target_value) == count_of_insertions);

        // here copy construction happens, 'couse target value passed as const
        TYPE_METHOD(JSON_VALUE_TYPE(), construct_from_value_at)(&json_value, (STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const*)&target_value);
        CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(&json_value) == JSON_ENUM_VALUE(object));
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const* value_ptr =
            TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const)(&json_value);
        CHECK(value_ptr);
        CHECK(TYPE_METHOD(JSON__object_type, size)(value_ptr) == count_of_insertions);
        // compare each element
        for (usize i = 0; i < count_elements; ++i) {
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) key_str = index_to_object_key_for_move_object_test(i);

            struct JSON_VALUE_TYPE() const* const json_object_element = TYPE_METHOD(JSON__object_type, at)(value_ptr, &key_str);
            CHECK(json_object_element);
            CHECK(TYPE_METHOD(JSON_VALUE_TYPE(), type)(json_object_element) == JSON_ENUM_VALUE(string));

            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* json_object_element_value_ptr =
                TYPE_METHOD(JSON_VALUE_TYPE(), as)(STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const)(json_object_element);
            CHECK(json_object_element_value_ptr);

            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) target_str_value = index_to_object_string_value_for_move_object_test(i);

            CHECK(!RAW_STRING_FUNCTION(char, compare)(TYPE_METHOD(JSON__string_type, data)(&target_str_value), TYPE_METHOD(JSON__string_type, data)(json_object_element_value_ptr)));

            TYPE_METHOD(JSON__string_type, destroy_at)(&target_str_value);
            TYPE_METHOD(JSON__string_type, destroy_at)(&key_str);
        }
        
        TYPE_METHOD(JSON__object_type, destroy_at)(&target_value);
        TYPE_METHOD(JSON_VALUE_TYPE(), destroy_at)(&json_value);
    }
}

static struct JSON__string_type index_to_string_for_move_array_test(usize index) {
    ullong value = (index << (index % 3)) + (index % (1 << 3));
    return NAMESPACE_UTILS_STRING(CONVERT(ullong, JSON__string_type)(&value));
}
static struct JSON__string_type index_to_string_for_copy_array_test(usize index) {
    ullong value = (index << (index % 4)) + (index % (1 << 4));
    return NAMESPACE_UTILS_STRING(CONVERT(ullong, JSON__string_type)(&value));
}

static struct JSON__key_type index_to_object_key_for_move_object_test(usize index) {
    ullong value = (index << (index % 5)) + (index % (1 << 7));
    value ^= index;
    return NAMESPACE_UTILS_STRING(CONVERT(ullong, JSON__key_type)(&value));
}
static struct JSON__key_type index_to_object_string_value_for_move_object_test(usize index) {
    return index_to_object_key_for_move_object_test(index);
}
