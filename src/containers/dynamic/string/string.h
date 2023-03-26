#pragma once

#include <utils/string/raw_string/helpers.h>
#include <containers/dynamic/common.h>
#include <primitives/limits.h>

// define macros for `string_type`
#define SPECIALIZED_STRING_TYPE(CHAR_TYPE) NAMESPACE_CONTAINERS_DYNAMIC(CONCAT3(string, _, CHAR_TYPE))
#define STRING_TYPE() SPECIALIZED_STRING_TYPE(char)
#define WSTRING_TYPE() SPECIALIZED_STRING_TYPE(wchar)

#if defined(_WIN32)
    #define OS_STRING_TYPE() SPECIALIZED_STRING_TYPE(winchar)
#else
    #define OS_STRING_TYPE() STRING_TYPE()
#endif

// define macros for string methods
#define SPECIALIZED_STRING_METHOD(CHAR_TYPE, METHOD) TYPE_METHOD(SPECIALIZED_STRING_TYPE(CHAR_TYPE), METHOD)
#define STRING_METHOD(METHOD) SPECIALIZED_STRING_METHOD(char, METHOD)
#define WSTRING_METHOD(METHOD) SPECIALIZED_STRING_METHOD(wchar, METHOD)

#if defined(_WIN32)
    #define OS_STRING_METHOD(METHOD) SPECIALIZED_STRING_METHOD(winchar, METHOD)
#else
    #define OS_STRING_METHOD(METHOD) STRING_METHOD(METHOD)
#endif

// define macro for string type & string methods declaration
#define DECLARE_SPECIALIZED_STRING(TYPE)\
struct SPECIALIZED_STRING_TYPE(TYPE);\
DECLARE_STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type, size_t);\
DECLARE_STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), char_type, TYPE);\
/* --- Construction/Destruction functions implementation --- */\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_copy_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE) const* const source);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_move_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE)* const source);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_by_value_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const size, TYPE const* const value);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_from_buffer_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const buffer_size, TYPE const* const source_buffer);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_from_c_string_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, TYPE const* const source_buffer);\
void* SPECIALIZED_STRING_METHOD(TYPE, destroy_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this);\
/* --- Assignment functions implementation --- */\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, assign_move_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE)* const source);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, assign_copy_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE) const* const source);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, assign_from_buffer_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const buffer_size, TYPE const* const source_buffer);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, assign_from_c_string_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, TYPE const* const source_buffer);\
void SPECIALIZED_STRING_METHOD(TYPE, swap)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE)* const source);\
/* --- Memory managment functions implementation --- */\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, resize)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const new_size, TYPE const* const value);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, reserve)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const new_capacity);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, clear)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, shrink_to_fit)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this);\
void SPECIALIZED_STRING_METHOD(TYPE, push_back)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, TYPE const* const value);\
void SPECIALIZED_STRING_METHOD(TYPE, pop_back)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_string)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE)* another_string);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_c_string)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, TYPE const * const);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_buffer)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, TYPE const* const source_buffer, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const buffer_size);\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_fill)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const size, TYPE const* const value);\
/* --- Getters functions implementation --- */\
STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) SPECIALIZED_STRING_METHOD(TYPE, capacity)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this);\
STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) SPECIALIZED_STRING_METHOD(TYPE, size)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this);\
STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) SPECIALIZED_STRING_METHOD(TYPE, length)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this);\
uchar SPECIALIZED_STRING_METHOD(TYPE, empty)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this);\
TYPE const* SPECIALIZED_STRING_METHOD(TYPE, data)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this);\
TYPE const* SPECIALIZED_STRING_METHOD(TYPE, at)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index);\
TYPE * SPECIALIZED_STRING_METHOD(TYPE, mut_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index);\
\
typedef struct STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), dynamically_allocated_data) {\
    TYPE* buffer;\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) size;\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) capacity;\
} STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), dynamically_allocated_data);\
typedef struct STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), stack_allocated_data) {\
    TYPE buffer[sizeof(struct STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), dynamically_allocated_data)) / sizeof(TYPE)];\
} STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), stack_allocated_data);\
typedef struct SPECIALIZED_STRING_TYPE(TYPE) {\
    union {\
        STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), dynamically_allocated_data) dynamic_data;\
        STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), stack_allocated_data) stack_data;\
    };\
    uchar is_stack_allocated;\
} SPECIALIZED_STRING_TYPE(TYPE)

