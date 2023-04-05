#pragma once

#include <concurrent/thread/thread.h>
#include <tests/utils/macros.h>
#include <primitives/atomic.h>

typedef struct int_atomically_increment_runnable_type {
    struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)) INTERFACE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
    ATOMIC_TYPE(int32) value;
} int_atomically_increment_runnable_type;

// cast functions
// int_atomically_increment_runnable_type -> STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))
DECLARE_ISTATIC_CAST_WITH_MODIFIER(static, int_atomically_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))) {
    return &this->INTERFACE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
}
DECLARE_CONST_ISTATIC_CAST_WITH_MODIFIER(static, int_atomically_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))) {
    return &this->INTERFACE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
}
// STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)) -> int_atomically_increment_runnable_type
DECLARE_ISTATIC_CAST_WITH_MODIFIER(static, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), int_atomically_increment_runnable_type) {
    return ((void*)((char*)this -
        offsetof(int_atomically_increment_runnable_type, INTERFACE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))))));
}
DECLARE_CONST_ISTATIC_CAST_WITH_MODIFIER(static, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), int_atomically_increment_runnable_type) {
    return ((void const*)((char const*)this -
        offsetof(int_atomically_increment_runnable_type, INTERFACE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))))));
}

// vtable declaration
DECLARE_CONTAINER_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(static, int_atomically_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));

// type methods definition
static struct int_atomically_increment_runnable_type*
    TYPE_METHOD(int_atomically_increment_runnable_type, construct_at)(
        struct int_atomically_increment_runnable_type* const this) {
    /* --- boilerplate --- */
    ASSERT(this);
    struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const base =
        ISTATIC_CAST(int_atomically_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)))(this);
    TYPE_METHOD(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), construct_at)(base);
    base->INTERFACE_VTABLE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))) =
                &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(int_atomically_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
    /* --- method body --- */
    ATOMIC_METHOD(int32, construct_at)(&this->value);
    return this;
}
static void*
    TYPE_METHOD(int_atomically_increment_runnable_type, VTABLE_MEMBER(destroy_at))(
        struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const base) {
    /* --- boilerplate --- */
    ASSERT(base);
    struct int_atomically_increment_runnable_type* const this =
        ISTATIC_CAST(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), int_atomically_increment_runnable_type)(base);
    /* --- method body --- */
    /* ... */
    /* --- boilerplate --- */
    TYPE_METHOD(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), VTABLE_MEMBER(destroy_at))(base);
    return this;
}
static void
    TYPE_METHOD(int_atomically_increment_runnable_type, VTABLE_MEMBER(run))(
        struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const base) {
    /* --- boilerplate --- */
    ASSERT(base);
    struct int_atomically_increment_runnable_type* const this =
        ISTATIC_CAST(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), int_atomically_increment_runnable_type)(base);
    /* --- method body --- */
    int32 value = ATOMIC_METHOD(int32, load_explicit)(&this->value, ATOMIC_MEMORY_ORDER_ENUM_VALUE(relaxed));
    NAMESPACE_CONCURRENT_ATOMIC(thread_fence)(ATOMIC_MEMORY_ORDER_ENUM_VALUE(acquire));
    ATOMIC_METHOD(int32, store_explicit)(&this->value, value + 1, ATOMIC_MEMORY_ORDER_ENUM_VALUE(relaxed));
    NAMESPACE_CONCURRENT_ATOMIC(thread_fence)(ATOMIC_MEMORY_ORDER_ENUM_VALUE(release));
}

// vtable definition
DECLARE_CONTAINER_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(static, int_atomically_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))) = {
    .destroy_at = TYPE_METHOD(int_atomically_increment_runnable_type, VTABLE_MEMBER(destroy_at)),
    .delete_at = NULL,
    .run = TYPE_METHOD(int_atomically_increment_runnable_type, VTABLE_MEMBER(run))
};
