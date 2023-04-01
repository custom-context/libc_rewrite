#pragma once

#include "common.h"

#include <memory/allocator/allocator.h>

#include <primitives/primitives.h>
#include <primitives/atomic.h>

// types
#define ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR)\
    NAMESPACE_ATOMICALLY_REFERENCE_COUNTED(\
        CONCAT5(CONCAT3(arc, __, control_block), _, with_value_allocator, _, VALUE_ALLOCATOR)\
    )

#define ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(TYPE)\
    ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(DEFAULT_ALLOCATOR_TYPE(TYPE))


#define ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)\
    NAMESPACE_ATOMICALLY_REFERENCE_COUNTED(\
        CONCAT5(\
            CONCAT5(\
                CONCAT3(arc, __, TYPE), _, with_value_allocator, _, VALUE_ALLOCATOR\
            ), _, and_control_block_allocator, _, CONTROL_BLOCK_ALLOCATOR\
        )\
    )

#define ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(TYPE, VALUE_ALLOCATOR)\
    ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR,\
        DEFAULT_ALLOCATOR_TYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR)))

#define ATOMICALLY_REFERENCE_COUNTED_TYPE(TYPE)\
    ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE))


// types definitions
/// rc::control_block<Allocator<Type>>
#define DEFINE_ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR)\
DECLARE_STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR),\
    value_allocator_type, VALUE_ALLOCATOR);\
DECLARE_STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR),\
    size_type, usize);\
DECLARE_STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR),\
    atomic_size_type, ATOMIC_TYPE(usize));\
typedef struct ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR) {\
    STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR),\
        atomic_size_type) strong_reference_counter;\
    STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR),\
        atomic_size_type) weak_reference_counter;\
    STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR),\
        value_allocator_type) value_allocator;\
} ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR)

#define DEFINE_ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE(TYPE)\
    DEFINE_ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(DEFAULT_ALLOCATOR_TYPE(TYPE))

/// rc<Type, Allocator<Type>, Allocator<rc::control_block>>
#define DEFINE_ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)\
DECLARE_STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR),\
    value_allocator_type, VALUE_ALLOCATOR);\
DECLARE_STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR),\
    value_type, TYPE);\
DECLARE_STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR),\
    control_block_allocator_type, CONTROL_BLOCK_ALLOCATOR);\
DECLARE_STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR),\
    control_block_type, ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR));\
typedef struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) {\
    STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), control_block_type)* control_block_pointer;\
    STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), value_type)* value_pointer;\
    STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), control_block_allocator_type) control_block_allocator;\
} ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)

#define DEFINE_ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(TYPE, VALUE_ALLOCATOR)\
    DEFINE_ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR,\
        DEFAULT_ALLOCATOR_TYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR)))

#define DEFINE_ATOMICALLY_REFERENCE_COUNTED_TYPE(TYPE)\
    DEFINE_ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE))

// methods
#define ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, METHOD)\
    TYPE_METHOD(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), METHOD)

#define ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_VALUE_ALLOCATOR_METHOD(TYPE, VALUE_ALLOCATOR, METHOD)\
    TYPE_METHOD(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(TYPE, VALUE_ALLOCATOR), METHOD)

#define ATOMICALLY_REFERENCE_COUNTED_METHOD(TYPE, METHOD)\
    TYPE_METHOD(ATOMICALLY_REFERENCE_COUNTED_TYPE(TYPE), METHOD)

