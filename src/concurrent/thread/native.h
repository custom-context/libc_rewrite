#pragma once

#include "common.h"

#include <containers/atomically_reference_counted/atomically_reference_counted.h>

#if defined(_WIN32)
    #include <Windows.h>
    #include <processthreadsapi.h>
#else
    #include <sys/types.h>
#endif

#define NATIVE_THREAD_TYPE() NAMESPACE_CONCURRENT_NATIVE_THREAD(thread)

#if defined(_WIN32)
    DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type, HANDLE);
    DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type, DWORD);
    DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type, DWORD);
#else
    DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type, pthread_t);
    DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type, pthread_t);
    DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type, int);
#endif

DECLARE_STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type, int, void*);
DECLARE_STRUCT_SUBTYPE(STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type), result_type, int);

typedef struct STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), callback_payload) {
    STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type) callback;
    STRUCT_SUBTYPE(STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type), result_type) return_value;
    void* arg;
} STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), callback_payload);

// arc<STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), callback_payload)>
#include <primitives/atomic.h>
#include <primitives/allocator.h>
DEFINE_DEFAULT_ALLOCATOR_TYPE(STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), callback_payload));
DEFINE_ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), callback_payload));
DEFINE_DEFAULT_ALLOCATOR_TYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), callback_payload)));
DEFINE_ATOMICALLY_REFERENCE_COUNTED_TYPE(STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), callback_payload));

typedef struct NATIVE_THREAD_TYPE() {
    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type) native_handler;
    struct ATOMICALLY_REFERENCE_COUNTED_TYPE(STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), callback_payload)) callback_payload;
#if defined(_WIN32)
    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type) native_id;
#endif
} NATIVE_THREAD_TYPE();

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NAMESPACE_CONCURRENT_NATIVE_THREAD(create_thread)(
        struct NATIVE_THREAD_TYPE()* const thread,
        STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type) callback,
        void* arg);

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NAMESPACE_CONCURRENT_NATIVE_THREAD(thread_join)(
        struct NATIVE_THREAD_TYPE() thread,
        STRUCT_SUBTYPE(STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type), result_type)* result);

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NAMESPACE_CONCURRENT_NATIVE_THREAD(thread_detach)(
        struct NATIVE_THREAD_TYPE() thread);
