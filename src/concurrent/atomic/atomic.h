#pragma once

#include "common.h"
#include "memory_order.h"
#include "native.h"
#include <primitives/bool_type_alias.h>
#include <construct/characters_helpers.h>
#include <construct/numeric_helpers.h>
#include <construct/data_model_helpers.h>

#define ATOMIC_TYPE(TYPE)\
    NAMESPACE_CONCURRENT_ATOMIC(CONCAT3(atomic, __, TYPE))

#define DEFINE_ATOMIC_TYPE(TYPE)\
DECLARE_STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type, TYPE);\
typedef struct ATOMIC_TYPE(TYPE) {\
    _Atomic(TYPE) value;\
} ATOMIC_TYPE(TYPE)

#define ATOMIC_METHOD(TYPE, METHOD)\
    TYPE_METHOD(ATOMIC_TYPE(TYPE), METHOD)

// methods declarations
#define DECLARE_ATOMIC_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
/* --- Construction/Destruction functions --- */\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, construct_at)(\
        struct ATOMIC_TYPE(TYPE)* const this);\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, construct_copy_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        struct ATOMIC_TYPE(TYPE) const* const source);\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, construct_move_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        struct ATOMIC_TYPE(TYPE)* const source);\
MODIFIER void*\
    ATOMIC_METHOD(TYPE, destroy_at)(\
        struct ATOMIC_TYPE(TYPE)* const this);\
/* --- Assign functions --- */\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, assign_copy_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        struct ATOMIC_TYPE(TYPE) const* const source);\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, assign_move_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        struct ATOMIC_TYPE(TYPE)* const source);\
/* --- Swap --- */\
MODIFIER void\
    ATOMIC_METHOD(TYPE, swap)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        struct ATOMIC_TYPE(TYPE)* const another);\
/* --- Non-default methods --- */\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, construct_from_value_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) value);\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, assign_from_value_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) value);\
/* --- --- is_lock_free --- --- */\
MODIFIER bool\
    ATOMIC_METHOD(TYPE, is_lock_free)(\
        struct ATOMIC_TYPE(TYPE) volatile const* const this);\
/* --- --- store --- --- */\
MODIFIER void\
    ATOMIC_METHOD(TYPE, store_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value);\
MODIFIER void\
    ATOMIC_METHOD(TYPE, store)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired);\
/* --- --- load --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, load_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile const* const this,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value);\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, load)(\
        struct ATOMIC_TYPE(TYPE) volatile const* const this);\
/* --- --- exchange --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, exchange_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value);\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, exchange)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired);\
/* --- --- compare_exchange_strong --- --- */\
MODIFIER bool\
    ATOMIC_METHOD(TYPE, compare_exchange_strong_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)* const expected,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() on_match_and_store,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() on_unmatch_and_load);\
MODIFIER bool\
    ATOMIC_METHOD(TYPE, compare_exchange_strong)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)* const expected,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired);\
/* --- --- compare_exchange_weak --- --- */\
MODIFIER bool\
    ATOMIC_METHOD(TYPE, compare_exchange_weak_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)* const expected,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() on_match_and_store,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() on_unmatch_and_load);\
MODIFIER bool\
    ATOMIC_METHOD(TYPE, compare_exchange_weak)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)* const expected,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired);\
