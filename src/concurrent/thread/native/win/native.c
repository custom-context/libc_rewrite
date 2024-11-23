#include <concurrent/thread/native/native.h>

#include <memory/native/native.h>
#include <synchapi.h>
#include <processthreadsapi.h>

static DWORD WINAPI callback_wrapper(LPVOID lpParam);
typedef DWORD wrapper_return_type;

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
    SetLastError(0u);

    struct callback_payload* const pcallback_payload =
        NAMESPACE_MEMORY_NATIVE(aligned_alloc)(ALIGNOF(struct callback_payload), SIZEOF(struct callback_payload));
    ASSERT(pcallback_payload);
    if (!pcallback_payload) {
        return GetLastError();
    }
    pcallback_payload->callback = callback;
    pcallback_payload->arguments_pack = arg;

    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type) thread_state = 0u;
    thread->native_handler = CreateThread(NULL, 0u, callback_wrapper, (LPVOID)(pcallback_payload), 0u, &thread->native_id);
    if (!thread->native_handler) {
        thread_state = GetLastError();
    }
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
    thread_state = WaitForSingleObject(thread->native_handler, INFINITE);
    if (result) {
        wrapper_return_type exit_code;
        if (GetExitCodeThread(thread->native_handler, &exit_code)) {
            *result = (int)exit_code;
        }
    }
    CloseHandle(thread->native_handler);
    return thread_state;
}

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NATIVE_THREAD_METHOD(thread_detach)(
        struct NATIVE_THREAD_TYPE()* const thread) {
    ASSERT(thread);
    if (!CloseHandle(thread->native_handler)) {
        return GetLastError();
    }
    return 0u;
}

bool NATIVE_THREAD_METHOD(thread_sleep)(uint32 ms) {
    Sleep(ms);
    return false;
}

bool NATIVE_THREAD_METHOD(thread_yield)(void) {
    return !!SwitchToThread();
}

static DWORD WINAPI callback_wrapper(LPVOID params) {
    struct callback_payload* const pcallback_payload = (struct callback_payload*)params;
    ASSERT(pcallback_payload);
    wrapper_return_type exit_code = (wrapper_return_type)pcallback_payload->callback(pcallback_payload->arguments_pack);
    NAMESPACE_MEMORY_NATIVE(aligned_free)(pcallback_payload);
    return exit_code;
}
