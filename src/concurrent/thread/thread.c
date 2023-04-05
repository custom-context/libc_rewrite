#include "thread.h"

#include <process/native.h>

#if !defined(_WIN32)
    #include <pthread.h>
#endif

#define CALLBACK_PAYLOAD_TYPE STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))

// runnable vtable definition
DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(, CALLBACK_PAYLOAD_TYPE) = {
    .run = NULL,
    .destroy_at = &TYPE_METHOD(CALLBACK_PAYLOAD_TYPE, VTABLE_MEMBER(destroy_at)),
    .delete_at = NULL
};

// runnable methods implementation
DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(extern, CALLBACK_PAYLOAD_TYPE);
struct CALLBACK_PAYLOAD_TYPE*
    TYPE_METHOD(CALLBACK_PAYLOAD_TYPE, construct_at)(
        struct CALLBACK_PAYLOAD_TYPE* const this) {
    ASSERT(this);
    this->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE) = &INTERFACE_VTABLE_STATIC_VARIABLE(CALLBACK_PAYLOAD_TYPE);
    return this;
}
void TYPE_METHOD(CALLBACK_PAYLOAD_TYPE, run)(struct CALLBACK_PAYLOAD_TYPE* const this) {
    ASSERT(this);
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE));
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE)->run);
    this->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE)->run(this);
}
void* TYPE_METHOD(CALLBACK_PAYLOAD_TYPE, destroy_at)(struct CALLBACK_PAYLOAD_TYPE* const this) {
    ASSERT(this);
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE));
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE)->destroy_at);
    return this->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE)->destroy_at(this);
}

// runnable vtable methods implementation
void* TYPE_METHOD(CALLBACK_PAYLOAD_TYPE, VTABLE_MEMBER(destroy_at))(struct CALLBACK_PAYLOAD_TYPE* const this) {
    return this;
}

// thread methods implementation
struct THREAD_TYPE()* THREAD_METHOD(construct_at)(struct THREAD_TYPE()* const this) {
    ASSERT(this);
#if defined(_WIN32)
    this->native_id = GetCurrentThreadId();
    this->native_handler = GetCurrentThread();
#else
    this->native_handler = pthread_self();
#endif
    this->is_joinable = false;
    return this;
}
struct THREAD_TYPE()* THREAD_METHOD(construct_move_at)(struct THREAD_TYPE()* const this, struct THREAD_TYPE()* const source) {
    ASSERT(this);
#if defined(_WIN32)
    this->native_id = source->native_id; source->native_id = GetCurrentThreadId();
    this->native_handler = source->native_handler; source->native_handler = GetCurrentThread();
#else
    this->native_handler = source->native_handler; source->native_handler = pthread_self();
#endif
    this->is_joinable = source->is_joinable; source->is_joinable = false;
    return this;
}
void* THREAD_METHOD(destroy_at)(struct THREAD_TYPE()* const this) {
    ASSERT(this);
    ASSERT(!this->is_joinable);
    if (this->is_joinable) {
        NAMESPACE_NATIVE_PROCESS(abort)();
    }
    return this;
}
struct THREAD_TYPE()* THREAD_METHOD(assign_move_at)(struct THREAD_TYPE()* const this, struct THREAD_TYPE()* const source) {
    struct THREAD_TYPE() temporary;
    THREAD_METHOD(construct_move_at)(&temporary, source);
    THREAD_METHOD(swap)(&temporary, this);
    THREAD_METHOD(destroy_at)(&temporary);
    return this;
}
void THREAD_METHOD(swap)(struct THREAD_TYPE()* const this, struct THREAD_TYPE()* const source) {
#if defined(_WIN32)
    {
        STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type) temporary = this->native_id;
        this->native_id = source->native_id;
        source->native_id = temporary;
    }
#endif
    {
        STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type) temporary = this->native_handler;
        this->native_handler = source->native_handler;
        source->native_handler = temporary;
    }
    {
        bool temporary = this->is_joinable;
        this->is_joinable = source->is_joinable;
        source->is_joinable = temporary;
    }
}
#if defined(_WIN32)
#include <synchapi.h>
static DWORD WINAPI callback_wrapper(LPVOID lpParam);
#else
#include <pthread.h>
static void* callback_wrapper(void* arg);
#endif
struct THREAD_TYPE()* THREAD_METHOD(construct_from_runnable_at)(struct THREAD_TYPE()* const this, CALLBACK_PAYLOAD_TYPE* const runnable) {
    ASSERT(this);
    ASSERT(runnable);
#if defined(_WIN32)
    this->native_handler = CreateThread(NULL, 0u, callback_wrapper, (LPVOID)(runnable), 0u, &this->native_id);
    this->is_joinable = !!this->native_handler;
#else
    this->is_joinable = !pthread_create(&this->native_handler, NULL, callback_wrapper, (void*)(runnable));
#endif
    return this;
}
void THREAD_METHOD(join)(struct THREAD_TYPE()* const this) {
    ASSERT(this);
    if (!this->is_joinable) {
        return;
    }
    this->is_joinable = false;
#if defined(_WIN32)
    WaitForSingleObject(this->native_handler, INFINITE);
    CloseHandle(this->native_handler);
#else
    pthread_join(this->native_handler, NULL);
#endif
}
void THREAD_METHOD(detach)(struct THREAD_TYPE()* const this) {
    ASSERT(this);
    if (!this->is_joinable) {
        return;
    }
    this->is_joinable = false;
#if defined(_WIN32)
    CloseHandle(this->native_handler);
#else
    pthread_detach(this->native_handler);
#endif
}
bool THREAD_METHOD(joinable)(struct THREAD_TYPE() const* const this) {
    ASSERT(this);
    return this->is_joinable;
}
STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type) THREAD_METHOD(get_id)(struct THREAD_TYPE() const* const this) {
#if defined(_WIN32)
    return this->native_id;
#else
    return this->native_handler;
#endif
}
STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type) THREAD_METHOD(native_handler)(struct THREAD_TYPE()* const this) {
    return this->native_handler;
}

// callback_wrapper definitions
#if defined(_WIN32)
static DWORD WINAPI callback_wrapper(LPVOID lpParam) {
    CALLBACK_PAYLOAD_TYPE* const runnable = (CALLBACK_PAYLOAD_TYPE*)(lpParam);
    ASSERT(runnable);
    TYPE_METHOD(CALLBACK_PAYLOAD_TYPE, run)(runnable);
    void* runnable_storage = TYPE_METHOD(CALLBACK_PAYLOAD_TYPE, destroy_at)(runnable);
    ASSERT(runnable->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE));
    if (runnable->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE)->delete_at) {
        runnable->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE)->delete_at(runnable_storage);
    }
    return 0u;
}
#else
static void* callback_wrapper(void* arg) {
    CALLBACK_PAYLOAD_TYPE* const runnable = (CALLBACK_PAYLOAD_TYPE*)(arg);
    ASSERT(runnable);
    TYPE_METHOD(CALLBACK_PAYLOAD_TYPE, run)(runnable);
    void* runnable_storage = TYPE_METHOD(CALLBACK_PAYLOAD_TYPE, destroy_at)(runnable);
    ASSERT(runnable->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE));
    if (runnable->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE)->delete_at) {
        runnable->INTERFACE_VTABLE_VARIABLE(CALLBACK_PAYLOAD_TYPE)->delete_at(runnable_storage);
    }
    return NULL;
}
#endif
