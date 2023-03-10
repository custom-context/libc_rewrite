#pragma once

#include <containers/iterator/iterator.h>
#include <containers/interface/common.h>

// set type
#define SET_INTERFACE_TYPE(TYPE) NAMESPACE_CONTAINERS_INTERFACE(CONCAT3(INTERFACE_TYPE(set), __, TYPE))

// set's iterator type
#define SET_INTERFACE_ITERATOR_TYPE(TYPE) ITERATOR_TYPE(SET_INTERFACE_TYPE(TYPE))
// set's const iterator type
#define SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) CONST_ITERATOR_TYPE(SET_INTERFACE_TYPE(TYPE))

// set type declaration
#define DECLARE_SET_INTERFACE_TYPE(TYPE)\
/* set's iterator type virtual table */\
struct SET_INTERFACE_ITERATOR_TYPE(TYPE);\
DECLARE_STRUCT_SUBTYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE), value_type, TYPE);\
typedef struct INTERFACE_VTABLE_TYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE)) {\
    void* (*destroy_at)(struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
    /* --- Element access functions --- */\
    STRUCT_SUBTYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE), value_type)* (*value)(struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
    STRUCT_SUBTYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE), value_type) const* (*const_value)(struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const this);\
    /* --- Compare functions --- */\
    /* return 0 if equals, !0 either */\
    int (*compare)(struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const this, struct SET_INTERFACE_ITERATOR_TYPE(TYPE) const* const source);\
    /* --- Increment functions --- */\
    /* point this to next value & return this-value */\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) (*next)(struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
    /* return this-value & point this to next value */\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) (*pnext)(struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
    /* --- Decrement functions --- */\
    /* point this to previous value & return this-value */\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) (*prev)(struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
    /* return this-value & point this to previous value */\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE) (*pprev)(struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this);\
} INTERFACE_VTABLE_TYPE(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
/* set's iterator type */\
typedef struct SET_INTERFACE_ITERATOR_TYPE(TYPE) {\
    DEFINE_INTERFACE_VTABLE_ADAPTER(SET_INTERFACE_ITERATOR_TYPE(TYPE));\
    void* element_storage;\
} SET_INTERFACE_ITERATOR_TYPE(TYPE);\
/* set's const iterator type virtual table */\
struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE);\
DECLARE_STRUCT_SUBTYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), value_type, TYPE const);\
typedef struct INTERFACE_VTABLE_TYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)) {\
    void* (*destroy_at)(struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
    /* --- Element access functions --- */\
    STRUCT_SUBTYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), value_type)* (*value)(struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
    STRUCT_SUBTYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE), value_type) const* (*const_value)(struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const this);\
    /* --- Compare functions --- */\
    /* return 0 if equals, !0 either */\
    int (*compare)(struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const this, struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) const* const source);\
    /* --- Increment functions --- */\
    /* point this to next value & return this-value */\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) (*next)(struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
    /* return this-value & point this to next value */\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) (*pnext)(struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
    /* --- Decrement functions --- */\
    /* point this to previous value & return this-value */\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) (*prev)(struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
    /* return this-value & point this to previous value */\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) (*pprev)(struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this);\
} INTERFACE_VTABLE_TYPE(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
/* set's const iterator type */\
typedef struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE) {\
    DEFINE_INTERFACE_VTABLE_ADAPTER(SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
    void const* element_storage;\
} SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE);\
struct SET_INTERFACE_TYPE(TYPE);\
DECLARE_STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), value_type, TYPE);\
DECLARE_STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), size_type, size_t);\
DECLARE_STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type, SET_INTERFACE_ITERATOR_TYPE(TYPE));\
DECLARE_STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type, SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE));\
/* set type virtual table */\
typedef struct INTERFACE_VTABLE_TYPE(SET_INTERFACE_TYPE(TYPE)) {\
    void* (*destroy_at)(struct SET_INTERFACE_TYPE(TYPE)* const this);\
    void (*clear)(struct SET_INTERFACE_TYPE(TYPE)* const this);\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), size_type) (*size)(struct SET_INTERFACE_TYPE(TYPE) const* const this);\
    /* insert element */\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) (*insert_copy)(struct SET_INTERFACE_TYPE(TYPE)* const this, TYPE const* const value);\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) (*insert_move)(struct SET_INTERFACE_TYPE(TYPE)* const this, TYPE* const value);\
    /* find element */\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) (*find)(struct SET_INTERFACE_TYPE(TYPE) const* const this, TYPE const* const value);\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) (*mut_find)(struct SET_INTERFACE_TYPE(TYPE)* const this, TYPE const* const value);\
    /* erase element */\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) (*erase_by_iterator)(struct SET_INTERFACE_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) iterator);\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) (*erase_by_const_iterator)(struct SET_INTERFACE_TYPE(TYPE)* const this, STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) iterator);\
    /* basic iterators' construction methods */\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) (*begin)(struct SET_INTERFACE_TYPE(TYPE)* const this);\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), iterator_type) (*end)(struct SET_INTERFACE_TYPE(TYPE)* const this);\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) (*cbegin)(struct SET_INTERFACE_TYPE(TYPE) const* const this);\
    STRUCT_SUBTYPE(SET_INTERFACE_TYPE(TYPE), const_iterator_type) (*cend)(struct SET_INTERFACE_TYPE(TYPE) const* const this);\
} INTERFACE_VTABLE_TYPE(SET_INTERFACE_TYPE(TYPE));\
/* set type */\
typedef struct SET_INTERFACE_TYPE(TYPE) {\
    DEFINE_INTERFACE_VTABLE_ADAPTER(SET_INTERFACE_TYPE(TYPE));\
} SET_INTERFACE_TYPE(TYPE)