/* --- --- fetch_add --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_add_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value);\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_add)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired);\
/* --- --- fetch_sub --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_sub_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value);\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_sub)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired);\
/* --- --- fetch_and --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_and_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value);\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_and)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired);\
/* --- --- fetch_or --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_or_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value);\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_or)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired);\
/* --- --- fetch_xor --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_xor_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value);\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_xor)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired)

// methods definitions
#define DEFINE_ATOMIC_METHODS_WITH_MODIFIER(MODIFIER, TYPE)\
/* --- Construction/Destruction functions --- */\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, construct_at)(\
        struct ATOMIC_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) value;\
    TYPE_METHOD(TYPE, construct_at)(&value);\
    atomic_init(&this->value, value);\
    return this;\
}\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, construct_copy_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        struct ATOMIC_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(false);\
    return this;\
}\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, construct_move_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        struct ATOMIC_TYPE(TYPE)* const source) {\
    return ATOMIC_METHOD(TYPE, construct_copy_at)(this, source);\
}\
MODIFIER void*\
    ATOMIC_METHOD(TYPE, destroy_at)(\
        struct ATOMIC_TYPE(TYPE)* const this) {\
    UNUSED(this);\
    return this;\
}\
/* --- Assign functions --- */\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, assign_copy_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        struct ATOMIC_TYPE(TYPE) const* const source) {\
    ASSERT(this);\
    ASSERT(source);\
    ASSERT(false);\
    return this;\
}\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, assign_move_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        struct ATOMIC_TYPE(TYPE)* const source) {\
    return ATOMIC_METHOD(TYPE, assign_copy_at)(this, source);\
}\
/* --- Swap --- */\
MODIFIER void\
    ATOMIC_METHOD(TYPE, swap)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        struct ATOMIC_TYPE(TYPE)* const another) {\
    ASSERT(this);\
    ASSERT(another);\
    ASSERT(false);\
}\
/* --- Non-default methods --- */\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, construct_from_value_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) value) {\
    ASSERT(this);\
    atomic_init(&this->value, value);\
    return this;\
}\
MODIFIER struct ATOMIC_TYPE(TYPE)*\
    ATOMIC_METHOD(TYPE, assign_from_value_at)(\
        struct ATOMIC_TYPE(TYPE)* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) value) {\
    ASSERT(this);\
    ATOMIC_METHOD(TYPE, store)(this, value);\
    return this;\
}\
/* --- --- is_lock_free --- --- */\
MODIFIER bool\
    ATOMIC_METHOD(TYPE, is_lock_free)(\
        struct ATOMIC_TYPE(TYPE) volatile const* const this) {\
    ASSERT(this);\
    return atomic_is_lock_free(&this->value);\
}\
/* --- --- store --- --- */\
MODIFIER void\
    ATOMIC_METHOD(TYPE, store_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value) {\
    ASSERT(this);\
    atomic_store_explicit(&this->value, desired, memory_order_enum_value);\
}\
MODIFIER void\
    ATOMIC_METHOD(TYPE, store)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired) {\
    ASSERT(this);\
    atomic_store(&this->value, desired);\
}\
/* --- --- load --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, load_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile const* const this,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value) {\
    ASSERT(this);\
    return atomic_load_explicit(&this->value, memory_order_enum_value);\
}\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, load)(\
        struct ATOMIC_TYPE(TYPE) volatile const* const this) {\
    ASSERT(this);\
    return atomic_load(&this->value);\
}\
/* --- --- exchange --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, exchange_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value) {\
    ASSERT(this);\
    return atomic_exchange_explicit(&this->value, desired, memory_order_enum_value);\
}\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, exchange)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired) {\
    ASSERT(this);\
    return atomic_exchange(&this->value, desired);\
}\
/* --- --- compare_exchange_strong --- --- */\
MODIFIER bool\
    ATOMIC_METHOD(TYPE, compare_exchange_strong_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)* const expected,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() on_match_and_store,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() on_unmatch_and_load) {\
    ASSERT(this);\
    ASSERT(expected);\
    return (bool)!!atomic_compare_exchange_strong_explicit(&this->value, expected, desired,\
        on_match_and_store, on_unmatch_and_load);\
}\
MODIFIER bool\
    ATOMIC_METHOD(TYPE, compare_exchange_strong)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)* const expected,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired) {\
    ASSERT(this);\
    ASSERT(expected);\
    return (bool)!!atomic_compare_exchange_strong(&this->value, expected, desired);\
}\
/* --- --- compare_exchange_weak --- --- */\
MODIFIER bool\
    ATOMIC_METHOD(TYPE, compare_exchange_weak_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)* const expected,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() on_match_and_store,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() on_unmatch_and_load) {\
    ASSERT(this);\
    ASSERT(expected);\
    return (bool)!!atomic_compare_exchange_weak_explicit(&this->value, expected, desired,\
        on_match_and_store, on_unmatch_and_load);\
}\
MODIFIER bool\
    ATOMIC_METHOD(TYPE, compare_exchange_weak)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)* const expected,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired) {\
    ASSERT(this);\
    ASSERT(expected);\
    return (bool)!!atomic_compare_exchange_weak(&this->value, expected, desired);\
}\
/* --- --- fetch_add --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_add_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value) {\
    ASSERT(this);\
    return atomic_fetch_add_explicit(&this->value, desired, memory_order_enum_value);\
}\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_add)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired) {\
    ASSERT(this);\
    return atomic_fetch_add(&this->value, desired);\
}\
/* --- --- fetch_sub --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_sub_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value) {\
    ASSERT(this);\
    return atomic_fetch_sub_explicit(&this->value, desired, memory_order_enum_value);\
}\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_sub)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired) {\
    ASSERT(this);\
    return atomic_fetch_sub(&this->value, desired);\
}\
/* --- --- fetch_and --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_and_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value) {\
    ASSERT(this);\
    return atomic_fetch_and_explicit(&this->value, desired, memory_order_enum_value);\
}\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_and)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired) {\
    ASSERT(this);\
    return atomic_fetch_and(&this->value, desired);\
}\
/* --- --- fetch_or --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_or_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value) {\
    ASSERT(this);\
    return atomic_fetch_or_explicit(&this->value, desired, memory_order_enum_value);\
}\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_or)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired) {\
    ASSERT(this);\
    return atomic_fetch_or(&this->value, desired);\
}\
/* --- --- fetch_xor --- --- */\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_xor_explicit)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired,\
        enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order_enum_value) {\
    ASSERT(this);\
    return atomic_fetch_xor_explicit(&this->value, desired, memory_order_enum_value);\
}\
MODIFIER STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type)\
    ATOMIC_METHOD(TYPE, fetch_xor)(\
        struct ATOMIC_TYPE(TYPE) volatile* const this,\
        STRUCT_SUBTYPE(ATOMIC_TYPE(TYPE), value_type) desired) {\
    ASSERT(this);\
    return atomic_fetch_xor(&this->value, desired);\
}
