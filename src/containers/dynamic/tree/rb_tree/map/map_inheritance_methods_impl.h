#pragma once

#include "map_inheritance_methods_decl.h"
#include "map_methods_impl.h"

// map non-dynamic 'dynamic' inner methods
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_INHERITANCE_METHODS(COMMON_MODIFIER, KEY, VALUE, COMPARATOR, ALLOCATOR)\
/* --- Set methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(destroy_at))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(clear))(base);\
    /* boilerplate */\
    TYPE_METHOD(COMPARATOR, destroy_at)(&this->comparator);\
    TYPE_METHOD(ALLOCATOR, destroy_at)(&this->allocator);\
    TYPE_METHOD(MAP_INTERFACE_TYPE(KEY, VALUE), VTABLE_MEMBER(destroy_at))(base);\
    return this;\
}\
/* --- Common containers' functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), size_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(size))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const base) {\
    /* boilerplate (const) */\
    ASSERT(base);\
    void const* const void_this = (void const*)(\
        (char const*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const*)(void_this);\
    /* method body */\
    return this->size;\
}\
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(clear))(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    if (!this->root) {\
        return;\
    }\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(destroy_subtree_at))(this, this->root);\
    this->root = NULL;\
    this->size = 0u;\
}\
/* --- Elements' manipulation functions --- */\
/* --- --- insert element --- --- */\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(insert_copy))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type) const* const value) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        /* first insertion */\
        this->root = RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
        TYPE_METHOD(PAIR_TYPE(KEY, VALUE), construct_copy_at)(&this->root->value, value);\
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 1u\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            &value->first);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, &value->first) && !TYPE_METHOD(COMPARATOR, compare)(&value->first, &parent->value.first)) {\
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = parent;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 0u\
        };\
        return result;\
    }\
    /* no node with provided value found => create new one & copy value to it */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
    TYPE_METHOD(PAIR_TYPE(KEY, VALUE), construct_copy_at)(&node->value, value);\
    iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
        .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
        .second = 1u\
    };\
    return result;\
}\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(insert_move))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type)* const value) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    ASSERT(value);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        /* first insertion */\
        this->root = RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
        TYPE_METHOD(PAIR_TYPE(KEY, VALUE), construct_move_at)(&this->root->value, value);\
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 1u\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            &value->first);\
    /* if parent contains same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, &value->first) && !TYPE_METHOD(COMPARATOR, compare)(&value->first, &parent->value.first)) {\
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = parent;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 0u\
        };\
        return result;\
    }\
    /* no node with provided value found => create new one & copy value to it */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(construct_node_at))(\
            TYPE_METHOD(ALLOCATOR, allocate)(&this->allocator, 1u)\
        );\
    TYPE_METHOD(PAIR_TYPE(KEY, VALUE), construct_move_at)(&node->value, value);\
    iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
        .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
        .second = 1u\
    };\
    return result;\
}\
/* --- --- insert or assign key-value --- --- */\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(insert_or_assign_with_key_copy_value_copy))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type) const* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const* const value) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
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
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 1u\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            key);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, key) && !TYPE_METHOD(COMPARATOR, compare)(key, &parent->value.first)) {\
        TYPE_METHOD(KEY, assign_copy_at)(&parent->value.first, key);\
        TYPE_METHOD(VALUE, assign_copy_at)(&parent->value.second, value);\
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = parent;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 0u\
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
    iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
        .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
        .second = 1u\
    };\
    return result;\
}\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(insert_or_assign_with_key_move_value_copy))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type)* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const* const value) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
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
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 1u\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            key);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, key) && !TYPE_METHOD(COMPARATOR, compare)(key, &parent->value.first)) {\
        TYPE_METHOD(KEY, assign_move_at)(&parent->value.first, key);\
        TYPE_METHOD(VALUE, assign_copy_at)(&parent->value.second, value);\
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = parent;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 0u\
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
    iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
        .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
        .second = 1u\
    };\
    return result;\
}\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(insert_or_assign_with_key_copy_value_move))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type) const* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)* const value) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
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
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 1u\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            key);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, key) && !TYPE_METHOD(COMPARATOR, compare)(key, &parent->value.first)) {\
        TYPE_METHOD(KEY, assign_copy_at)(&parent->value.first, key);\
        TYPE_METHOD(VALUE, assign_move_at)(&parent->value.second, value);\
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = parent;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 0u\
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
    iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
        .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
        .second = 1u\
    };\
    return result;\
}\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(insert_or_assign_with_key_move_value_move))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type)* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)* const value) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
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
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = this->root;\
        ++this->size;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 1u\
        };\
        return result;\
    }\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(find_parent_for_value_insertion))(this,\
            this->root,\
            key);\
    /* if parent contain same value => no insertion will be performed => return iterator to parent */\
    if (!TYPE_METHOD(COMPARATOR, compare)(&parent->value.first, key) && !TYPE_METHOD(COMPARATOR, compare)(key, &parent->value.first)) {\
        TYPE_METHOD(KEY, assign_move_at)(&parent->value.first, key);\
        TYPE_METHOD(VALUE, assign_move_at)(&parent->value.second, value);\
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = parent;\
        struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
            .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
            .second = 0u\
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
    iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    node->parent = parent;\
    parent->child[TYPE_METHOD(COMPARATOR, compare)(&node->value.first, &parent->value.first)] = node;\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_insertion))(this,\
        node);\
    ++this->size;\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) result = {\
        .first = iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
        .second = 1u\
    };\
    return result;\
}\
/* --- --- direct value access by key --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(at))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const base,\
        KEY const* const key) {\
    /* boilerplate (const) */\
    ASSERT(base);\
    void const* const void_this = (void const*)(\
        (char const*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const*)(void_this);\
    /* method body */\
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
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(mut_at))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base,\
        KEY const* const key) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
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
}/* --- --- find element by key --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(find))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const base,\
        KEY const* const key) {\
    /* boilerplate (const) */\
    ASSERT(base);\
    void const* const void_this = (void const*)(\
        (char const*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const*)(void_this);\
    /* method body */\
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
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
        break;\
    }\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(mut_find))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base,\
        KEY const* const key) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
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
        iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
        break;\
    }\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
}\
/* --- --- erase element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(erase_by_iterator))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) position) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!position.element_storage) {\
        return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
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
                iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = successor;\
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
            return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
        }\
    } else {\
        /* successor node was found => swap erasable-node with successor node */\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(swap_nodes))(this,\
            node, successor);\
        if (debug_enabled) {\
            LOG_DEBUG_FORMAT("node-successor key: %d\n", successor->value.first);\
        }\
    }\
    /* here erasable-node points to successor node (even if erase-node was an own successor node)*/\
    usize node_index = node->parent->child[1u] == node;\
    if (node->color == RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED)) {\
        if (debug_enabled) {\
            LOG_DEBUG("node-successor color: RED\n");\
        }\
        /* if current node is red => node have no child (it's a successor node) => just remove it */\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const parent = node->parent;\
        parent->child[node_index] = NULL;\
        TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
        return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
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
            node->child[child_index]->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            node->parent->child[node_index] = node->child[child_index];\
            node->child[child_index]->parent = node->parent;\
            TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
            return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
        }\
    }\
    /* node is black & has no child here => rebalance tree */\
    if (debug_enabled) {\
        LOG_DEBUG("node-successor has no children\n");\
    }\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rebalance_after_erasement))(this,\
        node);\
    /* erase node after rebalancing */\
    node->parent->child[node->parent->child[1u] == node] = NULL;\
    TYPE_MEMBER(ALLOCATOR, deallocate)(&this->allocator, node, 1u);\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(erase_by_const_iterator))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type) position) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!position.element_storage) {\
        return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
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
        return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
    }\
    iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) result =\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(erase_by_iterator))(&this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    return result;\
}\
/* --- Iterators' related methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(begin))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
    }\
    /* get pointer to root */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node = this->root;\
    while (node->child[0u]) {\
        node = node->child[0u];\
    }\
    iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(end))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    UNUSED(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(cbegin))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const base) {\
    /* boilerplate (const) */\
    ASSERT(base);\
    void const* const void_this = (void const*)(\
        (char const*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    if (!this->root) {\
        return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
    }\
    /* get pointer to root */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node = this->root;\
    while (node->child[0u]) {\
        node = node->child[0u];\
    }\
    iterator.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(cend))(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const base) {\
    /* boilerplate (const) */\
    ASSERT(base);\
    void const* const void_this = (void const*)(\
        (char const*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this =\
        (struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const*)(void_this);\
    /* method body */\
    UNUSED(this);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_at)(&iterator);\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
}\
/* --- Mutable iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(destroy_at))(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = NULL;\
    /* boilerplate */\
    TYPE_METHOD(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), VTABLE_MEMBER(destroy_at))(&this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    return this;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), key_type) const*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(key))(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const base) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const*)\
            (base->element_storage);\
    ASSERT(node);\
    return &node->value.first;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), mapped_type)*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(value))(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)*)\
            (base->element_storage);\
    ASSERT(node);\
    return &node->value.second;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), mapped_type) const*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(const_value))(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const base) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const*)\
            (base->element_storage);\
    ASSERT(node);\
    return &node->value.second;\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(compare))(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const base,\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const source_base) {\
    ASSERT(base);\
    ASSERT(source_base);\
    return base->element_storage == source_base->element_storage;\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(next))(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
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
    this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(pnext))(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
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
    this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(prev))(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
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
    this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(pprev))(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* node =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
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
    this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
}\
/* --- Const iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(destroy_at))(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage = NULL;\
    /* boilerplate */\
    TYPE_METHOD(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), VTABLE_MEMBER(destroy_at))(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    return this;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), key_type) const*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(key))(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const base) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const*)\
            (base->element_storage);\
    ASSERT(node);\
    return &node->value.first;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), mapped_type)*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(value))(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const*)\
            (base->element_storage);\
    ASSERT(node);\
    return &node->value.second;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), mapped_type) const*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(const_value))(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const base) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        (STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const*)\
            (base->element_storage);\
    ASSERT(node);\
    return &node->value.second;\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(compare))(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const base,\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const source_base) {\
    ASSERT(base);\
    ASSERT(source_base);\
    return base->element_storage == source_base->element_storage;\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(next))(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
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
    this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(pnext))(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
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
    this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(prev))(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
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
    this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) iterator;\
    TYPE_METHOD(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), construct_copy_at)(&iterator, this);\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, VTABLE_MEMBER(pprev))(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const base) {\
    /* boilerplate */\
    ASSERT(base);\
    void* const void_this = (void*)(\
        (char*)base - \
        offsetof(struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)))\
    );\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* this =\
        (struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*)(void_this);\
    /* method body */\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type) const* node =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
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
    this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage = node;\
    return iterator.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
}


#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_INHERITANCE_METHODS(TYPE) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_INHERITANCE_METHODS(, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_STATIC_INHERITANCE_METHODS(TYPE) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_INHERITANCE_METHODS(static, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_INLINE_INHERITANCE_METHODS(TYPE) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_INHERITANCE_METHODS(inline, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_EXTERNAL_INLINE_INHERITANCE_METHODS(TYPE) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_INHERITANCE_METHODS(extern inline, KEY, VALUE, COMPARATOR, ALLOCATOR)
