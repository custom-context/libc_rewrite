#include "result.h"

#include <utils/result.h>

#include <construct/numeric_helpers.h>

DEFINE_RESULT_TYPE(int, int);
DEFINE_RESULT_STATIC_METHODS(int, int)

IMPLEMENT_TYPE_TESTS(result) {
    TEST_BLOCK("result construction/destruction") {
        struct RESULT_TYPE(int, int) result;
        RESULT_METHOD(int, int, construct_at)(&result);
        CHECK(RESULT_METHOD(int, int, has_value)(&result) == 0);
        RESULT_METHOD(int, int, destroy_at)(&result);
    }
    TEST_BLOCK("result copy construct from value") {
        struct RESULT_TYPE(int, int) result;
        int value = 10;
        RESULT_METHOD(int, int, construct_copy_from_value_at)(&result, &value);
        CHECK(RESULT_METHOD(int, int, has_value)(&result));
        CHECK(*RESULT_METHOD(int, int, value)(&result) == value);
        RESULT_METHOD(int, int, destroy_at)(&result);
    }
}
