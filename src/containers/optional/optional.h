#pragma once

#include <primitives/bool_type_alias.h>

#include <containers/common.h>

#define OPTIONAL_TYPE(TYPE)\
NAMESPACE_CONTAINERS(CONCAT3(optional, __, TYPE))

#define OPTIONAL_METHOD(TYPE, METHOD)\
TYPE_METHOD(OPTIONAL_TYPE(TYPE), METHOD)

typedef struct nullopt nullopt;

#define NULLOPT ((struct nullopt const*)(void const*)(NULL))

#define DEFINE_OPTIONAL_TYPE(TYPE)\
DECLARE_STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type, TYPE);\
typedef struct OPTIONAL_TYPE(TYPE) {\
    STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type) value;\
    bool has_value;\
} OPTIONAL_TYPE(TYPE)\

#define DECLARE_OPTIONAL_METHODS_WITH_COMMON_MODIFIER(MODIFIER, TYPE)\
/* --- --- Construction/destruction methods --- --- */\
MODIFIER struct OPTIONAL_TYPE(TYPE)* OPTIONAL_METHOD(TYPE, construct_at)(\
    struct OPTIONAL_TYPE(TYPE)* const this);\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, construct_copy_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct OPTIONAL_TYPE(TYPE) const* const source);\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, construct_move_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct OPTIONAL_TYPE(TYPE)* const source);\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, construct_copy_from_value_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type) const* const value);\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, construct_move_from_value_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type)* const value);\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, construct_from_nullopt_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct nullopt const* const nullopt);\
MODIFIER void* OPTIONAL_METHOD(TYPE, destroy_at)(\
    struct OPTIONAL_TYPE(TYPE)* const this);\
/* --- --- Assignment methods --- --- */\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, assign_copy_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct OPTIONAL_TYPE(TYPE) const* const source);\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, assign_move_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct OPTIONAL_TYPE(TYPE)* const source);\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, assign_copy_from_value_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type) const* const value);\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, assign_move_from_value_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type)* const value);\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, assign_from_nullopt_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct nullopt const* const nullopt);\
/* --- --- Swap --- --- */\
MODIFIER void\
    OPTIONAL_METHOD(TYPE, swap)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct OPTIONAL_TYPE(TYPE)* const source);\
/* --- ---  --- --- */\
MODIFIER bool\
    OPTIONAL_METHOD(TYPE, has_value)(\
        struct OPTIONAL_TYPE(TYPE) const* const this);\
MODIFIER STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type) const*\
    OPTIONAL_METHOD(TYPE, value)(\
        struct OPTIONAL_TYPE(TYPE) const* const this);\
MODIFIER STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type)*\
    OPTIONAL_METHOD(TYPE, mut_value)(\
        struct OPTIONAL_TYPE(TYPE)* const this)

