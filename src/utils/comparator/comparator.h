#pragma once

#include <utils/common.h>

#define COMPARATOR_TYPE(NAME, TYPE)\
    NAMESPACE_UTILS(CONCAT3(NAME, __, TYPE))

#define COMPARATOR_METHOD(NAME, TYPE, METHOD)\
    TYPE_METHOD(COMPARATOR_TYPE(NAME, TYPE), METHOD)

#define DECLARE_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, NAME, TYPE)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct COMPARATOR_TYPE(NAME, TYPE)*\
    COMPARATOR_METHOD(NAME, TYPE, construct_at)(struct COMPARATOR_TYPE(NAME, TYPE)* const this);\
COMMON_MODIFIER struct COMPARATOR_TYPE(NAME, TYPE)*\
    COMPARATOR_METHOD(NAME, TYPE, construct_copy_at)(\
        struct COMPARATOR_TYPE(NAME, TYPE)* const this,\
        struct COMPARATOR_TYPE(NAME, TYPE) const* const source);\
COMMON_MODIFIER struct COMPARATOR_TYPE(NAME, TYPE)*\
    COMPARATOR_METHOD(NAME, TYPE, construct_move_at)(\
        struct COMPARATOR_TYPE(NAME, TYPE)* const this,\
        struct COMPARATOR_TYPE(NAME, TYPE)* const source);\
