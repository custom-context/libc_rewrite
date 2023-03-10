#pragma once

#include <memory/native/native.h>
#include <memory/common.h>

#define DEFAULT_ALLOCATOR_TYPE(TYPE) NAMESPACE_MEMORY(CONCAT3(default_allocator, __, TYPE))
#define DEFAULT_ALLOCATOR_METHOD(TYPE, METHOD) TYPE_METHOD(DEFAULT_ALLOCATOR_TYPE(TYPE), METHOD)

#define DEFINE_DEFAULT_ALLOCATOR_TYPE(TYPE)\
DECLARE_STRUCT_SUBTYPE(DEFAULT_ALLOCATOR_TYPE(TYPE), value_type, TYPE);\
typedef struct DEFAULT_ALLOCATOR_TYPE(TYPE) {\
    char bit: 1;\
} DEFAULT_ALLOCATOR_TYPE(TYPE)

#define DECLARE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct DEFAULT_ALLOCATOR_TYPE(TYPE)*\
    DEFAULT_ALLOCATOR_METHOD(TYPE, construct_at)(struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this);\
COMMON_MODIFIER struct DEFAULT_ALLOCATOR_TYPE(TYPE)*\
    DEFAULT_ALLOCATOR_METHOD(TYPE, construct_copy_at)(\
        struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
        struct DEFAULT_ALLOCATOR_TYPE(TYPE) const* const source);\
COMMON_MODIFIER struct DEFAULT_ALLOCATOR_TYPE(TYPE)*\
    DEFAULT_ALLOCATOR_METHOD(TYPE, construct_move_at)(\
        struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
        struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const source);\
COMMON_MODIFIER void* DEFAULT_ALLOCATOR_METHOD(TYPE, destroy_at)(struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct DEFAULT_ALLOCATOR_TYPE(TYPE)* DEFAULT_ALLOCATOR_METHOD(TYPE, assign_copy_at)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE) const* const source);\
COMMON_MODIFIER struct DEFAULT_ALLOCATOR_TYPE(TYPE)* DEFAULT_ALLOCATOR_METHOD(TYPE, assign_move_at)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const source);\
/* --- Swap --- */\
COMMON_MODIFIER void DEFAULT_ALLOCATOR_METHOD(TYPE, swap)(struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this, struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const another);\
/* --- Memory managment functions implementation --- */\
COMMON_MODIFIER TYPE* DEFAULT_ALLOCATOR_METHOD(TYPE, allocate)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    size_t count_of_elements);\
COMMON_MODIFIER void DEFAULT_ALLOCATOR_METHOD(TYPE, deallocate)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    TYPE* const elements_buffer,\
    size_t count_of_elements);\
COMMON_MODIFIER TYPE* DEFAULT_ALLOCATOR_METHOD(TYPE, reallocate)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    TYPE* const elements_buffer,\
    size_t count_of_elements,\
    size_t new_count_of_elements)

#define DECLARE_DEFAULT_ALLOCATOR_METHODS(COMMON_MODIFIER, TYPE) DECLARE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(, TYPE)

#define IS_ALLOCATOR(ALLOCATOR_TYPE)\
    (&TYPE_METHOD(ALLOCATOR_TYPE, construct_at) &&\
    &TYPE_METHOD(ALLOCATOR_TYPE, construct_move_at) &&\
    &TYPE_METHOD(ALLOCATOR_TYPE, construct_copy_at) &&\
    &TYPE_METHOD(ALLOCATOR_TYPE, assing_move_at) &&\
    &TYPE_METHOD(ALLOCATOR_TYPE, assing_copy_at) &&\
    &TYPE_METHOD(ALLOCATOR_TYPE, destroy_at) &&\
    &TYPE_METHOD(ALLOCATOR_TYPE, allocate) &&\
    &TYPE_METHOD(ALLOCATOR_TYPE, deallocate) &&\
    &TYPE_METHOD(ALLOCATOR_TYPE, reallocate))

#define DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
/* --- Construction/Destruction functions implementation --- */\
COMMON_MODIFIER struct DEFAULT_ALLOCATOR_TYPE(TYPE)* DEFAULT_ALLOCATOR_METHOD(TYPE, construct_at)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this) {\
    return this;\
}\
COMMON_MODIFIER struct DEFAULT_ALLOCATOR_TYPE(TYPE)* DEFAULT_ALLOCATOR_METHOD(TYPE, construct_copy_at)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE) const* const source) {\
    UNUSED(source);\
    return this;\
}\
COMMON_MODIFIER struct DEFAULT_ALLOCATOR_TYPE(TYPE)* DEFAULT_ALLOCATOR_METHOD(TYPE, construct_move_at)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const source) {\
    UNUSED(source);\
    return this;\
}\
COMMON_MODIFIER void* DEFAULT_ALLOCATOR_METHOD(TYPE, destroy_at)(struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this) {\
    return this;\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct DEFAULT_ALLOCATOR_TYPE(TYPE)* DEFAULT_ALLOCATOR_METHOD(TYPE, assign_copy_at)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE) const* const source) {\
    UNUSED(source);\
    return this;\
}\
COMMON_MODIFIER struct DEFAULT_ALLOCATOR_TYPE(TYPE)* DEFAULT_ALLOCATOR_METHOD(TYPE, assign_move_at)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const source) {\
    UNUSED(source);\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void DEFAULT_ALLOCATOR_METHOD(TYPE, swap)(struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this, struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const another) {\
    UNUSED(this);\
    UNUSED(another);\
}\
/* --- Memory managment functions implementation --- */\
COMMON_MODIFIER TYPE* DEFAULT_ALLOCATOR_METHOD(TYPE, allocate)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    size_t count_of_elements) {\
    UNUSED(this);\
    return NAMESPACE_MEMORY_NATIVE(malloc)(count_of_elements * sizeof(TYPE));\
}\
COMMON_MODIFIER void DEFAULT_ALLOCATOR_METHOD(TYPE, deallocate)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    TYPE* const elements_buffer,\
    size_t count_of_elements) {\
    UNUSED(this);\
    UNUSED(count_of_elements);\
    NAMESPACE_MEMORY_NATIVE(free)(elements_buffer);\
}\
COMMON_MODIFIER TYPE* DEFAULT_ALLOCATOR_METHOD(TYPE, reallocate)(\
    struct DEFAULT_ALLOCATOR_TYPE(TYPE)* const this,\
    TYPE* const elements_buffer,\
    size_t count_of_elements,\
    size_t new_count_of_elements) {\
    UNUSED(this);\
    UNUSED(count_of_elements);\
    return NAMESPACE_MEMORY_NATIVE(realloc)(elements_buffer, new_count_of_elements * sizeof(TYPE));\
}

#define DEFINE_DEFAULT_ALLOCATOR_METHODS(TYPE) DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, TYPE)
#define DEFINE_DEFAULT_ALLOCATOR_STATIC_METHODS(TYPE) DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(static, TYPE)