#define DEFINE_OPTIONAL_METHODS_WITH_COMMON_MODIFIER(MODIFIER, TYPE)\
/* --- --- Construction/destruction methods --- --- */\
MODIFIER struct OPTIONAL_TYPE(TYPE)* OPTIONAL_METHOD(TYPE, construct_at)(\
    struct OPTIONAL_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    this->has_value = false;\
    return this;\
}\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, construct_copy_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct OPTIONAL_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->has_value = source->has_value;\
    if (source->has_value) {\
        TYPE_METHOD(TYPE, construct_copy_at)(&this->value, &source->value);\
    }\
    return this;\
}\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, construct_move_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct OPTIONAL_TYPE(TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->has_value = source->has_value;\
    if (source->has_value) {\
        TYPE_METHOD(TYPE, construct_move_at)(&this->value, &source->value);\
    }\
    return this;\
}\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, construct_copy_from_value_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type) const* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    this->has_value = true;\
    TYPE_METHOD(TYPE, construct_copy_at)(&this->value, value);\
    return this;\
}\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, construct_move_from_value_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type)* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    this->has_value = true;\
    TYPE_METHOD(TYPE, construct_move_at)(&this->value, value);\
    return this;\
}\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, construct_from_nullopt_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct nullopt const* const value) {\
    ASSERT(this);\
    UNUSED(value);\
    this->has_value = false;\
    return this;\
}\
MODIFIER void* OPTIONAL_METHOD(TYPE, destroy_at)(\
    struct OPTIONAL_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    if (this->has_value) {\
        TYPE_METHOD(TYPE, destroy_at)(&this->value);\
    }\
    return this;\
}\
/* --- --- Assignment methods --- --- */\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, assign_copy_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct OPTIONAL_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    struct OPTIONAL_TYPE(TYPE) temporary;\
    OPTIONAL_METHOD(TYPE, construct_copy_at)(&temporary, source);\
    OPTIONAL_METHOD(TYPE, swap)(&temporary, this);\
    OPTIONAL_METHOD(TYPE, destroy_at)(&temporary);\
    return this;\
}\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, assign_move_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct OPTIONAL_TYPE(TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    struct OPTIONAL_TYPE(TYPE) temporary;\
    OPTIONAL_METHOD(TYPE, construct_move_at)(&temporary, source);\
    OPTIONAL_METHOD(TYPE, swap)(&temporary, this);\
    OPTIONAL_METHOD(TYPE, destroy_at)(&temporary);\
    return this;\
}\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, assign_copy_from_value_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type) const* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    if (this->has_value) {\
        TYPE_METHOD(TYPE, assign_copy_at)(&this->value, value);\
    } else {\
        TYPE_METHOD(TYPE, construct_copy_at)(&this->value, value);\
    }\
    this->has_value = true;\
    return this;\
}\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, assign_move_from_value_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type)* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    if (this->has_value) {\
        TYPE_METHOD(TYPE, assign_move_at)(&this->value, value);\
    } else {\
        TYPE_METHOD(TYPE, construct_move_at)(&this->value, value);\
    }\
    this->has_value = true;\
    return this;\
}\
MODIFIER struct OPTIONAL_TYPE(TYPE)*\
    OPTIONAL_METHOD(TYPE, assign_from_nullopt_at)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct nullopt const* const value) {\
    ASSERT(this);\
    UNUSED(value);\
    if (this->has_value) {\
        TYPE_METHOD(TYPE, destroy_at)(&this->value);\
    }\
    this->has_value = false;\
    return this;\
}\
/* --- --- Swap --- --- */\
MODIFIER void\
    OPTIONAL_METHOD(TYPE, swap)(\
        struct OPTIONAL_TYPE(TYPE)* const this,\
        struct OPTIONAL_TYPE(TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    if (this->has_value) {\
        if (source->has_value) {\
            TYPE_METHOD(TYPE, swap)(&this->value, &source->value);\
        } else {\
            TYPE_METHOD(TYPE, construct_move_at)(&source->value, &this->value);\
        }\
    } else {\
        if (source->has_value) {\
            TYPE_METHOD(TYPE, construct_move_at)(&this->value, &source->value);\
        }\
    }\
    \
    bool temporary = this->has_value;\
    this->has_value = source->has_value;\
    source->has_value = temporary;\
}\
/* --- ---  --- --- */\
MODIFIER bool\
    OPTIONAL_METHOD(TYPE, has_value)(\
        struct OPTIONAL_TYPE(TYPE) const* const this) {\
    ASSERT(this);\
    return this->has_value;\
}\
MODIFIER STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type) const*\
    OPTIONAL_METHOD(TYPE, value)(\
        struct OPTIONAL_TYPE(TYPE) const* const this) {\
    return &this->value;\
}\
MODIFIER STRUCT_SUBTYPE(OPTIONAL_TYPE(TYPE), value_type)*\
    OPTIONAL_METHOD(TYPE, mut_value)(\
        struct OPTIONAL_TYPE(TYPE)* const this) {\
    return &this->value;\
}\

#define DEFINE_OPTIONAL_STATIC_METHODS(TYPE)\
    DECLARE_OPTIONAL_METHODS_WITH_COMMON_MODIFIER(static, TYPE);\
    DEFINE_OPTIONAL_METHODS_WITH_COMMON_MODIFIER(static, TYPE)
