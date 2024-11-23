#define _POSIX_C_SOURCE __STDC_VERSION__

#include <concurrent/thread/native/native.h>

#include <memory/native/native.h>

#include <sched.h>
#include <errno.h>
#include <time.h>

static void* callback_wrapper(void* arg);
typedef void* wrapper_return_type;

typedef struct callback_payload {
    STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type) callback;
    void* arguments_pack;
} callback_payload;

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NATIVE_THREAD_METHOD(thread_create)(
        struct NATIVE_THREAD_TYPE()* const thread,
        STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type) callback,
        void* arg) {
    ASSERT(thread);
    ASSERT(callback);
    struct callback_payload* pcallback_payload = NAMESPACE_MEMORY_NATIVE(aligned_alloc)(ALIGNOF(struct callback_payload), SIZEOF(struct callback_payload));
    ASSERT(pcallback_payload);
    if (!pcallback_payload) {
        return errno;
    }
    pcallback_payload->callback = callback;
    pcallback_payload->arguments_pack = arg;

    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type) thread_state =
        pthread_create(&thread->native_handler, NULL, callback_wrapper, (void*)(pcallback_payload));

    if (thread_state) {
        NAMESPACE_MEMORY_NATIVE(aligned_free)(pcallback_payload);
    }

    return thread_state;
}


STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NATIVE_THREAD_METHOD(thread_join)(
        struct NATIVE_THREAD_TYPE()* const thread,
        STRUCT_SUBTYPE(STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type), result_type)* result) {
    ASSERT(thread);
    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type) thread_state;
    STATIC_ASSERT(SIZEOF(wrapper_return_type) >= SIZEOF(int));
    wrapper_return_type exit_code;
    thread_state = pthread_join(
        thread->native_handler,
        &exit_code // voidptr* presult (but here voidptr interpret as int)
    );
    if (result) {
        *result = (int)((intptr)exit_code);
    }
    return thread_state;
}

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NATIVE_THREAD_METHOD(thread_detach)(
        struct NATIVE_THREAD_TYPE()* const thread) {
    return pthread_detach(thread->native_handler);
}

bool NATIVE_THREAD_METHOD(thread_sleep)(uint32 ms) {
    return !!nanosleep(&((struct timespec) {
        .tv_sec = ms / 1000u,
        .tv_nsec = (ms % 1000u) * 1000000u
    }), NULL);
}

bool NATIVE_THREAD_METHOD(thread_yield)(void) {
    return !!sched_yield();
}

static void* callback_wrapper(void* params) {
    struct callback_payload* const pcallback_payload = (struct callback_payload*)params;
    ASSERT(pcallback_payload);
    wrapper_return_type exit_code = (wrapper_return_type)((intptr)pcallback_payload->callback(pcallback_payload->arguments_pack));
    NAMESPACE_MEMORY_NATIVE(aligned_free)(pcallback_payload);
    return exit_code;
}
