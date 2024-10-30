#include "convert.h"

#include <utils/string/raw_string/convert.h>
#include <utils/string/raw_string/length.h>

IMPLEMENT_TYPE_TESTS(raw_string_convert) {
    TEST_BLOCK("convert unicode character encoding literal to unicode character") {
        STATIC_ASSERT(sizeof(int) == sizeof(char32));
        char const source[] = {'\\', 'u', '0', '9', '3', '2'};
        char32 const target = 0x0932;
        struct OPTIONAL_TYPE(char32) value_opt = NAMESPACE_UTILS_STRING(CONVERT(unicode_character_buffer, unicode_character))(source, sizeof(source));
        CHECK(TYPE_METHOD(OPTIONAL_TYPE(char32), has_value)(&value_opt));
        CHECK(*TYPE_METHOD(OPTIONAL_TYPE(char32), value)(&value_opt) == target);
    }
    TEST_BLOCK("convert unicode character surrogate pair encoding literal to unicode character") {
        STATIC_ASSERT(sizeof(int) == sizeof(char32));
        // \uD834\uDD1E -> U+1D11E
        char const source[] = {'\\', 'u', 'D', '8', '3', '4', '\\', 'u', 'D', 'D', '1', 'E'};
        char32 const target = 0x1D11E;
        struct OPTIONAL_TYPE(char32) value_opt = NAMESPACE_UTILS_STRING(CONVERT(unicode_character_buffer, unicode_character))(source, sizeof(source));
        CHECK(TYPE_METHOD(OPTIONAL_TYPE(char32), has_value)(&value_opt));
        CHECK(*TYPE_METHOD(OPTIONAL_TYPE(char32), value)(&value_opt) == target);
    }
    TEST_BLOCK("[2] convert unicode character surrogate pair encoding literal to unicode character") {
        STATIC_ASSERT(sizeof(int) == sizeof(char32));
        // \uD800\uDE8F -> U+1028F
        char const source[] = {'\\', 'u', 'D', '8', '0', '0', '\\', 'u', 'D', 'C', '0', '0'};
        char32 const target = 0x1028F;
        struct OPTIONAL_TYPE(char32) value_opt = NAMESPACE_UTILS_STRING(CONVERT(unicode_character_buffer, unicode_character))(source, sizeof(source));
        CHECK(TYPE_METHOD(OPTIONAL_TYPE(char32), has_value)(&value_opt));
        CHECK(*TYPE_METHOD(OPTIONAL_TYPE(char32), value)(&value_opt) == target);
    }
}
