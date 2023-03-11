#pragma once

#include "map_types_decl.h"

// map method
#define MAP_INTERFACE_METHOD(KEY, VALUE, METHOD) TYPE_METHOD(MAP_INTERFACE_TYPE(KEY, VALUE), METHOD)

// map's iterator method
#define MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, METHOD) TYPE_METHOD(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), METHOD)

// map's const iterator method
#define MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, METHOD) TYPE_METHOD(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), METHOD)

// map methods declaration
#define DECLARE_MAP_INTERFACE_METHODS_WITH_MODIFIER(COMMON_MODIFIER, KEY, VALUE)\
/* --- Set interface methods --- */\
struct MAP_INTERFACE_TYPE(KEY, VALUE);\
DECLARE_PAIR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char);\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, construct_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
COMMON_MODIFIER struct MAP_INTERFACE_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, construct_move_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const source);\
COMMON_MODIFIER struct MAP_INTERFACE_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, construct_copy_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const source);\
COMMON_MODIFIER void* MAP_INTERFACE_METHOD(KEY, VALUE, destroy_at)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, assign_move_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const source);\
COMMON_MODIFIER struct MAP_INTERFACE_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, assign_copy_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const source);\
/* --- Common containers' functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), size_type)\
    MAP_INTERFACE_METHOD(KEY, VALUE, size)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this);\
COMMON_MODIFIER void MAP_INTERFACE_METHOD(KEY, VALUE, clear)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
/* --- Elements' manipulation functions --- */\
/* --- --- insert element --- --- */\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_copy)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type) const* const value);\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_move)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type)* const value);\
/* --- --- insert or assign key-value --- --- */\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_or_assign_with_key_copy_value_copy)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type) const* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const* const value);\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_or_assign_with_key_move_value_copy)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type)* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const* const value);\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_or_assign_with_key_copy_value_move)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type) const* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)* const value);\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_or_assign_with_key_move_value_move)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type)* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)* const value);\
/* --- --- direct value access by key --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const*\
    MAP_INTERFACE_METHOD(KEY, VALUE, at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this,\
        KEY const* const key);\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, mut_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        KEY const* const key);\
/* --- --- find element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type)\
    MAP_INTERFACE_METHOD(KEY, VALUE, find)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this,\
        KEY const* const key);\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type)\
    MAP_INTERFACE_METHOD(KEY, VALUE, mut_find)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        KEY const* const key);\
/* --- --- erase element by iterator --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type)\
    MAP_INTERFACE_METHOD(KEY, VALUE, erase_by_iterator)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) iterator);\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type)\
    MAP_INTERFACE_METHOD(KEY, VALUE, erase_by_const_iterator)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type) iterator);\
/* --- Iterators' related methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type)\
    MAP_INTERFACE_METHOD(KEY, VALUE, begin)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type)\
    MAP_INTERFACE_METHOD(KEY, VALUE, end)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type)\
    MAP_INTERFACE_METHOD(KEY, VALUE, cbegin)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type)\
    MAP_INTERFACE_METHOD(KEY, VALUE, cend)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
/* --- Mutable iterator's methods --- */\
struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE);\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, construct_at)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, construct_move_at)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const source);\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, construct_copy_at)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const source);\
COMMON_MODIFIER void* MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, destroy_at)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, assign_move_at)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const source);\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, assign_copy_at)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const source);\
/* --- Swap --- */\
COMMON_MODIFIER void\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, swap)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const source);\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), key_type) const*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, key)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), mapped_type)*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, value)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), mapped_type) const*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, const_value)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const this);\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, compare)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const this,\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const source);\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, next)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, pnext)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, prev)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, pprev)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
/* --- Const iterator's methods --- */\
struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE);\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, construct_at)(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, construct_move_at)(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const source);\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, construct_copy_at)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const source);\
COMMON_MODIFIER void* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, destroy_at)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, assign_move_at)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const source);\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, assign_copy_at)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const source);\
/* --- Swap --- */\
COMMON_MODIFIER void\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, swap)(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const source);\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), key_type) const*\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, key)(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), mapped_type)*\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, value)(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), mapped_type) const*\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, const_value)(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const this);\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, compare)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const this,\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const source);\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, next)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, pnext)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, prev)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, pprev)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this)

#define DECLARE_MAP_INTERFACE_METHODS(KEY, VALUE) DECLARE_MAP_INTERFACE_METHODS_WITH_MODIFIER(, TYPE)
#define DECLARE_MAP_INTERFACE_STATIC_METHODS(KEY, VALUE) DECLARE_MAP_INTERFACE_METHODS_WITH_MODIFIER(static, TYPE)
#define DECLARE_MAP_INTERFACE_INLINE_METHODS(KEY, VALUE) DECLARE_MAP_INTERFACE_METHODS_WITH_MODIFIER(inline, TYPE)
#define DECLARE_MAP_INTERFACE_EXTERNAL_METHODS(KEY, VALUE) DECLARE_MAP_INTERFACE_METHODS_WITH_MODIFIER(extern, TYPE)
#define DECLARE_MAP_INTERFACE_EXTERNAL_INLINE_METHODS(KEY, VALUE) DECLARE_MAP_INTERFACE_METHODS_WITH_MODIFIER(extern inline, TYPE)
