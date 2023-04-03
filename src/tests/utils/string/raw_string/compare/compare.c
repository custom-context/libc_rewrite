#include "compare.h"

#include <utils/string/raw_string/compare.h>

#include <containers/dynamic/string/string.h>

IMPLEMENT_TYPE_TESTS(raw_string_compare) {
    TEST_BLOCK("compare same c string") {
        char const* const raw_str = "stajgodjsguyr89gd97hvbfd";
        CHECK(!RAW_STRING_FUNCTION(char, compare)(raw_str, raw_str));
    }
    TEST_BLOCK("compare same w string") {
        wchar const* const raw_str = L"901231hjihjznvb9s74";
        CHECK(!RAW_STRING_FUNCTION(wchar, compare)(raw_str, raw_str));
    }
    TEST_BLOCK("compare same os string") {
        OS_CHAR_TYPE const* const raw_str = OS_STRING_LITERAL("dfjhgiudh89eyr78973y4riqui9q0-");
        CHECK(!RAW_STRING_FUNCTION(OS_CHAR_TYPE, compare)(raw_str, raw_str));
    }
    TEST_BLOCK("compare c strings with same values") {
        char const* const raw_str = "898475jsncvmmall2993uy5";
        CHECK(!RAW_STRING_FUNCTION(char, compare)(raw_str, "898475jsncvmmall2993uy5"));
    }
    TEST_BLOCK("compare same w strings with same values") {
        wchar const* const raw_str = L"t0-giskfopwjubgr78r5";
        CHECK(!RAW_STRING_FUNCTION(wchar, compare)(raw_str, L"t0-giskfopwjubgr78r5"));
    }
    TEST_BLOCK("compare same os strings with same values") {
        OS_CHAR_TYPE const* const raw_str = OS_STRING_LITERAL("we4mjnijklouer45h3.vc/b.q34sa\\asdagc@#$1237647");
        CHECK(!RAW_STRING_FUNCTION(OS_CHAR_TYPE, compare)(raw_str, OS_STRING_LITERAL("we4mjnijklouer45h3.vc/b.q34sa\\asdagc@#$1237647")));
    }
}
