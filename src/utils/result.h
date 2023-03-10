#pragma once

#include <utils/common.h>

#define RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) NAMESPACE_UTILS(CONCAT5(result, __, SUCCESS_TYPE, _, ERROR_TYPE))

#define RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, METHOD) TYPE_METHOD(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), METHOD)

#define DEFINE_RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)\
DECLARE_STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), success_type, SUCCESS_TYPE);\
DECLARE_STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), error_type, ERROR_TYPE);\
typedef struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) {\
    union {\
        STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), success_type) value;\
        STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), error_type) error;\
    };\
    char has_value;\
} RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)

#define DECLARE_RESULT_TYPE_METHODS_WITH_COMMON_MODIFIER(COMMON_MODIFIER, SUCCESS_TYPE, ERROR_TYPE)\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this);\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_from_value_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        SUCCESS_TYPE const* const src);\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_from_value_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        SUCCESS_TYPE* const src);\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_from_error_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        ERROR_TYPE const* const src);\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_from_error_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        ERROR_TYPE* const src);\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) const* const src);\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const src);\
COMMON_MODIFIER int RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, has_value)(\
    struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this);\
COMMON_MODIFIER SUCCESS_TYPE* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, value)(\
    struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this);\
COMMON_MODIFIER ERROR_TYPE* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, error)(\
    struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this);\
COMMON_MODIFIER void* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, destroy_at)(\
    struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this)

#define DEFINE_RESULT_TYPE_METHODS_WITH_COMMON_MODIFIER(COMMON_MODIFIER, SUCCESS_TYPE, ERROR_TYPE)\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this) {\
    this->has_value = 0;\
    TYPE_METHOD(ERROR_TYPE, construct_at)(&this->error);\
    return this;\
}\
\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_from_value_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this, SUCCESS_TYPE const* const src) {\
    this->has_value = 1;\
    TYPE_METHOD(SUCCESS_TYPE, construct_copy_at)(&this->value, src);\
    return this;\
}\
\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_from_value_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this, SUCCESS_TYPE* const src) {\
    this->has_value = 1;\
    TYPE_METHOD(SUCCESS_TYPE, construct_move_at)(&this->value, src);\
    return this;\
}\
\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_from_error_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this, ERROR_TYPE const* const src) {\
    this->has_value = 0;\
    TYPE_METHOD(ERROR_TYPE, construct_copy_at)(&this->error, src);\
    return this;\
}\
\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_from_error_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this, ERROR_TYPE* const src) {\
    this->has_value = 0;\
    TYPE_METHOD(ERROR_TYPE, construct_move_at)(&this->error, src);\
    return this;\
}\
\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this, struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) const* const src) {\
    this->has_value = src->has_value;\
    if (this->has_value) {\
        TYPE_METHOD(SUCCESS_TYPE, construct_copy_at)(&this->value, &src->value);\
    } else {\
        TYPE_METHOD(ERROR_TYPE, construct_copy_at)(&this->error, &src->error);\
    }\
    return this;\
}\
COMMON_MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this, struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const src) {\
    this->has_value = src->has_value;\
    if (this->has_value) {\
        TYPE_METHOD(SUCCESS_TYPE, construct_move_at)(&this->value, &src->value);\
    } else {\
        TYPE_METHOD(ERROR_TYPE, construct_move_at)(&this->error, &src->error);\
    }\
    src->has_value = 0;\
    return this;\
}\
COMMON_MODIFIER int RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, has_value)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this) {\
    return this->has_value;\
}\
COMMON_MODIFIER SUCCESS_TYPE* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, value)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this) {\
    return &this->value;\
}\
COMMON_MODIFIER ERROR_TYPE* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, error)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this) {\
    return &this->error;\
}\
COMMON_MODIFIER void* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, destroy_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this) {\
    if (this->has_value) {\
        TYPE_METHOD(SUCCESS_TYPE, destroy_at)(&this->value);\
    } else {\
        TYPE_METHOD(ERROR_TYPE, destroy_at)(&this->error);\
    }\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_at)(this);\
    return this;\
}

#define DEFINE_RESULT_TYPE_STATIC_METHODS(SUCCESS_TYPE, ERROR_TYPE)\
    DEFINE_RESULT_TYPE_METHODS_WITH_COMMON_MODIFIER(static, SUCCESS_TYPE, ERROR_TYPE)
