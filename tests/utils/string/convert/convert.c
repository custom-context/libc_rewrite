#include "convert.h"

#include <utils/string/convert.h>
#include <utils/string/raw_string/compare.h>
#include <containers/dynamic/string/string.h>

IMPLEMENT_TYPE_TESTS(string_convert) {
    TEST_BLOCK("convert int(0) to string") {
        char const* const target_raw_str = "0";
        int value = 0;
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(int, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
    TEST_BLOCK("convert negative int to string") {
        int value = -931283564;
        char const* const target_raw_str = "-931283564";
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(int, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
    TEST_BLOCK("convert positive int to string") {
        int value = 840351743;
        char const* const target_raw_str = "840351743";
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(int, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
    TEST_BLOCK("convert float(0) to string") {
        char const* const target_raw_str = "0";
        float value = .0f;
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(float, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
    TEST_BLOCK("convert negative float(.N) to string [preformatted value]") {
        float value = -.2354f;
        char const* const target_raw_str = "-0.2354";
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(float, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
    TEST_BLOCK("convert negative float to string [preformatted value]") {
        float value = -134936.25f;
        char const* const target_raw_str = "-134936.25";
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(float, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
    TEST_BLOCK("convert positive float to string [preformatted value]") {
        float value = 39945.390625f;
        char const* const target_raw_str = "39945.390625";
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(float, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
    TEST_BLOCK("convert double(0) to string") {
        char const* const target_raw_str = "0";
        double value = 0;
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(double, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
    TEST_BLOCK("convert negative double(.N) to string [preformatted value]") {
        double value = -.923767;
        char const* const target_raw_str = "-0.923767";
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(double, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
    TEST_BLOCK("convert negative double to string [preformatted value]") {
        double value = -49237838.2034;
        char const* const target_raw_str = "-49237838.2034";
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(double, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
    TEST_BLOCK("convert positive double to string [preformatted value]") {
        double value = 3942389.3213;
        char const* const target_raw_str = "3942389.3213";
        struct STRING_TYPE() value_str = NAMESPACE_UTILS_STRING(CONVERT(double, STRING_TYPE()))(&value);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(target_raw_str, TYPE_METHOD(STRING_TYPE(), data)(&value_str)));
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&value_str);
    }
}
