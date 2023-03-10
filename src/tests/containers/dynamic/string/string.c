#include "string.h"

#include <containers/dynamic/string/string.h>
#include <utils/string/helpers.h>

#include <utils/string/comparators_impl.h>

IMPLEMENT_TYPE_TESTS(string) {
    TEST_BLOCK("`size` & `capacity` methods on empty string") {
        STRING_TYPE() str;
        STRING_METHOD(construct_at)(&str);

        CHECK(STRING_METHOD(size)(&str) == 0);
        CHECK(STRING_METHOD(capacity)(&str) > 0);
        CHECK(str.is_stack_allocated_);
    }

    TEST_BLOCK("`push_back` & `at` methods without allocations") {
        STRING_TYPE() str;
        STRING_METHOD(construct_at)(&str);

        CHECK(STRING_METHOD(size)(&str) == 0);
        CHECK(STRING_METHOD(capacity)(&str) > 0);

        for (size_t i = 0u; i < STRING_METHOD(capacity)(&str); ++i) {
            char value;
            if (i < 10) {
                value = (char)(i) + '0';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i - 10 < 26) {
                value = (char)(i) - 10 + 'a';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i - 36 < 26) {
                value =  (char)(i) - 36 + 'A';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
        }
        CHECK(STRING_METHOD(capacity)(&str) == STRING_METHOD(size)(&str));
        
        for (size_t i = 0u; i < STRING_METHOD(size)(&str); ++i) {
            if (i < 10) {
                CHECK(*STRING_METHOD(at)(&str, (uint)(i)) == (char)(i) + '0');
                continue;
            }
            if (i - 10 < 26) {
                CHECK(*STRING_METHOD(at)(&str, (uint)(i)) == (char)(i) - 10 + 'a');
                continue;
            }
            if (i - 36 < 26) {
                CHECK(*STRING_METHOD(at)(&str, (uint)(i)) == (char)(i) - 36 + 'A');
                continue;
            }
        }

        CHECK(str.is_stack_allocated_);
    }

    TEST_BLOCK("`push_back` & `at` methods with reallocations") {
        STRING_TYPE() str;
        STRING_METHOD(construct_at)(&str);

        CHECK(STRING_METHOD(size)(&str) == 0);
        CHECK(STRING_METHOD(capacity)(&str) > 0);

        for (size_t i = 0u; i < 10 + 26 + 26; ++i) {
            char value;
            if (i < 10) {
                value = (char)(i) + '0';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i < 10 + 26) {
                value = (char)(i) - 10 + 'a';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i < 10 + 26 + 26) {
                value = (char)(i) - 36 + 'A';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
        }
        CHECK(STRING_METHOD(size)(&str) == 10 + 26 + 26);
        CHECK(STRING_METHOD(capacity)(&str) >= STRING_METHOD(size)(&str));
        CHECK(!str.is_stack_allocated_);
        
        for (size_t i = 0u; i < STRING_METHOD(size)(&str); ++i) {
            if (i < 10) {
                CHECK(*STRING_METHOD(at)(&str, (uint)(i)) == (char)(i) + '0');
                continue;
            }
            if (i < 10 + 26) {
                CHECK(*STRING_METHOD(at)(&str, (uint)(i)) == (char)(i) - 10 + 'a');
                continue;
            }
            if (i < 10 + 26 + 26) {
                CHECK(*STRING_METHOD(at)(&str, (uint)(i)) == (char)(i) - (10 + 26) + 'A');
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

        for (size_t i = 0u; i < 10 + 26 + 26; ++i) {
            char value;
            if (i < 10) {
                value = (char)(i) + '0';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i < 10 + 26) {
                value = (char)(i) - 10 + 'a';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
            if (i < 10 + 26 + 26) {
                value = (char)(i) - 36 + 'A';
                STRING_METHOD(push_back)(&str, &value);
                continue;
            }
        }
        CHECK(STRING_METHOD(size)(&str) == 10 + 26 + 26);
        CHECK(STRING_METHOD(capacity)(&str) >= STRING_METHOD(size)(&str));
        CHECK(!str.is_stack_allocated_);
        
        for (size_t i = 0u; i < STRING_METHOD(size)(&str); ++i) {
            if (i < 10) {
                CHECK(*STRING_METHOD(at)(&str, (uint)(i)) == (char)(i) + '0');
                continue;
            }
            if (i < 10 + 26) {
                CHECK(*STRING_METHOD(at)(&str, (uint)(i)) == (char)(i) - 10 + 'a');
                continue;
            }
            if (i < 10 + 26 + 26) {
                CHECK(*STRING_METHOD(at)(&str, (uint)(i)) == (char)(i) - (10 + 26) + 'A');
                continue;
            }
        }

        STRING_TYPE() str2;
        STRING_METHOD(construct_copy_at)(&str2, &str);

        for (size_t i = 0u; i < STRING_METHOD(size)(&str); ++i) {
            STRING_METHOD(pop_back)(&str2);
            CHECK(STRING_METHOD(size)(&str2) == STRING_METHOD(size)(&str) - 1 - i);
            CHECK(!NAMESPACE_UTILS_STRING(COMPARE_FUNCTION(STRING_TYPE(), buffer))(&str2, STRING_METHOD(size)(&str2), STRING_METHOD(data)(&str)));
        }

        STRING_METHOD(destroy_at)(&str2);
        STRING_METHOD(destroy_at)(&str);
    }

    TEST_BLOCK("`construct_from_c_string` method without reallocations") {
        char const* const c_string = "str w. len < 16";
        size_t const c_string_length = RAW_STRING_FUNCTION(char, length)(c_string);

        STRING_TYPE() str;
        STRING_METHOD(construct_from_c_string_at)(&str, c_string);

        CHECK(STRING_METHOD(size)(&str) == c_string_length);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_length);
        CHECK(!NAMESPACE_UTILS_STRING(COMPARE_FUNCTION(STRING_TYPE(), buffer))(&str, (uint)(c_string_length), c_string));
        CHECK(str.is_stack_allocated_);

        STRING_METHOD(destroy_at)(&str);
    }

    TEST_BLOCK("`construct_from_c_string` method with reallocations") {
        char const* const c_string = "str w. more than 16";
        size_t const c_string_length = RAW_STRING_FUNCTION(char, length)(c_string);

        STRING_TYPE() str;
        STRING_METHOD(construct_from_c_string_at)(&str, c_string);

        CHECK(STRING_METHOD(size)(&str) == c_string_length);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_length);

        CHECK(!NAMESPACE_UTILS_STRING(COMPARE_FUNCTION(STRING_TYPE(), buffer))(&str, (uint)(c_string_length), c_string));
        CHECK(!str.is_stack_allocated_);

        STRING_METHOD(destroy_at)(&str);
    }

    TEST_BLOCK("`shrink_to_fit` method without reallocations") {
        char const* const c_string = "str w. len < 16";
        size_t const c_string_length = RAW_STRING_FUNCTION(char, length)(c_string);

        STRING_TYPE() str;
        STRING_METHOD(construct_from_c_string_at)(&str, c_string);

        CHECK(STRING_METHOD(size)(&str) == c_string_length);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_length);
        CHECK(!NAMESPACE_UTILS_STRING(COMPARE_FUNCTION(STRING_TYPE(), buffer))(&str, (uint)(c_string_length), c_string));
        CHECK(str.is_stack_allocated_);

        STRING_METHOD(pop_back)(&str);
        STRING_METHOD(shrink_to_fit)(&str);

        CHECK(STRING_METHOD(size)(&str) == c_string_length - 1);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_length - 1);
        CHECK(!NAMESPACE_UTILS_STRING(COMPARE_FUNCTION(STRING_TYPE(), buffer))(&str, (uint)(c_string_length) - 1, c_string));
        CHECK(str.is_stack_allocated_);
    }

    TEST_BLOCK("`shrink_to_fit` method with deallocation") {
        char const* const c_string = "str w. len gt 16";
        size_t const c_string_length = RAW_STRING_FUNCTION(char, length)(c_string);

        STRING_TYPE() str;
        STRING_METHOD(construct_from_c_string_at)(&str, c_string);

        CHECK(STRING_METHOD(size)(&str) == c_string_length);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_length);

        CHECK(!NAMESPACE_UTILS_STRING(COMPARE_FUNCTION(STRING_TYPE(), buffer))(&str, (uint)(c_string_length), c_string));
        CHECK(!str.is_stack_allocated_);

        STRING_METHOD(pop_back)(&str);
        STRING_METHOD(shrink_to_fit)(&str);

        CHECK(STRING_METHOD(size)(&str) == c_string_length - 1);
        CHECK(STRING_METHOD(capacity)(&str) >= c_string_length - 1);
        CHECK(!NAMESPACE_UTILS_STRING(COMPARE_FUNCTION(STRING_TYPE(), buffer))(&str, (uint)(c_string_length) - 1, c_string));
        CHECK(str.is_stack_allocated_);

        STRING_METHOD(destroy_at)(&str);
    }
}
