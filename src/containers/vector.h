#pragma once

#include <construct/numeric_helpers.h>

#include <memory/memory.h>

#ifdef DEBUG
    #include <stdio.h>
    #define LOG_DEBUG(MSG) printf(MSG)
    #define LOG_DEBUG_FORMAT(FORMAT_STRING, ...) printf(FORMAT_STRING, __VA_ARGS__)
#else
    #define LOG_DEBUG(MSG) (MSG, 0)
    #define LOG_DEBUG_FORMAT(FORMAT_STRING, ...) (FORMAT_STRING, __VA_ARGS__, 0)
#endif

#define DECLARE_VECTOR(TYPE)\
struct vector_##TYPE;\
/* --- Construction/Destruction functions implementation --- */\
struct vector_##TYPE* vector_##TYPE##_construct_at(struct vector_##TYPE* const this);\
struct vector_##TYPE* vector_##TYPE##_construct_copy_at(struct vector_##TYPE* const this, struct vector_##TYPE* source);\
struct vector_##TYPE* vector_##TYPE##_construct_by_value_at(struct vector_##TYPE* const this, uint const size, TYPE const* const value);\
struct vector_##TYPE* vector_##TYPE##_construct_from_buffer_at(struct vector_##TYPE* const this, uint const buffer_size, TYPE const* const buffer);\
void vector_##TYPE##_destroy_at(struct vector_##TYPE* const this);\
/* --- Memory managment functions implementation --- */\
struct vector_##TYPE* vector_##TYPE##_resize(struct vector_##TYPE* const this, const uint new_size, TYPE const* const value);\
struct vector_##TYPE* vector_##TYPE##_reserve(struct vector_##TYPE* const this, const uint new_capacity);\
struct vector_##TYPE* vector_##TYPE##_clear(struct vector_##TYPE* const this);\
struct vector_##TYPE* vector_##TYPE##_shrink(struct vector_##TYPE* const this);\
void vector_##TYPE##_push_back(struct vector_##TYPE* const this, TYPE const* const value);\
/* --- Getters functions implementation --- */\
uint vector_##TYPE##_size(struct vector_##TYPE const* const this);\
uint vector_##TYPE##_capacity(struct vector_##TYPE const* const this);\
TYPE const* vector_##TYPE##_data(struct vector_##TYPE const* const this);\
TYPE const* vector_##TYPE##_at(struct vector_##TYPE const* const this, uint index);\
TYPE * vector_##TYPE##_mut_at(struct vector_##TYPE* const this, uint index);\
\
typedef struct vector_##TYPE {\
    TYPE* buffer_;\
    uint _size, capacity_;\
} vector_##TYPE

