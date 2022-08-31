#pragma once

#include <construct/numeric_helpers.h>
#include <assert.h>
#include <memory/memory.h>

#define SPECIALIZED_STRING_TYPE(CHAR_TYPE) string_##CHAR_TYPE
#define STRING_TYPE SPECIALIZED_STRING_TYPE(char)

#define DECLARE_SPECIALIZED_STRING(TYPE)\
struct string_##TYPE;\
/* --- Construction/Destruction functions implementation --- */\
struct string_##TYPE* string_##TYPE##_construct_at(struct string_##TYPE* const this);\
struct string_##TYPE* string_##TYPE##_construct_copy_at(struct string_##TYPE* const this, struct string_##TYPE const* const source);\
struct string_##TYPE* string_##TYPE##_construct_by_value_at(struct string_##TYPE* const this, uint const size, TYPE const* const value);\
struct string_##TYPE* string_##TYPE##_construct_from_buffer_at(struct string_##TYPE* const this, uint const buffer_size, TYPE const* const buffer);\
struct string_##TYPE* string_##TYPE##_construct_from_c_string_at(struct string_##TYPE* const this, TYPE const* const buffer);\
void string_##TYPE##_destroy_at(struct string_##TYPE* const this);\
/* --- Memory managment functions implementation --- */\
struct string_##TYPE* string_##TYPE##_resize(struct string_##TYPE* const this, const uint new_size, TYPE const* const value);\
struct string_##TYPE* string_##TYPE##_reserve(struct string_##TYPE* const this, const uint new_capacity);\
struct string_##TYPE* string_##TYPE##_clear(struct string_##TYPE* const this);\
struct string_##TYPE* string_##TYPE##_shrink(struct string_##TYPE* const this);\
void string_##TYPE##_push_back(struct string_##TYPE* const this, TYPE const* const value);\
void string_##TYPE##_pop_back(struct string_##TYPE* const this);\
struct string_##TYPE* string_##TYPE##_apppend_string(struct string_##TYPE* const this, struct string_##TYPE* another_string);\
struct string_##TYPE* string_##TYPE##_apppend_c_string(struct string_##TYPE* const this, char const * const);\
struct string_##TYPE* string_##TYPE##_apppend_buffer(struct string_##TYPE* const this, char const * const, TYPE const* const buffer, uint const buffer_size);\
struct string_##TYPE* string_##TYPE##_apppend_fill(struct string_##TYPE* const this, uint const size, TYPE const* const value);\
/* --- Getters functions implementation --- */\
uint string_##TYPE##_capacity(struct string_##TYPE const* const this);\
uint string_##TYPE##_size(struct string_##TYPE const* const this);\
uint string_##TYPE##_length(struct string_##TYPE const* const this);\
uint string_##TYPE##_empty(struct string_##TYPE const* const this);\
TYPE const* string_##TYPE##_data(struct string_##TYPE const* const this);\
TYPE const* string_##TYPE##_at(struct string_##TYPE const* const this, uint index);\
TYPE * string_##TYPE##_mut_at(struct string_##TYPE* const this, uint index);\
\
typedef struct string_##TYPE {\
    union {\
        struct string_##TYPE##_dynamically_allocated_data {\
            TYPE* buffer_;\
            uint size_;\
            uint capacity_;\
        } dynamic_data_;\
        struct string_##TYPE##_stack_allocated_data {\
            TYPE buffer_[sizeof(struct string_##TYPE##_dynamically_allocated_data) / sizeof(TYPE)];\
        } stack_data_;\
    };\
    uint is_stack_allocated_;\
} string_##TYPE

#define DECLARE_STRING() DECLARE_SPECIALIZED_STRING(char)

