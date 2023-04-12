#include "base64.h"

#include <encoding/base64/base64.h>
#include <utils/string/raw_string/compare.h>

IMPLEMENT_TYPE_TESTS(encoding_base64) {
    TEST_BLOCK("encode empty string") {
        char const value[] = "";
        char const target_value[] = "";
        struct STRING_TYPE() encoded_value = NAMESPACE_ENCODING_BASE64(encode)((uint8 const*)value, sizeof(value)-1);
        LOG_DEBUG(TYPE_METHOD(STRING_TYPE(), data)(&encoded_value));
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_value, TYPE_METHOD(STRING_TYPE(), data)(&encoded_value)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&encoded_value);
    }
    TEST_BLOCK("encode common test string for base64 encodingg") {
        char const value[] = "Many hands make light work.";
        char const target_value[] = "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu";
        struct STRING_TYPE() encoded_value = NAMESPACE_ENCODING_BASE64(encode)((uint8 const*)value, sizeof(value)-1);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_value, TYPE_METHOD(STRING_TYPE(), data)(&encoded_value)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&encoded_value);
    }
    TEST_BLOCK("encode string with padding") {
        char const value[] = "M";
        char const target_value[] = "TQ==";
        struct STRING_TYPE() encoded_value = NAMESPACE_ENCODING_BASE64(encode)((uint8 const*)value, sizeof(value)-1);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_value, TYPE_METHOD(STRING_TYPE(), data)(&encoded_value)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&encoded_value);
    }
    TEST_BLOCK("encode common test string & decode it back") {
        STATIC_ASSERT(sizeof(char) == sizeof(uint8));
        char const value[] = "Many hands make light work.";
        char const target_value[] = "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu";
        struct STRING_TYPE() encoded_value = NAMESPACE_ENCODING_BASE64(encode)((uint8 const*)value, sizeof(value)-1);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_value, TYPE_METHOD(STRING_TYPE(), data)(&encoded_value)));
        struct DYNAMIC_ARRAY_TYPE(uint8) decoded_value = NAMESPACE_ENCODING_BASE64(decode)(TYPE_METHOD(STRING_TYPE(), data)(&encoded_value), TYPE_METHOD(STRING_TYPE(), size)(&encoded_value));
        usize const decoded_value_size = TYPE_METHOD(DYNAMIC_ARRAY_TYPE(uint8), size)(&decoded_value);
        CHECK((sizeof(value) - 1) == decoded_value_size);
        
        for (usize i = 0u; i < decoded_value_size; ++i) {
            CHECK(*(uint8 const*)(value + i) == *TYPE_METHOD(DYNAMIC_ARRAY_TYPE(uint8), at)(&decoded_value, i));
        }
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&encoded_value);
    }
    TEST_BLOCK("encode string with padding & decode it back") {
        STATIC_ASSERT(sizeof(char) == sizeof(uint8));
        char const value[] = "M";
        char const target_value[] = "TQ==";
        struct STRING_TYPE() encoded_value = NAMESPACE_ENCODING_BASE64(encode)((uint8 const*)value, sizeof(value)-1);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_value, TYPE_METHOD(STRING_TYPE(), data)(&encoded_value)));
        struct DYNAMIC_ARRAY_TYPE(uint8) decoded_value = NAMESPACE_ENCODING_BASE64(decode)(TYPE_METHOD(STRING_TYPE(), data)(&encoded_value), TYPE_METHOD(STRING_TYPE(), size)(&encoded_value));
        usize const decoded_value_size = TYPE_METHOD(DYNAMIC_ARRAY_TYPE(uint8), size)(&decoded_value);
        CHECK((sizeof(value) - 1) == decoded_value_size);
        for (usize i = 0u; i < decoded_value_size; ++i) {
            CHECK(*(uint8 const*)(value + i) == *TYPE_METHOD(DYNAMIC_ARRAY_TYPE(uint8), at)(&decoded_value, i));
        }
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&encoded_value);
    }
}
