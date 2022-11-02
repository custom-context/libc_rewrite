#include "array.h"

#include <containers/array.h>

#define TEST_BUFFER_SIZE1 231
DEFINE_ARRAY(int, TEST_BUFFER_SIZE1);

#define TEST_BUFFER_SIZE2 348
DEFINE_ARRAY(int, TEST_BUFFER_SIZE2);

#define TEST_BUFFER_SIZE3 194
DEFINE_ARRAY(int, TEST_BUFFER_SIZE3);

typedef struct test__inc_on_construction__dec_on_destruction {
    int* encounter_pointer;
} test__inc_on_construction__dec_on_destruction;

void TYPE_METHOD(test__inc_on_construction__dec_on_destruction, construct_at)(test__inc_on_construction__dec_on_destruction* const this) {
    ++*(this->encounter_pointer);
}

void TYPE_METHOD(test__inc_on_construction__dec_on_destruction, construct_copy_at)(test__inc_on_construction__dec_on_destruction* const this, test__inc_on_construction__dec_on_destruction const* const from) {
    ++*(this->encounter_pointer);
}

void TYPE_METHOD(test__inc_on_construction__dec_on_destruction, destroy_at)(test__inc_on_construction__dec_on_destruction* const this) {
    --*(this->encounter_pointer);
}

#define TEST_BUFFER_SIZE4 275
DEFINE_ARRAY(test__inc_on_construction__dec_on_destruction, TEST_BUFFER_SIZE4);

IMPLEMENT_TYPE_TESTS(array) {
    TEST_BLOCK("size") {
        ARRAY_TYPE(int, TEST_BUFFER_SIZE1) arr_buffer;

        ASSERT(ARRAY_METHOD(int, TEST_BUFFER_SIZE1, size)(&arr_buffer) == TEST_BUFFER_SIZE1);
    }

    TEST_BLOCK("mut_at") {
        ARRAY_TYPE(int, TEST_BUFFER_SIZE2) arr_buffer;

        ASSERT(ARRAY_METHOD(int, TEST_BUFFER_SIZE2, size)(&arr_buffer) == TEST_BUFFER_SIZE2);

        for (size_t i = 0u; i < ARRAY_METHOD(int, TEST_BUFFER_SIZE2, size)(&arr_buffer); ++i) {
            *ARRAY_METHOD(int, TEST_BUFFER_SIZE2, mut_at)(&arr_buffer, i) = i * i;
        }
        
        for (size_t i = 0u; i < ARRAY_METHOD(int, TEST_BUFFER_SIZE2, size)(&arr_buffer); ++i) {
            ASSERT(*ARRAY_METHOD(int, TEST_BUFFER_SIZE2, mut_at)(&arr_buffer, i) == i * i);
        }
    }

    TEST_BLOCK("at") {
        ARRAY_TYPE(int, TEST_BUFFER_SIZE3) arr_buffer;

        ASSERT(ARRAY_METHOD(int, TEST_BUFFER_SIZE3, size)(&arr_buffer) == TEST_BUFFER_SIZE3);

        for (size_t i = 0u; i < ARRAY_METHOD(int, TEST_BUFFER_SIZE3, size)(&arr_buffer); ++i) {
            *ARRAY_METHOD(int, TEST_BUFFER_SIZE3, mut_at)(&arr_buffer, i) = i * i;
        }
        
        for (size_t i = 0u; i < ARRAY_METHOD(int, TEST_BUFFER_SIZE3, size)(&arr_buffer); ++i) {
            ASSERT(*ARRAY_METHOD(int, TEST_BUFFER_SIZE3, at)(&arr_buffer, i) == i * i);
        }
    }

    TEST_BLOCK("construct_at") {
        ARRAY_TYPE(test__inc_on_construction__dec_on_destruction, TEST_BUFFER_SIZE4) arr_buffer;
        int encounter = 0;

        for (size_t i = 0u; i < ARRAY_METHOD(test__inc_on_construction__dec_on_destruction, TEST_BUFFER_SIZE4, size)(&arr_buffer); ++i) {
            ARRAY_METHOD(test__inc_on_construction__dec_on_destruction, TEST_BUFFER_SIZE4, mut_at)(&arr_buffer, i)->encounter_pointer = &encounter;
        }
        
        ARRAY_METHOD(test__inc_on_construction__dec_on_destruction, TEST_BUFFER_SIZE4, construct_at)(&arr_buffer);

        ASSERT(encounter == ARRAY_METHOD(test__inc_on_construction__dec_on_destruction, TEST_BUFFER_SIZE4, size)(&arr_buffer));
    }
    TEST_BLOCK("destroy_at") {
        ARRAY_TYPE(test__inc_on_construction__dec_on_destruction, TEST_BUFFER_SIZE4) arr_buffer;
        int encounter = 0;

        for (size_t i = 0u; i < ARRAY_METHOD(test__inc_on_construction__dec_on_destruction, TEST_BUFFER_SIZE4, size)(&arr_buffer); ++i) {
            ARRAY_METHOD(test__inc_on_construction__dec_on_destruction, TEST_BUFFER_SIZE4, mut_at)(&arr_buffer, i)->encounter_pointer = &encounter;
        }
        
        ARRAY_METHOD(test__inc_on_construction__dec_on_destruction, TEST_BUFFER_SIZE4, destroy_at)(&arr_buffer);
        ASSERT(encounter == -TEST_BUFFER_SIZE4);
    }
}

#undef TEST_BUFFER_SIZE1
#undef TEST_BUFFER_SIZE2
#undef TEST_BUFFER_SIZE3
#undef TEST_BUFFER_SIZE4