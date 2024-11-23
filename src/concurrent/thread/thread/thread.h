#pragma once

#include <concurrent/thread/native/native.h>
#include <concurrent/thread/common.h>
#include <primitives/bool_type_alias.h>

#define THREAD_TYPE() NAMESPACE_CONCURRENT_THREAD(thread)
#define THREAD_METHOD(METHOD) TYPE_METHOD(THREAD_TYPE(), METHOD)

#define THREAD_RUNNABLE_INTERFACE_TYPE() TYPE_MEMBER(THREAD_TYPE(), INTERFACE_TYPE(runnable))
#define THREAD_RUNNABLE_INTERFACE_METHOD(METHOD) TYPE_METHOD(THREAD_RUNNABLE_INTERFACE_TYPE(), METHOD)

// thread::runnable declarations
struct THREAD_RUNNABLE_INTERFACE_TYPE();

// thread::runnable::vtable__ type
typedef struct INTERFACE_VTABLE_TYPE(THREAD_RUNNABLE_INTERFACE_TYPE()) {
    void (*run)(struct THREAD_RUNNABLE_INTERFACE_TYPE()* const this); // = 0
    void* (*destroy_at)(struct THREAD_RUNNABLE_INTERFACE_TYPE()* const this); // = default
    void (*free_at)(void* storage); // = NULL
} INTERFACE_VTABLE_TYPE(THREAD_RUNNABLE_INTERFACE_TYPE());

// thread::runnable::vtable__ global declaration (for re-usage)
DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(extern, THREAD_RUNNABLE_INTERFACE_TYPE());

// thread::runnable::vtable__ methods
void*
    THREAD_RUNNABLE_INTERFACE_METHOD(VTABLE_MEMBER(destroy_at))(
        struct THREAD_RUNNABLE_INTERFACE_TYPE()* const this);

// thread::runnable type
typedef struct THREAD_RUNNABLE_INTERFACE_TYPE() {
    DEFINE_INTERFACE_VTABLE_ADAPTER(THREAD_RUNNABLE_INTERFACE_TYPE());
} THREAD_RUNNABLE_INTERFACE_TYPE();

// thread::runnable methods
struct THREAD_RUNNABLE_INTERFACE_TYPE()*
    THREAD_RUNNABLE_INTERFACE_METHOD(construct_at)(
        struct THREAD_RUNNABLE_INTERFACE_TYPE()* const this);
void*
    THREAD_RUNNABLE_INTERFACE_METHOD(destroy_at)(
        struct THREAD_RUNNABLE_INTERFACE_TYPE()* const this);
void
    THREAD_RUNNABLE_INTERFACE_METHOD(run)(
        struct THREAD_RUNNABLE_INTERFACE_TYPE()* const this);

// thread declarations
struct THREAD_TYPE();
DECLARE_STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable), THREAD_RUNNABLE_INTERFACE_TYPE());

// thread type
typedef struct THREAD_TYPE() {
    struct NATIVE_THREAD_TYPE() native_thread;
    bool is_joinable;
} THREAD_TYPE();

// thread methods
DECLARE_DEFAULT_LIFECYCLE_METHODS_WITH_MODIFIER(, THREAD_TYPE());
struct THREAD_TYPE()* THREAD_METHOD(construct_from_runnable_at)(struct THREAD_TYPE()* const this, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const runnable);
void THREAD_METHOD(join)(struct THREAD_TYPE()* const this);
void THREAD_METHOD(detach)(struct THREAD_TYPE()* const this);
bool THREAD_METHOD(joinable)(struct THREAD_TYPE() const* const this);
STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type) THREAD_METHOD(get_id)(struct THREAD_TYPE() const* const this);
STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type) THREAD_METHOD(native_handler)(struct THREAD_TYPE()* const this);
