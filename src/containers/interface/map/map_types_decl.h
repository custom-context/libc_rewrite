#pragma once

#include <containers/iterator/iterator.h>
#include <containers/interface/common.h>
#include <containers/pair/pair.h>

// map type
#define MAP_INTERFACE_TYPE(KEY, VALUE) NAMESPACE_CONTAINERS_INTERFACE(CONCAT5(INTERFACE_TYPE(map), __, KEY, _to_, VALUE))

// map's iterator type
#define MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) ITERATOR_TYPE(MAP_INTERFACE_TYPE(KEY, VALUE))

// map's const iterator type
#define MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) CONST_ITERATOR_TYPE(MAP_INTERFACE_TYPE(KEY, VALUE))

// map type declaration
#define DECLARE_MAP_INTERFACE_TYPE(KEY, VALUE)\
/* map's iterator type virtual table */\
struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE);\
DECLARE_STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), key_type, KEY const);\
DECLARE_STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), mapped_type, VALUE);\
typedef struct INTERFACE_VTABLE_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) {\
    void* (*destroy_at)(struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
    /* --- Element access functions --- */\
    STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), key_type) const* (*key)(struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const this);\
    STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), mapped_type)* (*value)(struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
    STRUCT_SUBTYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), mapped_type) const* (*const_value)(struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const this);\
    /* --- Compare functions --- */\
    /* return 0 if equals, !0 either */\
    int (*compare)(struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const this, struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) const* const source);\
    /* --- Increment functions --- */\
    /* point this to next value & return this-value */\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) (*next)(struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
    /* return this-value & point this to next value */\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) (*pnext)(struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
    /* --- Decrement functions --- */\
    /* point this to previous value & return this-value */\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) (*prev)(struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
    /* return this-value & point this to previous value */\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) (*pprev)(struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
} INTERFACE_VTABLE_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
/* map's iterator type */\
typedef struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE) {\
    DEFINE_INTERFACE_VTABLE_ADAPTER(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
    void* element_storage;\
} MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE);\
/* map's const iterator type virtual table */\
struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE);\
DECLARE_STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), key_type, KEY const);\
DECLARE_STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), mapped_type, VALUE const);\
typedef struct INTERFACE_VTABLE_TYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)) {\
    void* (*destroy_at)(struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
    /* --- Element access functions --- */\
    STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), key_type) const* (*key)(struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const this);\
    STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), mapped_type)* (*value)(struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
    STRUCT_SUBTYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), mapped_type) const* (*const_value)(struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const this);\
    /* --- Compare functions --- */\
    /* return 0 if equals, !0 either */\
    int (*compare)(struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const this, struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) const* const source);\
    /* --- Increment functions --- */\
    /* point this to next value & return this-value */\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) (*next)(struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
    /* return this-value & point this to next value */\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) (*pnext)(struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
    /* --- Decrement functions --- */\
    /* point this to previous value & return this-value */\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) (*prev)(struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
    /* return this-value & point this to previous value */\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) (*pprev)(struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\
} INTERFACE_VTABLE_TYPE(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
/* map's const iterator type */\
typedef struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE) {\
    DEFINE_INTERFACE_VTABLE_ADAPTER(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
    void const* element_storage;\
} MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE);\
struct MAP_INTERFACE_TYPE(KEY, VALUE);\
DECLARE_STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type, KEY);\
DECLARE_STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type, VALUE);\
DECLARE_STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type, PAIR_TYPE(\
    KEY,\
    VALUE\
));\
DECLARE_STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), size_type, size_t);\
DECLARE_STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type, MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
DECLARE_STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type, MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
DEFINE_PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char);\
/* map type virtual table */\
typedef struct INTERFACE_VTABLE_TYPE(MAP_INTERFACE_TYPE(KEY, VALUE)) {\
    void* (*destroy_at)(struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
    void (*clear)(struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), size_type) (*size)(struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this);\
    /* insert element */\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) (*insert_copy)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type) const* const value);\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) (*insert_move)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), value_type)* const value);\
    /* insert or assign key-value */\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) (*insert_or_assign_with_key_copy_value_copy)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type) const* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const* const value);\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) (*insert_or_assign_with_key_move_value_copy)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type)* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const* const value);\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) (*insert_or_assign_with_key_copy_value_move)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type) const* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)* const value);\
    struct PAIR_TYPE(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), char) (*insert_or_assign_with_key_move_value_move)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), key_type)* const key,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)* const value);\
    /* direct value access by key */\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type) const* (*at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this,\
        KEY const* const key);\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), mapped_type)* (*mut_at)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        KEY const* const key);\
    /* find element by key */\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type) (*find)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this,\
        KEY const* const key);\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) (*mut_find)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        KEY const* const key);\
    /* erase element by iterator */\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) (*erase_by_iterator)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) iterator);\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) (*erase_by_const_iterator)(\
        struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this,\
        STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type) iterator);\
    /* basic iterators' construction methods */\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) (*begin)(struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), iterator_type) (*end)(struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type) (*cbegin)(struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this);\
    STRUCT_SUBTYPE(MAP_INTERFACE_TYPE(KEY, VALUE), const_iterator_type) (*cend)(struct MAP_INTERFACE_TYPE(KEY, VALUE) const* const this);\
} INTERFACE_VTABLE_TYPE(MAP_INTERFACE_TYPE(KEY, VALUE));\
/* map type */\
typedef struct MAP_INTERFACE_TYPE(KEY, VALUE) {\
    DEFINE_INTERFACE_VTABLE_ADAPTER(MAP_INTERFACE_TYPE(KEY, VALUE));\
} MAP_INTERFACE_TYPE(KEY, VALUE)