COMMON_MODIFIER void* COMPARATOR_METHOD(NAME, TYPE, destroy_at)(struct COMPARATOR_TYPE(NAME, TYPE)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct COMPARATOR_TYPE(NAME, TYPE)* COMPARATOR_METHOD(NAME, TYPE, assign_copy_at)(\
    struct COMPARATOR_TYPE(NAME, TYPE)* const this,\
    struct COMPARATOR_TYPE(NAME, TYPE) const* const source);\
COMMON_MODIFIER struct COMPARATOR_TYPE(NAME, TYPE)* COMPARATOR_METHOD(NAME, TYPE, assign_move_at)(\
    struct COMPARATOR_TYPE(NAME, TYPE)* const this,\
    struct COMPARATOR_TYPE(NAME, TYPE)* const source);\
/* --- Swap --- */\
COMMON_MODIFIER void COMPARATOR_METHOD(NAME, TYPE, swap)(struct COMPARATOR_TYPE(NAME, TYPE)* const this,\
    struct COMPARATOR_TYPE(NAME, TYPE)* const another);\
/* --- Compare function --- */\
COMMON_MODIFIER int COMPARATOR_METHOD(NAME, TYPE, compare)(TYPE const* const value1, TYPE const* const value2)

#define DECLARE_COMPARATOR_EXTERNAL_METHODS(NAME, TYPE)\
    DECLARE_COMPARATOR_METHODS_WITH_MODIFIER(extern, NAME, TYPE)
#define DECLARE_COMPARATOR_INTERNAL_METHODS(NAME, TYPE)\
    DECLARE_COMPARATOR_METHODS_WITH_MODIFIER(static, NAME, TYPE)
#define DECLARE_COMPARATOR_INLINE_METHODS(NAME, TYPE)\
    DECLARE_COMPARATOR_METHODS_WITH_MODIFIER(inline, NAME, TYPE)

#define DEFINE_DEFAULT_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, NAME, TYPE)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct COMPARATOR_TYPE(NAME, TYPE)*\
    COMPARATOR_METHOD(NAME, TYPE, construct_at)(struct COMPARATOR_TYPE(NAME, TYPE)* const this) {\
    return this;\
}\
COMMON_MODIFIER struct COMPARATOR_TYPE(NAME, TYPE)*\
    COMPARATOR_METHOD(NAME, TYPE, construct_copy_at)(\
        struct COMPARATOR_TYPE(NAME, TYPE)* const this,\
        struct COMPARATOR_TYPE(NAME, TYPE) const* const source) {\
    UNUSED(source);\
    return this;\
}\
COMMON_MODIFIER struct COMPARATOR_TYPE(NAME, TYPE)*\
    COMPARATOR_METHOD(NAME, TYPE, construct_move_at)(\
        struct COMPARATOR_TYPE(NAME, TYPE)* const this,\
        struct COMPARATOR_TYPE(NAME, TYPE)* const source) {\
    UNUSED(source);\
    return this;\
}\
COMMON_MODIFIER void* COMPARATOR_METHOD(NAME, TYPE, destroy_at)(struct COMPARATOR_TYPE(NAME, TYPE)* const this) {\
    return this;\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct COMPARATOR_TYPE(NAME, TYPE)* COMPARATOR_METHOD(NAME, TYPE, assign_copy_at)(\
    struct COMPARATOR_TYPE(NAME, TYPE)* const this,\
    struct COMPARATOR_TYPE(NAME, TYPE) const* const source) {\
    UNUSED(source);\
    return this;\
}\
COMMON_MODIFIER struct COMPARATOR_TYPE(NAME, TYPE)* COMPARATOR_METHOD(NAME, TYPE, assign_move_at)(\
    struct COMPARATOR_TYPE(NAME, TYPE)* const this,\
    struct COMPARATOR_TYPE(NAME, TYPE)* const source) {\
    UNUSED(source);\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void COMPARATOR_METHOD(NAME, TYPE, swap)(struct COMPARATOR_TYPE(NAME, TYPE)* const this,\
    struct COMPARATOR_TYPE(NAME, TYPE)* const another) {\
    UNUSED(this);\
    UNUSED(another);\
}\
/* --- Compare function --- */\
COMMON_MODIFIER int COMPARATOR_METHOD(NAME, TYPE, compare)(TYPE const* const value1, TYPE const* const value2)

#define DEFINE_DEFAULT_COMPARATOR_TYPE(NAME, TYPE)\
typedef struct COMPARATOR_TYPE(NAME, TYPE) {\
    char bit:1;\
} COMPARATOR_TYPE(NAME, TYPE)

// equal_to
#define EQUAL_TO_COMPARATOR_TYPE(TYPE)\
    COMPARATOR_TYPE(equal_to, TYPE)

#define DEFINE_EQUAL_TO_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
DEFINE_DEFAULT_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, equal_to, TYPE) {\
    ASSERT(value1);\
    ASSERT(value2);\
    return *value1 == *value2;\
}

// not_equal_to
#define NOT_EQUAL_TO_COMPARATOR_TYPE(TYPE)\
    COMPARATOR_TYPE(not_equal_to, TYPE)

#define DEFINE_NOT_EQUAL_TO_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
DEFINE_DEFAULT_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, not_equal_to, TYPE) {\
    ASSERT(value1);\
    ASSERT(value2);\
    return *value1 != *value2;\
}
 
// greater
#define GREATER_COMPARATOR_TYPE(TYPE)\
    COMPARATOR_TYPE(greater, TYPE)

#define DEFINE_GREATER_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
DEFINE_DEFAULT_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, greater, TYPE) {\
    ASSERT(value1);\
    ASSERT(value2);\
    return *value1 > *value2;\
}
 
// less
#define LESS_COMPARATOR_TYPE(TYPE)\
    COMPARATOR_TYPE(less, TYPE)

#define DEFINE_LESS_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
DEFINE_DEFAULT_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, less, TYPE) {\
    ASSERT(value1);\
    ASSERT(value2);\
    return *value1 < *value2;\
}
 
// greater_equal
#define GREATER_EQUAL_COMPARATOR_TYPE(TYPE)\
    COMPARATOR_TYPE(greater_equal, TYPE)

#define DEFINE_GREATER_EQUAL_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
DEFINE_DEFAULT_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, greater_equal, TYPE) {\
    ASSERT(value1);\
    ASSERT(value2);\
    return *value1 >= *value2;\
}

// less_equal
#define LESS_EQUAL_COMPARATOR_TYPE(TYPE)\
    COMPARATOR_TYPE(less_equal, TYPE)

#define DEFINE_LESS_EQUAL_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
DEFINE_DEFAULT_COMPARATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, less_equal, TYPE) {\
    ASSERT(value1);\
    ASSERT(value2);\
    return *value1 <= *value2;\
}
