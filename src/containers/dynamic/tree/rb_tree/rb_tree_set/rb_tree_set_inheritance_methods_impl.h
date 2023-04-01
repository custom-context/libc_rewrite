#pragma once

#include "rb_tree_set_inheritance_methods_decl.h"
#include "rb_tree_set_methods_impl.h"

// set non-dynamic 'dynamic' inner methods
#define DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_INHERITANCE_METHODS(COMMON_MODIFIER, TYPE, COMPARATOR, ALLOCATOR)\
/* --- Set methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(destroy_at))(\
    struct SET_INTERFACE_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(clear))(base);\
    /* boilerplate */\
    TYPE_METHOD(COMPARATOR, destroy_at)(&this->comparator);\
    TYPE_METHOD(ALLOCATOR, destroy_at)(&this->allocator);\
    TYPE_METHOD(SET_INTERFACE_TYPE(TYPE), VTABLE_MEMBER(destroy_at))(base);\
    return this;\
}\
/* --- Common containers' functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), size_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(size))(\
        struct SET_INTERFACE_TYPE(TYPE) const* const base) {\
    /* boilerplate (const) */\
    ASSERT(base);\
    void const* const void_this = (void const*)(\
        (char const*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const*)(void_this);\
    /* method body */\
    return this->size;\
}\
COMMON_MODIFIER void RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(clear))(\
    struct SET_INTERFACE_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    if (!this->root) {\
        return;\
    }\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(destroy_subtree_at))(this, this->root);\
    this->root = NULL;\
    this->size = 0u;\
}\
/* --- Elements' manipulation functions --- */\
/* --- --- insert element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(insert_copy))(\
        struct SET_INTERFACE_TYPE(TYPE)* const base,\
        TYPE const* const value) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        /* first insertion */\
        this->root = RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
        TYPE_METHOD(TYPE, construct_copy_at)(&this->root->value, value);\
        iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = this->root;\
        ++this->size;\
        return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            value);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value, value) && !TYPE_METHOD(COMPARATOR, compare)(value, &parent->value)) {\
        iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = parent;\
        return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    }\
    /* no node with provided value found => create new one & copy value to it */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node =\
        RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
    TYPE_METHOD(TYPE, construct_copy_at)(&node->value, value);\
    iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value, &parent->value)] = node;\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(insert_move))(\
        struct SET_INTERFACE_TYPE(TYPE)* const base,\
        TYPE* const value) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        /* first insertion */\
        this->root = RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
        TYPE_METHOD(TYPE, construct_move_at)(&this->root->value, value);\
        iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = this->root;\
        ++this->size;\
        return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            value);\
    /* if parent contains same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value, value) && !TYPE_METHOD(COMPARATOR, compare)(value, &parent->value)) {\
        iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = parent;\
        return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    }\
    /* no node with provided value found => create new one & copy value to it */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node =\
        RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
    TYPE_METHOD(TYPE, construct_move_at)(&node->value, value);\
    iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value, &parent->value)] = node;\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
}\
/* --- --- find element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(find))(\
        struct SET_INTERFACE_TYPE(TYPE) const* const base,\
        TYPE const* const value) {\
    /* boilerplate (const) */\
    ASSERT(base);\
    void const* const void_this = (void const*)(\
        (char const*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const*)(void_this);\
    /* method body */\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* node = this->root;\
    while (node) {\
        if (TYPE_METHOD(COMPARATOR, compare)(&node->value, value)) {\
            if (node->child[0u]) {\
                node = node->child[0u];\
                continue;\
            }\
            break;\
        }\
        if (TYPE_METHOD(COMPARATOR, compare)(value, &node->value)) {\
            if (node->child[1u]) {\
                node = node->child[1u];\
                continue;\
            }\
            break;\
        }\
        iterator.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage = node;\
        break;\
    }\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(mut_find))(\
        struct SET_INTERFACE_TYPE(TYPE)* const base,\
        TYPE const* const value) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node = this->root;\
    while (node) {\
        if (TYPE_METHOD(COMPARATOR, compare)(&node->value, value)) {\
            if (node->child[0u]) {\
                node = node->child[0u];\
                continue;\
            }\
            break;\
        }\
        if (TYPE_METHOD(COMPARATOR, compare)(value, &node->value)) {\
            if (node->child[1u]) {\
                node = node->child[1u];\
                continue;\
            }\
            break;\
        }\
        iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = node;\
        break;\
    }\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
}\
/* --- --- erase element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(erase_by_iterator))(\
        struct SET_INTERFACE_TYPE(TYPE)* const base,\
        STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) position) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!position.element_storage) {\
        return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    }\
    /* get pointer to erasable-node from position iterator*/\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)*)position.element_storage;\
    /* find erasable-node's successor (another node, that close to erasable-node by value) */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* successor = NULL;\
    for (usize child_index = 0u; child_index < sizeof(node->child) / sizeof(*node->child); ++child_index) {\
        /* start searching from 'higher'(next) value node, 'couse we want try to save pointer to 'higher'(next) successor to iterator's pointer*/\
        successor = node->child[1u - child_index];\
        if (successor) {\
            while (successor->child[child_index]) {\
                successor = successor->child[child_index];\
            }\
            if (!child_index) {\
                iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = successor;\
            }\
            break;\
        }\
    }\
    /* destroying element from erasable-node && decrement size */\
    TYPE_METHOD(TYPE, destroy_at)(&node->value);\
    --this->size;\
    /* check successor node */\
    if (!successor) {\
        /* if successor node not exists => erasable-node is an own successor node */\
        if (!node->parent) {\
            /* case 1: if erasable-node has no parent => it's a root without children => just remove it */\
            TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
            this->root = NULL;\
            return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
        }\
    } else {\
        /* successor node was found => swap erasable-node with successor node */\
        RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(swap_nodes))(this,\
            node, successor);\
        if (debug_enabled) {\
            LOG_DEBUG_FORMAT("node-successor value: %d\n", successor->value);\
        }\
    }\
    /* here erasable-node points to successor node (even if erase-node was an own successor node)*/\
    usize node_index = node->parent->child[1u] == node;\
    if (node->color == RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED)) {\
        if (debug_enabled) {\
            LOG_DEBUG("node-successor color: RED\n");\
        }\
        /* if current node is red => node have no child (it's a successor node) => just remove it */\
        STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* const parent = node->parent;\
        parent->child[node_index] = NULL;\
        TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
        return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    }\
    /* node is black here */\
    if (debug_enabled) {\
        LOG_DEBUG("node-successor color: BLACK\n");\
    }\
    /* if node has child => node has only one child & child is red, 'couse node is successor node */\
    for (usize child_index = 0u; child_index < sizeof(node->child) / sizeof(*node->child); ++child_index) {\
        if (node->child[child_index]) {\
            /* child found => repaint child, replace node by it & remove node */\
            if (debug_enabled) {\
                LOG_DEBUG("node-successor has one red child -> replace it by child (with repaint) & remove it\n");\
            }\
            node->child[child_index]->color = RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK);\
            node->parent->child[node_index] = node->child[child_index];\
            node->child[child_index]->parent = node->parent;\
            TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
            return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
        }\
    }\
    /* node is black & has no child here => rebalance tree */\
    if (debug_enabled) {\
        LOG_DEBUG("node-successor has no children\n");\
    }\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_erasement))(this,\
        node);\
    /* erase node after rebalancing */\
    node->parent->child[node->parent->child[1u] == node] = NULL;\
    TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(erase_by_const_iterator))(\
        struct SET_INTERFACE_TYPE(TYPE)* const base,\
        STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) position) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!position.element_storage) {\
        return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    }\
    /* get pointer to node (const) from position const-iterator*/\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* const_node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const*)position.element_storage;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node = NULL;\
    /* try get non-const pointer to node */\
    if (const_node->parent) {\
        node = const_node->parent->child[const_node->parent->child[1u] == const_node];\
    }\
    for (usize child_index = 0u; child_index < sizeof(const_node->child) / sizeof(*const_node->child); ++child_index) {\
        if (const_node->child[child_index]) {\
            node = const_node->child[child_index]->parent;\
            break;\
        }\
    }\
    if (!node) {\
        /* node has no non-null pointers => it's a root without children => simply remove root */\
        ASSERT(this->root == const_node);\
        TYPE_METHOD(TYPE, destroy_at)(&this->root->value);\
        TYPE_METHOD(ALLOCATOR, deallocate)(&this->allocator, this->root, 1u);\
        this->root = NULL;\
        --this->size;\
        return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    }\
    iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = node;\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) result =\
        RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(erase_by_iterator))(&this->INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)),\
            iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    return result;\
}\
/* --- Iterators' related methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(begin))(\
        struct SET_INTERFACE_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    }\
    /* get pointer to root */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node = this->root;\
    while (node->child[0u]) {\
        node = node->child[0u];\
    }\
    iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(end))(\
        struct SET_INTERFACE_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    UNUSED(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(cbegin))(\
        struct SET_INTERFACE_TYPE(TYPE) const* const base) {\
    /* boilerplate (const) */\
    ASSERT(base);\
    void const* const void_this = (void const*)(\
        (char const*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        return iterator.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
    }\
    /* get pointer to root */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* node = this->root;\
    while (node->child[0u]) {\
        node = node->child[0u];\
    }\
    iterator.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(cend))(\
        struct SET_INTERFACE_TYPE(TYPE) const* const base) {\
    /* boilerplate (const) */\
    ASSERT(base);\
    void const* const void_this = (void const*)(\
        (char const*)base - \
        offsetof(struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const* const this =\
        (struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) const*)(void_this);\
    /* method body */\
    UNUSED(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
}\
/* --- Mutable iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(destroy_at))(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = NULL;\
    /* boilerplate */\
    TYPE_METHOD(SET_INTERFACE_ITERATOR_TYPE(TYPE), VTABLE_MEMBER(destroy_at))(&this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)));\
    return this;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE), value_type)*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(value))(\
        struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const base) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)*)\
            (base->element_storage);\
    ASSERT(node);\
    return &node->value;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE), value_type) const*\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(const_value))(\
        struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const base) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const*)\
            (base->element_storage);\
    ASSERT(node);\
    return &node->value;\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(compare))(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const base,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const source_base) {\
    ASSERT(base);\
    ASSERT(source_base);\
    return base->element_storage == source_base->element_storage;\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(next))(\
        struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage;\
    ASSERT(node);\
    if (node->child[1u]) {\
        node = node->child[1u];\
        while (node->child[0u]) {\
            node = node->child[0u];\
        }\
    } else {\
        while (node->parent && node->parent->child[1u] == node) {\
            node = node->parent;\
        }\
        if (!node->parent) {\
            node = NULL;\
        } else {\
            node = node->parent;\
        }\
    }\
    this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = node;\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(pnext))(\
        struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage;\
    ASSERT(node);\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    if (node->child[1u]) {\
        node = node->child[1u];\
        while (node->child[0u]) {\
            node = node->child[0u];\
        }\
    } else {\
        while (node->parent && node->parent->child[1u] == node) {\
            node = node->parent;\
        }\
        if (!node->parent) {\
            node = NULL;\
        } else {\
            node = node->parent;\
        }\
    }\
    this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(prev))(\
        struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage;\
    ASSERT(node);\
    if (node->child[0u]) {\
        node = node->child[0u];\
        while (node->child[1u]) {\
            node = node->child[1u];\
        }\
    } else {\
        while (node->parent && node->parent->child[0u] == node) {\
            node = node->parent;\
        }\
        if (!node->parent) {\
            node = NULL;\
        } else {\
            node = node->parent;\
        }\
    }\
    this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = node;\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(pprev))(\
        struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage;\
    ASSERT(node);\
    struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    if (node->child[0u]) {\
        node = node->child[0u];\
        while (node->child[1u]) {\
            node = node->child[1u];\
        }\
    } else {\
        while (node->parent && node->parent->child[0u] == node) {\
            node = node->parent;\
        }\
        if (!node->parent) {\
            node = NULL;\
        } else {\
            node = node->parent;\
        }\
    }\
    this->INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
}\
/* --- Const iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(destroy_at))(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage = NULL;\
    /* boilerplate */\
    TYPE_METHOD(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), VTABLE_MEMBER(destroy_at))(\
        &this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)));\
    return this;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), value_type)*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(value))(\
        struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const base) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const*)\
            (base->element_storage);\
    ASSERT(node);\
    return &node->value;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), value_type) const*\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(const_value))(\
        struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const base) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const*)\
            (base->element_storage);\
    ASSERT(node);\
    return &node->value;\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(compare))(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const base,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const source_base) {\
    ASSERT(base);\
    ASSERT(source_base);\
    return base->element_storage == source_base->element_storage;\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(next))(\
        struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage;\
    ASSERT(node);\
    if (node->child[1u]) {\
        node = node->child[1u];\
        while (node->child[0u]) {\
            node = node->child[0u];\
        }\
    } else {\
        while (node->parent && node->parent->child[1u] == node) {\
            node = node->parent;\
        }\
        if (!node->parent) {\
            node = NULL;\
        } else {\
            node = node->parent;\
        }\
    }\
    this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage = node;\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(pnext))(\
        struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage;\
    ASSERT(node);\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    if (node->child[1u]) {\
        node = node->child[1u];\
        while (node->child[0u]) {\
            node = node->child[0u];\
        }\
    } else {\
        while (node->parent && node->parent->child[1u] == node) {\
            node = node->parent;\
        }\
        if (!node->parent) {\
            node = NULL;\
        } else {\
            node = node->parent;\
        }\
    }\
    this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(prev))(\
        struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage;\
    ASSERT(node);\
    if (node->child[0u]) {\
        node = node->child[0u];\
        while (node->child[1u]) {\
            node = node->child[1u];\
        }\
    } else {\
        while (node->parent && node->parent->child[0u] == node) {\
            node = node->parent;\
        }\
        if (!node->parent) {\
            node = NULL;\
        } else {\
            node = node->parent;\
        }\
    }\
    this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage = node;\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(TYPE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(pprev))(\
        struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)))\
    );\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage;\
    ASSERT(node);\
    struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    if (node->child[0u]) {\
        node = node->child[0u];\
        while (node->child[1u]) {\
            node = node->child[1u];\
        }\
    } else {\
        while (node->parent && node->parent->child[0u] == node) {\
            node = node->parent;\
        }\
        if (!node->parent) {\
            node = NULL;\
        } else {\
            node = node->parent;\
        }\
    }\
    this->INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
}


#define DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_INHERITANCE_METHODS(TYPE) DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_INHERITANCE_METHODS(, TYPE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_STATIC_INHERITANCE_METHODS(TYPE) DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_INHERITANCE_METHODS(static, TYPE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_INLINE_INHERITANCE_METHODS(TYPE) DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_INHERITANCE_METHODS(inline, TYPE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_EXTERNAL_INLINE_INHERITANCE_METHODS(TYPE) DEFINE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_INHERITANCE_METHODS(extern inline, TYPE, COMPARATOR, ALLOCATOR)
