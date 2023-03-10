#pragma once

#include "rb_tree_set_methods_decl.h"

#include <stddef.h>

static int debug_enabled = 0u;
static int debug_rebalance_iteration = 0u;

// set methods definition
#define DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(COMMON_MODIFIER, TYPE, COMPARATOR, ALLOCATOR)\
/* --- Set interface methods --- */\
struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR);\
/* --- Static cast to set interface --- */\
DECLARE_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
    SET_INTERFACE_TYPE(TYPE)) {\
    return &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE));\
}\
DECLARE_CONST_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
    SET_INTERFACE_TYPE(TYPE)) {\
    return &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE));\
}\
DECLARE_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    SET_INTERFACE_TYPE(TYPE),\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)) {\
    return (void*)((char*)this -\
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE))));\
}\
DECLARE_CONST_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    SET_INTERFACE_TYPE(TYPE),\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)) {\
    return (void const*)((char const*)this -\
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE))));\
}\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_with_allocator_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct ALLOCATOR const* const allocator) {\
    ASSERT(this);\
    ASSERT(allocator);\
    TYPE_METHOD(SET_INTERFACE_TYPE(TYPE), construct_at)(&this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            SET_INTERFACE_TYPE(TYPE));\
    TYPE_METHOD(ALLOCATOR, construct_copy_at)(&this->allocator, allocator);\
    TYPE_METHOD(COMPARATOR, construct_at)(&this->comparator);\
    this->root = NULL;\
    this->size = 0u;\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    TYPE_METHOD(SET_INTERFACE_TYPE(TYPE), construct_at)(&this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            SET_INTERFACE_TYPE(TYPE));\
    TYPE_METHOD(ALLOCATOR, construct_at)(&this->allocator);\
    TYPE_METHOD(COMPARATOR, construct_at)(&this->comparator);\
    this->root = NULL;\
    this->size = 0u;\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_move_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_at)(this);\
    TYPE_METHOD(ALLOCATOR, construct_move_at)(&this->allocator, &source->allocator);\
    TYPE_METHOD(COMPARATOR, construct_move_at)(&this->comparator, &source->comparator);\
    this->root = source->root; source->root = NULL;\
    this->size = source->size; source->size = 0u;\
    return this;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(construct_subtree_copy_at))(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const target,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* const source) {\
    ASSERT(this);\
    ASSERT(target);\
    ASSERT(source);\
    TYPE_METHOD(TYPE, construct_copy_at)(&target->value, &source->value);\
    for (size_t child_index = 0u; child_index < sizeof(target->child) / sizeof(*target->child); ++child_index) {\
        if (!source->child[child_index]) {\
            target->child[child_index] = NULL;\
            continue;\
        }\
        target->child[child_index] = TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u);\
        RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(construct_subtree_copy_at))(this,\
            target->child[child_index],\
            source->child[child_index]\
        )->parent = target;\
    }\
    return target;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_at)(this);\
    TYPE_METHOD(ALLOCATOR, construct_copy_at)(&this->allocator, &source->allocator);\
    TYPE_METHOD(COMPARATOR, construct_copy_at)(&this->comparator, &source->comparator);\
    if (source->root) {\
        this->root = TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u);\
        RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(construct_subtree_copy_at))(\
            this, this->root, source->root);\
    }\
    this->size = source->size;\
    return this;\
}\
COMMON_MODIFIER void* RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->destroy_at);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->destroy_at(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE))\
    );\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_move_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source) {\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_move_at)(&temporary, source);\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_copy_at)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source) {\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(&temporary, source);\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const another) {\
    {\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* temporary;\
        temporary = this->root;\
        this->root = another->root;\
        another->root = temporary;\
    }\
    {\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), size_type) temporary;\
        temporary = this->size;\
        this->size = another->size;\
        another->size = temporary;\
    }\
    TYPE_METHOD(ALLOCATOR, swap)(&this->allocator, &another->allocator);\
    TYPE_METHOD(COMPARATOR, swap)(&this->comparator, &another->comparator);\
}\
/* --- Common containers' functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), size_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, size)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->size);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->size(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE))\
    );\
}\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, clear)(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->clear);\
    this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->clear(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE))\
    );\
}\
/* --- Elements' manipulation functions --- */\
/* --- --- insert element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, insert_copy)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        TYPE const* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->insert_copy);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)) = this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->insert_copy(\
            &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)),\
            value\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, insert_move)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        TYPE* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->insert_move);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)) = this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->insert_move(\
            &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)),\
            value\
        )\
    };\
    return iterator;\
}\
/* --- --- find element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, find)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this,\
        TYPE const* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->find);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator = {\
        .INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)) = this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->find(\
            &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)),\
            value\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, mut_find)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        TYPE const* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->mut_find);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)) = this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->mut_find(\
            &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)),\
            value\
        )\
    };\
    return iterator;\
}\
/* --- --- erase element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, erase_by_iterator)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) position) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->erase_by_iterator);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)) = this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->erase_by_iterator(\
            &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)),\
            position.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, erase_by_const_iterator)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type) position) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->erase_by_const_iterator);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)) = this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->erase_by_const_iterator(\
            &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)),\
            position.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))\
        )\
    };\
    return iterator;\
}\
/* --- Nodes related private methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node) {\
    ASSERT(node);\
    node->parent = NULL;\
    for (size_t child_index = 0u; child_index < sizeof(node->child) / sizeof(*node->child); ++child_index) {\
        node->child[child_index] = NULL;\
    }\
    node->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED);\
    return node;\
}\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(destroy_subtree_at))(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node) {\
    ASSERT(this);\
    ASSERT(node);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node_child;\
    for (size_t child_index = 0u; child_index < sizeof(node->child) / sizeof(*node->child); ++child_index) {\
        node_child = node->child[child_index];\
        if (node_child) {\
            RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(destroy_subtree_at))(this, node_child);\
        }\
    }\
    TYPE_METHOD(TYPE, destroy_at)(&node->value);\
    TYPE_METHOD(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
}\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(swap_nodes))(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node1,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node2) {\
    ASSERT(this);\
    ASSERT(node1);\
    ASSERT(node2);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* temporary;\
    /* swap direct pointers */\
    /* swap parents */\
    temporary = node1->parent;\
    node1->parent = node2->parent;\
    node2->parent = temporary;\
    /* swap children */\
    for (size_t child_index = 0u; child_index < sizeof(node1->child) / sizeof(*node1->child); ++child_index) {\
        temporary = node1->child[child_index];\
        node1->child[child_index] = node2->child[child_index];\
        node2->child[child_index] = temporary;\
    }\
    /* relax pointers */\
    /* relax parents */\
    if (node1->parent == node1) {\
        node1->parent = node2;\
    }\
    if (node2->parent == node2) {\
        node2->parent = node1;\
    }\
    /* relax children */\
    for (size_t child_index = 0u; child_index < sizeof(node1->child) / sizeof(*node1->child); ++child_index) {\
        if (node1->child[child_index] == node1) {\
            node1->child[child_index] = node2;\
        }\
        if (node2->child[child_index] == node2) {\
            node2->child[child_index] = node1;\
        }\
    }\
    /* swap indirect pointers */\
    /* swap parents' pointers */\
    if (node1->parent) {\
        if (node1->parent != node2) {\
            node1->parent->child[node1->parent->child[1u] == node2] = node1;\
        }\
    } else {\
        this->root = node1;\
    }\
    if (node2->parent) {\
        if (node2->parent != node1) {\
            node2->parent->child[node2->parent->child[1u] == node1] = node2;\
        }\
    } else {\
        this->root = node2;\
    }\
    /* swap children's pointers */\
    for (size_t child_index = 0u; child_index < sizeof(node1->child) / sizeof(*node1->child); ++child_index) {\
        if (node1->child[child_index]) {\
            node1->child[child_index]->parent = node1;\
        }\
        if (node2->child[child_index]) {\
            node2->child[child_index]->parent = node2;\
        }\
    }\
    /* swap colors */\
    enum RED_BLACK_TREE_SET_NODE_COLOR_ENUM(TYPE) temporary_color = node1->color;\
    node1->color = node2->color;\
    node2->color = temporary_color;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)*\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node,\
        TYPE const* const value) {\
    ASSERT(this);\
    ASSERT(node);\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* result = node;\
    while (result) {\
        if (TYPE_METHOD(COMPARATOR, compare)(value, &result->value)) {\
            if (result->child[1u]) {\
                result = result->child[1u];\
                continue;\
            }\
            break;\
        }\
        if (TYPE_METHOD(COMPARATOR, compare)(&result->value, value)) {\
            if (result->child[0u]) {\
                result = result->child[0u];\
                continue;\
            }\
            break;\
        }\
        break;\
    }\
    return result;\
}\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const node,\
    size_t const move_direction) {\
    ASSERT(this);\
    ASSERT(node);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const parent = node->parent;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const outer_child = node->child[1u - move_direction];\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const outer_child__inner_child = outer_child->child[move_direction];\
    \
    node->child[1u - move_direction] = outer_child__inner_child;\
    if (outer_child__inner_child) {\
        outer_child__inner_child->parent = node;\
    }\
    \
    outer_child->child[move_direction] = node;\
    node->parent = outer_child;\
    \
    outer_child->parent = parent;\
    if (parent) {\
        parent->child[parent->child[1u] == node] = outer_child;\
        return;\
    }\
    this->root = outer_child;\
}\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node) {\
    ASSERT(this);\
    ASSERT(node);\
    while (node->parent &&\
        node->parent->color != RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK)) {\
        if (debug_enabled) { debug_rebalance_iteration++; }\
        if (debug_enabled) {\
            LOG_DEBUG_FORMAT("rebalance iteration: %d\n", debug_rebalance_iteration);\
        }\
        /* parent exists & it's red */\
        if (debug_enabled) {\
            LOG_DEBUG("parent exists & it's red\n");\
        }\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* parent = node->parent;\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* grandparent = parent->parent;\
        if (!grandparent) {\
            /* case 4: parent is a root => repaint it & return */\
            if (debug_enabled) {\
                LOG_DEBUG("case 4: parent is a root => repaint it & return\n");\
            }\
            parent->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            if (debug_enabled) { debug_rebalance_iteration = 0u; }\
            return;\
        }\
        /* grandparent exists & it's black ('couse parent is red) */\
        if (debug_enabled) {\
            LOG_DEBUG("grandparent exists & it's black ('couse parent is red)\n");\
        }\
        size_t parent_direction = grandparent->child[1u] == parent;\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const uncle = grandparent->child[1u - parent_direction];\
        if (uncle &&\
            uncle->color != RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK)) {\
            /* case 2: uncle exists is red => repaint parent/grandparent/uncle, set node <- grandparent & continue */\
            if (debug_enabled) {\
                LOG_DEBUG("case 2: uncle exists is red => repaint parent/grandparent/uncle, set node <- grandparent & continue\n");\
            }\
            parent->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            uncle->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            grandparent->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED);\
            node = grandparent;\
            continue;\
        }\
        /* uncle isn't exist or it's black */\
        if (debug_enabled) {\
            LOG_DEBUG("uncle isn't exist or it's black\n");\
        }\
        if (node == parent->child[1u - parent_direction]) {\
            /* case 5: node is an inner node => rotate parent/node & set node <- parent */\
            if (debug_enabled) {\
                LOG_DEBUG("case 5: node is an inner node => rotate parent/node & set node <- parent\n");\
            }\
            RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                parent, parent_direction);\
            node = parent;\
            parent = grandparent->child[parent_direction];\
        }\
        /* case 6: node is an outer node => rotate grandparent/parent, repaint them & return */\
        if (debug_enabled) {\
            LOG_DEBUG("case 6: node is an outer node => rotate grandparent/parent, repaint them & return\n");\
        }\
        RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
            grandparent, 1u - parent_direction);\
        parent->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
        grandparent->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED);\
        if (debug_enabled) { debug_rebalance_iteration = 0u; }\
        return;\
    }\
}\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_erasement))(\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node) {\
    size_t node_index;\
    do {\
        node_index = node->parent->child[1u] == node;\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* parent = node->parent;\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* sibling = parent->child[1u - node_index];\
        /* node must be black here => parent is red/black => sibling exists (it's red/black) */\
        ASSERT(sibling);\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* sibling_distant_child = sibling->child[1u - node_index];\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* sibling_close_child = sibling->child[node_index];\
        if (sibling->color == RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED)) {\
            /* case 3: sibling is red => parent & sibling's children exist and they're black */\
            if (debug_enabled) {\
                LOG_DEBUG("case 3: sibling is red => parent & sibling's children exist and they're black\n");\
            }\
            RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                parent,\
                node_index);\
            parent->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED);\
            sibling->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            sibling = sibling_close_child;\
            sibling_close_child = sibling->child[node_index];\
            sibling_distant_child = sibling->child[1u - node_index];\
            /* 3 -> check 6, check 5, else check 4 */\
        }\
        if (sibling_distant_child != NULL &&\
            sibling_distant_child->color == RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED)) {\
            /* case 6: sibling's distant child exists & it's red => sibling is black */\
            if (debug_enabled) {\
                LOG_DEBUG("case 6: sibling's distant child exists & it's red => sibling is black\n");\
            }\
            RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                parent,\
                node_index);\
            sibling->color = parent->color;\
            parent->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            sibling_distant_child->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            break;\
        }\
        if (sibling_close_child != NULL &&\
            sibling_close_child->color == RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED)) {\
            /* case 5: sibling's close child exists & it's red (& sibling's distant child is null/black) => sibling is black */\
            if (debug_enabled) {\
                LOG_DEBUG("case 5: sibling's close child exists & it's red (& sibling's distant child is null/black) => sibling is black\n");\
            }\
            RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                sibling,\
                1u - node_index);\
            sibling->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED);\
            sibling_close_child->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            sibling_distant_child = sibling;\
            sibling = sibling_close_child;\
            /* sibling_distant_child is red & sibling is black -> go to 6! [we're don't use goto, sorry] */\
            /* case 6: sibling's distant child exists & it's red => sibling is black */\
            if (debug_enabled) {\
                LOG_DEBUG("case 6 (from 5): sibling's distant child exists & it's red => sibling is black\n");\
            }\
            RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                parent,\
                node_index);\
            sibling->color = parent->color;\
            parent->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            sibling_distant_child->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            break;\
        }\
        if (parent->color == RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED)) {\
            /* case 4: parent is red => sibling & its' children are black */\
            if (debug_enabled) {\
                LOG_DEBUG("case 4: parent is red => sibling & its' children are black\n");\
            }\
            sibling->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED);\
            parent->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            break;\
        }\
        /* case 2: parent/sibling & its' children are black */\
        if (debug_enabled) {\
            LOG_DEBUG("case 2: parent/sibling & its' children are black\n");\
        }\
        sibling->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED);\
        node = parent;\
    } while (node->parent);\
}\
/* --- Iterators' related methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, begin)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->begin);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)) = this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->begin(\
            &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE))\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, end)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->end);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)) = this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->end(\
            &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE))\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, cbegin)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->cbegin);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator = {\
        .INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)) = this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->cbegin(\
            &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE))\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, cend)(\
        struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->cend);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator = {\
        .INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)) = this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->cend(\
            &this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE))\
        )\
    };\
    return iterator;\
}\
/* --- Mutable iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    TYPE_METHOD(SET_INTERFACE_ITERATOR_TYPE(TYPE), construct_at)(&this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_move_at)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source) {\
    return RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(this, source);\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_at)(this);\
    this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = source->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage;\
    return this;\
}\
COMMON_MODIFIER void* RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->destroy_at);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->destroy_at(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))\
    );\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_move_at)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source) {\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_move_at)(&temporary, source);\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_copy_at)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source) {\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(&temporary, source);\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const another) {\
    ASSERT(this);\
    ASSERT(another);\
    void* const temporary = this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage;\
    this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = another->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage;\
    another->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = temporary;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, value)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->value);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->value(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))\
    );\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type) const*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, const_value)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->const_value);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->const_value(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))\
    );\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, compare)(\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this,\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->compare);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->compare(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)),\
        &source->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))\
    );\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, next)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->next);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->next(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))\
    );\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, pnext)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->pnext);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->pnext(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))\
    );\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, prev)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->prev);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->prev(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))\
    );\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, pprev)(\
        struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->pprev);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->pprev(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))\
    );\
}\
/* --- Const iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    TYPE_METHOD(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), construct_at)(&this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)));\
    this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_move_at)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source) {\
    return RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(this, source);\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_at)(this);\
    this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage = source->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage;\
    return this;\
}\
COMMON_MODIFIER void* RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->destroy_at);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->destroy_at(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))\
    );\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_move_at)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const source) {\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_move_at)(&temporary, source);\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, assign_copy_at)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source) {\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, construct_copy_at)(&temporary, source);\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, swap)(\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this,\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const another) {\
    ASSERT(this);\
    ASSERT(another);\
    void const* const temporary = this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage;\
    this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage = another->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage;\
    another->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage = temporary;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, value)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->value);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->value(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))\
    );\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type) const*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, const_value)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->const_value);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->const_value(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))\
    );\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, compare)(\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this,\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->compare);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->compare(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)),\
        &source->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))\
    );\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, next)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->next);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->next(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))\
    );\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, pnext)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->pnext);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->pnext(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))\
    );\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, prev)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->prev);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->prev(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))\
    );\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, pprev)(\
        struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)));\
    ASSERT(this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->pprev);\
    return this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->pprev(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))\
    );\
}

#define DEFINE_SET_INTERFACE_WITH_COMPARATOR_AND_ALLOCATOR_METHODS(TYPE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(, TYPE, COMPARATOR, ALLOCATOR)
#define DEFINE_SET_INTERFACE_WITH_COMPARATOR_AND_ALLOCATOR_STATIC_METHODS(TYPE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(static, TYPE, COMPARATOR, ALLOCATOR)
#define DEFINE_SET_INTERFACE_WITH_COMPARATOR_AND_ALLOCATOR_INLINE_METHODS(TYPE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(inline, TYPE, COMPARATOR, ALLOCATOR)
#define DEFINE_SET_INTERFACE_WITH_COMPARATOR_AND_ALLOCATOR_EXTERNAL_METHODS(TYPE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(extern, TYPE, COMPARATOR, ALLOCATOR)
#define DEFINE_SET_INTERFACE_WITH_COMPARATOR_AND_ALLOCATOR_EXTERNAL_INLINE_METHODS(TYPE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(extern inline, TYPE, COMPARATOR, ALLOCATOR)
