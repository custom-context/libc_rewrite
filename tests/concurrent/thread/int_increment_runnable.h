#pragma once

#include <concurrent/thread/thread.h>
#include <tests/utils/macros.h>

typedef struct int_increment_runnable_type {
    struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)) INTERFACE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
    int value;
} int_increment_runnable_type;

// cast functions
// int_increment_runnable_type -> STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))
DECLARE_ISTATIC_CAST_WITH_MODIFIER(static, int_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))) {
    return &this->INTERFACE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
}
DECLARE_CONST_ISTATIC_CAST_WITH_MODIFIER(static, int_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))) {
    return &this->INTERFACE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
}
// STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)) -> int_increment_runnable_type
DECLARE_ISTATIC_CAST_WITH_MODIFIER(static, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), int_increment_runnable_type) {
    return ((void*)((char*)this -
        offsetof(int_increment_runnable_type, INTERFACE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))))));
}
DECLARE_CONST_ISTATIC_CAST_WITH_MODIFIER(static, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), int_increment_runnable_type) {
    return ((void const*)((char const*)this -
        offsetof(int_increment_runnable_type, INTERFACE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))))));
}

// vtable declaration
DECLARE_CONTAINER_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(static, int_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));

static struct int_increment_runnable_type*
    TYPE_METHOD(int_increment_runnable_type, construct_at)(
        struct int_increment_runnable_type* const this) {
    /* --- boilerplate --- */
    ASSERT(this);
    struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const base =
        ISTATIC_CAST(int_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)))(this);
    TYPE_METHOD(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), construct_at)(base);
    base->INTERFACE_VTABLE_VARIABLE(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))) =
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(int_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)));
    /* --- method body --- */
    this->value = 0;
    return this;
}
static void*
    TYPE_METHOD(int_increment_runnable_type, VTABLE_MEMBER(destroy_at))(
        struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const base) {
    /* --- boilerplate --- */
    ASSERT(base);
    struct int_increment_runnable_type* const this =
        ISTATIC_CAST(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), int_increment_runnable_type)(base);
    /* --- method body --- */
    /* ... */
    /* --- boilerplate --- */
    TYPE_METHOD(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), VTABLE_MEMBER(destroy_at))(base);
    return this;
}
static void
    TYPE_METHOD(int_increment_runnable_type, VTABLE_MEMBER(run))(
        struct STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))* const base) {
    /* --- boilerplate --- */
    ASSERT(base);
    struct int_increment_runnable_type* const this =
        ISTATIC_CAST(STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable)), int_increment_runnable_type)(base);
    /* --- method body --- */
    ++this->value;
}

DECLARE_CONTAINER_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(static, int_increment_runnable_type, STRUCT_SUBTYPE(THREAD_TYPE(), INTERFACE_TYPE(runnable))) = {
    .destroy_at = TYPE_METHOD(int_increment_runnable_type, VTABLE_MEMBER(destroy_at)),
    .delete_at = NULL,
    .run = TYPE_METHOD(int_increment_runnable_type, VTABLE_MEMBER(run))
};
