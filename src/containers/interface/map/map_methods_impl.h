#pragma once

#include "map_methods_decl.h"
#include "map_inheritance.h"

// map methods implementation
#define DEFINE_MAP_INTERFACE_METHODS_WITH_MODIFIER(COMMON_MODIFIER, KEY, VALUE)\
/* --- Set interface methods --- */\
DEFINE_PAIR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, construct_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE)) = &INTERFACE_VTABLE_STATIC_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE));\
    return this;\
}\
COMMON_MODIFIER struct MAP_INTERFACE_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, construct_move_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    MAP_INTERFACE_METHOD(KEY, VALUE, construct_at)(this);\
    return this;\
}\
COMMON_MODIFIER struct MAP_INTERFACE_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, construct_copy_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    MAP_INTERFACE_METHOD(KEY, VALUE, construct_at)(this);\
    return this;\
}\
COMMON_MODIFIER void* MAP_INTERFACE_METHOD(KEY, VALUE, destroy_at)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->destroy_at);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->destroy_at(this);\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, assign_move_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    return this;\
}\
COMMON_MODIFIER struct MAP_INTERFACE_TYPE(KEY, VALUE)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, assign_copy_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    return this;\
}\
/* --- Common containers' functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), size_type)\
    MAP_INTERFACE_METHOD(KEY, VALUE, size)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->size);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->size(this);\
}\
COMMON_MODIFIER void MAP_INTERFACE_METHOD(KEY, VALUE, clear)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->clear);\
    this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->clear(this);\
}\
/* --- Elements' manipulation functions --- */\
/* --- --- insert element --- --- */\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_copy)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type) const* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_copy);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_copy(this, value);\
}\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_move)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type)* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_move);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_move(this, value);\
}\
/* --- --- insert or assign key-value --- --- */\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_or_assign_with_key_copy_value_copy)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type) const* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const* const value) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(value);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_copy_value_copy);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_copy_value_copy(\
        this,\
        key,\
        value\
    );\
}\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_or_assign_with_key_move_value_copy)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type)* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const* const value) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(value);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_move_value_copy);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_move_value_copy(\
        this,\
        key,\
        value\
    );\
}\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_or_assign_with_key_copy_value_move)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type) const* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)* const value) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(value);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_copy_value_move);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_copy_value_move(\
        this,\
        key,\
        value\
    );\
}\
COMMON_MODIFIER struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char)\
    MAP_INTERFACE_METHOD(KEY, VALUE, insert_or_assign_with_key_move_value_move)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type)* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)* const value) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(value);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_move_value_move);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->insert_or_assign_with_key_move_value_move(\
        this,\
        key,\
        value\
    );\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const*\
    MAP_INTERFACE_METHOD(KEY, VALUE, at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this,\
        KEY const* const key) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->at);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->at(\
        this,\
        key\
    );\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)*\
    MAP_INTERFACE_METHOD(KEY, VALUE, mut_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        KEY const* const key) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->mut_at);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->mut_at(\
        this,\
        key\
    );\
}\
/* --- --- find element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type) MAP_INTERFACE_METHOD(KEY, VALUE, find)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this,\
    KEY const* const key) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->find);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->find(this, key);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) MAP_INTERFACE_METHOD(KEY, VALUE, mut_find)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
    KEY const* const key) {\
    ASSERT(this);\
    ASSERT(key);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->mut_find);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->mut_find(this, key);\
}\
/* --- --- erase element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) MAP_INTERFACE_METHOD(KEY, VALUE, erase_by_iterator)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) iterator) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->erase_by_iterator);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->erase_by_iterator(this, iterator);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) MAP_INTERFACE_METHOD(KEY, VALUE, erase_by_const_iterator)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type) iterator) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->erase_by_const_iterator);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->erase_by_const_iterator(this, iterator);\
}\
/* --- Iterators' related methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) MAP_INTERFACE_METHOD(KEY, VALUE, begin)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->begin);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->begin(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) MAP_INTERFACE_METHOD(KEY, VALUE, end)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->end);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->end(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type) MAP_INTERFACE_METHOD(KEY, VALUE, cbegin)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->cbegin);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->cbegin(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type) MAP_INTERFACE_METHOD(KEY, VALUE, cend)(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->cend);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_TYPE(KEY, VALUE))->cend(this);\
}\
/* --- Mutable iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, construct_at)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = &INTERFACE_VTABLE_STATIC_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
    this->element_storage = NULL;\
    return this;\
}\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, construct_move_at)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const source) {\
    return MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, construct_copy_at)(this, source);\
}\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, construct_copy_at)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, construct_at)(this)->element_storage = source->element_storage;\
    return this;\
}\
COMMON_MODIFIER void* MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, destroy_at)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->destroy_at);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->destroy_at(this);\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, assign_move_at)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const source) {\
    return MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, assign_copy_at)(this, source);\
}\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, assign_copy_at)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->element_storage = source->element_storage;\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, swap)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    void* temporary = this->element_storage;\
    this->element_storage = source->element_storage;\
    source->element_storage = temporary;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), key_type) const*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, key)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->key);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->key(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), mapped_type)*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, value)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->value);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->value(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), mapped_type) const*\
    MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, const_value)(\
        struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->const_value);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->const_value(this);\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, compare)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const this,\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->compare);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->compare(this, source);\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, next)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->next);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->next(this);\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, pnext)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->pnext);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->pnext(this);\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, prev)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->prev);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->prev(this);\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, pprev)(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->pprev);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE))->pprev(this);\
}\
/* --- Const iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, construct_at)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)) = &INTERFACE_VTABLE_STATIC_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
    this->element_storage = NULL;\
    return this;\
}\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, construct_move_at)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const source) {\
    return MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, construct_copy_at)(this, source);\
}\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, construct_copy_at)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, construct_at)(this)->element_storage = source->element_storage;\
    return this;\
}\
COMMON_MODIFIER void* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, destroy_at)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->destroy_at);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->destroy_at(this);\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, assign_move_at)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const source) {\
    return MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, assign_copy_at)(this, source);\
}\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, assign_copy_at)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this,\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->element_storage = source->element_storage;\
    return this;\
}\
/* --- Swap --- */\
COMMON_MODIFIER void\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, swap)(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this,\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    void const* temporary = this->element_storage;\
    this->element_storage = source->element_storage;\
    source->element_storage = temporary;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), key_type) const*\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, key)(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->key);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->key(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), mapped_type)*\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, value)(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->value);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->value(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), mapped_type) const*\
    MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, const_value)(\
        struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->const_value);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->const_value(this);\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, compare)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const this,\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->compare);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->compare(this, source);\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, next)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->next);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->next(this);\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, pnext)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->pnext);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->pnext(this);\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, prev)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->prev);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->prev(this);\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, pprev)(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->pprev);\
    return this->INTERFACE_VTABLE_VARIABLE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE))->pprev(this);\
}

#define DEFINE_MAP_INTERFACE_METHODS(KEY, VALUE) DEFINE_MAP_INTERFACE_METHODS_WITH_MODIFIER(, KEY, VALUE)
#define DEFINE_MAP_INTERFACE_STATIC_METHODS(KEY, VALUE) DEFINE_MAP_INTERFACE_METHODS_WITH_MODIFIER(static, KEY, VALUE)
#define DEFINE_MAP_INTERFACE_INLINE_METHODS(KEY, VALUE) DEFINE_MAP_INTERFACE_METHODS_WITH_MODIFIER(inline, KEY, VALUE)
