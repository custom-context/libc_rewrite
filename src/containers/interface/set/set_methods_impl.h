#pragma once

#include "set_methods_decl.h"
#include "set_inheritance.h"

// set methods implementation
#define DEFINE_SET_INTERFACE_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
/* --- Set interface methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_TYPE(TYPE)* SET_INTERFACE_METHOD(TYPE, construct_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE)) = &INTERFACE_VTABLE_STATIC_VARIABLE(SET_INTERFACE_TYPE(TYPE));\
    return this;\
}\
COMMON_MODIFIER struct SET_INTERFACE_TYPE(TYPE)* SET_INTERFACE_METHOD(TYPE, construct_move_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_TYPE(TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    SET_INTERFACE_METHOD(TYPE, construct_at)(this);\
    return this;\
}\
COMMON_MODIFIER struct SET_INTERFACE_TYPE(TYPE)* SET_INTERFACE_METHOD(TYPE, construct_copy_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    SET_INTERFACE_METHOD(TYPE, construct_at)(this);\
    return this;\
}\
COMMON_MODIFIER void* SET_INTERFACE_DYNAMIC_METHOD(TYPE, destroy_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->destroy_at);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->destroy_at(this);\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_TYPE(TYPE)* SET_INTERFACE_METHOD(TYPE, assign_move_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_TYPE(TYPE)* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    return this;\
}\
COMMON_MODIFIER struct SET_INTERFACE_TYPE(TYPE)* SET_INTERFACE_METHOD(TYPE, assign_copy_at)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    return this;\
}\
/* --- Common containers' functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), size_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, size)(\
    struct SET_INTERFACE_TYPE(TYPE) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->size);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->size(this);\
}\
COMMON_MODIFIER void SET_INTERFACE_DYNAMIC_METHOD(TYPE, clear)(struct SET_INTERFACE_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->clear);\
    this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->clear(this);\
}\
/* --- Elements' manipulation functions --- */\
/* --- --- insert element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, insert_copy)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    TYPE const* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->insert_copy);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->insert_copy(this, value);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, insert_move)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    TYPE* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->insert_move);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->insert_move(this, value);\
}\
/* --- --- find element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, find)(\
    struct SET_INTERFACE_TYPE(TYPE) const* const this,\
    TYPE const* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->find);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->find(this, value);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, mut_find)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    TYPE const* const value) {\
    ASSERT(this);\
    ASSERT(value);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->mut_find);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->mut_find(this, value);\
}\
/* --- --- erase element --- --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, erase_by_iterator)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) iterator) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->erase_by_iterator);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->erase_by_iterator(this, iterator);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, erase_by_const_iterator)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this,\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) iterator) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->erase_by_const_iterator);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->erase_by_const_iterator(this, iterator);\
}\
/* --- Iterators' related methods --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, begin)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->begin);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->begin(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, end)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->end);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->end(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, cbegin)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->cbegin);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->cbegin(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) SET_INTERFACE_DYNAMIC_METHOD(TYPE, cend)(\
    struct SET_INTERFACE_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->cend);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_TYPE(TYPE))->cend(this);\
}\
/* --- Mutable iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* SET_INTERFACE_ITERATOR_METHOD(TYPE, construct_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE)) = &INTERFACE_VTABLE_STATIC_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    this->element_storage = NULL;\
    return this;\
}\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* SET_INTERFACE_ITERATOR_METHOD(TYPE, construct_move_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const source) {\
    return SET_INTERFACE_ITERATOR_METHOD(TYPE, construct_copy_at)(this, source);\
}\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* SET_INTERFACE_ITERATOR_METHOD(TYPE, construct_copy_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    SET_INTERFACE_ITERATOR_METHOD(TYPE, construct_at)(this)->element_storage = source->element_storage;\
    return this;\
}\
COMMON_MODIFIER void* SET_INTERFACE_ITERATOR_DYNAMIC_METHOD(TYPE, destroy_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->destroy_at);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->destroy_at(this);\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* SET_INTERFACE_ITERATOR_METHOD(TYPE, assign_move_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const source) {\
    return SET_INTERFACE_ITERATOR_METHOD(TYPE, assign_copy_at)(this, source);\
}\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* SET_INTERFACE_ITERATOR_METHOD(TYPE, assign_copy_at)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->element_storage = source->element_storage;\
    return this;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE), value_type)* SET_INTERFACE_ITERATOR_DYNAMIC_METHOD(TYPE, value)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->value);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->value(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE), value_type) const* SET_INTERFACE_ITERATOR_DYNAMIC_METHOD(TYPE, const_value)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->const_value);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->const_value(this);\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int SET_INTERFACE_ITERATOR_DYNAMIC_METHOD(TYPE, compare)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const this,\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->compare);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->compare(this, source);\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE) SET_INTERFACE_ITERATOR_DYNAMIC_METHOD(TYPE, next)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->next);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->next(this);\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE) SET_INTERFACE_ITERATOR_DYNAMIC_METHOD(TYPE, pnext)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->pnext);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->pnext(this);\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE) SET_INTERFACE_ITERATOR_DYNAMIC_METHOD(TYPE, prev)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->prev);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->prev(this);\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct SET_INTERFACE_ITERATOR_TYPE(TYPE) SET_INTERFACE_ITERATOR_DYNAMIC_METHOD(TYPE, pprev)(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->pprev);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_ITERATOR_TYPE(TYPE))->pprev(this);\
}\
/* --- Const iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, construct_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)) = &INTERFACE_VTABLE_STATIC_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
    this->element_storage = NULL;\
    return this;\
}\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, construct_move_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const source) {\
    return SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, construct_copy_at)(this, source);\
}\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, construct_copy_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, construct_at)(this)->element_storage = source->element_storage;\
    return this;\
}\
COMMON_MODIFIER void* SET_INTERFACE_CONST_ITERATOR_DYNAMIC_METHOD(TYPE, destroy_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->destroy_at);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->destroy_at(this);\
}\
/* --- Assign functions --- */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, assign_move_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const source) {\
    return SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, assign_copy_at)(this, source);\
}\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, assign_copy_at)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    this->element_storage = source->element_storage;\
    return this;\
}\
/* --- Element access functions --- */\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), value_type)* SET_INTERFACE_CONST_ITERATOR_DYNAMIC_METHOD(TYPE, value)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->value);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->value(this);\
}\
COMMON_MODIFIER STRUCT_SUBTYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), value_type) const* SET_INTERFACE_CONST_ITERATOR_DYNAMIC_METHOD(TYPE, const_value)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->const_value);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->const_value(this);\
}\
/* --- Compare functions --- */\
/* return 0 if equals, !0 either */\
COMMON_MODIFIER int SET_INTERFACE_CONST_ITERATOR_DYNAMIC_METHOD(TYPE, compare)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const this,\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->compare);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->compare(this, source);\
}\
/* --- Increment functions --- */\
/* point this to next value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) SET_INTERFACE_CONST_ITERATOR_DYNAMIC_METHOD(TYPE, next)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->next);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->next(this);\
}\
/* return this-value & point this to next value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) SET_INTERFACE_CONST_ITERATOR_DYNAMIC_METHOD(TYPE, pnext)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->pnext);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->pnext(this);\
}\
/* --- Decrement functions --- */\
/* point this to previous value & return this-value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) SET_INTERFACE_CONST_ITERATOR_DYNAMIC_METHOD(TYPE, prev)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->prev);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->prev(this);\
}\
/* return this-value & point this to previous value */\
COMMON_MODIFIER struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) SET_INTERFACE_CONST_ITERATOR_DYNAMIC_METHOD(TYPE, pprev)(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    ASSERT(this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->pprev);\
    return this->INTERFACE_VTABLE_VARIABLE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE))->pprev(this);\
}

#define DEFINE_SET_INTERFACE_METHODS(TYPE) DEFINE_SET_INTERFACE_METHODS_WITH_MODIFIER(, TYPE)
#define DEFINE_SET_INTERFACE_STATIC_METHODS(TYPE) DEFINE_SET_INTERFACE_METHODS_WITH_MODIFIER(static, TYPE)
#define DEFINE_SET_INTERFACE_INLINE_METHODS(TYPE) DEFINE_SET_INTERFACE_METHODS_WITH_MODIFIER(inline, TYPE)
