#pragma once

#include <utils/string/raw_string/helpers.h>
#include <containers/static/common.h>
#include <primitives/limits.h>
#include <primitives/allocator.h>

// define macros for `string_type`
#define SPECIALIZED_STRING_VIEW_TYPE(TYPE)\
    NAMESPACE_CONTAINERS_STATIC(CONCAT3(string_view, __, TYPE))

#define CSTRING_VIEW_TYPE() SPECIALIZED_STRING_VIEW_TYPE(char)
#define WSTRING_VIEW_TYPE() SPECIALIZED_STRING_VIEW_TYPE(wchar)
#define OS_STRING_VIEW_TYPE() SPECIALIZED_STRING_VIEW_TYPE(OS_CHAR_TYPE)

// define macros for string methods
#define SPECIALIZED_STRING_VIEW_METHOD(TYPE, METHOD)\
    TYPE_METHOD(SPECIALIZED_STRING_VIEW_TYPE(TYPE), METHOD)

#define CSTRING_VIEW_METHOD(METHOD) SPECIALIZED_STRING_VIEW_METHOD(char, METHOD)
#define WSTRING_VIEW_METHOD(METHOD) SPECIALIZED_STRING_VIEW_METHOD(wchar, METHOD)
#define OS_STRING_VIEW_METHOD(METHOD) TYPE_METHOD(OS_STRING_VIEW_TYPE(), METHOD)

// define macro for string view type
#define DECLARE_SPECIALIZED_STRING_VIEW_VIEW_TYPE(TYPE)\
DECLARE_STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type, usize);\
DECLARE_STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), char_type, TYPE);\
typedef struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) {\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), char_type) const* buffer;\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) size;\
} SPECIALIZED_STRING_VIEW_TYPE(TYPE)

// define macro for string view type & string methods declaration
#define DECLARE_SPECIALIZED_STRING_VIEW_VIEW_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
/* --- Construction/Destruction functions implementation --- */\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this);\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_copy_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const source);\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_move_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const source);\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_from_buffer_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), char_type) const* const source_buffer, STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) const buffer_size);\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_from_raw_string_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), char_type) const* const source_buffer);\
MODIFIER void* SPECIALIZED_STRING_VIEW_METHOD(TYPE, destroy_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this);\
/* --- Assignment functions implementation --- */\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, assign_move_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const source);\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, assign_copy_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const source);\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, assign_from_buffer_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) const buffer_size, TYPE const* const source_buffer);\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, assign_from_raw_string_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), char_type) const* const source_buffer);\
/* --- Swap --- */\
MODIFIER void SPECIALIZED_STRING_VIEW_METHOD(TYPE, swap)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const source);\
/* --- Getters functions implementation --- */\
MODIFIER STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) SPECIALIZED_STRING_VIEW_METHOD(TYPE, size)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const this);\
MODIFIER bool SPECIALIZED_STRING_VIEW_METHOD(TYPE, empty)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const this);\
MODIFIER TYPE const* SPECIALIZED_STRING_VIEW_METHOD(TYPE, data)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const this);\
MODIFIER TYPE const* SPECIALIZED_STRING_VIEW_METHOD(TYPE, at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) index)

// define macro for string type & string methods declaration
#define DECLARE_SPECIALIZED_STRING_VIEW(TYPE)\
DECLARE_SPECIALIZED_STRING_VIEW_VIEW_TYPE(TYPE);\
DECLARE_SPECIALIZED_STRING_VIEW_VIEW_METHODS_WITH_MODIFIER(extern, TYPE)

#define DECLARE_STRING_VIEW() DECLARE_SPECIALIZED_STRING_VIEW(char)
#define DECLARE_WSTRING_VIEW() DECLARE_SPECIALIZED_STRING_VIEW(wchar)

