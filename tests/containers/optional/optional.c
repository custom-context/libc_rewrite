#include "optional.h"

#include "debug_context.h"

#include <containers/optional/optional.h>
#include <primitives/optional.h>

DEFINE_OPTIONAL_TYPE(debug_context);
DEFINE_OPTIONAL_STATIC_METHODS(debug_context)

IMPLEMENT_TYPE_TESTS(optional) {
    TEST_BLOCK("(using debug_context) optional construction/destruction") {
        GLOBAL_DEBUG_CONTEXT_FLUSH();

        struct OPTIONAL_TYPE(debug_context) optional;
        OPTIONAL_METHOD(debug_context, construct_at)(&optional);
        CHECK(OPTIONAL_METHOD(debug_context, has_value)(&optional) == 0);
        OPTIONAL_METHOD(debug_context, destroy_at)(&optional);

        CHECK(global_debug_context.count_of_construct_at == 0u);
        CHECK(global_debug_context.count_of_destroy_at == 0u);
    }

    TEST_BLOCK("(using debug_context) optional move construct from value") {
        GLOBAL_DEBUG_CONTEXT_FLUSH();

        struct OPTIONAL_TYPE(debug_context) optional;
        OPTIONAL_METHOD(debug_context, construct_move_from_value_at)(&optional, DEBUG_CONTEXT());
        CHECK(OPTIONAL_METHOD(debug_context, has_value)(&optional) == true);
        OPTIONAL_METHOD(debug_context, destroy_at)(&optional);

        GLOBAL_DEBUG_CONTEXT_CHECK_EQ();
    }

    TEST_BLOCK("(using debug_context) optional copy construct from value") {
        GLOBAL_DEBUG_CONTEXT_FLUSH();

        struct OPTIONAL_TYPE(debug_context) optional;
        OPTIONAL_METHOD(debug_context, construct_copy_from_value_at)(&optional, DEBUG_CONTEXT());
        CHECK(OPTIONAL_METHOD(debug_context, has_value)(&optional) == true);
        OPTIONAL_METHOD(debug_context, destroy_at)(&optional);

        GLOBAL_DEBUG_CONTEXT_CHECK_EQ();
    }

    TEST_BLOCK("(using debug_context) optional copy assign from value") {
        GLOBAL_DEBUG_CONTEXT_FLUSH();

        struct OPTIONAL_TYPE(debug_context) optional;
        OPTIONAL_METHOD(debug_context, construct_copy_from_value_at)(&optional, DEBUG_CONTEXT());
        CHECK(OPTIONAL_METHOD(debug_context, has_value)(&optional) == true);

        struct OPTIONAL_TYPE(debug_context) optional2;
        OPTIONAL_METHOD(debug_context, construct_copy_from_value_at)(&optional2, DEBUG_CONTEXT());
        CHECK(OPTIONAL_METHOD(debug_context, has_value)(&optional2) == true);

        OPTIONAL_METHOD(debug_context, assign_copy_at)(&optional, &optional2);

        OPTIONAL_METHOD(debug_context, destroy_at)(&optional2);
        OPTIONAL_METHOD(debug_context, destroy_at)(&optional);

        GLOBAL_DEBUG_CONTEXT_CHECK_EQ();
    }

    TEST_BLOCK("(using debug_context) optional move assign from value") {
        GLOBAL_DEBUG_CONTEXT_FLUSH();

        struct OPTIONAL_TYPE(debug_context) optional;
        OPTIONAL_METHOD(debug_context, construct_copy_from_value_at)(&optional, DEBUG_CONTEXT());
        CHECK(OPTIONAL_METHOD(debug_context, has_value)(&optional) == true);

        struct OPTIONAL_TYPE(debug_context) optional2;
        OPTIONAL_METHOD(debug_context, construct_copy_from_value_at)(&optional2, DEBUG_CONTEXT());
        CHECK(OPTIONAL_METHOD(debug_context, has_value)(&optional2) == true);

        OPTIONAL_METHOD(debug_context, assign_move_at)(&optional, &optional2);

        OPTIONAL_METHOD(debug_context, destroy_at)(&optional2);
        OPTIONAL_METHOD(debug_context, destroy_at)(&optional);

        GLOBAL_DEBUG_CONTEXT_CHECK_EQ();
    }

    TEST_BLOCK("(using debug_context) optional copy assign from value") {
        GLOBAL_DEBUG_CONTEXT_FLUSH();

        struct OPTIONAL_TYPE(debug_context) optional;
        OPTIONAL_METHOD(debug_context, construct_copy_from_value_at)(&optional, DEBUG_CONTEXT());
        CHECK(OPTIONAL_METHOD(debug_context, has_value)(&optional) == true);

        struct OPTIONAL_TYPE(debug_context) optional2;
        OPTIONAL_METHOD(debug_context, construct_copy_from_value_at)(&optional2, DEBUG_CONTEXT());
        CHECK(OPTIONAL_METHOD(debug_context, has_value)(&optional2) == true);

        OPTIONAL_METHOD(debug_context, assign_copy_at)(&optional, &optional2);
        CHECK(OPTIONAL_METHOD(debug_context, has_value)(&optional) == true);

        OPTIONAL_METHOD(debug_context, destroy_at)(&optional2);
        OPTIONAL_METHOD(debug_context, destroy_at)(&optional);

        GLOBAL_DEBUG_CONTEXT_CHECK_EQ();
    }

    TEST_BLOCK("optional copy construct from value") {
        GLOBAL_DEBUG_CONTEXT_FLUSH();

        struct OPTIONAL_TYPE(int8) optional;
        int8 const value = 10;
        OPTIONAL_METHOD(int8, construct_copy_from_value_at)(&optional, &value);
        CHECK(OPTIONAL_METHOD(int8, has_value)(&optional) == true);
        CHECK(*OPTIONAL_METHOD(int8, value)(&optional) == value);

        struct OPTIONAL_TYPE(int8) empty_optional;
        OPTIONAL_METHOD(int8, construct_at)(&empty_optional);
        OPTIONAL_METHOD(int8, assign_move_at)(&optional, &empty_optional);

        CHECK(OPTIONAL_METHOD(int8, has_value)(&optional) == 0);
        OPTIONAL_METHOD(int8, destroy_at)(&optional);
    }
}
