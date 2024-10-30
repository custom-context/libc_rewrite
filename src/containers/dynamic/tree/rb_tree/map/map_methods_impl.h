#pragma once

#include "map_methods_decl.h"

#include <stddef.h>

// map methods definition
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(COMMON_MODIFIER, KEY, VALUE, COMPARATOR, ALLOCATOR)\
/* --- Map interface methods --- */\
struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR);\
DEFINE_PAIR_METHODS_WITH_MODIFIER(COMMON_MODIFIER,\
    RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
    bool\
)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_with_allocator_at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct ALLOCATOR const* const allocator) {\
    ASSERT(this);\
    ASSERT(allocator);\
    TYPE_METHOD(ALLOCATOR, construct_copy_at)(&this->allocator, allocator);\
    TYPE_METHOD(COMPARATOR, construct_at)(&this->comparator);\
    this->root = NULL;\
    this->size = 0u;\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    TYPE_METHOD(ALLOCATOR, construct_at)(&this->allocator);\
    TYPE_METHOD(COMPARATOR, construct_at)(&this->comparator);\
    this->root = NULL;\
    this->size = 0u;\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_move_at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_at)(this);\
    TYPE_METHOD(ALLOCATOR, construct_move_at)(&this->allocator, &source->allocator);\
    TYPE_METHOD(COMPARATOR, construct_move_at)(&this->comparator, &source->comparator);\
    this->root = source->root; source->root = NULL;\
    this->size = source->size; source->size = 0u;\
    return this;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_subtree_copy_at))(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const target,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* const source) {\
    ASSERT(this);\
    ASSERT(target);\
    ASSERT(source);\
    TYPE_METHOD(PAIR_TYPE(KEY, VALUE), construct_copy_at)(&target->value, &source->value);\
    for (usize child_index = 0u; child_index < sizeof(target->child) / sizeof(*target->child); ++child_index) {\
        if (!source->child[child_index]) {\
            target->child[child_index] = NULL;\
            continue;\
        }\
        target->child[child_index] = TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u);\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_subtree_copy_at))(this,\
            target->child[child_index],\
            source->child[child_index]\
        )->parent = target;\
    }\
    return target;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_copy_at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_at)(this);\
    TYPE_METHOD(ALLOCATOR, construct_copy_at)(&this->allocator, &source->allocator);\
    TYPE_METHOD(COMPARATOR, construct_copy_at)(&this->comparator, &source->comparator);\
    if (source->root) {\
        this->root = TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u);\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_subtree_copy_at))(\
            this, this->root, source->root);\
    }\
    this->size = source->size;\
    return this;\
}\
COMMON_MODIFIER void* RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, clear)(this);\
    return this;\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, assign_move_at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const source) {\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_move_at)(&temporary, source);\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, assign_copy_at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const source) {\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_copy_at)(&temporary, source);\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, swap)(\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const another) {\
    {\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* temporary;\
        temporary = this->root;\
        this->root = another->root;\
        another->root = temporary;\
    }\
    {\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), size_type) temporary;\
        temporary = this->size;\
        this->size = another->size;\
        another->size = temporary;\
    }\
    TYPE_METHOD(ALLOCATOR, swap)(&this->allocator, &another->allocator);\
    TYPE_METHOD(COMPARATOR, swap)(&this->comparator, &another->comparator);\
}\
/* --- Common containers' functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), size_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, size)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    return this->size;\
}\
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, clear)(\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    if (!this->root) {\
        return;\
    }\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(destroy_subtree_at))(this, this->root);\
    this->root = NULL;\
    this->size = 0u;\
}\
/* --- Elements' manipulation functions --- */\
/* --- --- insert element --- --- */\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_copy)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), value_type) const* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        /* first insertion */\
        this->root = RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
        TYPE_METHOD(PAIR_TYPE(KEY, VALUE), construct_copy_at)(&this->root->value, value);\
        iterator.element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = true\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            &value->first);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, &value->first) && !TYPE_METHOD(COMPARATOR, compare)(&value->first, &parent->value.first)) {\
        iterator.element_storage = parent;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = false\
        };\
        return result;\
    }\
    /* no node with provided value found => create new one & copy value to it */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
    TYPE_METHOD(PAIR_TYPE(KEY, VALUE), construct_copy_at)(&node->value, value);\
    iterator.element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
        .first = iterator,\
        .second = true\
    };\
    return result;\
}\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_move)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), value_type)* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        /* first insertion */\
        this->root = RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
        TYPE_METHOD(PAIR_TYPE(KEY, VALUE), construct_move_at)(&this->root->value, value);\
        iterator.element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = true\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            &value->first);\
    /* if parent contains same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, &value->first) && !TYPE_METHOD(COMPARATOR, compare)(&value->first, &parent->value.first)) {\
        iterator.element_storage = parent;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = false\
        };\
        return result;\
    }\
    /* no node with provided value found => create new one & copy value to it */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
    TYPE_METHOD(PAIR_TYPE(KEY, VALUE), construct_move_at)(&node->value, value);\
    iterator.element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
        .first = iterator,\
        .second = true\
    };\
    return result;\
}\
/* --- --- insert or assign key-value --- --- */\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_or_assign_with_key_copy_value_copy)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type) const* const key,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type) const* const value) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        /* first insertion */\
        this->root = RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
        TYPE_METHOD(KEY, construct_copy_at)(&this->root->value.first, key);\
        TYPE_METHOD(VALUE, construct_copy_at)(&this->root->value.second, value);\
        iterator.element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = true\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            key);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, key) && !TYPE_METHOD(COMPARATOR, compare)(key, &parent->value.first)) {\
        TYPE_METHOD(VALUE, assign_copy_at)(&parent->value.second, value);\
        iterator.element_storage = parent;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = false\
        };\
        return result;\
    }\
    /* no node with provided value found => create new one & copy value to it */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
    TYPE_METHOD(KEY, construct_copy_at)(&node->value.first, key);\
    TYPE_METHOD(VALUE, construct_copy_at)(&node->value.second, value);\
    iterator.element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
        .first = iterator,\
        .second = true\
    };\
    return result;\
}\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_or_assign_with_key_move_value_copy)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type)* const key,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type) const* const value) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        /* first insertion */\
        this->root = RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
        TYPE_METHOD(KEY, construct_move_at)(&this->root->value.first, key);\
        TYPE_METHOD(VALUE, construct_copy_at)(&this->root->value.second, value);\
        iterator.element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = true\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            key);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, key) && !TYPE_METHOD(COMPARATOR, compare)(key, &parent->value.first)) {\
        TYPE_METHOD(VALUE, assign_copy_at)(&parent->value.second, value);\
        iterator.element_storage = parent;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = false\
        };\
        return result;\
    }\
    /* no node with provided value found => create new one & copy value to it */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
    TYPE_METHOD(KEY, construct_move_at)(&node->value.first, key);\
    TYPE_METHOD(VALUE, construct_copy_at)(&node->value.second, value);\
    iterator.element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
        .first = iterator,\
        .second = true\
    };\
    return result;\
}\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_or_assign_with_key_copy_value_move)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type) const* const key,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type)* const value) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        /* first insertion */\
        this->root = RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
        TYPE_METHOD(KEY, construct_copy_at)(&this->root->value.first, key);\
        TYPE_METHOD(VALUE, construct_move_at)(&this->root->value.second, value);\
        iterator.element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = true\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            key);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, key) && !TYPE_METHOD(COMPARATOR, compare)(key, &parent->value.first)) {\
        TYPE_METHOD(VALUE, assign_move_at)(&parent->value.second, value);\
        iterator.element_storage = parent;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = false\
        };\
        return result;\
    }\
    /* no node with provided value found => create new one & copy value to it */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
    TYPE_METHOD(KEY, construct_copy_at)(&node->value.first, key);\
    TYPE_METHOD(VALUE, construct_move_at)(&node->value.second, value);\
    iterator.element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
        .first = iterator,\
        .second = true\
    };\
    return result;\
}\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_or_assign_with_key_move_value_move)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type)* const key,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type)* const value) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        /* first insertion */\
        this->root = RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
        TYPE_METHOD(KEY, construct_move_at)(&this->root->value.first, key);\
        TYPE_METHOD(VALUE, construct_move_at)(&this->root->value.second, value);\
        iterator.element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = true\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            key);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, key) && !TYPE_METHOD(COMPARATOR, compare)(key, &parent->value.first)) {\
        TYPE_METHOD(VALUE, assign_move_at)(&parent->value.second, value);\
        iterator.element_storage = parent;\
        struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
            .first = iterator,\
            .second = false\
        };\
        return result;\
    }\
    /* no node with provided value found => create new one & copy value to it */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
    TYPE_METHOD(KEY, construct_move_at)(&node->value.first, key);\
    TYPE_METHOD(VALUE, construct_move_at)(&node->value.second, value);\
    iterator.element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), bool) result = {\
        .first = iterator,\
        .second = true\
    };\
    return result;\
}\
/* --- --- direct value access by key --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type) const*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this,\
        KEY const* const key) {\
    ASSERT(this);\
    ASSERT(key);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node = this->root;\
    while (node) {\
        if (TYPE_METHOD(COMPARATOR, compare)(&node->value.first, key)) {\
            if (node->child[0u]) {\
                node = node->child[0u];\
                continue;\
            }\
            break;\
        }\
        if (TYPE_METHOD(COMPARATOR, compare)(key, &node->value.first)) {\
            if (node->child[1u]) {\
                node = node->child[1u];\
                continue;\
            }\
            break;\
        }\
        return &node->value.second;\
        break;\
    }\
    return NULL;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, mut_at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        KEY const* const key) {\
    ASSERT(this);\
    ASSERT(key);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node = this->root;\
    while (node) {\
        if (TYPE_METHOD(COMPARATOR, compare)(&node->value.first, key)) {\
            if (node->child[0u]) {\
                node = node->child[0u];\
                continue;\
            }\
            break;\
        }\
        if (TYPE_METHOD(COMPARATOR, compare)(key, &node->value.first)) {\
            if (node->child[1u]) {\
                node = node->child[1u];\
                continue;\
            }\
            break;\
        }\
        return &node->value.second;\
        break;\
    }\
    return NULL;\
}\
/* --- --- find element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, find)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this,\
        KEY const* const key) {\
    ASSERT(this);\
    ASSERT(key);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node = this->root;\
    while (node) {\
        if (TYPE_METHOD(COMPARATOR, compare)(&node->value.first, key)) {\
            if (node->child[0u]) {\
                node = node->child[0u];\
                continue;\
            }\
            break;\
        }\
        if (TYPE_METHOD(COMPARATOR, compare)(key, &node->value.first)) {\
            if (node->child[1u]) {\
                node = node->child[1u];\
                continue;\
            }\
            break;\
        }\
        iterator.element_storage = node;\
        break;\
    }\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, mut_find)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        KEY const* const key) {\
    ASSERT(this);\
    ASSERT(key);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node = this->root;\
    while (node) {\
        if (TYPE_METHOD(COMPARATOR, compare)(&node->value.first, key)) {\
            if (node->child[0u]) {\
                node = node->child[0u];\
                continue;\
            }\
            break;\
        }\
        if (TYPE_METHOD(COMPARATOR, compare)(key, &node->value.first)) {\
            if (node->child[1u]) {\
                node = node->child[1u];\
                continue;\
            }\
            break;\
        }\
        iterator.element_storage = node;\
        break;\
    }\
    return iterator;\
}\
/* --- --- erase element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, erase_by_iterator)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) position) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!position.element_storage) {\
        return iterator;\
    }\
    /* get pointer to erasable-node from position iterator*/\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)*)position.element_storage;\
    /* find erasable-node's successor (another node, that close to erasable-node by value) */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* successor = NULL;\
    for (usize child_index = 0u; child_index < sizeof(node->child) / sizeof(*node->child); ++child_index) {\
        /* start searching from 'higher'(next) value node, 'couse we want try to save pointer to 'higher'(next) successor to iterator's pointer*/\
        successor = node->child[1u - child_index];\
        if (successor) {\
            while (successor->child[child_index]) {\
                successor = successor->child[child_index];\
            }\
            if (!child_index) {\
                iterator.element_storage = successor;\
            }\
            break;\
        }\
    }\
    /* destroying element from erasable-node && decrement size */\
    TYPE_METHOD(PAIR_TYPE(KEY, VALUE), destroy_at)(&node->value);\
    --this->size;\
    /* check successor node */\
    if (!successor) {\
        /* if successor node not exists => erasable-node is an own successor node */\
        if (!node->parent) {\
            /* case 1: if erasable-node has no parent => it's a root without children => just remove it */\
            TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
            this->root = NULL;\
            return iterator;\
        }\
    } else {\
        /* successor node was found => swap erasable-node with successor node */\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(swap_nodes))(this,\
            node, successor);\
    }\
    /* here erasable-node points to successor node (even if erase-node was an own successor node)*/\
    usize node_index = node->parent->child[1u] == node;\
    if (node->color == RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED)) {\
        /* if current node is red => node have no child (it's a successor node) => just remove it */\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const parent = node->parent;\
        parent->child[node_index] = NULL;\
        TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
        return iterator;\
    }\
    /* node is black here */\
    /* if node has child => node has only one child & child is red, 'couse node is successor node */\
    for (usize child_index = 0u; child_index < sizeof(node->child) / sizeof(*node->child); ++child_index) {\
        if (node->child[child_index]) {\
            /* child found => repaint child, replace node by it & remove node */\
            node->child[child_index]->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            node->parent->child[node_index] = node->child[child_index];\
            node->child[child_index]->parent = node->parent;\
            TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
            return iterator;\
        }\
    }\
    /* node is black & has no child here => rebalance tree */\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_erasement))(this,\
        node);\
    /* erase node after rebalancing */\
    node->parent->child[node->parent->child[1u] == node] = NULL;\
    TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, erase_by_const_iterator)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type) position) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!position.element_storage) {\
        return iterator;\
    }\
    /* get pointer to node (const) from position const-iterator*/\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* const_node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const*)position.element_storage;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node = NULL;\
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
        TYPE_METHOD(PAIR_TYPE(KEY, VALUE), destroy_at)(&this->root->value);\
        TYPE_METHOD(ALLOCATOR, deallocate)(&this->allocator, this->root, 1u);\
        this->root = NULL;\
        --this->size;\
        return iterator;\
    }\
    iterator.element_storage = node;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) result =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, erase_by_iterator)(this, iterator);\
    return result;\
}\
/* --- Nodes related private methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const node) {\
    ASSERT(node);\
    node->parent = NULL;\
    for (usize child_index = 0u; child_index < sizeof(node->child) / sizeof(*node->child); ++child_index) {\
        node->child[child_index] = NULL;\
    }\
    node->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
    return node;\
}\
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(destroy_subtree_at))(\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const node) {\
    ASSERT(this);\
    ASSERT(node);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node_child;\
    for (usize child_index = 0u; child_index < sizeof(node->child) / sizeof(*node->child); ++child_index) {\
        node_child = node->child[child_index];\
        if (node_child) {\
            RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(destroy_subtree_at))(this, node_child);\
        }\
    }\
    TYPE_METHOD(PAIR_TYPE(KEY, VALUE), destroy_at)(&node->value);\
    TYPE_METHOD(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
}\
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(swap_nodes))(\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const node1,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const node2) {\
    ASSERT(this);\
    ASSERT(node1);\
    ASSERT(node2);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* temporary;\
    /* swap direct pointers */\
    /* swap parents */\
    temporary = node1->parent;\
    node1->parent = node2->parent;\
    node2->parent = temporary;\
    /* swap children */\
    for (usize child_index = 0u; child_index < sizeof(node1->child) / sizeof(*node1->child); ++child_index) {\
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
    for (usize child_index = 0u; child_index < sizeof(node1->child) / sizeof(*node1->child); ++child_index) {\
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
    for (usize child_index = 0u; child_index < sizeof(node1->child) / sizeof(*node1->child); ++child_index) {\
        if (node1->child[child_index]) {\
            node1->child[child_index]->parent = node1;\
        }\
        if (node2->child[child_index]) {\
            node2->child[child_index]->parent = node2;\
        }\
    }\
    /* swap colors */\
    enum RED_BLACK_TREE_MAP_NODE_COLOR_ENUM(KEY, VALUE) temporary_color = node1->color;\
    node1->color = node2->color;\
    node2->color = temporary_color;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const node,\
        KEY const* const value) {\
    ASSERT(this);\
    ASSERT(node);\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* result = node;\
    while (result) {\
        if (TYPE_METHOD(COMPARATOR, compare)(value, &result->value.first)) {\
            if (result->child[1u]) {\
                result = result->child[1u];\
                continue;\
            }\
            break;\
        }\
        if (TYPE_METHOD(COMPARATOR, compare)(&result->value.first, value)) {\
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
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const node,\
    usize const move_direction) {\
    ASSERT(this);\
    ASSERT(node);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const parent = node->parent;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const outer_child = node->child[1u - move_direction];\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const outer_child__inner_child = outer_child->child[move_direction];\
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
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node) {\
    ASSERT(this);\
    ASSERT(node);\
    while (node->parent &&\
        node->parent->color != RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK)) {\
        /* parent exists & it's red */\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent = node->parent;\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* grandparent = parent->parent;\
        if (!grandparent) {\
            /* case 4: parent is a root => repaint it & return */\
            parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            return;\
        }\
        /* grandparent exists & it's black ('couse parent is red) */\
        usize parent_direction = grandparent->child[1u] == parent;\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const uncle = grandparent->child[1u - parent_direction];\
        if (uncle &&\
            uncle->color != RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK)) {\
            /* case 2: uncle exists is red => repaint parent/grandparent/uncle, set node <- grandparent & continue */\
            parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            uncle->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            grandparent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
            node = grandparent;\
            continue;\
        }\
        /* uncle isn't exist or it's black */\
        if (node == parent->child[1u - parent_direction]) {\
            /* case 5: node is an inner node => rotate parent/node & set node <- parent */\
            RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                parent, parent_direction);\
            node = parent;\
            parent = grandparent->child[parent_direction];\
        }\
        /* case 6: node is an outer node => rotate grandparent/parent, repaint them & return */\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
            grandparent, 1u - parent_direction);\
        parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
        grandparent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
        return;\
    }\
}\
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_erasement))(\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node) {\
    usize node_index;\
    do {\
        node_index = node->parent->child[1u] == node;\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent = node->parent;\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* sibling = parent->child[1u - node_index];\
        /* node must be black here => parent is red/black => sibling exists (it's red/black) */\
        ASSERT(sibling);\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* sibling_distant_child = sibling->child[1u - node_index];\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* sibling_close_child = sibling->child[node_index];\
        if (sibling->color == RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED)) {\
            /* case 3: sibling is red => parent & sibling's children exist and they're black */\
            RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                parent,\
                node_index);\
            parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
            sibling->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            sibling = sibling_close_child;\
            sibling_close_child = sibling->child[node_index];\
            sibling_distant_child = sibling->child[1u - node_index];\
            /* 3 -> check 6, check 5, else check 4 */\
        }\
        if (sibling_distant_child != NULL &&\
            sibling_distant_child->color == RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED)) {\
            /* case 6: sibling's distant child exists & it's red => sibling is black */\
            RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                parent,\
                node_index);\
            sibling->color = parent->color;\
            parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            sibling_distant_child->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            break;\
        }\
        if (sibling_close_child != NULL &&\
            sibling_close_child->color == RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED)) {\
            /* case 5: sibling's close child exists & it's red (& sibling's distant child is null/black) => sibling is black */\
            RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                sibling,\
                1u - node_index);\
            sibling->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
            sibling_close_child->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            sibling_distant_child = sibling;\
            sibling = sibling_close_child;\
            /* sibling_distant_child is red & sibling is black -> go to 6! [we're don't use goto, sorry] */\
            /* case 6: sibling's distant child exists & it's red => sibling is black */\
            RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                parent,\
                node_index);\
            sibling->color = parent->color;\
            parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            sibling_distant_child->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            break;\
        }\
        if (parent->color == RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED)) {\
            /* case 4: parent is red => sibling & its' children are black */\
            sibling->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
            parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            break;\
        }\
        /* case 2: parent/sibling & its' children are black */\
        sibling->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
        node = parent;\
    } while (node->parent);\
}\
/* --- Iterators' related methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, begin)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        return iterator;\
    }\
    /* get pointer to root */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node = this->root;\
    while (node->child[0u]) {\
        node = node->child[0u];\
    }\
    iterator.element_storage = node;\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, end)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    UNUSED(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, cbegin)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        return iterator;\
    }\
    /* get pointer to root */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node = this->root;\
    while (node->child[0u]) {\
        node = node->child[0u];\
    }\
    iterator.element_storage = node;\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, cend)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    return iterator;\
}\
/* --- Mutable iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    this->element_storage = NULL;\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_move_at)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const source) {\
    return RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_copy_at)(this, source);\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_copy_at)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_at)(this);\
    this->element_storage = source->element_storage;\
    return this;\
}\
COMMON_MODIFIER void* RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    this->element_storage = NULL;\
    return this;\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, assign_move_at)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const source) {\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_move_at)(&temporary, source);\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, assign_copy_at)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const source) {\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_copy_at)(&temporary, source);\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, swap)(\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const another) {\
    ASSERT(this);\
    ASSERT(another);\
    void* const temporary = this->element_storage;\
    this->element_storage = another->element_storage;\
    another->element_storage = temporary;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type) const*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, key)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->element_storage);\
    return &this->element_storage->value.first;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type)*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, value)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->element_storage);\
    return &this->element_storage->value.second;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type) const*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, const_value)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->element_storage);\
    return &this->element_storage->value.second;\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, compare)(\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this,\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    return this->element_storage == source->element_storage;\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, next)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->element_storage;\
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
    this->element_storage = node;\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator;\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, pnext)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->element_storage;\
    ASSERT(node);\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
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
    this->element_storage = node;\
    return iterator;\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, prev)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->element_storage;\
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
    this->element_storage = node;\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator;\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, pprev)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->element_storage;\
    ASSERT(node);\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
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
    this->element_storage = node;\
    return iterator;\
}\
/* --- Const iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    this->element_storage = NULL;\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_move_at)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const source) {\
    return RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_copy_at)(this, source);\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_copy_at)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_at)(this);\
    this->element_storage = source->element_storage;\
    return this;\
}\
COMMON_MODIFIER void* RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    this->element_storage = NULL;\
    return this;\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, assign_move_at)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const source) {\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_move_at)(&temporary, source);\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, assign_copy_at)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const source) {\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) temporary;\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_copy_at)(&temporary, source);\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, swap)(this, &temporary);\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(&temporary);\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, swap)(\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const another) {\
    ASSERT(this);\
    ASSERT(another);\
    void const* const temporary = this->element_storage;\
    this->element_storage = another->element_storage;\
    another->element_storage = temporary;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type) const*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, key)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->element_storage);\
    return &this->element_storage->value.first;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type)*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, value)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->element_storage);\
    return &this->element_storage->value.second;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type) const*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, const_value)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->element_storage);\
    return &this->element_storage->value.second;\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, compare)(\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this,\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    return this->element_storage == source->element_storage;\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, next)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->element_storage;\
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
    this->element_storage = node;\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator;\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, pnext)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->element_storage;\
    ASSERT(node);\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
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
    this->element_storage = node;\
    return iterator;\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, prev)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->element_storage;\
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
    this->element_storage = node;\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator;\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, pprev)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->element_storage;\
    ASSERT(node);\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
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
    this->element_storage = node;\
    return iterator;\
}

#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHODS(KEY, VALUE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_STATIC_METHODS(KEY, VALUE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(static, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_INLINE_METHODS(KEY, VALUE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(inline, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_EXTERNAL_METHODS(KEY, VALUE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(extern, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_EXTERNAL_INLINE_METHODS(KEY, VALUE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(extern inline, KEY, VALUE, COMPARATOR, ALLOCATOR)
