#pragma once

#include <containers/common.h>

#define PAIR_TYPE(TYPE1, TYPE2)\
    NAMESPACE_CONTAINERS(CONCAT5(pair, __, TYPE1, _, TYPE2))

#define DEFINE_PAIR_TYPE(TYPE1, TYPE2)\
DECLARE_STRUCT_SUBTYPE(PAIR_TYPE(TYPE1, TYPE2), first_value_type, TYPE1);\
DECLARE_STRUCT_SUBTYPE(PAIR_TYPE(TYPE1, TYPE2), second_value_type, TYPE2);\
typedef struct PAIR_TYPE(TYPE1, TYPE2) {\
    TYPE1 first;\
    TYPE2 second;\
} PAIR_TYPE(TYPE1, TYPE2)

#define DECLARE_PAIR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE1, TYPE2)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), construct_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this);\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), construct_copy_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2) const* const source);\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), construct_move_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2)* const source);\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), destroy_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), assign_copy_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2) const* const source);\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), assign_move_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2)* const source);\
/* --- Swap --- */\
COMMON_MODIFIER void TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), swap)(\
    struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
    struct PAIR_TYPE(TYPE1, TYPE2)* const another);

#define DEFINE_PAIR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE1, TYPE2)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), construct_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this) {\
    TYPE_METHOD(TYPE1, construct_at)(&this->first);\
    TYPE_METHOD(TYPE2, construct_at)(&this->second);\
    return this;\
}\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), construct_copy_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2) const* const source) {\
    TYPE_METHOD(TYPE1, construct_copy_at)(&this->first, &source->first);\
    TYPE_METHOD(TYPE2, construct_copy_at)(&this->second, &source->second);\
    return this;\
}\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), construct_move_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2)* const source) {\
    TYPE_METHOD(TYPE1, construct_move_at)(&this->first, &source->first);\
    TYPE_METHOD(TYPE2, construct_move_at)(&this->second, &source->second);\
    return this;\
}\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), destroy_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this) {\
    TYPE_METHOD(TYPE1, destroy_at)(&this->first);\
    TYPE_METHOD(TYPE2, destroy_at)(&this->second);\
    return this;\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), assign_copy_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2) const* const source) {\
    TYPE_METHOD(TYPE1, assign_copy_at)(&this->first, &source->first);\
    TYPE_METHOD(TYPE2, assign_copy_at)(&this->second, &source->second);\
    return this;\
}\
COMMON_MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), assign_move_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2)* const source) {\
    TYPE_METHOD(TYPE1, assign_move_at)(&this->first, &source->first);\
    TYPE_METHOD(TYPE2, assign_move_at)(&this->second, &source->second);\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), swap)(\
    struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
    struct PAIR_TYPE(TYPE1, TYPE2)* const another) {\
    TYPE_METHOD(TYPE1, swap)(&this->first, &another->first);\
    TYPE_METHOD(TYPE2, swap)(&this->second, &another->second);\
}
