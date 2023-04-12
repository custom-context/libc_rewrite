#pragma once

#include <primitives/limits.h>

// dynamic array methods implementations
#define IMPLEMENT_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE, ALLOCATOR_TYPE)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct ALLOCATOR_TYPE const* const allocator) {\
    ASSERT(this);\
    ASSERT(allocator);\
    TYPE_METHOD(ALLOCATOR_TYPE, construct_copy_at)(&this->allocator, allocator);\
    this->buffer = NULL;\
    this->size = this->capacity = 0u;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    TYPE_METHOD(ALLOCATOR_TYPE, construct_at)(&this->allocator);\
    this->buffer = NULL;\
    this->size = this->capacity = 0u;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_copying_from_buffer_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        TYPE const* const buffer,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const buffer_size);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_copy_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source,\
        struct ALLOCATOR_TYPE const* const allocator) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(allocator);\
    TYPE_METHOD(ALLOCATOR_TYPE, construct_copy_at)(&this->allocator, allocator);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_copying_from_buffer_at)(this, source->buffer, source->size);\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source) {\
    return DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_copy_with_allocator_at)(this, source, &source->allocator);\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    TYPE_METHOD(ALLOCATOR_TYPE, construct_move_at)(&this->allocator, &source->allocator);\
    this->buffer = source->buffer; source->buffer = NULL;\
    this->size = source->size; source->size = 0u;\
    this->capacity = source->capacity; source->capacity = 0u;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_move_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source,\
        struct ALLOCATOR_TYPE const* const allocator) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(allocator);\
    TYPE_METHOD(ALLOCATOR_TYPE, construct_copy_at)(&this->allocator, allocator);\
    this->buffer = source->buffer; source->buffer = NULL;\
    this->size = source->size; source->size = 0u;\
    this->capacity = source->capacity; source->capacity = 0u;\
    return this;\
}\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, resize)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const new_size,\
    TYPE const* const value);\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_value_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const count,\
        TYPE const* const value) {\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_at)(this);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, resize)(this, count, value);\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_value_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const count,\
        TYPE const* const value,\
        struct ALLOCATOR_TYPE const* const allocator) {\
    ASSERT(this);\
    ASSERT(allocator);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_with_allocator_at)(this, allocator);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, resize)(this, count, value);\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_copying_from_buffer_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        TYPE const* const buffer,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const buffer_size) {\
    ASSERT(this);\
    ASSERT(buffer);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_at)(this);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, reserve)(this, buffer_size);\
    for (STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) index = 0u;\
        index < buffer_size; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(\
            DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, PRIVATE(unsafe_mut_at))(this, index),\
            buffer + index\
        );\
    }\
    this->size = buffer_size;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_copying_from_buffer_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        TYPE const* const buffer,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type)  const buffer_size,\
        struct ALLOCATOR_TYPE const* const allocator) {\
    ASSERT(this);\
    ASSERT(buffer);\
    ASSERT(allocator);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_with_allocator_at)(this, allocator);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, reserve)(this, buffer_size);\
    for (STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type)  index = 0u; index < buffer_size; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(\
            DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, PRIVATE(unsafe_mut_at))(this, index),\
            buffer + index\
        );\
    }\
    this->size = buffer_size;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_moving_from_buffer_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        TYPE* const buffer,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const buffer_size) {\
    ASSERT(this);\
    ASSERT(buffer);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_at)(this);\
    this->buffer = buffer;\
    this->capacity = this->size = buffer_size;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_by_moving_from_buffer_with_allocator_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        TYPE* const buffer,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const buffer_size,\
        struct ALLOCATOR_TYPE const* const allocator) {\
    ASSERT(this);\
    ASSERT(buffer);\
    ASSERT(allocator);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_with_allocator_at)(this, allocator);\
    this->buffer = buffer;\
    this->capacity = this->size = buffer_size;\
    return this;\
}\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, clear)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this);\
COMMON_MODIFIER void* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, destroy_at)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, clear)(this);\
    TYPE_METHOD(ALLOCATOR_TYPE, deallocate)(&this->allocator, this->buffer, this->capacity);\
    return this;\
}\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, swap)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    {\
        TYPE* temporary = this->buffer;\
        this->buffer = source->buffer;\
        source->buffer = temporary;\
    }\
    {\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) temporary = this->size;\
        this->size = source->size;\
        source->size = temporary;\
    }\
    {\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) temporary = this->capacity;\
        this->capacity = source->capacity;\
        source->capacity = temporary;\
    }\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, assign_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) temporary;\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_copy_at)(&temporary, source);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, swap)(this, &temporary);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, destroy_at)(&temporary);\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, assign_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) temporary;\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_move_at)(&temporary, source);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, swap)(this, &temporary);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, destroy_at)(&temporary);\
    return this;\
}\
/* --- Memory managment functions --- */\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, reserve)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const new_capacity) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) current_capacity =\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, capacity)(this);\
    if (current_capacity >= new_capacity) {\
        return;\
    }\
    if (new_capacity < (MAX_VALUE(usize) >> 1)) {\
        if (!current_capacity) current_capacity = 1;\
        while ((current_capacity <<= 1) < new_capacity);\
    } else {\
        current_capacity = new_capacity;\
    }\
    TYPE* const new_buffer = TYPE_METHOD(ALLOCATOR_TYPE, allocate)(&this->allocator, current_capacity);\
    /* Copy elements one-by-one */\
    for (STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) index = 0u;\
        index < DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(this); ++index) {\
        TYPE_METHOD(TYPE, construct_move_at)(\
            new_buffer + index,\
            DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, mut_at)(this, index)\
        );\
    }\
    TYPE_METHOD(ALLOCATOR_TYPE, deallocate)(&this->allocator,\
        this->buffer,\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, capacity)(this)\
    );\
    this->buffer = new_buffer;\
    this->capacity = current_capacity;\
}\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, resize)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const new_size,\
    TYPE const* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, reserve)(this, new_size);\
    for (; this->size < new_size; ++this->size) {\
        TYPE_METHOD(TYPE, construct_copy_at)(\
            this->buffer + this->size,\
            value\
        );\
    }\
}\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, push_back_by_copying)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    TYPE const* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, resize)(\
        this,\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(this) + 1,\
        value\
    );\
}\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, push_back_by_moving)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    TYPE* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, reserve)(this,\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(this) + 1\
    );\
    \
    TYPE_METHOD(TYPE, construct_move_at)(\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, PRIVATE(unsafe_mut_at))(\
            this,\
            this->size++\
        ),\
        value\
    );\
}\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, shrink_to_fit)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    if (\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(this) ==\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, capacity)(this)\
    ) {\
        return;\
    }\
    \
    TYPE* const new_buffer = TYPE_METHOD(ALLOCATOR_TYPE, allocate)(\
        &this->allocator,\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(this)\
    );\
    /* Copy elements one-by-one */\
    for (STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) index = 0u;\
        index < DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(this); ++index) {\
        TYPE_METHOD(TYPE, construct_move_at)(\
            new_buffer + index,\
            DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, mut_at)(this, index)\
        );\
    }\
    TYPE_METHOD(ALLOCATOR_TYPE, deallocate)(&this->allocator,\
        this->buffer,\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, capacity)(this)\
    );\
    this->buffer = new_buffer;\
    this->capacity = DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(this);\
}\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, clear)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    while (this->size) {\
        TYPE_METHOD(TYPE, destroy_at)(\
            DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, mut_at)(this, this->size - 1u)\
        );\
        this->size--;\
    }\
}\
COMMON_MODIFIER void DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, pop_back)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    if (this->size) {\
        TYPE_METHOD(TYPE, destroy_at)(\
            DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, mut_at)(this, --this->size)\
        );\
    }\
}\
/* --- Getters/Setters functions --- */\
COMMON_MODIFIER struct ALLOCATOR_TYPE const* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, get_allocator)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    ASSERT(this);\
    return &this->allocator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, capacity)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    ASSERT(this);\
    return this->capacity;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    ASSERT(this);\
    return this->size;\
}\
COMMON_MODIFIER TYPE const* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, data)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    ASSERT(this);\
    return this->buffer;\
}\
COMMON_MODIFIER TYPE const* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, at)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const position) {\
    ASSERT(this);\
    ASSERT(this->size > position);\
    return this->buffer + position;\
}\
COMMON_MODIFIER TYPE* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, PRIVATE(unsafe_mut_at))(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const position) {\
    ASSERT(this);\
    return this->buffer + position;\
}\
COMMON_MODIFIER TYPE* DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, mut_at)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type) const position) {\
    ASSERT(this);\
    ASSERT(this->size > position);\
    return this->buffer + position;\
}\
/* --- Mutable iterators' related functions --- */\
/* --- --- Container's specific methods --- --- */\
DECLARE_RANDOM_ACCESS_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, ALLOCATOR_TYPE, DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)) {\
    ASSERT(this);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_at)(this);\
    /* reserve memory for O(1) offset calculation */\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) offset =\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, offset)(&end, &begin);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, reserve)(this,\
        (STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type))offset);\
    /* push values from iterators by moving */\
    while(TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), compare)(&begin, &end)) {\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) current = \
            DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, next)(&begin);\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, push_back_by_moving)(this,\
            DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, value)(&current)\
        );\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, destroy_at)(&current);\
    }\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, begin)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator;\
    iterator.pointer_to_element = this->buffer;\
    return iterator;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, end)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator;\
    iterator.pointer_to_element = this->buffer + this->size;\
    return iterator;\
}\
/* --- --- Iterator's specific methods --- --- */\
/*DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*/\
/* --- --- --- Construction/Destruction functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    this->pointer_to_element = NULL;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pointer_to_element = source->pointer_to_element;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    return TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_copy_at)(this, source);\
}\
COMMON_MODIFIER void* TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), destroy_at)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    return this;\
}\
/* --- --- --- Assign functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pointer_to_element = source->pointer_to_element;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    return TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_copy_at)(this, source);\
}\
/* --- --- --- Element access functions --- --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    return this->pointer_to_element;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type) const*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), const_value)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    ASSERT(this);\
    return this->pointer_to_element;\
}\
/* --- --- --- Compare functions --- --- --- */\
/* return 0 if equals, !0 either (for random-access iterators 1 if iterator_1 > iterator_2 & -1 if iterator_1 < iterator_2)*/\
COMMON_MODIFIER int TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), compare)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const iterator_1,\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const iterator_2) {\
    ASSERT(iterator_1);\
    ASSERT(iterator_2);\
    return (int)(iterator_1->pointer_to_element - iterator_2->pointer_to_element);\
}\
/* --- --- --- Increment functions --- --- --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), next)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    ++this->pointer_to_element;\
    return *this;\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), pnext)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element++\
    };\
    return iterator;\
}\
/* --- --- --- Decrement functions --- --- --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), prev)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    --this->pointer_to_element;\
    return *this;\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), pprev)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element--\
    };\
    return iterator;\
}\
/* --- --- --- Assign functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), add_in_place)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    this->pointer_to_element += offset;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), sub_in_place)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    this->pointer_to_element -= offset;\
    return this;\
}\
/* --- --- --- Shift functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), add)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element + offset\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), sub)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element - offset\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), offset)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const another_iterator) {\
    ASSERT(this);\
    ASSERT(another_iterator);\
    return this->pointer_to_element - another_iterator->pointer_to_element;\
}\
/* --- --- --- Element access functions --- --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), mut_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    return this->pointer_to_element + offset;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type) const*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    return this->pointer_to_element + offset;\
}\
/* --- Const iterators' related functions --- */\
/* --- --- Container's specific methods --- --- */\
DECLARE_RANDOM_ACCESS_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_CONSTRUCT_BY_ITERATORS(TYPE, ALLOCATOR_TYPE, DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)) {\
    ASSERT(this);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, construct_at)(this);\
    /* reserve memory for O(1) offset calculation */\
    STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) offset =\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, offset)(&end, &begin);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, reserve)(this,\
        (STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE), size_type))offset);\
    /* push values from iterators by moving */\
    while(TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), compare)(&begin, &end)) {\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) current = \
            DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, next)(&begin);\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, push_back_by_copying)(this,\
            DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, value)(&current)\
        );\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, destroy_at)(&current);\
    }\
    return this;\
}\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_MOVE_BY(TYPE, ALLOCATOR_TYPE,\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE),\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)) {\
    ASSERT(this);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, reserve)(this,\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(this) + 1u);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator =\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, end)(this);\
    while (iterator.pointer_to_element != position.pointer_to_element) {\
        TYPE_METHOD(TYPE, construct_move_at)(iterator.pointer_to_element, --iterator.pointer_to_element);\
    }\
    TYPE_METHOD(TYPE, construct_move_at)(iterator.pointer_to_element, value);\
    ++this->size;\
    return iterator;\
}\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COUNT_COPY_BY(TYPE, ALLOCATOR_TYPE,\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE),\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE));\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COPY_BY(TYPE, ALLOCATOR_TYPE,\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE),\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)) {\
    return DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COUNT_COPY_BY(TYPE, ALLOCATOR_TYPE,\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    )(this, position, 1u, value);\
}\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_INSERT_COUNT_COPY_BY(TYPE, ALLOCATOR_TYPE,\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE),\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator;\
    if (!count) {\
        iterator.pointer_to_element = position.pointer_to_element;\
        return iterator;\
    }\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, reserve)(this,\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, size)(this) + count);\
    iterator =\
        DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, end)(this);\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_METHOD(TYPE, ALLOCATOR_TYPE, add_in_place)(&iterator,\
        (STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type))(count - 1u));\
    while ((iterator.pointer_to_element - count + 1u) != position.pointer_to_element) {\
        TYPE_METHOD(TYPE, construct_move_at)(iterator.pointer_to_element, (--iterator.pointer_to_element) - count + 1u);\
    }\
    do {\
        TYPE_METHOD(TYPE, construct_copy_at)(iterator.pointer_to_element, value);\
    } while (iterator.pointer_to_element-- != position.pointer_to_element);\
    this->size += count;\
    return iterator;\
}\
COMMON_MODIFIER DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_ERASE_BY(TYPE, ALLOCATOR_TYPE,\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE),\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = position.pointer_to_element\
    };\
    if (position.pointer_to_element == DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, end)(this).pointer_to_element) {\
        return iterator;\
    }\
    while (iterator.pointer_to_element != DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, end)(this).pointer_to_element - 1u) {\
        TYPE_METHOD(TYPE, assign_move_at)(iterator.pointer_to_element, ++iterator.pointer_to_element);\
    }\
    TYPE_METHOD(TYPE, destroy_at)(iterator.pointer_to_element);\
    --this->size;\
    iterator.pointer_to_element = position.pointer_to_element;\
    return iterator;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, cbegin)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->buffer\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, cend)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->buffer + this->size\
    };\
    return iterator;\
}\
/* --- --- Iterator's specific methods --- --- */\
/*DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*/\
/* --- --- --- Construction/Destruction functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    this->pointer_to_element = NULL;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pointer_to_element = source->pointer_to_element;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    return TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_copy_at)(this, source);\
}\
COMMON_MODIFIER void* TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), destroy_at)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    return this;\
}\
/* --- --- --- Assign functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pointer_to_element = source->pointer_to_element;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    return TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_copy_at)(this, source);\
}\
/* --- --- --- Element access functions --- --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    return this->pointer_to_element;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type) const*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), const_value)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    ASSERT(this);\
    return this->pointer_to_element;\
}\
/* --- --- --- Compare functions --- --- --- */\
/* return 0 if equals, !0 either (for random-access iterators 1 if iterator_1 > iterator_2 & -1 if iterator_1 < iterator_2)*/\
COMMON_MODIFIER int TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), compare)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const iterator_1,\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const iterator_2) {\
    ASSERT(iterator_1);\
    ASSERT(iterator_2);\
    return (int)(iterator_1->pointer_to_element - iterator_2->pointer_to_element);\
}\
/* --- --- --- Increment functions --- --- --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), next)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    ++this->pointer_to_element;\
    return *this;\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), pnext)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element++\
    };\
    return iterator;\
}\
/* --- --- --- Decrement functions --- --- --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), prev)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    --this->pointer_to_element;\
    return *this;\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), pprev)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element--\
    };\
    return iterator;\
}\
/* --- --- --- Assign functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), add_in_place)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    this->pointer_to_element += offset;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), sub_in_place)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    this->pointer_to_element -= offset;\
    return this;\
}\
/* --- --- --- Shift functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), add)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element + offset\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), sub)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element - offset\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), offset)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const another_iterator) {\
    ASSERT(this);\
    ASSERT(another_iterator);\
    return this->pointer_to_element - another_iterator->pointer_to_element;\
}\
/* --- --- --- Element access functions --- --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), mut_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    return this->pointer_to_element + offset;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type) const*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    return this->pointer_to_element + offset;\
}\
/* --- Mutable reverse iterators' related functions --- */\
/* --- --- Container's specific methods --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, rbegin)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->buffer + this->size - 1u\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, rend)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->buffer - 1u\
    };\
    return iterator;\
}\
/* --- --- Iterator's specific methods --- --- */\
/*DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*/\
/* --- --- --- Construction/Destruction functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    this->pointer_to_element = NULL;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pointer_to_element = source->pointer_to_element;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    return TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_copy_at)(this, source);\
}\
COMMON_MODIFIER void* TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), destroy_at)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    return this;\
}\
/* --- --- --- Assign functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pointer_to_element = source->pointer_to_element;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    return TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_copy_at)(this, source);\
}\
/* --- --- --- Element access functions --- --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    return this->pointer_to_element;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type) const*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), const_value)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    ASSERT(this);\
    return this->pointer_to_element;\
}\
/* --- --- --- Compare functions --- --- --- */\
/* return 0 if equals, !0 either (for random-access iterators 1 if iterator_1 > iterator_2 & -1 if iterator_1 < iterator_2)*/\
COMMON_MODIFIER int TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), compare)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const iterator_1,\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const iterator_2) {\
    ASSERT(iterator_1);\
    ASSERT(iterator_2);\
    return (int)(iterator_1->pointer_to_element - iterator_2->pointer_to_element);\
}\
/* --- --- --- Increment functions --- --- --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), next)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    --this->pointer_to_element;\
    return *this;\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), pnext)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element--\
    };\
    return iterator;\
}\
/* --- --- --- Decrement functions --- --- --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), prev)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    ++this->pointer_to_element;\
    return *this;\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), pprev)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element++\
    };\
    return iterator;\
}\
/* --- --- --- Assign functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), add_in_place)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    this->pointer_to_element -= offset;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), sub_in_place)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    this->pointer_to_element += offset;\
    return this;\
}\
/* --- --- --- Shift functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), add)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element - offset\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), sub)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element + offset\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), offset)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const another_iterator) {\
    ASSERT(this);\
    ASSERT(another_iterator);\
    return this->pointer_to_element - another_iterator->pointer_to_element;\
}\
/* --- --- --- Element access functions --- --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), mut_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    return this->pointer_to_element + offset;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type) const*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    return this->pointer_to_element + offset;\
}\
/* --- Reverse const iterators' related functions --- */\
/* --- --- Container's specific methods --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, crbegin)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->buffer + this->size - 1u\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_METHOD(TYPE, ALLOCATOR_TYPE, crend)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->buffer - 1u\
    };\
    return iterator;\
}\
/* --- --- Iterator's specific methods --- --- */\
/*DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*/\
/* --- --- --- Construction/Destruction functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    this->pointer_to_element = NULL;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pointer_to_element = source->pointer_to_element;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    return TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), construct_copy_at)(this, source);\
}\
COMMON_MODIFIER void* TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), destroy_at)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    return this;\
}\
/* --- --- --- Assign functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_copy_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->pointer_to_element = source->pointer_to_element;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_move_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const source) {\
    return TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), assign_copy_at)(this, source);\
}\
/* --- --- --- Element access functions --- --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    return this->pointer_to_element;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type) const*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), const_value)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this) {\
    ASSERT(this);\
    return this->pointer_to_element;\
}\
/* --- --- --- Compare functions --- --- --- */\
/* return 0 if equals, !0 either (for random-access iterators 1 if iterator_1 > iterator_2 & -1 if iterator_1 < iterator_2)*/\
COMMON_MODIFIER int TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), compare)(\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const iterator_1,\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const iterator_2) {\
    ASSERT(iterator_1);\
    ASSERT(iterator_2);\
    return (int)(iterator_1->pointer_to_element - iterator_2->pointer_to_element);\
}\
/* --- --- --- Increment functions --- --- --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), next)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    --this->pointer_to_element;\
    return *this;\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), pnext)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element--\
    };\
    return iterator;\
}\
/* --- --- --- Decrement functions --- --- --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), prev)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    ++this->pointer_to_element;\
    return *this;\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), pprev)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element++\
    };\
    return iterator;\
}\
/* --- --- --- Assign functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), add_in_place)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    this->pointer_to_element -= offset;\
    return this;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), sub_in_place)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    this->pointer_to_element += offset;\
    return this;\
}\
/* --- --- --- Shift functions --- --- --- */\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), add)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element - offset\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), sub)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) iterator = {\
        .pointer_to_element = this->pointer_to_element + offset\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type)\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), offset)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const another_iterator) {\
    ASSERT(this);\
    ASSERT(another_iterator);\
    return this->pointer_to_element - another_iterator->pointer_to_element;\
}\
/* --- --- --- Element access functions --- --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type)*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), mut_at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE)* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    return this->pointer_to_element + offset;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), value_type) const*\
    TYPE_METHOD(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), at)(\
        struct DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE) const* const this,\
        STRUCT_SUBTYPE(DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_REVERSE_CONST_ITERATOR_TYPE(TYPE, ALLOCATOR_TYPE), difference_type) const offset) {\
    ASSERT(this);\
    return this->pointer_to_element + offset;\
}

#define IMPLEMENT_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS(TYPE, ALLOCATOR_TYPE) IMPLEMENT_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS_WITH_MODIFIER(, TYPE, ALLOCATOR_TYPE)
#define IMPLEMENT_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_STATIC_METHODS(TYPE, ALLOCATOR_TYPE) IMPLEMENT_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS_WITH_MODIFIER(static, TYPE, ALLOCATOR_TYPE)

#define IMPLEMENT_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(TYPE) IMPLEMENT_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_STATIC_METHODS(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE))
#define IMPLEMENT_DYNAMIC_ARRAY_TYPE_METHODS(TYPE) IMPLEMENT_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS(TYPE, DEFAULT_ALLOCATOR_TYPE(TYPE))