#define DECLARE_STRING() DECLARE_SPECIALIZED_STRING(char)
#define DECLARE_WSTRING() DECLARE_SPECIALIZED_STRING(wchar)

#define IMPLEMENT_SPECIALIZED_STRING(TYPE)\
/* --- Construction/Destruction functions implementation --- */\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this) {\
    static_assert(sizeof(struct STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), dynamically_allocated_data)) / sizeof(TYPE) > 1, "sizeof(" "##TYPE##" ") is higher than size of 3x pointers");\
    static_assert(sizeof(struct STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), dynamically_allocated_data)) / sizeof(TYPE) < MAX_VALUE(TYPE), "sizeof(" "##TYPE##" ") is higher than size of 3x pointers");\
    this->is_stack_allocated = 1u;\
    TYPE_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, 0u));\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
    TYPE* const stack_allocated_data__capacity_element = SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, capacity);\
    TYPE const casted_capacity = (TYPE const)(capacity);\
    TYPE_METHOD(TYPE, construct_copy_at)(stack_allocated_data__capacity_element, &casted_capacity);\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_copy_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE) const* const source) {\
    SPECIALIZED_STRING_METHOD(TYPE, construct_at)(this);\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, SPECIALIZED_STRING_METHOD(TYPE, size)(source));\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const source_string_size = SPECIALIZED_STRING_METHOD(TYPE, size)(source);\
    for (STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index = 0u; index < source_string_size; ++index) {\
        SPECIALIZED_STRING_METHOD(TYPE, push_back)(this, SPECIALIZED_STRING_METHOD(TYPE, at)(source, index));\
    }\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_move_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE)* const source) {\
    if (source->is_stack_allocated) {\
        SPECIALIZED_STRING_METHOD(TYPE, construct_copy_at)(this, source);\
        return this;\
    }\
    this->is_stack_allocated = 0u;\
    this->dynamic_data.buffer = source->dynamic_data.buffer;\
    this->dynamic_data.size = source->dynamic_data.size;\
    this->dynamic_data.capacity = source->dynamic_data.capacity;\
\
    SPECIALIZED_STRING_METHOD(TYPE, destroy_at)(source);\
    source->is_stack_allocated = 1u;\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_by_value_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const size, TYPE const* const value) {\
    SPECIALIZED_STRING_METHOD(TYPE, construct_at)(this);\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, size);\
    for (STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index = 0u; index < size; ++index) {\
        SPECIALIZED_STRING_METHOD(TYPE, push_back)(this, value);\
    }\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_from_buffer_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const buffer_size, TYPE const* const source_buffer) {\
    SPECIALIZED_STRING_METHOD(TYPE, construct_at)(this);\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, buffer_size);\
    for (STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index = 0u; index < buffer_size; ++index) {\
        SPECIALIZED_STRING_METHOD(TYPE, push_back)(this, &source_buffer[index]);\
    }\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, construct_from_c_string_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, TYPE const* const source_buffer) {\
    SPECIALIZED_STRING_METHOD(TYPE, construct_at)(this);\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const buffer_size = RAW_STRING_FUNCTION(TYPE, length)(source_buffer);\
    SPECIALIZED_STRING_METHOD(TYPE, construct_from_buffer_at)(this, buffer_size, source_buffer);\
    return this;\
}\
void* SPECIALIZED_STRING_METHOD(TYPE, destroy_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this) {\
    if (!this->is_stack_allocated) {\
        NAMESPACE_MEMORY_NATIVE(free)(this->dynamic_data.buffer);\
    };\
    return this;\
}\
/* --- Assignment functions implementation --- */\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, assign_move_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE)* const source) {\
    struct SPECIALIZED_STRING_TYPE(TYPE) temporary_string;\
    SPECIALIZED_STRING_METHOD(TYPE, construct_move_at)(&temporary_string, source);\
    SPECIALIZED_STRING_METHOD(TYPE, swap)(this, &temporary_string);\
    SPECIALIZED_STRING_METHOD(TYPE, destroy_at)(&temporary_string);\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, assign_copy_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE) const* const source) {\
    struct SPECIALIZED_STRING_TYPE(TYPE) temporary_string;\
    SPECIALIZED_STRING_METHOD(TYPE, construct_copy_at)(&temporary_string, source);\
    SPECIALIZED_STRING_METHOD(TYPE, swap)(this, &temporary_string);\
    SPECIALIZED_STRING_METHOD(TYPE, destroy_at)(&temporary_string);\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, assign_from_buffer_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const buffer_size, TYPE const* const source_buffer) {\
    struct SPECIALIZED_STRING_TYPE(TYPE) temporary_string;\
    SPECIALIZED_STRING_METHOD(TYPE, construct_from_buffer_at)(&temporary_string, buffer_size, source_buffer);\
    SPECIALIZED_STRING_METHOD(TYPE, swap)(this, &temporary_string);\
    SPECIALIZED_STRING_METHOD(TYPE, destroy_at)(&temporary_string);\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, assign_from_c_string_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, TYPE const* const source_buffer) {\
    struct SPECIALIZED_STRING_TYPE(TYPE) temporary_string;\
    SPECIALIZED_STRING_METHOD(TYPE, construct_from_c_string_at)(&temporary_string, source_buffer);\
    SPECIALIZED_STRING_METHOD(TYPE, swap)(this, &temporary_string);\
    SPECIALIZED_STRING_METHOD(TYPE, destroy_at)(&temporary_string);\
    return this;\
}\
void SPECIALIZED_STRING_METHOD(TYPE, swap)(\
    struct SPECIALIZED_STRING_TYPE(TYPE)* const this,\
    struct SPECIALIZED_STRING_TYPE(TYPE)* const source) {\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const stack_allocated_capacity = sizeof(this->dynamic_data) / sizeof(TYPE);\
    if (this->is_stack_allocated && source->is_stack_allocated) {\
        for (size_t index = 0u; index < stack_allocated_capacity; ++index) {\
            TYPE const temporary = this->stack_data.buffer[index];\
            this->stack_data.buffer[index] = source->stack_data.buffer[index];\
            source->stack_data.buffer[index] = temporary;\
        }\
        return;\
    }\
    if (!this->is_stack_allocated && !source->is_stack_allocated) {\
        {\
            TYPE* const temporary = this->dynamic_data.buffer;\
            this->dynamic_data.buffer = source->dynamic_data.buffer;\
            source->dynamic_data.buffer = temporary;\
        }\
        {\
            STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const temporary = this->dynamic_data.size;\
            this->dynamic_data.size = source->dynamic_data.size;\
            source->dynamic_data.size = temporary;\
        }\
        {\
            STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const temporary = this->dynamic_data.capacity;\
            this->dynamic_data.capacity = source->dynamic_data.capacity;\
            source->dynamic_data.capacity = temporary;\
        }\
        return;\
    }\
    struct SPECIALIZED_STRING_TYPE(TYPE)* const stack_allocated_string = this->is_stack_allocated ? this : source;\
    struct SPECIALIZED_STRING_TYPE(TYPE)* const dynamically_allocated_string = source->is_stack_allocated ? this : source;\
    ASSERT(stack_allocated_string != dynamically_allocated_string);\
    {\
        TYPE temporary[sizeof(this->dynamic_data) / sizeof(TYPE)];\
        for (size_t index = 0u; index < stack_allocated_capacity; ++index) {\
            temporary[index] = stack_allocated_string->stack_data.buffer[index];\
        }\
        stack_allocated_string->dynamic_data.buffer = dynamically_allocated_string->dynamic_data.buffer;\
        stack_allocated_string->dynamic_data.size = dynamically_allocated_string->dynamic_data.size;\
        stack_allocated_string->dynamic_data.capacity = dynamically_allocated_string->dynamic_data.capacity;\
        stack_allocated_string->is_stack_allocated = !(dynamically_allocated_string->is_stack_allocated = 1u);\
        for (size_t index = 0u; index < stack_allocated_capacity; ++index) {\
            dynamically_allocated_string->stack_data.buffer[index] = temporary[index];\
        }\
    }\
}\
/* --- Memory managment functions implementation --- */\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, resize)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const new_size, TYPE const* const value) {\
    if (SPECIALIZED_STRING_METHOD(TYPE, size)(this) >= new_size) {\
        return this;\
    }\
    if (this->is_stack_allocated) {\
        STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
        if (capacity >= new_size) {\
            for (STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index = SPECIALIZED_STRING_METHOD(TYPE, size)(this); index < new_size; ++index) {\
                TYPE_METHOD(TYPE, construct_copy_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, index), value);\
            }\
            TYPE_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, new_size));\
            TYPE const current_extension_size = (TYPE const)(capacity - new_size);\
            TYPE* const stack_allocated_data__capacity_element = SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, capacity);\
            TYPE_METHOD(TYPE, construct_copy_at)(stack_allocated_data__capacity_element, &current_extension_size);\
            return this;\
        }\
    }\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, new_size);\
    for (; this->dynamic_data.size < new_size; ++this->dynamic_data.size) {\
        TYPE_METHOD(TYPE, construct_copy_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, this->dynamic_data.size), value);\
    }\
    TYPE_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, new_size));\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, reserve)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const new_capacity) {\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) current_capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
    if (current_capacity++ >= new_capacity) {\
        return this;\
    }\
    while (((current_capacity <<= 1) - 1) < new_capacity);\
    TYPE* const new_buffer = NAMESPACE_MEMORY_NATIVE(malloc)(current_capacity * sizeof(TYPE));\
    /* Copy elements one-by-one */\
    for (STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index = 0u; index < SPECIALIZED_STRING_METHOD(TYPE, size)(this); ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(&new_buffer[index], SPECIALIZED_STRING_METHOD(TYPE, at)(this, index));\
    }\
    if (!this->is_stack_allocated) {\
        NAMESPACE_MEMORY_NATIVE(free)(this->dynamic_data.buffer);\
    }\
    this->dynamic_data.size = SPECIALIZED_STRING_METHOD(TYPE, size)(this);\
    this->dynamic_data.buffer = new_buffer;\
    this->dynamic_data.capacity = current_capacity - 1;\
    this->is_stack_allocated = 0;\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, clear)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this) {\
    if (!this->is_stack_allocated) {\
        this->dynamic_data.size = 0;\
    } else {\
        STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
        TYPE* const stack_allocated_data__capacity_element = SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, capacity);\
        TYPE const casted_capacity = (TYPE const)(capacity);\
        TYPE_METHOD(TYPE, construct_copy_at)(stack_allocated_data__capacity_element, &casted_capacity);\
    }\
    TYPE_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, SPECIALIZED_STRING_METHOD(TYPE, capacity)(this)));\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, shrink_to_fit)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this) {\
    if (this->is_stack_allocated) {\
        return this;\
    }\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const stack_allocated_string_capacity = (sizeof(this->dynamic_data) / sizeof(TYPE)) - 1;\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const string_size = SPECIALIZED_STRING_METHOD(TYPE, size)(this);\
    if (string_size <= stack_allocated_string_capacity) {\
        TYPE temporary_buffer[(sizeof(this->dynamic_data) / sizeof(TYPE))];\
        for (STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index = 0u; index < string_size; ++index) {\
            TYPE_METHOD(TYPE, construct_copy_at)(&temporary_buffer[index], SPECIALIZED_STRING_METHOD(TYPE, at)(this, index));\
        }\
        NAMESPACE_MEMORY_NATIVE(free)(this->dynamic_data.buffer);\
        SPECIALIZED_STRING_METHOD(TYPE, construct_from_buffer_at)(this, string_size, temporary_buffer);\
        return this;\
    }\
    TYPE* const temporary_buffer = NAMESPACE_MEMORY_NATIVE(malloc)((string_size + 1) * sizeof(TYPE));\
    for (STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index = 0u; index < string_size; ++index) {\
        TYPE_METHOD(TYPE, construct_copy_at)(&temporary_buffer[index], SPECIALIZED_STRING_METHOD(TYPE, at)(this, index));\
    }\
    TYPE const null_terminate_character = '\0';\
    TYPE_METHOD(TYPE, construct_copy_at)(&temporary_buffer[string_size], &null_terminate_character);\
    NAMESPACE_MEMORY_NATIVE(free)(this->dynamic_data.buffer);\
    this->dynamic_data.buffer = temporary_buffer;\
    this->dynamic_data.capacity = string_size + 1;\
    return this;\
}\
void SPECIALIZED_STRING_METHOD(TYPE, push_back)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, TYPE const* const value) {\
    SPECIALIZED_STRING_METHOD(TYPE, resize)(this, SPECIALIZED_STRING_METHOD(TYPE, size)(this) + 1, value);\
}\
void SPECIALIZED_STRING_METHOD(TYPE, pop_back)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this) {\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const size = SPECIALIZED_STRING_METHOD(TYPE, size)(this);\
    TYPE_METHOD(TYPE, construct_at)(SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, size - 1));\
    if (this->is_stack_allocated) {\
        STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
        TYPE const current_extension_size = (TYPE const)(capacity - size + 1);\
        TYPE* const stack_allocated_data__capacity_element = SPECIALIZED_STRING_METHOD(TYPE, mut_at)(this, capacity);\
        TYPE_METHOD(TYPE, construct_copy_at)(stack_allocated_data__capacity_element, (TYPE const* const)(&current_extension_size));\
        return;\
    }\
    this->dynamic_data.size = size - 1;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_string)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_TYPE(TYPE)* another_string) {\
    SPECIALIZED_STRING_METHOD(TYPE, append_buffer)(this, SPECIALIZED_STRING_METHOD(TYPE, data)(another_string), SPECIALIZED_STRING_METHOD(TYPE, size)(another_string));\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_c_string)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, TYPE const * const source_buffer) {\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const buffer_size = RAW_STRING_FUNCTION(TYPE, length)(source_buffer);\
    SPECIALIZED_STRING_METHOD(TYPE, append_buffer)(this, source_buffer, buffer_size);\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_buffer)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, TYPE const* const source_buffer, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const buffer_size) {\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, SPECIALIZED_STRING_METHOD(TYPE, size)(this) + buffer_size);\
    for (STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index = 0u; index < buffer_size; ++index) {\
        SPECIALIZED_STRING_METHOD(TYPE, push_back)(this, &source_buffer[index]);\
    }\
    return this;\
}\
struct SPECIALIZED_STRING_TYPE(TYPE)* SPECIALIZED_STRING_METHOD(TYPE, append_fill)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const size, TYPE const* const value) {\
    SPECIALIZED_STRING_METHOD(TYPE, reserve)(this, SPECIALIZED_STRING_METHOD(TYPE, size)(this) + size);\
    for (STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index = 0u; index < size; ++index) {\
        SPECIALIZED_STRING_METHOD(TYPE, push_back)(this, value);\
    }\
    return this;\
}\
/* --- Getters functions implementation --- */\
STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) SPECIALIZED_STRING_METHOD(TYPE, capacity)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this) {\
    if (this->is_stack_allocated) {\
        return (sizeof(this->dynamic_data) / sizeof(TYPE)) - 1;\
    }\
    return this->dynamic_data.capacity;\
}\
STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) SPECIALIZED_STRING_METHOD(TYPE, size)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this) {\
    if (this->is_stack_allocated) {\
        STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) const capacity = SPECIALIZED_STRING_METHOD(TYPE, capacity)(this);\
        return (capacity - (STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type))(*SPECIALIZED_STRING_METHOD(TYPE, at)(this, capacity)));\
    }\
    return this->dynamic_data.size;\
}\
STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) SPECIALIZED_STRING_METHOD(TYPE, length)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this) {\
    return SPECIALIZED_STRING_METHOD(TYPE, size)(this);\
}\
uchar SPECIALIZED_STRING_METHOD(TYPE, empty)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this) {\
    return (uchar)!!SPECIALIZED_STRING_METHOD(TYPE, size)(this);\
}\
TYPE const* SPECIALIZED_STRING_METHOD(TYPE, data)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this) {\
    return SPECIALIZED_STRING_METHOD(TYPE, at)(this, 0u);\
}\
TYPE const* SPECIALIZED_STRING_METHOD(TYPE, at)(struct SPECIALIZED_STRING_TYPE(TYPE) const* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index) {\
    return (this->is_stack_allocated ? this->stack_data.buffer : this->dynamic_data.buffer) + index;\
}\
TYPE * SPECIALIZED_STRING_METHOD(TYPE, mut_at)(struct SPECIALIZED_STRING_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_TYPE(TYPE), size_type) index) {\
    return (this->is_stack_allocated ? this->stack_data.buffer : this->dynamic_data.buffer) + index;\
}

#define IMPLEMENT_STRING() IMPLEMENT_SPECIALIZED_STRING(char)
#define IMPLEMENT_WSTRING() IMPLEMENT_SPECIALIZED_STRING(wchar)

// predefine strings types/functions
#include <construct/characters_helpers.h>

DECLARE_STRING();
DECLARE_WSTRING();
DECLARE_SPECIALIZED_STRING(char8);
DECLARE_SPECIALIZED_STRING(char16);
DECLARE_SPECIALIZED_STRING(char32);
DECLARE_SPECIALIZED_STRING(char64);

#if defined(_WIN32)
    DECLARE_SPECIALIZED_STRING(winchar);
#endif