// methods declarations
#define DECLARE_ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHODS_WITH_MODIFIER(MODIFIER, TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)\
/* --- Construction/Destruction functions --- */\
MODIFIER struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this);\
MODIFIER struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_copy_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) const* const source);\
MODIFIER struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_move_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const source);\
MODIFIER void*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, destroy_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this);\
/* --- Assign functions --- */\
MODIFIER struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, assign_copy_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) const* const source);\
MODIFIER struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, assign_move_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const source);\
/* --- Swap --- */\
MODIFIER void\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, swap)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const another);\
/* --- Non-default methods --- */\
MODIFIER ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_from_value_pointer_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), value_type)* const pointer);\
MODIFIER ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, assign_from_value_pointer_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), value_type)* const pointer);\
MODIFIER STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), value_type) const*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, get)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) const* const this);\
MODIFIER STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), value_type)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, mut_get)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this);\
MODIFIER STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR), size_type)\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, count_owners)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) const* const this)

#define DECLARE_ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_VALUE_ALLOCATOR_METHODS_WITH_MODIFIER(MODIFIER, TYPE, VALUE_ALLOCATOR)\
    DECLARE_ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHODS_WITH_MODIFIER(MODIFIER, TYPE, VALUE_ALLOCATOR,\
        DEFAULT_ALLOCATOR_TYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR)))

#define DECLARE_ATOMICALLY_REFERENCE_COUNTED_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
    DECLARE_ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_VALUE_ALLOCATOR_METHODS_WITH_MODIFIER(MODIFIER, TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE))

// methods definitions
#define DEFINE_ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHODS_WITH_MODIFIER(MODIFIER, TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)\
/* --- Construction/Destruction functions --- */\
MODIFIER struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this) {\
    ASSERT(this);\
    this->control_block_pointer = NULL;\
    this->value_pointer = NULL;\
    TYPE_METHOD(CONTROL_BLOCK_ALLOCATOR, construct_at)(&this->control_block_allocator);\
    return this;\
}\
MODIFIER struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_copy_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->control_block_pointer = source->control_block_pointer;\
    if (this->control_block_pointer) {\
        ATOMIC_METHOD(usize, fetch_add_explicit)(&this->control_block_pointer->strong_reference_counter,\
            1u, ATOMIC_MEMORY_ORDER_ENUM_VALUE(relaxed));\
    }\
    this->value_pointer = source->value_pointer;\
    TYPE_METHOD(CONTROL_BLOCK_ALLOCATOR, construct_copy_at)(&this->control_block_allocator, &source->control_block_allocator);\
    return this;\
}\
MODIFIER struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_move_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->control_block_pointer = source->control_block_pointer; source->control_block_pointer = NULL;\
    this->value_pointer = source->value_pointer; source->value_pointer = NULL;\
    TYPE_METHOD(CONTROL_BLOCK_ALLOCATOR, construct_move_at)(&this->control_block_allocator, &source->control_block_allocator);\
    return this;\
}\
MODIFIER void*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, destroy_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this) {\
    ASSERT(this);\
    do {\
        if (!this->control_block_pointer) {\
            break;\
        }\
        if (ATOMIC_METHOD(usize, fetch_sub_explicit)(&this->control_block_pointer->strong_reference_counter,\
            1u, ATOMIC_MEMORY_ORDER_ENUM_VALUE(acquire_release))) {\
            break;\
        }\
        TYPE_METHOD(TYPE, destroy_at)(this->value_pointer);\
        TYPE_METHOD(VALUE_ALLOCATOR, deallocate)(&this->control_block_pointer->value_allocator, this->value_pointer, 1u);\
        TYPE_METHOD(VALUE_ALLOCATOR, destroy_at)(&this->control_block_pointer->value_allocator);\
        if (ATOMIC_METHOD(usize, fetch_sub_explicit)(&this->control_block_pointer->weak_reference_counter,\
            1u, ATOMIC_MEMORY_ORDER_ENUM_VALUE(acquire_release))) {\
            break;\
        }\
        TYPE_METHOD(CONTROL_BLOCK_ALLOCATOR, deallocate)(&this->control_block_allocator, this->control_block_pointer, 1u);\
    } while(0);\
    TYPE_METHOD(CONTROL_BLOCK_ALLOCATOR, destroy_at)(&this->control_block_allocator);\
    return this;\
}\
/* --- Assign functions --- */\
MODIFIER struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, assign_copy_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) temporary;\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_copy_at)(&temporary, source);\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, swap)(&temporary, this);\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
MODIFIER struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, assign_move_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) temporary;\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_move_at)(&temporary, source);\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, swap)(&temporary, this);\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
/* --- Swap --- */\
MODIFIER void\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, swap)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const another) {\
    ASSERT(this);\
    ASSERT(another);\
    {\
        STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR),\
            control_block_type)* temporary = this->control_block_pointer;\
        this->control_block_pointer = another->control_block_pointer;\
        another->control_block_pointer = temporary;\
    }\
    {\
        STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR),\
            value_type)* temporary = this->value_pointer;\
        this->value_pointer = another->value_pointer;\
        another->value_pointer = temporary;\
    }\
    TYPE_METHOD(CONTROL_BLOCK_ALLOCATOR, swap)(&this->control_block_allocator, &another->control_block_allocator);\
}\
/* --- Non-default methods --- */\
MODIFIER ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_from_value_pointer_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), value_type)* const pointer) {\
    ASSERT(this);\
    if (!pointer) {\
        return ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_at)(this);\
    }\
    TYPE_METHOD(CONTROL_BLOCK_ALLOCATOR, construct_at)(&this->control_block_allocator);\
    this->control_block_pointer = TYPE_METHOD(CONTROL_BLOCK_ALLOCATOR, allocate)(&this->control_block_allocator, 1u);\
    TYPE_METHOD(VALUE_ALLOCATOR, construct_at)(&this->control_block_pointer->value_allocator);\
    ATOMIC_METHOD(usize, construct_at)(&this->control_block_pointer->strong_reference_counter);\
    ATOMIC_METHOD(usize, construct_at)(&this->control_block_pointer->weak_reference_counter);\
    this->value_pointer = pointer;\
    return this;\
}\
MODIFIER ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, assign_from_value_pointer_at)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), value_type)* const pointer) {\
    ASSERT(this);\
    ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) temporary;\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, construct_from_value_pointer_at)(&temporary, pointer);\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, swap)(&temporary, this);\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
