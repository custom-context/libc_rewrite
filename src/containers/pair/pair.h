#pragma once

#include <containers/common.h>

#define PAIR_TYPE(TYPE1, TYPE2)\
    NAMESPACE_CONTAINERS(CONCAT5(pair, __, TYPE1, _, TYPE2))

#define PAIR_METHOD(TYPE1, TYPE2, METHOD)\
    TYPE_METHOD(PAIR_TYPE(TYPE1, TYPE2), METHOD)

#define DEFINE_PAIR_TYPE(TYPE1, TYPE2)\
DECLARE_STRUCT_SUBTYPE(PAIR_TYPE(TYPE1, TYPE2), first_value_type, TYPE1);\
DECLARE_STRUCT_SUBTYPE(PAIR_TYPE(TYPE1, TYPE2), second_value_type, TYPE2);\
typedef struct PAIR_TYPE(TYPE1, TYPE2) {\
    STRUCT_SUBTYPE(PAIR_TYPE(TYPE1, TYPE2), first_value_type) first;\
    STRUCT_SUBTYPE(PAIR_TYPE(TYPE1, TYPE2), second_value_type) second;\
} PAIR_TYPE(TYPE1, TYPE2)

#define DECLARE_PAIR_METHODS_WITH_MODIFIER(MODIFIER, TYPE1, TYPE2)\
    DECLARE_DEFAULT_LIFECYCLE_METHODS_WITH_MODIFIER(MODIFIER, PAIR_TYPE(TYPE1, TYPE2))

#define DEFINE_PAIR_METHODS_WITH_MODIFIER(MODIFIER, TYPE1, TYPE2)\
/* --- Construction/Destruction functions --- */\
MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    PAIR_METHOD(TYPE1, TYPE2, construct_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this) {\
    TYPE_METHOD(TYPE1, construct_at)(&this->first);\
    TYPE_METHOD(TYPE2, construct_at)(&this->second);\
    return this;\
}\
MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    PAIR_METHOD(TYPE1, TYPE2, construct_copy_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2) const* const source) {\
    TYPE_METHOD(TYPE1, construct_copy_at)(&this->first, &source->first);\
    TYPE_METHOD(TYPE2, construct_copy_at)(&this->second, &source->second);\
    return this;\
}\
MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    PAIR_METHOD(TYPE1, TYPE2, construct_move_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2)* const source) {\
    TYPE_METHOD(TYPE1, construct_move_at)(&this->first, &source->first);\
    TYPE_METHOD(TYPE2, construct_move_at)(&this->second, &source->second);\
    return this;\
}\
MODIFIER void*\
    PAIR_METHOD(TYPE1, TYPE2, destroy_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this) {\
    TYPE_METHOD(TYPE1, destroy_at)(&this->first);\
    TYPE_METHOD(TYPE2, destroy_at)(&this->second);\
    return this;\
}\
/* --- Assign functions --- */\
MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    PAIR_METHOD(TYPE1, TYPE2, assign_copy_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2) const* const source) {\
    TYPE_METHOD(TYPE1, assign_copy_at)(&this->first, &source->first);\
    TYPE_METHOD(TYPE2, assign_copy_at)(&this->second, &source->second);\
    return this;\
}\
MODIFIER struct PAIR_TYPE(TYPE1, TYPE2)*\
    PAIR_METHOD(TYPE1, TYPE2, assign_move_at)(\
        struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
        struct PAIR_TYPE(TYPE1, TYPE2)* const source) {\
    TYPE_METHOD(TYPE1, assign_move_at)(&this->first, &source->first);\
    TYPE_METHOD(TYPE2, assign_move_at)(&this->second, &source->second);\
    return this;\
}\
/* --- Swap --- */\
MODIFIER void PAIR_METHOD(TYPE1, TYPE2, swap)(\
    struct PAIR_TYPE(TYPE1, TYPE2)* const this,\
    struct PAIR_TYPE(TYPE1, TYPE2)* const another) {\
    TYPE_METHOD(TYPE1, swap)(&this->first, &another->first);\
    TYPE_METHOD(TYPE2, swap)(&this->second, &another->second);\
}
