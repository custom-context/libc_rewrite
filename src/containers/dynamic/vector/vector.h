#pragma once

#include <containers/dynamic/common.h>

#define VECTOR_TYPE(TYPE) NAMESPACE_CONTAINERS_DYNAMIC(CONCAT3(vector, _, TYPE))
#define VECTOR_METHOD(TYPE, METHOD) TYPE_METHOD(VECTOR_TYPE(TYPE), METHOD)

#define DECLARE_VECTOR(TYPE)\
struct VECTOR_TYPE(TYPE);\
/* --- Construction/Destruction functions implementation --- */\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, construct_at)(struct VECTOR_TYPE(TYPE)* const this);\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, construct_copy_at)(struct VECTOR_TYPE(TYPE)* const this, struct VECTOR_TYPE(TYPE) const* const source);\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, construct_by_value_at)(struct VECTOR_TYPE(TYPE)* const this, uint const size, TYPE const* const value);\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, construct_from_buffer_at)(struct VECTOR_TYPE(TYPE)* const this, uint const buffer_size, TYPE const* const buffer);\
void* VECTOR_METHOD(TYPE, destroy_at)(struct VECTOR_TYPE(TYPE)* const this);\
/* --- Memory managment functions implementation --- */\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, resize)(struct VECTOR_TYPE(TYPE)* const this, const uint new_size, TYPE const* const value);\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, reserve)(struct VECTOR_TYPE(TYPE)* const this, const uint new_capacity);\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, clear)(struct VECTOR_TYPE(TYPE)* const this);\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, shrink)(struct VECTOR_TYPE(TYPE)* const this);\
void VECTOR_METHOD(TYPE, push_back)(struct VECTOR_TYPE(TYPE)* const this, TYPE const* const value);\
/* --- Getters functions implementation --- */\
uint VECTOR_METHOD(TYPE, size)(struct VECTOR_TYPE(TYPE) const* const this);\
uint VECTOR_METHOD(TYPE, capacity)(struct VECTOR_TYPE(TYPE) const* const this);\
TYPE const* VECTOR_METHOD(TYPE, data)(struct VECTOR_TYPE(TYPE) const* const this);\
TYPE const* VECTOR_METHOD(TYPE, at)(struct VECTOR_TYPE(TYPE) const* const this, uint index);\
TYPE * VECTOR_METHOD(TYPE, mut_at)(struct VECTOR_TYPE(TYPE)* const this, uint index);\
\
typedef struct VECTOR_TYPE(TYPE) {\
    TYPE* buffer_;\
    uint size_, capacity_;\
} VECTOR_TYPE(TYPE)

