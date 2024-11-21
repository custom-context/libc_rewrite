#pragma once

#include "array_storage_methods.h"

#include <primitives/limits.h>
#include <construct/data_model_helpers.h>

// dynamic array methods implementations
#define DEFINE_DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHODS_WITH_MODIFIER(MODIFIER, TYPE, ALLOCATOR)\
/* --- Construction/Destruction functions --- */\
MODIFIER struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, construct_at)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const this) {\
    return DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, construct_with_capacity_at)(this, 0u);\
}\
MODIFIER struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, construct_with_capacity_at)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR), size_type) const capacity) {\
    ASSERT(this);\
    TYPE_METHOD(ALLOCATOR, construct_at)(&this->allocator);\
    this->storage = TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, capacity);\
    this->capacity = this->storage ? capacity : 0u;\
    return this;\
}\
MODIFIER struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, construct_with_allocator_at)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const this,\
        struct ALLOCATOR const* const allocator) {\
    return DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, construct_with_allocator__capacity_at)(this, allocator, 0u);\
}\
MODIFIER struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, construct_with_allocator__capacity_at)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const this,\
        struct ALLOCATOR const* const allocator,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR), size_type) const capacity) {\
    ASSERT(this);\
    ASSERT(allocator);\
    TYPE_METHOD(ALLOCATOR, construct_copy_at)(&this->allocator, allocator);\
    this->storage = TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, capacity);\
    this->capacity = this->storage ? capacity : 0u;\
    return this;\
}\
MODIFIER struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, construct_copy_at)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const this,\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(false);\
    return this;\
}\
MODIFIER struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, construct_move_at)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const this,\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    TYPE_METHOD(ALLOCATOR, construct_move_at)(&this->allocator, &source->allocator);\
    this->storage = source->storage; source->storage = NULL;\
    this->capacity = source->capacity; source->capacity = 0u;\
    return this;\
}\
MODIFIER void*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, destroy_at)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const this) {\
    ASSERT(this);\
    TYPE_METHOD(ALLOCATOR, deallocate)(&this->allocator, this->storage, this->capacity);\
    TYPE_METHOD(ALLOCATOR, destroy_at)(&this->allocator);\
    return this;\
}\
/* --- Assign functions --- */\
DEFINE_DEFAULT_ASSIGNMENT_METHODS_WITH_MODIFIER(MODIFIER, DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR))\
/* --- Swap --- */\
MODIFIER void\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, swap)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const this,\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    TYPE_METHOD(ALLOCATOR, swap)(&this->allocator, &source->allocator);\
    TYPE_METHOD(voidptr, swap)((voidptr*)&this->storage, (voidptr*)&source->storage);\
    STATIC_ASSERT(SIZEOF(usize) == SIZEOF(this->capacity));\
    TYPE_METHOD(usize, swap)(&this->capacity, &source->capacity);\
}\
/* --- Getters/Setters functions --- */\
MODIFIER struct ALLOCATOR const*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, allocator)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    return &this->allocator;\
}\
MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR), size_type)\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, capacity)(\
    struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    return this->capacity;\
}\
MODIFIER TYPE const*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, data)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    return this->storage;\
}\
MODIFIER TYPE*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, mut_data)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const this) {\
    ASSERT(this);\
    return this->storage;\
}\
MODIFIER TYPE const*\
    DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, at)(\
        struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR), size_type) const position) {\
    ASSERT(this);\
    ASSERT(position < this->capacity);\
    return this->storage + position;\
}\
MODIFIER TYPE* DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHOD(TYPE, ALLOCATOR, mut_at)(\
    struct DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR(TYPE, ALLOCATOR), size_type) const position) {\
    ASSERT(this);\
    ASSERT(position < this->capacity);\
    return this->storage + position;\
}

#define DEFINE_DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHODS(TYPE, ALLOCATOR) DEFINE_DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHODS_WITH_MODIFIER(, TYPE, ALLOCATOR)
#define DEFINE_DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_STATIC_METHODS(TYPE, ALLOCATOR) DEFINE_DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHODS_WITH_MODIFIER(static, TYPE, ALLOCATOR)

#define DEFINE_DYNAMIC_ARRAY_STORAGE_TYPE_STATIC_METHODS(TYPE) DEFINE_DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_STATIC_METHODS(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE))
#define DEFINE_DYNAMIC_ARRAY_STORAGE_TYPE_METHODS(TYPE) DEFINE_DYNAMIC_ARRAY_STORAGE_TYPE__ALLOCATOR_METHODS(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE))
