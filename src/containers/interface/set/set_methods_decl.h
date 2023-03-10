#pragma once

#include "set_types_decl.h"

// set method
#define SET_INTERFACE_METHOD(TYPE, METHOD) TYPE_METHOD(SET_INTERFACE_TYPE(TYPE), METHOD)

// set's iterator method
#define SET_INTERFACE_ITERATOR_METHOD(TYPE, METHOD) TYPE_METHOD(SET_INTERFACE_ITERATOR_TYPE(TYPE), METHOD)

// set's const iterator method
#define SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, METHOD) TYPE_METHOD(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), METHOD)

// set methods declaration
#define DECLARE_SET_INTERFACE_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
/* --- Set interface methods --- */\
struct SET_INTERFACE_TYPE(TYPE);\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_TYPE(TYPE)* SET_INTERFACE_METHOD(TYPE, construct_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this);\
COMMON_MODIFIER struct SET_INTERFACE_TYPE(TYPE)* SET_INTERFACE_METHOD(TYPE, construct_move_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_TYPE(TYPE)* const source);\
COMMON_MODIFIER struct SET_INTERFACE_TYPE(TYPE)* SET_INTERFACE_METHOD(TYPE, construct_copy_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_TYPE(TYPE) const* const source);\
COMMON_MODIFIER void* SET_INTERFACE_METHOD(TYPE, destroy_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_TYPE(TYPE)* SET_INTERFACE_METHOD(TYPE, assign_move_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_TYPE(TYPE)* const source);\
COMMON_MODIFIER struct SET_INTERFACE_TYPE(TYPE)* SET_INTERFACE_METHOD(TYPE, assign_copy_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_TYPE(TYPE) const* const source);\
/* --- Common containers' functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), size_type) SET_INTERFACE_METHOD(TYPE, size)(\
    struct SET_INTERFACE_TYPE(TYPE) const* const this);\
COMMON_MODIFIER void SET_INTERFACE_METHOD(TYPE, clear)(struct SET_INTERFACE_TYPE(TYPE)* const this);\
/* --- Elements' manipulation functions --- */\
/* --- --- insert element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_METHOD(TYPE, insert_copy)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    TYPE const* const value);\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_METHOD(TYPE, insert_move)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    TYPE* const value);\
/* --- --- find element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) SET_INTERFACE_METHOD(TYPE, find)(\
    struct SET_INTERFACE_TYPE(TYPE) const* const this,\
    TYPE const* const value);\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_METHOD(TYPE, mut_find)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    TYPE const* const value);\
/* --- --- erase element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_METHOD(TYPE, erase_by_iterator)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) iterator);\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_METHOD(TYPE, erase_by_const_iterator)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) iterator);\
/* --- Iterators' related methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_METHOD(TYPE, begin)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_METHOD(TYPE, end)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) SET_INTERFACE_METHOD(TYPE, cbegin)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) SET_INTERFACE_METHOD(TYPE, cend)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this);\
/* --- Mutable iterator's methods --- */\
struct SET_INTERFACE_ITERATOR_TYPE(TYPE);\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* SET_INTERFACE_ITERATOR_METHOD(TYPE, construct_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* SET_INTERFACE_ITERATOR_METHOD(TYPE, construct_move_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const source);\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* SET_INTERFACE_ITERATOR_METHOD(TYPE, construct_copy_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const source);\
COMMON_MODIFIER void* SET_INTERFACE_ITERATOR_METHOD(TYPE, destroy_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* SET_INTERFACE_ITERATOR_METHOD(TYPE, assign_move_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const source);\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* SET_INTERFACE_ITERATOR_METHOD(TYPE, assign_copy_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const source);\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE), value_type)* SET_INTERFACE_ITERATOR_METHOD(TYPE, value)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE), value_type) const* SET_INTERFACE_ITERATOR_METHOD(TYPE, const_value)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const this);\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int SET_INTERFACE_ITERATOR_METHOD(TYPE, compare)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const this,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const source);\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE) SET_INTERFACE_ITERATOR_METHOD(TYPE, next)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE) SET_INTERFACE_ITERATOR_METHOD(TYPE, pnext)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE) SET_INTERFACE_ITERATOR_METHOD(TYPE, prev)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE) SET_INTERFACE_ITERATOR_METHOD(TYPE, pprev)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
/* --- Const iterator's methods --- */\
struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE);\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, construct_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, construct_move_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const source);\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, construct_copy_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const source);\
COMMON_MODIFIER void* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, destroy_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, assign_move_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const source);\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, assign_copy_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const source);\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), value_type)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, value)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), value_type) const* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, const_value)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const this);\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, compare)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const this,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const source);\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, next)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, pnext)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, prev)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, pprev)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this)

#define DECLARE_SET_INTERFACE_METHODS(TYPE) DECLARE_SET_INTERFACE_METHODS_WITH_MODIFIER(, TYPE)
#define DECLARE_SET_INTERFACE_STATIC_METHODS(TYPE) DECLARE_SET_INTERFACE_METHODS_WITH_MODIFIER(static, TYPE)
#define DECLARE_SET_INTERFACE_INLINE_METHODS(TYPE) DECLARE_SET_INTERFACE_METHODS_WITH_MODIFIER(inline, TYPE)
#define DECLARE_SET_INTERFACE_EXTERNAL_METHODS(TYPE) DECLARE_SET_INTERFACE_METHODS_WITH_MODIFIER(extern, TYPE)
#define DECLARE_SET_INTERFACE_EXTERNAL_INLINE_METHODS(TYPE) DECLARE_SET_INTERFACE_METHODS_WITH_MODIFIER(extern inline, TYPE)
