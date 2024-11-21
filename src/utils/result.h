#pragma once

#include <utils/common.h>
#include <primitives/bool_type_alias.h>

#define RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) NAMESPACE_UTILS(CONCAT5(result, __, SUCCESS_TYPE, _, ERROR_TYPE))
#define RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, METHOD) TYPE_METHOD(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), METHOD)

#define DEFINE_RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)\
DECLARE_STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), success_type, SUCCESS_TYPE);\
DECLARE_STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), error_type, ERROR_TYPE);\
DECLARE_STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), PRIVATE(value_holder), union {\
    STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), success_type) value;\
    STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), error_type) error;\
});\
typedef struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) {\
    STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), PRIVATE(value_holder)) holder;\
    bool has_value;\
} RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)

#define DECLARE_RESULT_METHODS_WITH_COMMON_MODIFIER(MODIFIER, SUCCESS_TYPE, ERROR_TYPE)\
DECLARE_DEFAULT_LIFECYCLE_METHODS_WITH_MODIFIER(MODIFIER, RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE));\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_from_value_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        SUCCESS_TYPE const* const source);\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_from_value_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        SUCCESS_TYPE* const source);\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_from_error_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        ERROR_TYPE const* const source);\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_from_error_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        ERROR_TYPE* const source);\
MODIFIER bool RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, has_value)(\
    struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) const* const this);\
MODIFIER SUCCESS_TYPE const* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, value)(\
    struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) const* const this);\
MODIFIER SUCCESS_TYPE* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, mut_value)(\
    struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this);\
MODIFIER ERROR_TYPE const* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, error)(\
    struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) const* const this);\
MODIFIER ERROR_TYPE* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, mut_error)(\
    struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this)

#define DEFINE_RESULT_METHODS_WITH_COMMON_MODIFIER(MODIFIER, SUCCESS_TYPE, ERROR_TYPE)\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this) {\
    this->has_value = 0;\
    TYPE_METHOD(ERROR_TYPE, construct_at)(&this->holder.error);\
    return this;\
}\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this, struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) const* const source) {\
    this->has_value = source->has_value;\
    if (this->has_value) {\
        TYPE_METHOD(SUCCESS_TYPE, construct_copy_at)(&this->holder.value, &source->holder.value);\
        return this;\
    }\
    TYPE_METHOD(ERROR_TYPE, construct_copy_at)(&this->holder.error, &source->holder.error);\
    return this;\
}\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this, struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const source) {\
    this->has_value = source->has_value;\
    if (this->has_value) {\
        TYPE_METHOD(SUCCESS_TYPE, construct_move_at)(&this->holder.value, &source->holder.value);\
        return this;\
    }\
    TYPE_METHOD(ERROR_TYPE, construct_move_at)(&this->holder.error, &source->holder.error);\
    return this;\
}\
DEFINE_DEFAULT_ASSIGNMENT_METHODS_WITH_MODIFIER(MODIFIER, RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE))\
MODIFIER void RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, swap)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this, struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const source) {\
    if (this->has_value == source->has_value) {\
        if (this->has_value) {\
            TYPE_METHOD(SUCCESS_TYPE, swap)(&this->holder.value, &source->holder.value);\
            return;\
        }\
        TYPE_METHOD(ERROR_TYPE, swap)(&this->holder.error, &source->holder.error);\
        return;\
    }\
    struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* pvalue_with_success, * pvalue_with_error;\
    if (this->has_value) {\
        pvalue_with_success = this;\
        pvalue_with_error = source;\
    } else {\
        pvalue_with_success = source;\
        pvalue_with_error = this;\
    }\
    /* error & success values are hold in same storage area (in union)*/\
    /* so we must save temporary value somewhere between move operations*/\
    STRUCT_SUBTYPE(RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE), PRIVATE(value_holder)) temporary;\
    TYPE_METHOD(ERROR_TYPE, construct_move_at)(&temporary.error, &pvalue_with_error->holder.error);\
    TYPE_METHOD(SUCCESS_TYPE, construct_move_at)(&pvalue_with_error->holder.value, &pvalue_with_success->holder.value);\
    TYPE_METHOD(ERROR_TYPE, construct_move_at)(&pvalue_with_success->holder.error, &temporary.error);\
    \
    this->has_value ^= source->has_value;\
    source->has_value ^= this->has_value;\
    this->has_value ^= source->has_value;\
}\
MODIFIER void* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, destroy_at)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this) {\
    if (this->has_value) {\
        TYPE_METHOD(SUCCESS_TYPE, destroy_at)(&this->holder.value);\
        return this;\
    }\
    TYPE_METHOD(ERROR_TYPE, destroy_at)(&this->holder.error);\
    return this;\
}\
\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_from_value_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        SUCCESS_TYPE const* const source) {\
    this->has_value = 1;\
    TYPE_METHOD(SUCCESS_TYPE, construct_copy_at)(&this->holder.value, source);\
    return this;\
}\
\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_from_value_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        SUCCESS_TYPE* const source) {\
    this->has_value = 1;\
    TYPE_METHOD(SUCCESS_TYPE, construct_move_at)(&this->holder.value, source);\
    return this;\
}\
\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_copy_from_error_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        ERROR_TYPE const* const source) {\
    this->has_value = 0;\
    TYPE_METHOD(ERROR_TYPE, construct_copy_at)(&this->holder.error, source);\
    return this;\
}\
\
MODIFIER struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)*\
    RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, construct_move_from_error_at)(\
        struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this,\
        ERROR_TYPE* const source) {\
    this->has_value = 0;\
    TYPE_METHOD(ERROR_TYPE, construct_move_at)(&this->holder.error, source);\
    return this;\
}\
\
MODIFIER bool RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, has_value)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) const* const this) {\
    return this->has_value;\
}\
MODIFIER SUCCESS_TYPE const* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, value)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) const* const this) {\
    return &this->holder.value;\
}\
MODIFIER SUCCESS_TYPE* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, mut_value)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this) {\
    return &this->holder.value;\
}\
MODIFIER ERROR_TYPE const* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, error)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE) const* const this) {\
    return &this->holder.error;\
}\
MODIFIER ERROR_TYPE* RESULT_METHOD(SUCCESS_TYPE, ERROR_TYPE, mut_error)(struct RESULT_TYPE(SUCCESS_TYPE, ERROR_TYPE)* const this) {\
    return &this->holder.error;\
}

#define DEFINE_RESULT_STATIC_METHODS(SUCCESS_TYPE, ERROR_TYPE)\
    DECLARE_RESULT_METHODS_WITH_COMMON_MODIFIER(static, SUCCESS_TYPE, ERROR_TYPE);\
    DEFINE_RESULT_METHODS_WITH_COMMON_MODIFIER(static, SUCCESS_TYPE, ERROR_TYPE)
