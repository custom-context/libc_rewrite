#pragma once

#include <memory/common.h>

#define PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT) NAMESPACE_MEMORY(CONCAT5(proxy_allocator, __, ALLOCATOR, __, CONTEXT))

#define PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, METHOD)\
    TYPE_METHOD(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), METHOD)

#define DEFINE_PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)\
DECLARE_STRUCT_SUBTYPE(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), allocator_type, ALLOCATOR);\
DECLARE_STRUCT_SUBTYPE(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), context_type, CONTEXT);\
typedef struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT) {\
    STRUCT_SUBTYPE(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), allocator_type) allocator;\
    STRUCT_SUBTYPE(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), context_type)* context;\
    void (*on_allocation)(\
        STRUCT_SUBTYPE(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), context_type)* const context,\
        STRUCT_SUBTYPE(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), allocator_type)* const this,\
        \
        size_t count_of_elements);\
    void (*on_deallocation)(\
        STRUCT_SUBTYPE(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), context_type)* const context,\
        \
        STRUCT_SUBTYPE(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), allocator_type)* const this,\
        STRUCT_SUBTYPE(ALLOCATOR, value_type)* const elements_buffer,\
        size_t count_of_elements);\
    void (*on_reallocation)(\
        STRUCT_SUBTYPE(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), context_type)* const context,\
        \
        STRUCT_SUBTYPE(PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT), allocator_type)* const this,\
        STRUCT_SUBTYPE(ALLOCATOR, value_type)* const elements_buffer,\
        size_t count_of_elements,\
        size_t new_count_of_elements);\
} PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)

#define DECLARE_PROXY_ALLOCATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, ALLOCATOR, CONTEXT)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)*\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, construct_at)(struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this);\
COMMON_MODIFIER struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)*\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, construct_copy_at)(\
        struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
        struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT) const* const source);\
COMMON_MODIFIER struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)*\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, construct_move_at)(\
        struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
        struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const source);\
COMMON_MODIFIER void* PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, destroy_at)(struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, assign_copy_at)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT) const* const source);\
COMMON_MODIFIER struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, assign_move_at)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const source);\
/* --- Swap --- */\
COMMON_MODIFIER void PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, swap)(struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this, struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const another);\
/* --- Memory managment functions implementation --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(ALLOCATOR, value_type)* PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, allocate)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    size_t count_of_elements);\
COMMON_MODIFIER void PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, deallocate)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    STRUCT_SUBTYPE(ALLOCATOR, value_type)* const elements_buffer,\
    size_t count_of_elements);\
COMMON_MODIFIER STRUCT_SUBTYPE(ALLOCATOR, value_type)* PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, reallocate)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    STRUCT_SUBTYPE(ALLOCATOR, value_type)* const elements_buffer,\
    size_t count_of_elements,\
    size_t new_count_of_elements)

#define DECLARE_PROXY_ALLOCATOR_METHODS(COMMON_MODIFIER, ALLOCATOR, CONTEXT) DECLARE_PROXY_ALLOCATOR_METHODS_WITH_MODIFIER(, ALLOCATOR, CONTEXT)

#define DEFINE_PROXY_ALLOCATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, ALLOCATOR, CONTEXT)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)*\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, construct_at)(struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this) {\
    this->context = NULL;\
    this->on_allocation = NULL;\
    this->on_deallocation = NULL;\
    this->on_reallocation = NULL;\
    TYPE_METHOD(ALLOCATOR, construct_at)(&this->allocator);\
    return this;\
}\
COMMON_MODIFIER struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)*\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, construct_copy_at)(\
        struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
        struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT) const* const source) {\
    this->context = source->context;\
    this->on_allocation = source->on_allocation;\
    this->on_deallocation = source->on_deallocation;\
    this->on_reallocation = source->on_reallocation;\
    TYPE_METHOD(ALLOCATOR, construct_copy_at)(&this->allocator, &source->allocator);\
    return this;\
}\
COMMON_MODIFIER struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)*\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, construct_move_at)(\
        struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
        struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const source) {\
    this->context = source->context;\
    this->on_allocation = source->on_allocation;\
    this->on_deallocation = source->on_deallocation;\
    this->on_reallocation = source->on_reallocation;\
    TYPE_METHOD(ALLOCATOR, construct_move_at)(&this->allocator, &source->allocator);\
    return this;\
}\
COMMON_MODIFIER void* PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, destroy_at)(struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this) {\
    TYPE_METHOD(ALLOCATOR, destroy_at)(&this->allocator);\
    return this;\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, assign_copy_at)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT) const* const source) {\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT) temporary;\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, construct_copy_at)(&temporary, source);\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, swap)(&temporary, this);\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, destroy_at)(&temporary);\
    return this;\
}\
COMMON_MODIFIER struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, assign_move_at)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const source) {\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT) temporary;\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, construct_move_at)(&temporary, source);\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, swap)(&temporary, this);\
    PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, destroy_at)(&temporary);\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, swap)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const another) {\
    {\
        CONTEXT* temporary = this->context;\
        this->context = another->context;\
        another->context = temporary;\
    }\
    {\
        void(*temporary)(CONTEXT* const, struct ALLOCATOR* const, size_t) = this->on_allocation;\
        this->on_allocation = another->on_allocation;\
        another->on_allocation = temporary;\
    }\
    {\
        void(*temporary)(CONTEXT* const, struct ALLOCATOR* const, STRUCT_SUBTYPE(ALLOCATOR, value_type)* const, size_t) = this->on_deallocation;\
        this->on_deallocation = another->on_deallocation;\
        another->on_deallocation = temporary;\
    }\
    {\
        void (*temporary)(CONTEXT* const, struct ALLOCATOR* const, STRUCT_SUBTYPE(ALLOCATOR, value_type)* const, size_t, size_t) = this->on_reallocation;\
        this->on_reallocation = another->on_reallocation;\
        another->on_reallocation = temporary;\
    }\
    TYPE_METHOD(ALLOCATOR, swap)(&this->allocator, &another->allocator);\
}\
/* --- Memory managment functions implementation --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(ALLOCATOR, value_type)* PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, allocate)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    size_t count_of_elements) {\
    if (this->on_allocation) {\
        this->on_allocation(this->context, &this->allocator, count_of_elements);\
    }\
    return TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, count_of_elements);\
}\
COMMON_MODIFIER void PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, deallocate)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    STRUCT_SUBTYPE(ALLOCATOR, value_type)* const elements_buffer,\
    size_t count_of_elements) {\
    if (this->on_deallocation) {\
        this->on_deallocation(this->context, &this->allocator, elements_buffer, count_of_elements);\
    }\
    TYPE_METHOD(ALLOCATOR, deallocate)(&this->allocator, elements_buffer, count_of_elements);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(ALLOCATOR, value_type)* PROXY_ALLOCATOR_METHOD(ALLOCATOR, CONTEXT, reallocate)(\
    struct PROXY_ALLOCATOR_TYPE(ALLOCATOR, CONTEXT)* const this,\
    STRUCT_SUBTYPE(ALLOCATOR, value_type)* const elements_buffer,\
    size_t count_of_elements,\
    size_t new_count_of_elements) {\
    if (this->on_reallocation) {\
        this->on_reallocation(this->context, &this->allocator, elements_buffer, count_of_elements, new_count_of_elements);\
    }\
    return TYPE_METHOD(ALLOCATOR, reallocate)(&this->allocator, elements_buffer, count_of_elements, new_count_of_elements);\
}