#define IMPLEMENT_SPECIALIZED_STRING(TYPE)\
/* --- Construction/Destruction functions implementation --- */\
struct string_##TYPE* string_##TYPE##_construct_at(struct string_##TYPE* const this) {\
    static_assert(sizeof(this->dynamic_data_) / sizeof(TYPE) > 1, "sizeof(" "##TYPE##" ") is higher than size of 3x pointers");\
    this->is_stack_allocated_ = 1;\
    TYPE##_construct_at(string_##TYPE##_mut_at(this, 0u));\
    TYPE const capacity = string_##TYPE##_capacity(this);\
    TYPE##_construct_copy_at(string_##TYPE##_mut_at(this, capacity), (TYPE const* const)&capacity);\
    return this;\
}\
struct string_##TYPE* string_##TYPE##_construct_copy_at(struct string_##TYPE* const this, struct string_##TYPE const* const source) {\
    string_##TYPE##_construct_at(this);\
    string_##TYPE##_reserve(this, string_##TYPE##_size(source));\
    uint const source_string_size = string_##TYPE##_size(source);\
    for (uint index = 0u; index < source_string_size; ++index) {\
        string_##TYPE##_push_back(this, string_##TYPE##_at(source, index));\
    }\
    return this;\
}\
struct string_##TYPE* string_##TYPE##_construct_by_value_at(struct string_##TYPE* const this, uint const size, TYPE const* const value) {\
    string_##TYPE##_construct_at(this);\
    string_##TYPE##_reserve(this, size);\
    for (uint index = 0u; index < size; ++index) {\
        string_##TYPE##_push_back(this, value);\
    }\
    return this;\
}\
struct string_##TYPE* string_##TYPE##_construct_from_buffer_at(struct string_##TYPE* const this, uint const buffer_size, TYPE const* const buffer) {\
    string_##TYPE##_construct_at(this);\
    string_##TYPE##_reserve(this, buffer_size);\
    for (uint index = 0u; index < buffer_size; ++index) {\
        string_##TYPE##_push_back(this, &buffer[index]);\
    }\
    return this;\
}\
struct string_##TYPE* string_##TYPE##_construct_from_c_string_at(struct string_##TYPE* const this, TYPE const* const buffer) {\
    string_##TYPE##_construct_at(this);\
    for (uint index = 0u; buffer[index] != '\0'; ++index) {\
        string_##TYPE##_push_back(this, &buffer[index]);\
    }\
    return this;\
}\
void string_##TYPE##_destroy_at(struct string_##TYPE* const this) {\
    if (!this->is_stack_allocated_) {\
        free(this->dynamic_data_.buffer_);\
    };\
}\
/* --- Memory managment functions implementation --- */\
struct string_##TYPE* string_##TYPE##_resize(struct string_##TYPE* const this, const uint new_size, TYPE const* const value) {\
    if (string_##TYPE##_size(this) >= new_size) {\
        return this;\
    }\
    if (this->is_stack_allocated_) {\
        uint const capacity = string_##TYPE##_capacity(this);\
        if (capacity >= new_size) {\
            for (uint index = string_##TYPE##_size(this); index < new_size; ++index) {\
                TYPE##_construct_copy_at(string_##TYPE##_mut_at(this, index), value);\
            }\
            TYPE##_construct_at(string_##TYPE##_mut_at(this, new_size));\
            TYPE const current_extension_size = capacity - new_size;\
            TYPE##_construct_copy_at(string_##TYPE##_mut_at(this, capacity), (TYPE const* const)(&current_extension_size));\
            return this;\
        }\
    }\
    string_##TYPE##_reserve(this, new_size);\
    for (; this->dynamic_data_.size_ < new_size; ++this->dynamic_data_.size_) {\
        TYPE##_construct_copy_at(string_##TYPE##_mut_at(this, this->dynamic_data_.size_), value);\
    }\
    TYPE##_construct_at(string_##TYPE##_mut_at(this, new_size));\
    return this;\
}\
struct string_##TYPE* string_##TYPE##_reserve(struct string_##TYPE* const this, const uint new_capacity) {\
    uint current_capacity = string_##TYPE##_capacity(this);\
    if (current_capacity++ - 1 >= new_capacity) {\
        return this;\
    }\
    while (((current_capacity <<= 1) - 1) < new_capacity);\
    TYPE* const new_buffer = malloc(current_capacity * sizeof(TYPE));\
    /* Copy elements one-by-one */\
    for (uint index = 0u; index < string_##TYPE##_size(this); ++index) {\
        TYPE##_construct_copy_at(&new_buffer[index], string_##TYPE##_at(this, index));\
    }\
    if (!this->is_stack_allocated_) {\
        free(this->dynamic_data_.buffer_);\
    }\
    this->dynamic_data_.size_ = string_##TYPE##_size(this);\
    this->dynamic_data_.buffer_ = new_buffer;\
    this->dynamic_data_.capacity_ = current_capacity - 1;\
    this->is_stack_allocated_ = 0;\
    return this;\
}\
struct string_##TYPE* string_##TYPE##_clear(struct string_##TYPE* const this) {\
    if (!this->is_stack_allocated_) {\
        this->dynamic_data_.size_ = 0;\
    } else {\
        TYPE const capacity = string_##TYPE##_capacity(this);\
        TYPE##_construct_copy_at(string_##TYPE##_mut_at(this, capacity), (TYPE const* const)&capacity);\
    }\
    TYPE##_construct_at(string_##TYPE##_mut_at(this, string_##TYPE##_capacity(this)));\
    return this;\
}\
struct string_##TYPE* string_##TYPE##_shrink_to_fit(struct string_##TYPE* const this);\
void string_##TYPE##_push_back(struct string_##TYPE* const this, TYPE const* const value) {\
    string_##TYPE##_resize(this, string_##TYPE##_size(this) + 1, value);\
}\
/* --- Getters functions implementation --- */\
uint string_##TYPE##_capacity(struct string_##TYPE const* const this) {\
    if (this->is_stack_allocated_) {\
        return (sizeof(this->dynamic_data_) / sizeof(TYPE)) - 1;\
    }\
    return this->dynamic_data_.capacity_;\
}\
uint string_##TYPE##_size(struct string_##TYPE const* const this) {\
    if (this->is_stack_allocated_) {\
        uint const capacity = string_##TYPE##_capacity(this);\
        return (capacity - *string_##TYPE##_at(this, capacity));\
    }\
    return this->dynamic_data_.size_;\
}\
uint string_##TYPE##_length(struct string_##TYPE const* const this) {\
    return string_##TYPE##_size(this);\
}\
uint string_##TYPE##_empty(struct string_##TYPE const* const this) {\
    return string_##TYPE##_size(this);\
}\
TYPE const* string_##TYPE##_data(struct string_##TYPE const* const this) {\
    return string_##TYPE##_at(this, 0u);\
}\
TYPE const* string_##TYPE##_at(struct string_##TYPE const* const this, uint index) {\
    if (this->is_stack_allocated_) {\
        return this->stack_data_.buffer_ + index;\
    }\
    return this->dynamic_data_.buffer_ + index;\
}\
TYPE * string_##TYPE##_mut_at(struct string_##TYPE* const this, uint index) {\
    if (this->is_stack_allocated_) {\
        return this->stack_data_.buffer_ + index;\
    }\
    return this->dynamic_data_.buffer_ + index;\
}\

#define IMPLEMENT_STRING() IMPLEMENT_SPECIALIZED_STRING(char)
