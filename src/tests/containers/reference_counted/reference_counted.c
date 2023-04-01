#include "reference_counted.h"

#include <containers/reference_counted/reference_counted.h>
#include <primitives/allocator.h>
DEFINE_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(int);
DEFINE_DEFAULT_ALLOCATOR_TYPE(REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(int));
DEFINE_REFERENCE_COUNTED_TYPE(int);

DECLARE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(int));
DECLARE_REFERENCE_COUNTED_METHODS_WITH_MODIFIER(static, int);

DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(int))
DEFINE_REFERENCE_COUNTED_METHODS_WITH_MODIFIER(static, int)

IMPLEMENT_TYPE_TESTS(reference_counted) {
    TEST_BLOCK("default constructor/destructor") {
        struct REFERENCE_COUNTED_TYPE(int) rc_int;
        REFERENCE_COUNTED_METHOD(int, construct_at)(&rc_int);
        CHECK(!REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int));
        CHECK(!REFERENCE_COUNTED_METHOD(int, get)(&rc_int));
        REFERENCE_COUNTED_METHOD(int, destroy_at)(&rc_int);
    }
    TEST_BLOCK("constructor_from_value/destructor") {
        struct DEFAULT_ALLOCATOR_TYPE(int) int_allocator;
        DEFAULT_ALLOCATOR_METHOD(int, construct_at)(&int_allocator);
        {
            int* value_pointer = DEFAULT_ALLOCATOR_METHOD(int, allocate)(&int_allocator, 1u);
            *value_pointer = 2327893;

            struct REFERENCE_COUNTED_TYPE(int) rc_int;
            REFERENCE_COUNTED_METHOD(int, construct_from_value_pointer_at)(&rc_int, value_pointer);
            CHECK(REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(REFERENCE_COUNTED_METHOD(int, get)(&rc_int) == value_pointer);

            REFERENCE_COUNTED_METHOD(int, destroy_at)(&rc_int);
        }
        DEFAULT_ALLOCATOR_METHOD(int, destroy_at)(&int_allocator);
    }
    TEST_BLOCK("constructor_copy/destructor") {
        struct DEFAULT_ALLOCATOR_TYPE(int) int_allocator;
        DEFAULT_ALLOCATOR_METHOD(int, construct_at)(&int_allocator);
        {
            int* value_pointer = DEFAULT_ALLOCATOR_METHOD(int, allocate)(&int_allocator, 1u);
            *value_pointer = 348999;

            struct REFERENCE_COUNTED_TYPE(int) rc_int;
            REFERENCE_COUNTED_METHOD(int, construct_from_value_pointer_at)(&rc_int, value_pointer);
            CHECK(REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(REFERENCE_COUNTED_METHOD(int, get)(&rc_int) == value_pointer);

            {
                struct REFERENCE_COUNTED_TYPE(int) rc_int2;
                REFERENCE_COUNTED_METHOD(int, construct_copy_at)(&rc_int2, &rc_int);
                CHECK(REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int) == 2u);
                CHECK(REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int2) ==
                    REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int));

                CHECK(REFERENCE_COUNTED_METHOD(int, get)(&rc_int2) == value_pointer);
                CHECK(REFERENCE_COUNTED_METHOD(int, get)(&rc_int2) == REFERENCE_COUNTED_METHOD(int, get)(&rc_int));

                REFERENCE_COUNTED_METHOD(int, destroy_at)(&rc_int2);
            }

            CHECK(REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(REFERENCE_COUNTED_METHOD(int, get)(&rc_int) == value_pointer);

            REFERENCE_COUNTED_METHOD(int, destroy_at)(&rc_int);
        }
        DEFAULT_ALLOCATOR_METHOD(int, destroy_at)(&int_allocator);
    }
}