#define IMPLEMENT_VECTOR(TYPE)\
/* --- Construction/Destruction functions implementation --- */\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, construct_at)(struct VECTOR_TYPE(TYPE)* const this) {\
    this->buffer_ = NULL;\
    this->size_ = this->capacity_ = 0u;\
    return this;\
}\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, construct_copy_at)(struct VECTOR_TYPE(TYPE)* const this, struct VECTOR_TYPE(TYPE) const* const source) {\
    return VECTOR_METHOD(TYPE, construct_from_buffer_at)(this, VECTOR_METHOD(TYPE, size)(source), VECTOR_METHOD(TYPE, data(source)));\
}\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, construct_by_value_at)(struct VECTOR_TYPE(TYPE)* const this, uint const size, TYPE const* const value) {\
    if (!size) {\
        return VECTOR_METHOD(TYPE, construct_at)(this);\
    }\
    this->buffer_ = malloc(size * sizeof(TYPE));\
    this->size_ = size;\
    this->capacity_ = size;\
    /* Copy elements one-by-one */\
    for (uint index = 0u; index < size; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(VECTOR_METHOD(TYPE, mut_at)(this, index), value);\
    }\
    return this;\
}\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, construct_from_buffer_at)(struct VECTOR_TYPE(TYPE)* const this, uint const buffer_size, TYPE const* const buffer) {\
    if (!buffer_size) {\
        return VECTOR_METHOD(TYPE, construct_at)(this);\
    }\
    this->buffer_ = malloc(buffer_size * sizeof(TYPE));\
    this->size_ = buffer_size;\
    this->capacity_ = buffer_size;\
    /* Copy elements one-by-one */\
    for (uint index = 0u; index < buffer_size; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(VECTOR_METHOD(TYPE, mut_at)(this, index), &buffer[index]);\
    }\
    return this;\
}\
void* VECTOR_METHOD(TYPE, destroy_at)(struct VECTOR_TYPE(TYPE)* const this) {\
    VECTOR_METHOD(TYPE, clear)(this);\
    free(this->buffer_);\
    return this;\
}\
/* --- Memory managment functions implementation --- */\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, resize)(struct VECTOR_TYPE(TYPE)* const this, const uint new_size, TYPE const* const value) {\
    if (VECTOR_METHOD(TYPE, size)(this) >= new_size) {\
        return this;\
    }\
    VECTOR_METHOD(TYPE, reserve)(this, new_size);\
    for (; this->size_ < new_size; ++this->size_) {\
        TYPE_METHOD(TYPE, construct_copy_at)(VECTOR_METHOD(TYPE, mut_at)(this, this->size_), value);\
    }\
    return this;\
}\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, reserve)(struct VECTOR_TYPE(TYPE)* const this, const uint new_capacity) {\
    uint current_capacity = VECTOR_METHOD(TYPE, capacity)(this);\
    if (current_capacity >= new_capacity) {\
        return this;\
    }\
    if (!current_capacity) current_capacity = 1;\
    while ((current_capacity <<= 1) < new_capacity);\
    TYPE* const new_buffer = malloc(current_capacity * sizeof(TYPE));\
    /* Copy elements one-by-one */\
    for (uint index = 0u; index < VECTOR_METHOD(TYPE, size)(this); ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(&new_buffer[index], VECTOR_METHOD(TYPE, at)(this, index));\
    }\
    free(this->buffer_);\
    this->buffer_ = new_buffer;\
    this->capacity_ = current_capacity;\
    return this;\
}\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, clear)(struct VECTOR_TYPE(TYPE)* const this) {\
    while (this->size_) {\
        TYPE_METHOD(TYPE, destroy_at)(VECTOR_METHOD(TYPE, mut_at)(this, --this->size_));\
    }\
    return this;\
}\
struct VECTOR_TYPE(TYPE)* VECTOR_METHOD(TYPE, shrink)(struct VECTOR_TYPE(TYPE)* const this) {\
    if (VECTOR_METHOD(TYPE, size)(this) == VECTOR_METHOD(TYPE, capacity)(this)) {\
        return this;\
    }\
    TYPE* const new_buffer = malloc(VECTOR_METHOD(TYPE, size)(this) * sizeof(TYPE));\
    /* Copy elements one-by-one */\
    for (uint index = 0u; index < VECTOR_METHOD(TYPE, size)(this); ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(&new_buffer[index], VECTOR_METHOD(TYPE, at)(this, index));\
    }\
    free(this->buffer_);\
    this->buffer_ = new_buffer;\
    this->capacity_ = VECTOR_METHOD(TYPE, size)(this);\
    return this;\
}\
void VECTOR_METHOD(TYPE, push_back)(struct VECTOR_TYPE(TYPE)* const this, TYPE const* const value) {\
    VECTOR_METHOD(TYPE, resize)(this, VECTOR_METHOD(TYPE, size)(this) + 1, value);\
}\
/* --- Getters functions implementation --- */\
uint VECTOR_METHOD(TYPE, size)(struct VECTOR_TYPE(TYPE) const* const this) {\
    return this->size_;\
}\
uint VECTOR_METHOD(TYPE, capacity)(struct VECTOR_TYPE(TYPE) const* const this) {\
    return this->capacity_;\
}\
TYPE const* VECTOR_METHOD(TYPE, data)(struct VECTOR_TYPE(TYPE) const* const this) {\
    return this->buffer_;\
}\
TYPE const* VECTOR_METHOD(TYPE, at)(struct VECTOR_TYPE(TYPE) const* const this, uint index) {\
    return this->buffer_ + index;\
}\
TYPE * VECTOR_METHOD(TYPE, mut_at)(struct VECTOR_TYPE(TYPE)* const this, uint index) {\
    return this->buffer_ + index;\
}
