#include "thread.h"

#include <process/native.h>

// thread::runnable::vtable__ global declaration (for re-usage)
DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(, THREAD_RUNNABLE_INTERFACE_TYPE()) = {
    .run = NULL,
    .destroy_at = &THREAD_RUNNABLE_INTERFACE_METHOD(VTABLE_MEMBER(destroy_at)),
    .free_at = NULL
};

// thread::runnable::vtable__ methods
void*
    THREAD_RUNNABLE_INTERFACE_METHOD(VTABLE_MEMBER(destroy_at))(
        struct THREAD_RUNNABLE_INTERFACE_TYPE()* const this) {
    ASSERT(this);
    return this;
}

// thread::runnable methods
struct THREAD_RUNNABLE_INTERFACE_TYPE()*
    THREAD_RUNNABLE_INTERFACE_METHOD(construct_at)(
        struct THREAD_RUNNABLE_INTERFACE_TYPE()* const this) {
    ASSERT(this);
    this->INTERFACE_VTABLE_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE()) = &INTERFACE_VTABLE_STATIC_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE());
    return this;
}
void THREAD_RUNNABLE_INTERFACE_METHOD(run)(struct THREAD_RUNNABLE_INTERFACE_TYPE()* const this) {
    ASSERT(this);
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE()));
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE())->run);
    this->INTERFACE_VTABLE_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE())->run(this);
}
void* THREAD_RUNNABLE_INTERFACE_METHOD(destroy_at)(struct THREAD_RUNNABLE_INTERFACE_TYPE()* const this) {
    ASSERT(this);
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE()));
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE())->destroy_at);
    return this->INTERFACE_VTABLE_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE())->destroy_at(this);
}

// thread methods implementation
struct THREAD_TYPE()* THREAD_METHOD(construct_move_at)(struct THREAD_TYPE()* const this, struct THREAD_TYPE()* const source) {
    ASSERT(this);
    this->native_thread.native_handler = source->native_thread.native_handler;
    this->is_joinable = source->is_joinable;
    THREAD_METHOD(construct_at)(source);
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

static int callback_wrapper(void* params);

struct THREAD_TYPE()* THREAD_METHOD(construct_from_runnable_at)(struct THREAD_TYPE()* const this, THREAD_RUNNABLE_INTERFACE_TYPE()* const runnable) {
    ASSERT(this);
    ASSERT(runnable);
    this->is_joinable =
        !NATIVE_THREAD_METHOD(thread_create)(&this->native_thread, callback_wrapper, (void*)(runnable));
    return this;
}
void THREAD_METHOD(join)(struct THREAD_TYPE()* const this) {
    ASSERT(this);
    if (!this->is_joinable) {
        return;
    }
    this->is_joinable = false;

    NATIVE_THREAD_METHOD(thread_join)(&this->native_thread, NULL);
}

void THREAD_METHOD(detach)(struct THREAD_TYPE()* const this) {
    ASSERT(this);
    if (!this->is_joinable) {
        return;
    }
    this->is_joinable = false;
    NATIVE_THREAD_METHOD(thread_detach)(&this->native_thread);
}
bool THREAD_METHOD(joinable)(struct THREAD_TYPE() const* const this) {
    ASSERT(this);
    return this->is_joinable;
}
static int callback_wrapper(void* params) {
    THREAD_RUNNABLE_INTERFACE_TYPE()* const runnable = (THREAD_RUNNABLE_INTERFACE_TYPE()*)(params);
    ASSERT(runnable);
    THREAD_RUNNABLE_INTERFACE_METHOD(run)(runnable);
    void* const runnable_storage = THREAD_RUNNABLE_INTERFACE_METHOD(destroy_at)(runnable);
    ASSERT(runnable->INTERFACE_VTABLE_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE()));
    if (runnable->INTERFACE_VTABLE_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE())->free_at) {
        runnable->INTERFACE_VTABLE_VARIABLE(THREAD_RUNNABLE_INTERFACE_TYPE())->free_at(runnable_storage);
    }
    return 0u;
}