MODIFIER STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), value_type) const*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, get)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) const* const this) {\
    return this->value_pointer;\
}\
MODIFIER STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR), value_type)*\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, mut_get)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR)* const this) {\
    return this->value_pointer;\
}\
MODIFIER STRUCT_SUBTYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR), size_type)\
    ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHOD(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR, count_owners)(\
        struct ATOMICALLY_REFERENCE_COUNTED_TYPE_WITH_CUSTOM_ALLOCATORS(TYPE, VALUE_ALLOCATOR, CONTROL_BLOCK_ALLOCATOR) const* const this) {\
    return this->control_block_pointer ?\
        (ATOMIC_METHOD(usize, load_explicit)(&this->control_block_pointer->strong_reference_counter,\
            ATOMIC_MEMORY_ORDER_ENUM_VALUE(relaxed)) + 1u)\
        : 0u;\
}

#define DEFINE_ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_VALUE_ALLOCATOR_METHODS_WITH_MODIFIER(MODIFIER, TYPE, VALUE_ALLOCATOR)\
    DEFINE_ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_ALLOCATORS_METHODS_WITH_MODIFIER(MODIFIER, TYPE, VALUE_ALLOCATOR,\
        DEFAULT_ALLOCATOR_TYPE(ATOMICALLY_REFERENCE_COUNTED_CONTROL_BLOCK_TYPE_WITH_CUSTOM_VALUE_ALLOCATOR(VALUE_ALLOCATOR)))

#define DEFINE_ATOMICALLY_REFERENCE_COUNTED_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
    DEFINE_ATOMICALLY_REFERENCE_COUNTED_WITH_CUSTOM_VALUE_ALLOCATOR_METHODS_WITH_MODIFIER(MODIFIER, TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE))
