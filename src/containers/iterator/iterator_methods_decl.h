#pragma once

#include <containers/common.h>

#define DECLARE_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, ITERATOR_TYPE)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct ITERATOR_TYPE* TYPE_METHOD(ITERATOR_TYPE, construct_at)(struct ITERATOR_TYPE* const this);\
COMMON_MODIFIER struct ITERATOR_TYPE* TYPE_METHOD(ITERATOR_TYPE, construct_copy_at)(struct ITERATOR_TYPE* const this, struct ITERATOR_TYPE const* const source);\
COMMON_MODIFIER struct ITERATOR_TYPE* TYPE_METHOD(ITERATOR_TYPE, construct_move_at)(struct ITERATOR_TYPE* const this, struct ITERATOR_TYPE* const source);\
COMMON_MODIFIER void* TYPE_METHOD(ITERATOR_TYPE, destroy_at)(struct ITERATOR_TYPE* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct ITERATOR_TYPE* TYPE_METHOD(ITERATOR_TYPE, assign_copy_at)(struct ITERATOR_TYPE* const this, struct ITERATOR_TYPE const* const source);\
COMMON_MODIFIER struct ITERATOR_TYPE* TYPE_METHOD(ITERATOR_TYPE, assign_move_at)(struct ITERATOR_TYPE* const this, struct ITERATOR_TYPE* const source);\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(ITERATOR_TYPE, value_type)* TYPE_METHOD(ITERATOR_TYPE, value)(struct ITERATOR_TYPE* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(ITERATOR_TYPE, value_type) const* TYPE_METHOD(ITERATOR_TYPE, const_value)(struct ITERATOR_TYPE const* const this);\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either (for random-access iterators 1 if iterator_1 > iterator_2 & -1 if iterator_1 < iterator_2)*/\
COMMON_MODIFIER int TYPE_METHOD(ITERATOR_TYPE, compare)(struct ITERATOR_TYPE const* const iterator_1, struct ITERATOR_TYPE const* const iterator_2)

#define IS_ITERATOR(ITERATOR_TYPE)\
    (sizeof(STRUCT_SUBTYPE(ITERATOR_TYPE, value_type)) && \
    &TYPE_METHOD(ITERATOR_TYPE, construct_at) && \
    &TYPE_METHOD(ITERATOR_TYPE, construct_copy_at) && \
    &TYPE_METHOD(ITERATOR_TYPE, construct_move_at) && \
    &TYPE_METHOD(ITERATOR_TYPE, destroy_at) && \
    &TYPE_METHOD(ITERATOR_TYPE, assign_copy_at) && \
    &TYPE_METHOD(ITERATOR_TYPE, assign_move_at) && \
    &TYPE_METHOD(ITERATOR_TYPE, value) && \
    &TYPE_METHOD(ITERATOR_TYPE, compare))

#define DECLARE_FORWARD_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, ITERATOR_TYPE)\
DECLARE_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, ITERATOR_TYPE);\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct ITERATOR_TYPE TYPE_METHOD(ITERATOR_TYPE, next)(struct ITERATOR_TYPE* const this);\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct ITERATOR_TYPE TYPE_METHOD(ITERATOR_TYPE, pnext)(struct ITERATOR_TYPE* const this)

#define IS_FORWARD_ITERATOR(ITERATOR_TYPE)\
    (IS_ITERATOR(ITERATOR_TYPE) && \
    &TYPE_METHOD(ITERATOR_TYPE, next) && \
    &TYPE_METHOD(ITERATOR_TYPE, pnext))

#define DECLARE_BIDIRECTIONAL_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, ITERATOR_TYPE)\
DECLARE_FORWARD_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, ITERATOR_TYPE);\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct ITERATOR_TYPE TYPE_METHOD(ITERATOR_TYPE, prev)(struct ITERATOR_TYPE* const this);\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct ITERATOR_TYPE TYPE_METHOD(ITERATOR_TYPE, pprev)(struct ITERATOR_TYPE* const this)

#define IS_BIDIRECTIONAL_ITERATOR(ITERATOR_TYPE)\
    (IS_FORWARD_ITERATOR(ITERATOR_TYPE) && \
    &TYPE_METHOD(ITERATOR_TYPE, prev) && \
    &TYPE_METHOD(ITERATOR_TYPE, pprev))

#define DECLARE_RANDOM_ACCESS_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, ITERATOR_TYPE)\
DECLARE_BIDIRECTIONAL_ITERATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, ITERATOR_TYPE);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct ITERATOR_TYPE* TYPE_METHOD(ITERATOR_TYPE, add_in_place)(struct ITERATOR_TYPE* const this, STRUCT_SUBTYPE(ITERATOR_TYPE, difference_type) const offset);\
COMMON_MODIFIER struct ITERATOR_TYPE* TYPE_METHOD(ITERATOR_TYPE, sub_in_place)(struct ITERATOR_TYPE* const this, STRUCT_SUBTYPE(ITERATOR_TYPE, difference_type) const offset);\
/* --- Shift functions --- */\
COMMON_MODIFIER struct ITERATOR_TYPE TYPE_METHOD(ITERATOR_TYPE, add)(struct ITERATOR_TYPE const* const this, STRUCT_SUBTYPE(ITERATOR_TYPE, difference_type) const offset);\
COMMON_MODIFIER struct ITERATOR_TYPE TYPE_METHOD(ITERATOR_TYPE, sub)(struct ITERATOR_TYPE const* const this, STRUCT_SUBTYPE(ITERATOR_TYPE, difference_type) const offset);\
COMMON_MODIFIER STRUCT_SUBTYPE(ITERATOR_TYPE, difference_type) TYPE_METHOD(ITERATOR_TYPE, offset)(struct ITERATOR_TYPE const* const this, struct ITERATOR_TYPE const* const another_iterator);\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(ITERATOR_TYPE, value_type)* TYPE_METHOD(ITERATOR_TYPE, mut_at)(struct ITERATOR_TYPE* const this, STRUCT_SUBTYPE(ITERATOR_TYPE, difference_type) const offset);\
COMMON_MODIFIER STRUCT_SUBTYPE(ITERATOR_TYPE, value_type) const* TYPE_METHOD(ITERATOR_TYPE, at)(struct ITERATOR_TYPE const* const this, STRUCT_SUBTYPE(ITERATOR_TYPE, difference_type) const offset)

#define IS_RANDOM_ACCESS_ITERATOR(ITERATOR_TYPE)\
    (IS_BIDIRECTIONAL_ITERATOR(ITERATOR_TYPE) && \
    sizeof(STRUCT_SUBTYPE(ITERATOR_TYPE, difference_type)) && \
    &TYPE_METHOD(ITERATOR_TYPE, add_in_place) && \
    &TYPE_METHOD(ITERATOR_TYPE, sub_in_place) && \
    &TYPE_METHOD(ITERATOR_TYPE, add) && \
    &TYPE_METHOD(ITERATOR_TYPE, sub) && \
    &TYPE_METHOD(ITERATOR_TYPE, offset) && \
    &TYPE_METHOD(ITERATOR_TYPE, at))
