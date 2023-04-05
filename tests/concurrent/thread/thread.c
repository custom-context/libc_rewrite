#include "thread.h"

#include "int_increment_runnable.h"
#include "int_atomically_increment_runnable.h"
#include <concurrent/thread/thread.h>
#include <primitives/atomic.h>

IMPLEMENT_TYPE_TESTS(thread) {
    TEST_BLOCK("construct/destroy empty thread 'object'") {
        struct THREAD_TYPE() thread;
        THREAD_METHOD(construct_at)(&thread);
        THREAD_METHOD(destroy_at)(&thread);
    }
    TEST_BLOCK("construct/destroy non-empty thread 'object'") {
        struct THREAD_TYPE() thread;
        int_increment_runnable_type int_increment_runnable;
        TYPE_METHOD(int_increment_runnable_type, construct_at)(&int_increment_runnable);
        CHECK(int_increment_runnable.value == 0);
        THREAD_METHOD(construct_from_runnable_at)(&thread,
            ISTATIC_CAST(int_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))(
                &int_increment_runnable))
        );
        THREAD_METHOD(join)(&thread);
        CHECK(int_increment_runnable.value == 1);
        THREAD_METHOD(destroy_at)(&thread);
    }
    TEST_BLOCK("construct/destroy many non-empty thread 'object's") {
        enum {
            ARRAY_SIZE = 500
        };
        struct THREAD_TYPE() arr_threads[ARRAY_SIZE];

        int_atomically_increment_runnable_type int_atomically_increment_runnable;
        TYPE_METHOD(int_atomically_increment_runnable_type, construct_at)(&int_atomically_increment_runnable);
        CHECK(ATOMIC_METHOD(int32, load_explicit)(&int_atomically_increment_runnable.value,
            ATOMIC_MEMORY_ORDER_ENUM_VALUE(relaxed)) == 0);

        for (usize i = 0; i < ARRAY_SIZE; ++i) {
            THREAD_METHOD(construct_from_runnable_at)(&arr_threads[i],
            ISTATIC_CAST(int_atomically_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))(
                &int_atomically_increment_runnable))
            );
        }

        for (usize i = 0; i < ARRAY_SIZE; ++i) {
            THREAD_METHOD(join)(&arr_threads[i]);
        }

        CHECK(ATOMIC_METHOD(int32, load_explicit)(&int_atomically_increment_runnable.value,
            ATOMIC_MEMORY_ORDER_ENUM_VALUE(relaxed)) == ARRAY_SIZE);

        for (usize i = 0; i < ARRAY_SIZE; ++i) {
            THREAD_METHOD(destroy_at)(&arr_threads[i]);
        }
    }
}
