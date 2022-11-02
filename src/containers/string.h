#pragma once

#include <construct/numeric_helpers.h>
#include <utils/macros.h>
#include <utils/debug.h>
#include <utils/string/c_string_helpers.h>
#include <memory/memory.h>

// define macros for `string_type`
#define SPECIALIZED_STRING_TYPE_(CHAR_TYPE) CONCAT3(string, _, CHAR_TYPE)
#define SPECIALIZED_STRING_TYPE(CHAR_TYPE) SPECIALIZED_STRING_TYPE_(CHAR_TYPE)

#define STRING_TYPE() SPECIALIZED_STRING_TYPE(char)

// define macros for `struct string_type`
#define SPECIALIZED_STRING_STRUCT_TYPE_(CHAR_TYPE) struct SPECIALIZED_STRING_TYPE(CHAR_TYPE)
#define SPECIALIZED_STRING_STRUCT_TYPE(CHAR_TYPE) SPECIALIZED_STRING_STRUCT_TYPE_(CHAR_TYPE)

#define STRING_STRUCT_TYPE() SPECIALIZED_STRING_STRUCT_TYPE(char)

// define macros for string methods
#define SPECIALIZED_STRING_METHOD_(CHAR_TYPE, METHOD) TYPE_METHOD(SPECIALIZED_STRING_TYPE(CHAR_TYPE), METHOD)
#define SPECIALIZED_STRING_METHOD(CHAR_TYPE, METHOD) SPECIALIZED_STRING_METHOD_(CHAR_TYPE, METHOD)

#define STRING_METHOD(METHOD) SPECIALIZED_STRING_METHOD(char, METHOD)

// define macro for string type & string methods declaration
#define DECLARE_SPECIALIZED_STRING_(TYPE)\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE);\
/* --- Construction/Destruction functions implementation --- */\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_copy_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const source);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_by_value_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, uint const size, TYPE const* const value);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_from_buffer_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, uint const buffer_size, TYPE const* const buffer);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_from_c_string_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, TYPE const* const buffer);\
void SPECIALIZED_STRING_METHOD(TYPE, destroy_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this);\
/* --- Memory managment functions implementation --- */\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, resize)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, const uint new_size, TYPE const* const value);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, reserve)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, const uint new_capacity);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, clear)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, shrink)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this);\
void SPECIALIZED_STRING_METHOD(TYPE, push_back)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, TYPE const* const value);\
void SPECIALIZED_STRING_METHOD(TYPE, pop_back)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_string)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* another_string);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_c_string)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, TYPE const * const);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_buffer)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, TYPE const* const buffer, uint const buffer_size);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_fill)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, uint const size, TYPE const* const value);\
/* --- Getters functions implementation --- */\
uint SPECIALIZED_STRING_METHOD(TYPE, capacity)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this);\
uint SPECIALIZED_STRING_METHOD(TYPE, size)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this);\
uint SPECIALIZED_STRING_METHOD(TYPE, length)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this);\
uint SPECIALIZED_STRING_METHOD(TYPE, empty)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this);\
TYPE const* SPECIALIZED_STRING_METHOD(TYPE, data)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this);\
TYPE const* SPECIALIZED_STRING_METHOD(TYPE, at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this, uint index);\
TYPE * SPECIALIZED_STRING_METHOD(TYPE, mut_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, uint index);\
\
typedef SPECIALIZED_STRING_STRUCT_TYPE(TYPE) {\
    union {\
        struct CONCAT3(SPECIALIZED_STRING_TYPE(TYPE), _, dynamically_allocated_data) {\
            TYPE* buffer_;\
            uint size_;\
            uint capacity_;\
        } dynamic_data_;\
        struct CONCAT3(SPECIALIZED_STRING_TYPE(TYPE), _, stack_allocated_data) {\
            TYPE buffer_[sizeof(struct CONCAT3(SPECIALIZED_STRING_TYPE(TYPE), _, dynamically_allocated_data)) / sizeof(TYPE)];\
        } stack_data_;\
    };\
    uint is_stack_allocated_;\
} SPECIALIZED_STRING_TYPE(TYPE)
#define DECLARE_SPECIALIZED_STRING(TYPE) DECLARE_SPECIALIZED_STRING_(TYPE)

