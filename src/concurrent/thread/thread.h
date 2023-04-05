#pragma once

#include <concurrent/thread/native.h>
#include "common.h"

#define THREAD_TYPE() NAMESPACE_CONCURRENT_THREAD(thread)

#if defined(_WIN32)
    DECLARE_STRUCT_SUBTYPE(THREAD_TYPE(), native_handler_type, HANDLE);
    DECLARE_STRUCT_SUBTYPE(THREAD_TYPE(), native_id_type, DWORD);
#else
    DECLARE_STRUCT_SUBTYPE(THREAD_TYPE(), native_handler_type, pthread_t);
    DECLARE_STRUCT_SUBTYPE(THREAD_TYPE(), native_id_type, pthread_t);
#endif

// mutable INTERFACE_TYPE(runnable)
/// mutable INTERFACE_TYPE(runnable) vtable
struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable));
typedef struct INTERFACE_VTABLE_TYPE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))) {
    void (*run)(struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const this); // = 0
    void* (*destroy_at)(struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const this); // = default
    void (*delete_at)(void* storage); // = NULL
} INTERFACE_VTABLE_TYPE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
/// mutable INTERFACE_TYPE(runnable) type
typedef struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)) {
    DEFINE_INTERFACE_VTABLE_ADAPTER(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
} STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable));
/// mutable INTERFACE_TYPE(runnable) methods
struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))*
    TYPE_METHOD(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), construct_at)(
        struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const this);
void
    TYPE_METHOD(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), run)(
        struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const this);
void*
    TYPE_METHOD(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), destroy_at)(
        struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const this);

// thread type
typedef struct THREAD_TYPE() {
    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type) native_handler;
#if defined(_WIN32)
    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type) native_id;
#endif
    bool is_joinable;
} THREAD_TYPE();

// thread methods
#define THREAD_METHOD(METHOD) TYPE_METHOD(THREAD_TYPE(), METHOD)
struct THREAD_TYPE()* THREAD_METHOD(construct_at)(struct THREAD_TYPE()* const this);
struct THREAD_TYPE()* THREAD_METHOD(construct_move_at)(struct THREAD_TYPE()* const this, struct THREAD_TYPE()* const source);
void* THREAD_METHOD(destroy_at)(struct THREAD_TYPE()* const this);
struct THREAD_TYPE()* THREAD_METHOD(assign_move_at)(struct THREAD_TYPE()* const this, struct THREAD_TYPE()* const source);
void THREAD_METHOD(swap)(struct THREAD_TYPE()* const this, struct THREAD_TYPE()* const source);
struct THREAD_TYPE()* THREAD_METHOD(construct_from_runnable_at)(struct THREAD_TYPE()* const this, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const runnable);
void THREAD_METHOD(join)(struct THREAD_TYPE()* const this);
void THREAD_METHOD(detach)(struct THREAD_TYPE()* const this);
bool THREAD_METHOD(joinable)(struct THREAD_TYPE() const* const this);
STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type) THREAD_METHOD(get_id)(struct THREAD_TYPE() const* const this);
STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type) THREAD_METHOD(native_handler)(struct THREAD_TYPE()* const this);

// runnable vtable declaration
DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(extern, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
// runnable vtable methods declaration
void* TYPE_METHOD(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), VTABLE_MEMBER(destroy_at))(struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const this);
