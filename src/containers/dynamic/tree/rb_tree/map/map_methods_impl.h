#pragma once

#include "map_methods_decl.h"

#include <stddef.h>

static int debug_enabled = 0u;
static int debug_rebalance_iteration = 0u;

// map methods definition
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(COMMON_MODIFIER, KEY, VALUE, COMPARATOR, ALLOCATOR)\
/* --- Map interface methods --- */\
struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR);\
DEFINE_PAIR_METHODS_WITH_MODIFIER(COMMON_MODIFIER,\
    RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
    char\
)\
/* --- Static cast to map interface --- */\
DECLARE_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
    MAP_INTERFACE_TYPE(KEY, VALUE)) {\
    return &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE));\
}\
DECLARE_CONST_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
    MAP_INTERFACE_TYPE(KEY, VALUE)) {\
    return &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE));\
}\
DECLARE_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    MAP_INTERFACE_TYPE(KEY, VALUE),\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)) {\
    return (void*)((char*)this -\
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))));\
}\
DECLARE_CONST_INTERFACE_STATIC_CAST_WITH_MODIFIER(COMMON_MODIFIER,\
    MAP_INTERFACE_TYPE(KEY, VALUE),\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)) {\
    return (void const*)((char const*)this -\
        offsetof(struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))));\
}\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_with_allocator_at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        struct ALLOCATOR const* const allocator) {\
    ASSERT(this);\
    ASSERT(allocator);\
    TYPE_METHOD(MAP_INTERFACE_TYPE(KEY, VALUE), construct_at)(&this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            MAP_INTERFACE_TYPE(KEY, VALUE));\
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
    TYPE_METHOD(MAP_INTERFACE_TYPE(KEY, VALUE), construct_at)(&this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            MAP_INTERFACE_TYPE(KEY, VALUE));\
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
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->destroy_at);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->destroy_at(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))\
    );\
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
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->size);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->size(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))\
    );\
}\
COMMON_MODIFIER void RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, clear)(\
    struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->clear);\
    this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->clear(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))\
    );\
}\
/* --- Elements' manipulation functions --- */\
/* --- --- insert element --- --- */\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_copy)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type) const* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_copy);\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) interface_iterator =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_copy(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            value\
    );\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char) iterator = {\
        .first = {.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = interface_iterator.first},\
        .second = interface_iterator.second\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_move)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type)* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_move);\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) interface_iterator =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_move(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            value\
    );\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char) iterator = {\
        .first = {.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = interface_iterator.first},\
        .second = interface_iterator.second\
    };\
    return iterator;\
}\
/* --- --- insert or assign key-value --- --- */\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_or_assign_with_key_copy_value_copy)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type) const* const key,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type) const* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_copy_value_copy);\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) interface_iterator =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_copy_value_copy(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            key,\
            value\
    );\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char) iterator = {\
        .first = {.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = interface_iterator.first},\
        .second = interface_iterator.second\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_or_assign_with_key_move_value_copy)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type)* const key,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type) const* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_move_value_copy);\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) interface_iterator =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_move_value_copy(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            key,\
            value\
    );\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char) iterator = {\
        .first = {.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = interface_iterator.first},\
        .second = interface_iterator.second\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_or_assign_with_key_copy_value_move)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type) const* const key,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type)* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_copy_value_move);\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) interface_iterator =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_copy_value_move(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            key,\
            value\
    );\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char) iterator = {\
        .first = {.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = interface_iterator.first},\
        .second = interface_iterator.second\
    };\
    return iterator;\
}\
COMMON_MODIFIER struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, insert_or_assign_with_key_move_value_move)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type)* const key,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type)* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_move_value_move);\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) interface_iterator =\
        this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_move_value_move(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            key,\
            value\
    );\
    struct PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char) iterator = {\
        .first = {.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = interface_iterator.first},\
        .second = interface_iterator.second\
    };\
    return iterator;\
}\
/* --- --- direct value access by key --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type) const*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this,\
        KEY const* const key) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->at);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->at(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
        key\
    );\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type)*\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, mut_at)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        KEY const* const key) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->mut_at);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->mut_at(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
        key\
    );\
}\
/* --- --- find element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, find)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this,\
        KEY const* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->find);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator = {\
        .INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)) = this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->find(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            value\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, mut_find)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        KEY const* const value) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->mut_find);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->mut_find(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            value\
        )\
    };\
    return iterator;\
}\
/* --- --- erase element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, erase_by_iterator)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) position) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->erase_by_iterator);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->erase_by_iterator(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            position.INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, erase_by_const_iterator)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this,\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type) position) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->erase_by_const_iterator);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->erase_by_const_iterator(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)),\
            position.INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))\
        )\
    };\
    return iterator;\
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
        if (debug_enabled) { debug_rebalance_iteration++; }\
        if (debug_enabled) {\
            LOG_DEBUG_FORMAT("rebalance iteration: %d\n", debug_rebalance_iteration);\
        }\
        /* parent exists & it's red */\
        if (debug_enabled) {\
            LOG_DEBUG("parent exists & it's red\n");\
        }\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* parent = node->parent;\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* grandparent = parent->parent;\
        if (!grandparent) {\
            /* case 4: parent is a root => repaint it & return */\
            if (debug_enabled) {\
                LOG_DEBUG("case 4: parent is a root => repaint it & return\n");\
            }\
            parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            if (debug_enabled) { debug_rebalance_iteration = 0u; }\
            return;\
        }\
        /* grandparent exists & it's black ('couse parent is red) */\
        if (debug_enabled) {\
            LOG_DEBUG("grandparent exists & it's black ('couse parent is red)\n");\
        }\
        usize parent_direction = grandparent->child[1u] == parent;\
        STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* const uncle = grandparent->child[1u - parent_direction];\
        if (uncle &&\
            uncle->color != RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK)) {\
            /* case 2: uncle exists is red => repaint parent/grandparent/uncle, set node <- grandparent & continue */\
            if (debug_enabled) {\
                LOG_DEBUG("case 2: uncle exists is red => repaint parent/grandparent/uncle, set node <- grandparent & continue\n");\
            }\
            parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            uncle->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            grandparent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
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
            RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                parent, parent_direction);\
            node = parent;\
            parent = grandparent->child[parent_direction];\
        }\
        /* case 6: node is an outer node => rotate grandparent/parent, repaint them & return */\
        if (debug_enabled) {\
            LOG_DEBUG("case 6: node is an outer node => rotate grandparent/parent, repaint them & return\n");\
        }\
        RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
            grandparent, 1u - parent_direction);\
        parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
        grandparent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
        if (debug_enabled) { debug_rebalance_iteration = 0u; }\
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
            if (debug_enabled) {\
                LOG_DEBUG("case 3: sibling is red => parent & sibling's children exist and they're black\n");\
            }\
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
            if (debug_enabled) {\
                LOG_DEBUG("case 6: sibling's distant child exists & it's red => sibling is black\n");\
            }\
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
            if (debug_enabled) {\
                LOG_DEBUG("case 5: sibling's close child exists & it's red (& sibling's distant child is null/black) => sibling is black\n");\
            }\
            RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, PRIVATE(rotate))(this,\
                sibling,\
                1u - node_index);\
            sibling->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
            sibling_close_child->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            sibling_distant_child = sibling;\
            sibling = sibling_close_child;\
            /* sibling_distant_child is red & sibling is black -> go to 6! [we're don't use goto, sorry] */\
            /* case 6: sibling's distant child exists & it's red => sibling is black */\
            if (debug_enabled) {\
                LOG_DEBUG("case 6 (from 5): sibling's distant child exists & it's red => sibling is black\n");\
            }\
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
            if (debug_enabled) {\
                LOG_DEBUG("case 4: parent is red => sibling & its' children are black\n");\
            }\
            sibling->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
            parent->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK);\
            break;\
        }\
        /* case 2: parent/sibling & its' children are black */\
        if (debug_enabled) {\
            LOG_DEBUG("case 2: parent/sibling & its' children are black\n");\
        }\
        sibling->color = RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED);\
        node = parent;\
    } while (node->parent);\
}\
/* --- Iterators' related methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, begin)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->begin);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->begin(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, end)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->end);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type) iterator = {\
        .INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->end(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, cbegin)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->cbegin);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator = {\
        .INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)) = this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->cbegin(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))\
        )\
    };\
    return iterator;\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, cend)(\
        struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->cend);\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type) iterator = {\
        .INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)) = this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->cend(\
            &this->INTERFACE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))\
        )\
    };\
    return iterator;\
}\
/* --- Mutable iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    TYPE_METHOD(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), construct_at)(&this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
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
    this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = source->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
    return this;\
}\
COMMON_MODIFIER void* RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->destroy_at);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->destroy_at(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))\
    );\
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
    void* const temporary = this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
    this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = another->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
    another->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).element_storage = temporary;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type) const*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, key)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->key);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->key(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type)*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, value)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->value);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->value(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type) const*\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, const_value)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->const_value);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->const_value(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, compare)(\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this,\
    struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->compare);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->compare(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)),\
        &source->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, next)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->next);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->next(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, pnext)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->pnext);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->pnext(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, prev)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->prev);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->prev(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, pprev)(\
        struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->pprev);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->pprev(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* --- Const iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, construct_at)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    TYPE_METHOD(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), construct_at)(&this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)) =\
        &CONTAINER_INTERFACE_VTABLE_STATIC_VARIABLE(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR),\
            MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
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
    this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage = source->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
    return this;\
}\
COMMON_MODIFIER void* RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, destroy_at)(\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->destroy_at);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->destroy_at(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))\
    );\
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
    void const* const temporary = this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
    this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage = another->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage;\
    another->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).element_storage = temporary;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type) const*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, key)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->key);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->key(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type)*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, value)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->value);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->value(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type) const*\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, const_value)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->const_value);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->const_value(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, compare)(\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const this,\
    struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->compare);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->compare(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)),\
        &source->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, next)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->next);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->next(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, pnext)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->pnext);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->pnext(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, prev)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->prev);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->prev(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))\
    );\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_CONST_ITERATOR_WITH_COMPARATOR_AND_ALLOCATOR_METHOD(KEY, VALUE, COMPARATOR, ALLOCATOR, pprev)(\
        struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)));\
    ASSERT(this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->pprev);\
    return this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)).INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->pprev(\
        &this->INTERFACE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))\
    );\
}

#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_METHODS(KEY, VALUE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_STATIC_METHODS(KEY, VALUE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(static, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_INLINE_METHODS(KEY, VALUE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(inline, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_EXTERNAL_METHODS(KEY, VALUE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(extern, KEY, VALUE, COMPARATOR, ALLOCATOR)
#define DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_EXTERNAL_INLINE_METHODS(KEY, VALUE, COMPARATOR, ALLOCATOR) DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(extern inline, KEY, VALUE, COMPARATOR, ALLOCATOR)
