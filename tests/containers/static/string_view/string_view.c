#include "string_view.h"

#include <containers/static/string_view/string_view.h>
#include <utils/string/helpers.h>

#include <containers/dynamic/array/array.h>

DECLARE_DYNAMIC_ARRAY_TYPE(char);
DECLARE_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(char);
IMPLEMENT_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(char)

IMPLEMENT_TYPE_TESTS(string_view) {
    TEST_BLOCK("`size` method on empty string_view") {
        CSTRING_VIEW_TYPE() view;
        CSTRING_VIEW_METHOD(construct_at)(&view);

        CHECK(CSTRING_VIEW_METHOD(size)(&view) == 0);
        CHECK(CSTRING_VIEW_METHOD(data)(&view) == NULL);

        CSTRING_VIEW_METHOD(destroy_at)(&view);
    }

    TEST_BLOCK("`construct_from_raw_string_at` method") {
        STRUCT_SUBTYPE(CSTRING_VIEW_TYPE(), char_type) const* const test_raw_string = "test string 293joiwtg1268"; 

        CSTRING_VIEW_TYPE() view;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&view, test_raw_string);

        CHECK(CSTRING_VIEW_METHOD(size)(&view) == RAW_STRING_FUNCTION(char, length)(test_raw_string));
        CHECK(CSTRING_VIEW_METHOD(data)(&view) == test_raw_string);

        CSTRING_VIEW_METHOD(destroy_at)(&view);
    }

    TEST_BLOCK("`at` method") {
        STRUCT_SUBTYPE(CSTRING_VIEW_TYPE(), char_type) const* const test_raw_string = "5utjgwo3p28121!@#$^T5ua80sdf"; 

        CSTRING_VIEW_TYPE() view;
        CSTRING_VIEW_METHOD(construct_from_raw_string_at)(&view, test_raw_string);

        CHECK(CSTRING_VIEW_METHOD(size)(&view) == RAW_STRING_FUNCTION(char, length)(test_raw_string));
        CHECK(CSTRING_VIEW_METHOD(data)(&view) == test_raw_string);

        STRUCT_SUBTYPE(CSTRING_VIEW_TYPE(), size_type) i;
        STRUCT_SUBTYPE(CSTRING_VIEW_TYPE(), char_type) ch;
        for (i = 0u; i < CSTRING_VIEW_METHOD(size)(&view) && ((ch = *CSTRING_VIEW_METHOD(at)(&view, i)) || true); ++i) {
            CHECK(test_raw_string[i] == ch);
        }

        CSTRING_VIEW_METHOD(destroy_at)(&view);
    }

    TEST_BLOCK("`construct_from_buffer_at` method") {
        STRUCT_SUBTYPE(CSTRING_VIEW_TYPE(), char_type) const* const test_string = "j@$%YSDfgdry0523AS@)^*@Fbdf9w3*^";
        DYNAMIC_ARRAY_TYPE(char) dynamic_array;
        // copy `test_string`'s content before '\0' to `dynamic_array`
        DYNAMIC_ARRAY_METHOD(char, construct_by_copying_from_buffer_at)(&dynamic_array, test_string, RAW_STRING_FUNCTION(char, length)(test_string));

        CSTRING_VIEW_TYPE() view;
        // copy `dynamic_array` pointer (to it's data) to `view` 
        CSTRING_VIEW_METHOD(construct_from_buffer_at)(&view, DYNAMIC_ARRAY_METHOD(char, data)(&dynamic_array), DYNAMIC_ARRAY_METHOD(char, size)(&dynamic_array));

        CHECK(CSTRING_VIEW_METHOD(size)(&view) == DYNAMIC_ARRAY_METHOD(char, size)(&dynamic_array));
        CHECK(CSTRING_VIEW_METHOD(data)(&view) != test_string);

        for (STRUCT_SUBTYPE(CSTRING_VIEW_TYPE(), size_type) index = 0u; index < CSTRING_VIEW_METHOD(size)(&view); ++index) {
            CHECK(*CSTRING_VIEW_METHOD(at)(&view, index) == *DYNAMIC_ARRAY_METHOD(char, at)(&dynamic_array, index));
        }

        CSTRING_VIEW_METHOD(destroy_at)(&view);
        DYNAMIC_ARRAY_METHOD(char, destroy_at)(&dynamic_array);
    }
}
