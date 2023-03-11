#pragma once

#include "map_inheritance_methods_decl.h"
#include "map_types_decl.h"
#include <utils/macros.h>

#define DEFINE_MAP_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, KEY, VALUE)\
    DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, MAP_INTERFACE_TYPE(KEY, VALUE)) = {\
        .destroy_at = &TYPE_METHOD(MAP_INTERFACE_TYPE(KEY, VALUE), VTABLE_MEMBER(destroy_at)),\
        .clear = NULL,\
        .size = NULL,\
        /* insert element */\
        .insert_copy = NULL,\
        .insert_move = NULL,\
        /* insert or assign key-value */\
        .insert_or_assign_with_key_copy_value_copy = NULL,\
        .insert_or_assign_with_key_move_value_copy = NULL,\
        .insert_or_assign_with_key_copy_value_move = NULL,\
        .insert_or_assign_with_key_move_value_move = NULL,\
        /* direct value access by key */\
        .at = NULL,\
        .mut_at = NULL,\
        /* find element */\
        .find = NULL,\
        .mut_find = NULL,\
        /* erase element */\
        .erase_by_iterator = NULL,\
        .erase_by_const_iterator = NULL,\
        /* basic iterators' construction methods */\
        .begin = NULL,\
        .end = NULL,\
        .cbegin = NULL,\
        .cend = NULL\
    }

#define DEFINE_MAP_INTERFACE_ITERATOR_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, KEY, VALUE)\
    DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)) = {\
        .destroy_at = &TYPE_METHOD(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE), VTABLE_MEMBER(destroy_at)),\
        /* --- Element access functions --- */\
        .key = NULL,\
        .value = NULL,\
        .const_value = NULL,\
        /* --- Compare functions --- */\
        /* return 0 if equals, !0 either */\
        .compare = NULL,\
        /* --- Increment functions --- */\
        /* point this to next value & return this-value */\
        .next = NULL,\
        /* return this-value & point this to next value */\
        .pnext = NULL,\
        /* --- Decrement functions --- */\
        /* point this to previous value & return this-value */\
        .prev = NULL,\
        /* return this-value & point this to previous value */\
        .pprev = NULL\
    }


#define DEFINE_SET_CONST_INTERFACE_ITERATOR_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, KEY, VALUE)\
    DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)) = {\
        .destroy_at = &TYPE_VT_METHOD(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE), destroy_at),\
        /* --- Element access functions --- */\
        .key = NULL,\
        .value = NULL,\
        .const_value = NULL,\
        /* --- Compare functions --- */\
        /* return 0 if equals, !0 either */\
        .compare = NULL,\
        /* --- Increment functions --- */\
        /* point this to next value & return this-value */\
        .next = NULL,\
        /* return this-value & point this to next value */\
        .pnext = NULL,\
        /* --- Decrement functions --- */\
        /* point this to previous value & return this-value */\
        .prev = NULL,\
        /* return this-value & point this to previous value */\
        .pprev = NULL\
    }

#define DEFINE_MAP_INTERFACE_VTABLES_VARIABLES_WITH_MODIFIER(MODIFIER, KEY, VALUE)\
    DEFINE_MAP_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, KEY, VALUE);\
    DEFINE_MAP_INTERFACE_ITERATOR_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, KEY, VALUE);\
    DEFINE_SET_CONST_INTERFACE_ITERATOR_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, KEY, VALUE)
