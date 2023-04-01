#pragma once

#include "rb_tree_set_types_decl.h"

// set method
#define RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, METHOD)\
    TYPE_METHOD(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), METHOD)

// set's iterator method
#define RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, METHOD)\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), METHOD)

// set's const iterator method
#define RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, METHOD)\
    TYPE_METHOD(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), METHOD)

// set methods declaration
#define DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(COMMON_MODIFIER, TYPE, COMPARATOR, ALLOCATOR)\
/* --- Set interface methods --- */\
struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR);\
/* --- Static cast to set interface --- */\
DECLARE_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
    SET_INTERFACE_TYPE(TYPE));\
DECLARE_CONST_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
    SET_INTERFACE_TYPE(TYPE));\
DECLARE_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    SET_INTERFACE_TYPE(TYPE),\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR));\
DECLARE_CONST_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    SET_INTERFACE_TYPE(TYPE),\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR));\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_with_allocator_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct ALLOCATOR const* const allocator);\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_move_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source);\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source);\
COMMON_MODIFIER void* RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_move_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source);\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_copy_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source);\
/* --- Swap --- */\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const another);\
/* --- Common containers' functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), size_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, size)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this);\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, clear)(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* --- Elements' manipulation functions --- */\
/* --- --- insert element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, insert_copy)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        TYPE const* const value);\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, insert_move)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        TYPE* const value);\
/* --- --- find element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, find)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this,\
        TYPE const* const value);\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, mut_find)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        TYPE const* const value);\
/* --- --- erase element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, erase_by_iterator)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator);\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, erase_by_const_iterator)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator);\
/* --- Nodes related private methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node);\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(destroy_subtree_at))(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) * const node);\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(swap_nodes))(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node1,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node2);\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node,\
        TYPE const* const value);\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node,\
    usize const direction);\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node);\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_erasement))(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node);\
/* --- Iterators' related methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, begin)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, end)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, cbegin)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, cend)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* --- Mutable iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_move_at)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source);\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source);\
COMMON_MODIFIER void* RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_move_at)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source);\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_copy_at)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source);\
/* --- Swap --- */\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const another);\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, value)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type) const*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, const_value)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this);\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, compare)(\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this,\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source);\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, next)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, pnext)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, prev)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, pprev)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* --- Const iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_move_at)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source);\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source);\
COMMON_MODIFIER void* RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* --- Assign functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_move_at)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source);\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_copy_at)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source);\
/* --- Swap --- */\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const another);\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, value)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type) const*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, const_value)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this);\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, compare)(\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this,\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source);\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, next)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, pnext)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, prev)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this);\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, pprev)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this)

#define DECLARE_SET_INTERFACE_WITH_COMPARATOR_AND_ALLOCATOR_METHODS(TYPE, COMPARATOR, ALLOCATOR) DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(, TYPE, COMPARATOR, ALLOCATOR)
#define DECLARE_SET_INTERFACE_WITH_COMPARATOR_AND_ALLOCATOR_STATIC_METHODS(TYPE, COMPARATOR, ALLOCATOR) DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(static, TYPE, COMPARATOR, ALLOCATOR)
#define DECLARE_SET_INTERFACE_WITH_COMPARATOR_AND_ALLOCATOR_INLINE_METHODS(TYPE, COMPARATOR, ALLOCATOR) DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(inline, TYPE, COMPARATOR, ALLOCATOR)
#define DECLARE_SET_INTERFACE_WITH_COMPARATOR_AND_ALLOCATOR_EXTERNAL_METHODS(TYPE, COMPARATOR, ALLOCATOR) DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(extern, TYPE, COMPARATOR, ALLOCATOR)
#define DECLARE_SET_INTERFACE_WITH_COMPARATOR_AND_ALLOCATOR_EXTERNAL_INLINE_METHODS(TYPE, COMPARATOR, ALLOCATOR) DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(extern inline, TYPE, COMPARATOR, ALLOCATOR)
