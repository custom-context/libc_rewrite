#include "string.h"

#include <containers/dynamic/string/string.h>
#include <utils/string/helpers.h>

IMPLEMENT_TYPE_TESTS(string) {
    TEST_BLOCK("`size` & `capacity` methods on empty string") {
        STRING_TYPE() str;
        STRING_METHOD(construct_at)(&str);

        CHECK(STRING_METHOD(size)(&str) == 0);
        CHECK(STRING_METHOD(capacity)(&str) > 0);
        CHECK(str.is_stack_allocated);
    }

    TEST_BLOCK("`push_back` & `at` methods without allocations") {
        STRING_TYPE() str;
        STRING_METHOD(construct_at)(&str);

        CHECK(STRING_METHOD(size)(&str) == 0);
        CHECK(STRING_METHOD(capacity)(&str) > 0);

        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) i = 0u; i < STRING_METHOD(capacity)(&str); ++i) {
            STRUCT_SUBTYPE(STRING_TYPE(), char_type) value;
            if (i < 10) {
                value = (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) + '0';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i - 10 < 26) {
                value = (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - 10 + 'a';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i - 36 < 26) {
                value =  (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - 36 + 'A';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
        }
        CHECK(STRING_METHOD(capacity)(&str) == STRING_METHOD(size)(&str));
        
        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) i = 0u; i < STRING_METHOD(size)(&str); ++i) {
            if (i < 10) {
                CHECK(*STRING_METHOD(at)(&str, i) == (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) + '0');
                continue;
            }
            if (i - 10 < 26) {
                CHECK(*STRING_METHOD(at)(&str, i) == (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - 10 + 'a');
                continue;
            }
            if (i - 36 < 26) {
                CHECK(*STRING_METHOD(at)(&str, i) == (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - 36 + 'A');
                continue;
            }
        }

        CHECK(str.is_stack_allocated);
    }

    TEST_BLOCK("`push_back` & `at` methods with reallocations") {
        STRING_TYPE() str;
        STRING_METHOD(construct_at)(&str);

        CHECK(STRING_METHOD(size)(&str) == 0);
        CHECK(STRING_METHOD(capacity)(&str) > 0);

        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) i = 0u; i < 10 + 26 + 26; ++i) {
            STRUCT_SUBTYPE(STRING_TYPE(), char_type) value;
            if (i < 10) {
                value = (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) + '0';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i < 10 + 26) {
                value = (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - 10 + 'a';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i < 10 + 26 + 26) {
                value = (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - 36 + 'A';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
        }
        CHECK(STRING_METHOD(size)(&str) == 10 + 26 + 26);
        CHECK(STRING_METHOD(capacity)(&str) >= STRING_METHOD(size)(&str));
        CHECK(!str.is_stack_allocated);
        
        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) i = 0u; i < STRING_METHOD(size)(&str); ++i) {
            if (i < 10) {
                CHECK(*STRING_METHOD(at)(&str, i) == (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) + '0');
                continue;
            }
            if (i < 10 + 26) {
                CHECK(*STRING_METHOD(at)(&str, i) == (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - 10 + 'a');
                continue;
            }
            if (i < 10 + 26 + 26) {
                CHECK(*STRING_METHOD(at)(&str, i) == (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - (10 + 26) + 'A');
                continue;
            }
        }
        STRING_METHOD(destroy_at)(&str);
    }

    TEST_BLOCK("`pop_back`") {
        STRING_TYPE() str;
        STRING_METHOD(construct_at)(&str);

        CHECK(STRING_METHOD(size)(&str) == 0);
        CHECK(STRING_METHOD(capacity)(&str) > 0);

        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) i = 0u; i < 10 + 26 + 26; ++i) {
            STRUCT_SUBTYPE(STRING_TYPE(), char_type) value;
            if (i < 10) {
                value = (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) + '0';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i < 10 + 26) {
                value = (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - 10 + 'a';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i < 10 + 26 + 26) {
                value = (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - 36 + 'A';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
        }
        CHECK(STRING_METHOD(size)(&str) == 10 + 26 + 26);
        CHECK(STRING_METHOD(capacity)(&str) >= STRING_METHOD(size)(&str));
        CHECK(!str.is_stack_allocated);
        
        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) i = 0u; i < STRING_METHOD(size)(&str); ++i) {
            if (i < 10) {
                CHECK(*STRING_METHOD(at)(&str, i) == (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) + '0');
                continue;
            }
            if (i < 10 + 26) {
                CHECK(*STRING_METHOD(at)(&str, i) == (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - 10 + 'a');
                continue;
            }
            if (i < 10 + 26 + 26) {
                CHECK(*STRING_METHOD(at)(&str, i) == (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(i) - (10 + 26) + 'A');
                continue;
            }
        }

        STRING_TYPE() str2;
        STRING_METHOD(construct_copy_at)(&str2, &str);

        {
            STRING_TYPE() temporary;
            for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) i = 0u; i < STRING_METHOD(size)(&str); ++i) {
                STRING_METHOD(pop_back)(&str2);
                STRING_METHOD(construct_from_buffer_at)(&temporary, STRING_METHOD(size)(&str2), STRING_METHOD(data)(&str));

                CHECK(STRING_METHOD(size)(&str2) == STRING_METHOD(size)(&str) - 1 - i);
                CHECK(!STRING_FUNCTION(STRING_TYPE(), compare)(&str2, &temporary));

                STRING_METHOD(destroy_at)(&temporary);
            }
        }

        STRING_METHOD(destroy_at)(&str2);
        STRING_METHOD(destroy_at)(&str);
    }

    TEST_BLOCK("`construct_from_c_string` method without reallocations") {
        STRUCT_SUBTYPE(STRING_TYPE(), char_type) const* const c_string = "str w. len < 16";
        STRUCT_SUBTYPE(STRING_TYPE(), size_type) const c_string_length = RAW_STRING_FUNCTION(char, length)(c_string);

        STRING_TYPE() str;
        STRING_METHOD(construct_from_c_string_at)(&str, c_string);

        CHECK(STRING_METHOD(size)(&str) == c_string_length);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_length);
        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) index = 0u; index < c_string_length; ++index) {
            CHECK(*TYPE_METHOD(STRING_TYPE(), at)(&str, index) == c_string[index]);
        }
        CHECK(str.is_stack_allocated);

        STRING_METHOD(destroy_at)(&str);
    }

    STRUCT_SUBTYPE(STRING_TYPE(), char_type)
        c_string_with_sup[sizeof(STRUCT_SUBTYPE(STRING_TYPE(), stack_allocated_data)) / sizeof(char) + 1u];
    STRUCT_SUBTYPE(STRING_TYPE(), size_type) const
        c_string_with_sup_length = sizeof(c_string_with_sup) / sizeof(STRUCT_SUBTYPE(STRING_TYPE(), char_type)) - 1u;
    {
        STRUCT_SUBTYPE(STRING_TYPE(), char_type) const numeric_shift = '9' - '0';
        STRUCT_SUBTYPE(STRING_TYPE(), char_type) const small_latin_letters_shift = 'z' - 'a';
        STRUCT_SUBTYPE(STRING_TYPE(), char_type) const large_latin_letters_shift = 'Z' - 'A';
        STRUCT_SUBTYPE(STRING_TYPE(), size_type) index_shift = 0u;
        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) index = 0u; index < c_string_with_sup_length; ++index) {
            if ((index - index_shift) <= numeric_shift) {
                c_string_with_sup[index] = numeric_shift + '0';
                continue;
            }
            if ((index - index_shift - numeric_shift) <= small_latin_letters_shift) {
                c_string_with_sup[index] = numeric_shift + '0';
                continue;
            }
            if ((index - index_shift - numeric_shift - small_latin_letters_shift) <= large_latin_letters_shift) {
                c_string_with_sup[index] = numeric_shift + '0';
                continue;
            }
            index_shift += numeric_shift + small_latin_letters_shift + large_latin_letters_shift;
        }
        c_string_with_sup[c_string_with_sup_length] = '\0';
    }

    TEST_BLOCK("`construct_from_c_string` method with reallocations") {
        STRING_TYPE() str;
        STRING_METHOD(construct_from_c_string_at)(&str, c_string_with_sup);

        CHECK(STRING_METHOD(size)(&str) == c_string_with_sup_length);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_with_sup_length);

        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) index = 0u; index < c_string_with_sup_length; ++index) {
            CHECK(*TYPE_METHOD(STRING_TYPE(), at)(&str, index) == c_string_with_sup[index]);
        }
        CHECK(!str.is_stack_allocated);

        STRING_METHOD(destroy_at)(&str);
    }

    TEST_BLOCK("`shrink_to_fit` method without reallocations") {
        STRUCT_SUBTYPE(STRING_TYPE(), char_type) const* const c_string = "str w. len < 16";
        STRUCT_SUBTYPE(STRING_TYPE(), size_type) const c_string_length = RAW_STRING_FUNCTION(char, length)(c_string);

        STRING_TYPE() str;
        STRING_METHOD(construct_from_c_string_at)(&str, c_string);

        CHECK(STRING_METHOD(size)(&str) == c_string_length);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_length);
        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) index = 0u; index < c_string_length; ++index) {
            CHECK(*TYPE_METHOD(STRING_TYPE(), at)(&str, index) == c_string[index]);
        }
        CHECK(str.is_stack_allocated);

        STRING_METHOD(pop_back)(&str);
        STRING_METHOD(shrink_to_fit)(&str);

        CHECK(STRING_METHOD(size)(&str) == c_string_length - 1);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_length - 1);
        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) index = 0u; index < c_string_length - 1; ++index) {
            CHECK(*TYPE_METHOD(STRING_TYPE(), at)(&str, index) == c_string[index]);
        }
        CHECK(str.is_stack_allocated);
    }

    TEST_BLOCK("`shrink_to_fit` method with deallocation") {
        STRING_TYPE() str;
        STRING_METHOD(construct_from_c_string_at)(&str, c_string_with_sup);

        CHECK(STRING_METHOD(size)(&str) == c_string_with_sup_length);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_with_sup_length);

        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) index = 0u; index < c_string_with_sup_length; ++index) {
            CHECK(*TYPE_METHOD(STRING_TYPE(), at)(&str, index) == c_string_with_sup[index]);
        }
        CHECK(!str.is_stack_allocated);

        STRING_METHOD(pop_back)(&str);
        STRING_METHOD(shrink_to_fit)(&str);

        CHECK(STRING_METHOD(size)(&str) == c_string_with_sup_length - 1);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_with_sup_length - 1);
        for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) index = 0u; index < c_string_with_sup_length - 1; ++index) {
            CHECK(*TYPE_METHOD(STRING_TYPE(), at)(&str, index) == c_string_with_sup[index]);
        }
        CHECK(str.is_stack_allocated);

        STRING_METHOD(destroy_at)(&str);
    }
}