#define DECLARE_STRING() DECLARE_SPECIALIZED_STRING(char)

#define IMPLEMENT_SPECIALIZED_STRING_(TYPE)\
/* --- Construction/Destruction functions implementation --- */\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this) {\
    static_assert(sizeof(this->dynamic_data_) / sizeof(TYPE) > 1, "sizeof(" "##TYPE##" ") is higher than size of 3x pointers");\
    this->is_stack_allocated_ = 1;\
    TYPE_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, 0u));\
    TYPE const capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
    TYPE_METHOD(TYPE, construct_copy_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, capacity), (TYPE const* const)&capacity);\
    return this;\
}\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_copy_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const source) {\
    SPECIALIZED_STRING_METHOD(TYPE, construct_at)(this);\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, SPECIALIZED_STRING_METHOD(TYPE, size)(source));\
    uint const source_string_size = SPECIALIZED_STRING_METHOD(TYPE, size)(source);\
    for (uint index = 0u; index < source_string_size; ++index) {\
        SPECIALIZED_STRING_METHOD(TYPE, push_back)(this, SPECIALIZED_STRING_METHOD(TYPE, at)(source, index));\
    }\
    return this;\
}\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_by_value_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, uint const size, TYPE const* const value) {\
    SPECIALIZED_STRING_METHOD(TYPE, construct_at)(this);\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, size);\
    for (uint index = 0u; index < size; ++index) {\
        SPECIALIZED_STRING_METHOD(TYPE, push_back)(this, value);\
    }\
    return this;\
}\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_from_buffer_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, uint const buffer_size, TYPE const* const buffer) {\
    SPECIALIZED_STRING_METHOD(TYPE, construct_at)(this);\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, buffer_size);\
    for (uint index = 0u; index < buffer_size; ++index) {\
        SPECIALIZED_STRING_METHOD(TYPE, push_back)(this, &buffer[index]);\
    }\
    return this;\
}\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_from_c_string_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, TYPE const* const buffer) {\
    SPECIALIZED_STRING_METHOD(TYPE, construct_at)(this);\
    uint const buffer_size = CONCAT5(utils__string, __, SPECIALIZED_STRING_TYPE(TYPE), _, length)(buffer);\
    SPECIALIZED_STRING_METHOD(TYPE, construct_from_buffer_at)(this, buffer_size, buffer);\
    return this;\
}\
void SPECIALIZED_STRING_METHOD(TYPE, destroy_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this) {\
    if (!this->is_stack_allocated_) {\
        free(this->dynamic_data_.buffer_);\
    };\
}\
/* --- Memory managment functions implementation --- */\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, resize)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, const uint new_size, TYPE const* const value) {\
    if (SPECIALIZED_STRING_METHOD(TYPE, size)(this) >= new_size) {\
        return this;\
    }\
    if (this->is_stack_allocated_) {\
        uint const capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
        if (capacity >= new_size) {\
            for (uint index = SPECIALIZED_STRING_METHOD(TYPE, size)(this); index < new_size; ++index) {\
                TYPE_METHOD(TYPE, construct_copy_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, index), value);\
            }\
            TYPE_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, new_size));\
            TYPE const current_extension_size = capacity - new_size;\
            TYPE_METHOD(TYPE, construct_copy_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, capacity), (TYPE const* const)(&current_extension_size));\
            return this;\
        }\
    }\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, new_size);\
    for (; this->dynamic_data_.size_ < new_size; ++this->dynamic_data_.size_) {\
        TYPE_METHOD(TYPE, construct_copy_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, this->dynamic_data_.size_), value);\
    }\
    TYPE_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, new_size));\
    return this;\
}\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, reserve)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, const uint new_capacity) {\
    uint current_capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
    if (current_capacity++ >= new_capacity) {\
        return this;\
    }\
    while (((current_capacity <<= 1) - 1) < new_capacity);\
    TYPE* const new_buffer = malloc(current_capacity * sizeof(TYPE));\
    /* Copy elements one-by-one */\
    for (uint index = 0u; index < SPECIALIZED_STRING_METHOD(TYPE, size)(this); ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(&new_buffer[index], SPECIALIZED_STRING_METHOD(TYPE, at)(this, index));\
    }\
    if (!this->is_stack_allocated_) {\
        free(this->dynamic_data_.buffer_);\
    }\
    this->dynamic_data_.size_ = SPECIALIZED_STRING_METHOD(TYPE, size)(this);\
    this->dynamic_data_.buffer_ = new_buffer;\
    this->dynamic_data_.capacity_ = current_capacity - 1;\
    this->is_stack_allocated_ = 0;\
    return this;\
}\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, clear)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this) {\
    if (!this->is_stack_allocated_) {\
        this->dynamic_data_.size_ = 0;\
    } else {\
        TYPE const capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
        TYPE_METHOD(TYPE, construct_copy_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, capacity), (TYPE const* const)&capacity);\
    }\
    TYPE_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, SPECIALIZED_STRING_METHOD(TYPE, capacity)(this)));\
    return this;\
}\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, shrink_to_fit)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this);\
void SPECIALIZED_STRING_METHOD(TYPE, push_back)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, TYPE const* const value) {\
    SPECIALIZED_STRING_METHOD(TYPE, resize)(this, SPECIALIZED_STRING_METHOD(TYPE, size)(this) + 1, value);\
}\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_string)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* another_string);\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_c_string)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, TYPE const * const buffer) {\
    uint const buffer_size = CONCAT5(utils__string, __, SPECIALIZED_STRING_TYPE(TYPE), _, length)(buffer);\
    SPECIALIZED_STRING_METHOD(TYPE, append_buffer)(this, buffer, buffer_size);\
    return this;\
}\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_buffer)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, TYPE const* const buffer, uint const buffer_size) {\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, SPECIALIZED_STRING_METHOD(TYPE, size)(this) + buffer_size);\
    for (uint index = 0u; index < buffer_size; ++index) {\
        SPECIALIZED_STRING_METHOD(TYPE, push_back)(this, &buffer[index]);\
    }\
    return this;\
}\
SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_fill)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, uint const size, TYPE const* const value);\
/* --- Getters functions implementation --- */\
uint SPECIALIZED_STRING_METHOD(TYPE, capacity)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this) {\
    if (this->is_stack_allocated_) {\
        return (sizeof(this->dynamic_data_) / sizeof(TYPE)) - 1;\
    }\
    return this->dynamic_data_.capacity_;\
}\
uint SPECIALIZED_STRING_METHOD(TYPE, size)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this) {\
    if (this->is_stack_allocated_) {\
        uint const capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
        return (capacity - *SPECIALIZED_STRING_METHOD(TYPE, at)(this, capacity));\
    }\
    return this->dynamic_data_.size_;\
}\
uint SPECIALIZED_STRING_METHOD(TYPE, length)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this) {\
    return SPECIALIZED_STRING_METHOD(TYPE, size)(this);\
}\
uint SPECIALIZED_STRING_METHOD(TYPE, empty)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this) {\
    return SPECIALIZED_STRING_METHOD(TYPE, size)(this);\
}\
TYPE const* SPECIALIZED_STRING_METHOD(TYPE, data)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this) {\
    return SPECIALIZED_STRING_METHOD(TYPE, at)(this, 0u);\
}\
TYPE const* SPECIALIZED_STRING_METHOD(TYPE, at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE) const* const this, uint index) {\
    return (this->is_stack_allocated_ ? this->stack_data_.buffer_ : this->dynamic_data_.buffer_) + index;\
}\
TYPE * SPECIALIZED_STRING_METHOD(TYPE, mut_at)(SPECIALIZED_STRING_STRUCT_TYPE(TYPE)* const this, uint index) {\
    return (this->is_stack_allocated_ ? this->stack_data_.buffer_ : this->dynamic_data_.buffer_) + index;\
}
#define IMPLEMENT_SPECIALIZED_STRING(TYPE) IMPLEMENT_SPECIALIZED_STRING_(TYPE)
#define IMPLEMENT_STRING() IMPLEMENT_SPECIALIZED_STRING(char)
