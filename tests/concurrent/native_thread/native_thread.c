#include "native_thread.h"

#include <concurrent/thread/native/native.h>
#include <primitives/atomic.h>

static int int_increment(void* argument);

static int int_atomic_increment(void* argument);

IMPLEMENT_TYPE_TESTS(native_thread) {
    TEST_BLOCK("create & join single thread") {
        struct NATIVE_THREAD_TYPE() thread;

        int initial_value = 0;

        NATIVE_THREAD_METHOD(thread_create)(&thread, int_increment, (void*)&initial_value);
        NATIVE_THREAD_METHOD(thread_join)(&thread, &initial_value);

        CHECK(initial_value == 1);
    }
    TEST_BLOCK("create & join many threads") {
        enum {
            ARRAY_SIZE = 500
        };
        struct NATIVE_THREAD_TYPE() arr_threads[ARRAY_SIZE];

        ATOMIC_TYPE(int32) atomic_value;
        ATOMIC_METHOD(int32, construct_at)(&atomic_value);

        for (usize i = 0; i < ARRAY_SIZE; ++i) {
            NATIVE_THREAD_METHOD(thread_create)(&arr_threads[i], int_atomic_increment, (void*)&atomic_value);
        }

        for (usize i = 0; i < ARRAY_SIZE; ++i) {
            NATIVE_THREAD_METHOD(thread_join)(&arr_threads[i], NULL);
        }

        CHECK(ATOMIC_METHOD(int32, load_explicit)(&atomic_value, ATOMIC_MEMORY_ORDER_ENUM_VALUE(RELAXED)) == ARRAY_SIZE);

        ATOMIC_METHOD(int32, destroy_at)(&atomic_value);
    }
}

static int int_increment(void* argument) {
    int* const int_pointer = (int*)(argument);
    return ++*int_pointer;
}

static int int_atomic_increment(void* argument) {
    ATOMIC_TYPE(int32)* const patomic_int = (ATOMIC_TYPE(int32)*)(argument);
    int32 const value = ATOMIC_METHOD(int32, load_explicit)(patomic_int, ATOMIC_MEMORY_ORDER_ENUM_VALUE(RELAXED));
    NAMESPACE_CONCURRENT_ATOMIC(thread_fence)(ATOMIC_MEMORY_ORDER_ENUM_VALUE(ACQUIRE));
    ATOMIC_METHOD(int32, store_explicit)(patomic_int, value + 1, ATOMIC_MEMORY_ORDER_ENUM_VALUE(RELAXED));
    NAMESPACE_CONCURRENT_ATOMIC(thread_fence)(ATOMIC_MEMORY_ORDER_ENUM_VALUE(RELEASE));
    return 0;
}
