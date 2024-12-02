#include "reference_counted.h"

#include <containers/reference_counted/reference_counted.h>
#include <primitives/allocator.h>

DEFINE_RC_TYPE(int);
DECLARE_RC_METHODS_WITH_MODIFIER(static, int);
DEFINE_RC_METHODS_WITH_MODIFIER(static, int)

static int* TYPE_METHOD(int, construct_valued_at)(int* const this, int const value) {
    ASSERT(this);
    *this = value;
    return this;
}

DECLARE_MAKE_RC_WITH_MODIFIER(static, int, construct_valued_at, int const, value);
DEFINE_MAKE_RC_WITH_MODIFIER(static, int, construct_valued_at, int const, value)

IMPLEMENT_TYPE_TESTS(reference_counted) {
    TEST_BLOCK("default constructor/destructor") {
        struct RC_TYPE(int) rc_int;
        RC_METHOD(int, construct_at)(&rc_int);
        CHECK(!RC_METHOD(int, count_owners)(&rc_int));
        CHECK(!RC_METHOD(int, get)(&rc_int));
        RC_METHOD(int, destroy_at)(&rc_int);
    }
    TEST_BLOCK("constructor_from_value/destructor") {
        struct DEFAULT_ALLOCATOR_TYPE(int) int_allocator;
        DEFAULT_ALLOCATOR_METHOD(int, construct_at)(&int_allocator);
        {
            int* value_pointer = DEFAULT_ALLOCATOR_METHOD(int, allocate)(&int_allocator, 1u);
            *value_pointer = 2327893;

            struct RC_TYPE(int) rc_int;
            RC_METHOD(int, construct_from_value_pointer_at)(&rc_int, value_pointer);
            CHECK(RC_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(RC_METHOD(int, get)(&rc_int) == value_pointer);

            RC_METHOD(int, destroy_at)(&rc_int);
        }
        DEFAULT_ALLOCATOR_METHOD(int, destroy_at)(&int_allocator);
    }
    TEST_BLOCK("constructor_copy/destructor") {
        struct DEFAULT_ALLOCATOR_TYPE(int) int_allocator;
        DEFAULT_ALLOCATOR_METHOD(int, construct_at)(&int_allocator);
        {
            int* value_pointer = DEFAULT_ALLOCATOR_METHOD(int, allocate)(&int_allocator, 1u);
            *value_pointer = 348999;

            struct RC_TYPE(int) rc_int;
            RC_METHOD(int, construct_from_value_pointer_at)(&rc_int, value_pointer);
            CHECK(RC_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(RC_METHOD(int, get)(&rc_int) == value_pointer);

            {
                struct RC_TYPE(int) rc_int2;
                RC_METHOD(int, construct_copy_at)(&rc_int2, &rc_int);
                CHECK(RC_METHOD(int, count_owners)(&rc_int) == 2u);
                CHECK(RC_METHOD(int, count_owners)(&rc_int2) ==
                    RC_METHOD(int, count_owners)(&rc_int));

                CHECK(RC_METHOD(int, get)(&rc_int2) == value_pointer);
                CHECK(RC_METHOD(int, get)(&rc_int2) == RC_METHOD(int, get)(&rc_int));

                RC_METHOD(int, destroy_at)(&rc_int2);
            }

            CHECK(RC_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(RC_METHOD(int, get)(&rc_int) == value_pointer);

            RC_METHOD(int, destroy_at)(&rc_int);
        }
        DEFAULT_ALLOCATOR_METHOD(int, destroy_at)(&int_allocator);
    }
    TEST_BLOCK("make_rc(construct_valued_at) & destroy") {
        int const value = 91357832;
        struct RC_TYPE(int) rc_int;
        MAKE_RC(int, construct_valued_at)(&rc_int, value);
        CHECK(RC_METHOD(int, count_owners)(&rc_int) == 1u);
        CHECK(RC_METHOD(int, get)(&rc_int));
        CHECK(*RC_METHOD(int, get)(&rc_int) == value);
        RC_METHOD(int, destroy_at)(&rc_int);
    }
    TEST_BLOCK("make_rc(construct_valued_at), copy & destroy") {
        {
            int const value = -527163823;
            struct RC_TYPE(int) rc_int;
            MAKE_RC(int, construct_valued_at)(&rc_int, value);
            CHECK(RC_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(RC_METHOD(int, get)(&rc_int));
            CHECK(*RC_METHOD(int, get)(&rc_int) == value);

            {
                struct RC_TYPE(int) rc_int2;
                RC_METHOD(int, construct_copy_at)(&rc_int2, &rc_int);
                CHECK(RC_METHOD(int, count_owners)(&rc_int) == 2u);
                CHECK(RC_METHOD(int, count_owners)(&rc_int2) ==
                    RC_METHOD(int, count_owners)(&rc_int));

                CHECK(RC_METHOD(int, get)(&rc_int2));
                CHECK(*RC_METHOD(int, get)(&rc_int2) == value);
                CHECK(RC_METHOD(int, get)(&rc_int2) == RC_METHOD(int, get)(&rc_int));

                RC_METHOD(int, destroy_at)(&rc_int2);
            }

            CHECK(RC_METHOD(int, count_owners)(&rc_int) == 1u);
            CHECK(RC_METHOD(int, get)(&rc_int));
            CHECK(*RC_METHOD(int, get)(&rc_int) == value);

            RC_METHOD(int, destroy_at)(&rc_int);
        }
    }
}