#define DEFINE_SPECIALIZED_STRING_VIEW_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
/* --- Construction/Destruction functions implementation --- */\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    this->buffer = NULL;\
    this->size = 0u;\
    return this;\
}\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_copy_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this,\
    struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->buffer = source->buffer;\
    this->size = source->size;\
    return this;\
}\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_move_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this,\
    struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const source) {\
    return SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_copy_at)(this, source);\
}\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_from_buffer_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this,\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), char_type) const* const source_buffer,\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) const buffer_size) {\
    ASSERT(this);\
    this->buffer = source_buffer;\
    this->size = buffer_size;\
    return this;\
}\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_from_raw_string_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this,\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), char_type) const* const source_buffer) {\
    ASSERT(this);\
    ASSERT(source_buffer);\
    STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) const buffer_size = RAW_STRING_FUNCTION(TYPE, length)(source_buffer);\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_from_buffer_at)(this, source_buffer, buffer_size);\
    return this;\
}\
MODIFIER void* SPECIALIZED_STRING_VIEW_METHOD(TYPE, destroy_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    return this;\
}\
/* --- Assignment functions implementation --- */\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, assign_move_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const source) {\
    struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) temporary_string_view;\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_move_at)(&temporary_string_view, source);\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, swap)(this, &temporary_string_view);\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, destroy_at)(&temporary_string_view);\
    return this;\
}\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, assign_copy_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const source) {\
    struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) temporary_string_view;\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_copy_at)(&temporary_string_view, source);\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, swap)(this, &temporary_string_view);\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, destroy_at)(&temporary_string_view);\
    return this;\
}\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, assign_from_buffer_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) const buffer_size, TYPE const* const source_buffer) {\
    struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) temporary_string_view;\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_from_buffer_at)(&temporary_string_view, source_buffer, buffer_size);\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, swap)(this, &temporary_string_view);\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, destroy_at)(&temporary_string_view);\
    return this;\
}\
MODIFIER struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* SPECIALIZED_STRING_VIEW_METHOD(TYPE, assign_from_raw_string_at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this, TYPE const* const source_buffer) {\
    struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) temporary_string_view;\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, construct_from_raw_string_at)(&temporary_string_view, source_buffer);\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, swap)(this, &temporary_string_view);\
    SPECIALIZED_STRING_VIEW_METHOD(TYPE, destroy_at)(&temporary_string_view);\
    return this;\
}\
/* --- Swap --- */\
MODIFIER void SPECIALIZED_STRING_VIEW_METHOD(TYPE, swap)(\
    struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const this,\
    struct SPECIALIZED_STRING_VIEW_TYPE(TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    {\
        STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) temporary = this->size;\
        this->size = source->size;\
        source->size = temporary;\
    }\
    {\
        STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), char_type) const* temporary = this->buffer;\
        this->buffer = source->buffer;\
        source->buffer = temporary;\
    }\
}\
MODIFIER STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) SPECIALIZED_STRING_VIEW_METHOD(TYPE, size)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const this) {\
    ASSERT(this);\
    return this->size;\
}\
MODIFIER bool SPECIALIZED_STRING_VIEW_METHOD(TYPE, empty)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const this) {\
    ASSERT(this);\
    return !!this->size;\
}\
MODIFIER TYPE const* SPECIALIZED_STRING_VIEW_METHOD(TYPE, data)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const this) {\
    ASSERT(this);\
    return this->buffer;\
}\
MODIFIER TYPE const* SPECIALIZED_STRING_VIEW_METHOD(TYPE, at)(struct SPECIALIZED_STRING_VIEW_TYPE(TYPE) const* const this, STRUCT_SUBTYPE(SPECIALIZED_STRING_VIEW_TYPE(TYPE), size_type) index) {\
    ASSERT(this);\
    return this->buffer + index;\
}

#define DEFINE_SPECIALIZED_STRING_VIEW(TYPE) DEFINE_SPECIALIZED_STRING_VIEW_METHODS_WITH_MODIFIER(, TYPE)

#define DEFINE_STRING_VIEW() DEFINE_SPECIALIZED_STRING_VIEW(char)
#define DEFINE_WSTRING_VIEW() DEFINE_SPECIALIZED_STRING_VIEW(wchar)

// predefine strings types/functions
#include <construct/characters_helpers.h>

DECLARE_STRING_VIEW();
DECLARE_WSTRING_VIEW();
DECLARE_SPECIALIZED_STRING_VIEW(char8);
DECLARE_SPECIALIZED_STRING_VIEW(char16);
DECLARE_SPECIALIZED_STRING_VIEW(char32);
DECLARE_SPECIALIZED_STRING_VIEW(char64);

#if defined(_WIN32)
    DECLARE_SPECIALIZED_STRING_VIEW(winchar);
#endif
