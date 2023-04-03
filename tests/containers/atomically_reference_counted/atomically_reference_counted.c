#include "atomically_reference_counted.h"

#include <containers/atomically_reference_counted/atomically_reference_counted.h>
#include <primitives/allocator.h>
DEFINE_ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(int);
DEFINE_DEFAULT_ALLOCATOR_TYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(int));
DEFINE_ATOMICALLY_REFERENCE_COUNTED_TYPE(int);

DECLARE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(int));
DECLARE_ATOMICALLY_REFERENCE_COUNTED_METHODS_WITH_MODIFIER(static, int);

DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(int))
DEFINE_ATOMICALLY_REFERENCE_COUNTED_METHODS_WITH_MODIFIER(static, int)

IMPLEMENT_TYPE_TESTS(atomically_reference_counted) {
    TEST_BLOCK("default constructor/destructor") {
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE(int) rc_int;
        ATOMICALLY_REFERENCE_COUNTED_METHOD(int, construct_at)(&rc_int);
        CHECK(!ATOMICALLY_REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int));
        CHECK(!ATOMICALLY_REFERENCE_COUNTED_METHOD(int, get)(&rc_int));
        ATOMICALLY_REFERENCE_COUNTED_METHOD(int, destroy_at)(&rc_int);
    }
    TEST_BLOCK("constructor_from_value/destructor") {
        struct DEFAULT_ALLOCATOR_TYPE(int) int_allocator;
        DEFAULT_ALLOCATOR_METHOD(int, construct_at)(&int_allocator);
        {
            int* value_pointer = DEFAULT_ALLOCATOR_METHOD(int, allocate)(&int_allocator, 1u);
            *value_pointer = 2327893;

            struct ATOMICALLY_REFERENCE_COUNTED_TYPE(int) rc_int;
            ATOMICALLY_REFERENCE_COUNTED_METHOD(int, construct_from_value_pointer_at)(&rc_int, value_pointer);
            CHECK(ATOMICALLY_REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(ATOMICALLY_REFERENCE_COUNTED_METHOD(int, get)(&rc_int) == value_pointer);

            ATOMICALLY_REFERENCE_COUNTED_METHOD(int, destroy_at)(&rc_int);
        }
        DEFAULT_ALLOCATOR_METHOD(int, destroy_at)(&int_allocator);
    }
    TEST_BLOCK("constructor_copy/destructor") {
        struct DEFAULT_ALLOCATOR_TYPE(int) int_allocator;
        DEFAULT_ALLOCATOR_METHOD(int, construct_at)(&int_allocator);
        {
            int* value_pointer = DEFAULT_ALLOCATOR_METHOD(int, allocate)(&int_allocator, 1u);
            *value_pointer = 348999;

            struct ATOMICALLY_REFERENCE_COUNTED_TYPE(int) rc_int;
            ATOMICALLY_REFERENCE_COUNTED_METHOD(int, construct_from_value_pointer_at)(&rc_int, value_pointer);
            CHECK(ATOMICALLY_REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(ATOMICALLY_REFERENCE_COUNTED_METHOD(int, get)(&rc_int) == value_pointer);

            {
                struct ATOMICALLY_REFERENCE_COUNTED_TYPE(int) rc_int2;
                ATOMICALLY_REFERENCE_COUNTED_METHOD(int, construct_copy_at)(&rc_int2, &rc_int);
                CHECK(ATOMICALLY_REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int) == 2u);
                CHECK(ATOMICALLY_REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int2) ==
                    ATOMICALLY_REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int));

                CHECK(ATOMICALLY_REFERENCE_COUNTED_METHOD(int, get)(&rc_int2) == value_pointer);
                CHECK(ATOMICALLY_REFERENCE_COUNTED_METHOD(int, get)(&rc_int2) == ATOMICALLY_REFERENCE_COUNTED_METHOD(int, get)(&rc_int));

                ATOMICALLY_REFERENCE_COUNTED_METHOD(int, destroy_at)(&rc_int2);
            }

            CHECK(ATOMICALLY_REFERENCE_COUNTED_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(ATOMICALLY_REFERENCE_COUNTED_METHOD(int, get)(&rc_int) == value_pointer);

            ATOMICALLY_REFERENCE_COUNTED_METHOD(int, destroy_at)(&rc_int);
        }
        DEFAULT_ALLOCATOR_METHOD(int, destroy_at)(&int_allocator);
    }
}