#define IMPLEMENT_VECTOR(TYPE)\
/* --- Construction/Destruction functions implementation --- */\
struct vector_##TYPE* vector_##TYPE##_construct_at(struct vector_##TYPE* const this) {\
    this->buffer_ = NULL;\
    this->_size = this->capacity_ = 0u;\
    return this;\
}\
struct vector_##TYPE* vector_##TYPE##_construct_copy_at(struct vector_##TYPE* const this, struct vector_##TYPE* source) {\
    return vector_##TYPE##_construct_from_buffer_at(this, vector_##TYPE##_size(source), vector_##TYPE##_data(source));\
}\
struct vector_##TYPE* vector_##TYPE##_construct_by_value_at(struct vector_##TYPE* const this, uint const size, TYPE const* const value) {\
    if (!size) {\
        return vector_##TYPE##_construct_at(this);\
    }\
    this->buffer_ = malloc(size * sizeof(TYPE));\
    this->_size = size;\
    this->capacity_ = size;\
    /* Copy elements one-by-one */\
    for (uint index = 0u; index < size; ++index) {\
        TYPE##_construct_copy_at(vector_##TYPE##_mut_at(this, index), value);\
    }\
    return this;\
}\
struct vector_##TYPE* vector_##TYPE##_construct_from_buffer_at(struct vector_##TYPE* const this, uint const buffer_size, TYPE const* const buffer) {\
    if (!buffer_size) {\
        return vector_##TYPE##_construct_at(this);\
    }\
    this->buffer_ = malloc(buffer_size * sizeof(TYPE));\
    this->_size = buffer_size;\
    this->capacity_ = buffer_size;\
    /* Copy elements one-by-one */\
    for (uint index = 0u; index < buffer_size; ++index) {\
        TYPE##_construct_copy_at(vector_##TYPE##_mut_at(this, index), &buffer[index]);\
    }\
    return this;\
}\
void vector_##TYPE##_destroy_at(struct vector_##TYPE* const this) {\
    vector_##TYPE##_clear(this);\
    free(this->buffer_);\
}\
/* --- Memory managment functions implementation --- */\
struct vector_##TYPE* vector_##TYPE##_resize(struct vector_##TYPE* const this, const uint new_size, TYPE const* const value) {\
    if (vector_##TYPE##_size(this) >= new_size) {\
        return this;\
    }\
    vector_##TYPE##_reserve(this, new_size);\
    for (; this->_size < new_size; ++this->_size) {\
        TYPE##_construct_copy_at(vector_##TYPE##_mut_at(this, this->_size), value);\
    }\
    return this;\
}\
struct vector_##TYPE* vector_##TYPE##_reserve(struct vector_##TYPE* const this, const uint new_capacity) {\
    uint current_capacity = vector_##TYPE##_capacity(this);\
    if (current_capacity >= new_capacity) {\
        return this;\
    }\
    if (!current_capacity) current_capacity = 1;\
    while ((current_capacity <<= 1) < new_capacity);\
    TYPE* const new_buffer = malloc(current_capacity * sizeof(TYPE));\
    /* Copy elements one-by-one */\
    for (uint index = 0u; index < vector_##TYPE##_size(this); ++index) {\
        TYPE##_construct_copy_at(&new_buffer[index], vector_##TYPE##_at(this, index));\
    }\
    free(this->buffer_);\
    this->buffer_ = new_buffer;\
    this->capacity_ = current_capacity;\
    return this;\
}\
struct vector_##TYPE* vector_##TYPE##_clear(struct vector_##TYPE* const this) {\
    while (this->_size) {\
        TYPE##_destroy_at(vector_##TYPE##_mut_at(this, --this->_size));\
    }\
    return this;\
}\
struct vector_##TYPE* vector_##TYPE##_shrink(struct vector_##TYPE* const this) {\
    if (vector_##TYPE##_size(this) == vector_##TYPE##_capacity(this)) {\
        return this;\
    }\
    TYPE* const new_buffer = malloc(vector_##TYPE##_size(this) * sizeof(TYPE));\
    /* Copy elements one-by-one */\
    for (uint index = 0u; index < vector_##TYPE##_size(this); ++index) {\
        TYPE##_construct_copy_at(&new_buffer[index], vector_##TYPE##_at(this, index));\
    }\
    free(this->buffer_);\
    this->buffer_ = new_buffer;\
    this->capacity_ = vector_##TYPE##_size(this);\
    return this;\
}\
void vector_##TYPE##_push_back(struct vector_##TYPE* const this, TYPE const* const value) {\
    vector_##TYPE##_resize(this, vector_##TYPE##_size(this) + 1, value);\
}\
/* --- Getters functions implementation --- */\
uint vector_##TYPE##_size(struct vector_##TYPE const* const this) {\
    return this->_size;\
}\
uint vector_##TYPE##_capacity(struct vector_##TYPE const* const this) {\
    return this->capacity_;\
}\
TYPE const* vector_##TYPE##_data(struct vector_##TYPE const* const this) {\
    return this->buffer_;\
}\
TYPE const* vector_##TYPE##_at(struct vector_##TYPE const* const this, uint index) {\
    return this->buffer_ + index;\
}\
TYPE * vector_##TYPE##_mut_at(struct vector_##TYPE* const this, uint index) {\
    return this->buffer_ + index;\
}
