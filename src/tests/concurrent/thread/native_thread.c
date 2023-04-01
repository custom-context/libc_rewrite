#include "native_thread.h"

#include <concurrent/thread/native.h>
#include <primitives/atomic.h>

static int int_increment(void* argument);

static int int_atomic_increment(void* argument);

IMPLEMENT_TYPE_TESTS(native_thread) {
    TEST_BLOCK("create & join single thread") {
        struct NATIVE_THREAD_TYPE() thread;

        int initial_value = 0;

        NAMESPACE_CONCURRENT_NATIVE_THREAD(create_thread)(&thread, int_increment, (void*)&initial_value);
        NAMESPACE_CONCURRENT_NATIVE_THREAD(thread_join)(thread, &initial_value);

        CHECK(initial_value == 1);
    }
    TEST_BLOCK("create & join many threads") {
        enum {
            ARRAY_SIZE = 500
        };
        struct NATIVE_THREAD_TYPE() arr_threads[ARRAY_SIZE];

        NATIVE_ATOMIC_TYPE(int32) initial_value = 0;
        for (usize i = 0; i < ARRAY_SIZE; ++i) {
            NAMESPACE_CONCURRENT_NATIVE_THREAD(create_thread)(&arr_threads[i], int_atomic_increment, (void*)&initial_value);
        }

        for (usize i = 0; i < ARRAY_SIZE; ++i) {
            NAMESPACE_CONCURRENT_NATIVE_THREAD(thread_join)(arr_threads[i], NULL);
        }

        CHECK(atomic_load_explicit(&initial_value, memory_order_relaxed) == ARRAY_SIZE);
    }
}

static int int_increment(void* argument) {
    int* const int_pointer = (int*)(argument);
    return ++*int_pointer;
}

static int int_atomic_increment(void* argument) {
    NATIVE_ATOMIC_TYPE(int32)* const atomic_int_pointer = (NATIVE_ATOMIC_TYPE(int32)*)(argument);
    int32 value = atomic_load_explicit(atomic_int_pointer, memory_order_relaxed);
    atomic_thread_fence(memory_order_acquire);
    atomic_store_explicit(atomic_int_pointer, value + 1, memory_order_relaxed);
    atomic_thread_fence(memory_order_release);
    return value + 1;
}
