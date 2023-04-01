#include "native.h"

#include <memory/native/native.h>


#if defined(_WIN32)
#include <synchapi.h>
static DWORD WINAPI callback_wrapper(LPVOID lpParam);
#else
#include <pthread.h>
static void callback_wrapper(void* arg);
#endif

#define CALLBACK_PAYLOAD_TYPE STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), callback_payload)
#define ARC_CTRL_BLK ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(CALLBACK_PAYLOAD_TYPE)

inline static void* TYPE_METHOD(CALLBACK_PAYLOAD_TYPE, destroy_at)(CALLBACK_PAYLOAD_TYPE* const this) {
    return this;
}

DECLARE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, CALLBACK_PAYLOAD_TYPE);
DECLARE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, ARC_CTRL_BLK);
DECLARE_ATOMICALLY_REFERENCE_COUNTED_METHODS_WITH_MODIFIER(static, CALLBACK_PAYLOAD_TYPE);

DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, CALLBACK_PAYLOAD_TYPE)
DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, ARC_CTRL_BLK)
DEFINE_ATOMICALLY_REFERENCE_COUNTED_METHODS_WITH_MODIFIER(static, CALLBACK_PAYLOAD_TYPE)

#define ARC_CALLBACK_PAYLOAD ATOMICALLY_REFERENCE_COUNTED_TYPE(CALLBACK_PAYLOAD_TYPE)

// allocator for arc<thread::callback_payload>
DEFINE_DEFAULT_ALLOCATOR_TYPE(ARC_CALLBACK_PAYLOAD);
DECLARE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, ARC_CALLBACK_PAYLOAD);
DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, ARC_CALLBACK_PAYLOAD)

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NAMESPACE_CONCURRENT_NATIVE_THREAD(create_thread)(
        struct NATIVE_THREAD_TYPE()* const thread,
        STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type) callback,
        void* arg) {
    ASSERT(thread);
    CALLBACK_PAYLOAD_TYPE* callback_payload_pointer;
    {
        struct DEFAULT_ALLOCATOR_TYPE(CALLBACK_PAYLOAD_TYPE) temporary_allocator;
        DEFAULT_ALLOCATOR_METHOD(CALLBACK_PAYLOAD_TYPE, construct_at)(&temporary_allocator);
        callback_payload_pointer = DEFAULT_ALLOCATOR_METHOD(CALLBACK_PAYLOAD_TYPE, allocate)(&temporary_allocator, 1u);
        DEFAULT_ALLOCATOR_METHOD(CALLBACK_PAYLOAD_TYPE, destroy_at)(&temporary_allocator);
    }
    ASSERT(callback_payload_pointer);
    callback_payload_pointer->callback = callback;
    callback_payload_pointer->arg = arg;
    ATOMICALLY_REFERENCE_COUNTED_METHOD(CALLBACK_PAYLOAD_TYPE, construct_from_value_pointer_at)(&thread->callback_payload, callback_payload_pointer);
    struct ARC_CALLBACK_PAYLOAD* thread_move_arc_callback_payload_pointer;
    {
        struct DEFAULT_ALLOCATOR_TYPE(ARC_CALLBACK_PAYLOAD) temporary_allocator;
        DEFAULT_ALLOCATOR_METHOD(ARC_CALLBACK_PAYLOAD, construct_at)(&temporary_allocator);
        thread_move_arc_callback_payload_pointer = DEFAULT_ALLOCATOR_METHOD(ARC_CALLBACK_PAYLOAD, allocate)(&temporary_allocator, 1u);
        DEFAULT_ALLOCATOR_METHOD(ARC_CALLBACK_PAYLOAD, destroy_at)(&temporary_allocator);
    }
    ASSERT(thread_move_arc_callback_payload_pointer);
    ATOMICALLY_REFERENCE_COUNTED_METHOD(CALLBACK_PAYLOAD_TYPE, construct_copy_at)(thread_move_arc_callback_payload_pointer, &thread->callback_payload);
#if defined(_WIN32)
    thread->native_handler = CreateThread(NULL, 0u, callback_wrapper, (LPVOID)(thread_move_arc_callback_payload_pointer), 0u, &thread->native_id);
    if (!thread->native_handler) {
        return GetLastError();
    }
    return 0u;
#else
    return pthread_create(&thread->native_handler, NULL, callback_wrapper, (void*)(thread_move_arc_callback_payload_pointer));
#endif
}


STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NAMESPACE_CONCURRENT_NATIVE_THREAD(thread_join)(
        struct NATIVE_THREAD_TYPE() thread,
        STRUCT_SUBTYPE(STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type), result_type)* result) {
#if defined(_WIN32)
    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type) state = WaitForSingleObject(thread.native_handler, INFINITE);
    CloseHandle(thread.native_handler);
#else
    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type) state = pthread_join(thread.native_handler, NULL);
#endif
    if (result) {
        *result = TYPE_METHOD(ARC_CALLBACK_PAYLOAD, get)(&thread.callback_payload)->return_value;
    }
    TYPE_METHOD(ARC_CALLBACK_PAYLOAD, destroy_at)(&thread.callback_payload);
    return state;
}

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NAMESPACE_CONCURRENT_NATIVE_THREAD(thread_detach)(
        struct NATIVE_THREAD_TYPE() thread) {
    TYPE_METHOD(ARC_CALLBACK_PAYLOAD, destroy_at)(&thread.callback_payload);
#if defined(_WIN32)
    if (!CloseHandle(thread.native_handler)) {
        return GetLastError();
    }
    return 0u;
#else
    return pthread_detach(thread.native_handler);
#endif
}

#if defined(_WIN32)
static DWORD WINAPI callback_wrapper(LPVOID lpParam) {
    struct ARC_CALLBACK_PAYLOAD* const arc_payload = (struct ARC_CALLBACK_PAYLOAD* const)(lpParam);
    ASSERT(arc_payload);
    {
        CALLBACK_PAYLOAD_TYPE* const payload = TYPE_METHOD(ARC_CALLBACK_PAYLOAD, mut_get)(arc_payload);
        ASSERT(payload->callback);
        {
            payload->return_value = payload->callback(payload->arg);
        }
    }
    TYPE_METHOD(ARC_CALLBACK_PAYLOAD, destroy_at)(arc_payload);
    {
        struct DEFAULT_ALLOCATOR_TYPE(ARC_CALLBACK_PAYLOAD) temporary_allocator;
        DEFAULT_ALLOCATOR_METHOD(ARC_CALLBACK_PAYLOAD, construct_at)(&temporary_allocator);
        DEFAULT_ALLOCATOR_METHOD(ARC_CALLBACK_PAYLOAD, deallocate)(&temporary_allocator, arc_payload, 1u);
        DEFAULT_ALLOCATOR_METHOD(ARC_CALLBACK_PAYLOAD, destroy_at)(&temporary_allocator);
    }
    return 0u;
}
#else
static void callback_wrapper(void* arg) {
    struct ARC_CALLBACK_PAYLOAD* const arc_payload = (struct ARC_CALLBACK_PAYLOAD* const)(arg);
    ASSERT(arc_payload);
    {
        CALLBACK_PAYLOAD_TYPE* const payload = TYPE_METHOD(ARC_CALLBACK_PAYLOAD, mut_get)(&arc_payload);
        ASSERT(payload->callback);
        {
            payload->return_value = payload->callback(payload->arg);
        }
    }
    TYPE_METHOD(ARC_CALLBACK_PAYLOAD, destroy_at)(arc_payload);
    {
        struct DEFAULT_ALLOCATOR_TYPE(ARC_CALLBACK_PAYLOAD) temporary_allocator;
        DEFAULT_ALLOCATOR_METHOD(ARC_CALLBACK_PAYLOAD, construct_at)(&temporary_allocator);
        DEFAULT_ALLOCATOR_METHOD(ARC_CALLBACK_PAYLOAD, deallocate)(&temporary_allocator, arc_payload, 1u);
        DEFAULT_ALLOCATOR_METHOD(ARC_CALLBACK_PAYLOAD, destroy_at)(&temporary_allocator);
    }
}
#endif
