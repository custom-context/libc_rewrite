#pragma once

#include "set_inheritance_methods_decl.h"
#include "set_types_decl.h"
#include <utils/macros.h>

#define DEFINE_SET_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, TYPE)\
    DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, SET_INTERFACE_TYPE(TYPE)) = {\
        .destroy_at = &SET_INTERFACE_METHOD(TYPE, destroy_at),\
        .clear = NULL,\
        .size = NULL,\
        /* insert element */\
        .insert_copy = NULL,\
        .insert_move = NULL,\
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

#define DEFINE_SET_INTERFACE_ITERATOR_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, TYPE)\
    DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, SET_INTERFACE_ITERATOR_TYPE(TYPE)) = {\
        .destroy_at = &SET_INTERFACE_ITERATOR_METHOD(TYPE, destroy_at),\
        /* --- Element access functions --- */\
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


#define DEFINE_SET_CONST_INTERFACE_ITERATOR_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, TYPE)\
    DECLARE_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)) = {\
        .destroy_at = &SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, destroy_at),\
        /* --- Element access functions --- */\
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

#define DEFINE_SET_INTERFACE_VTABLES_VARIABLES_WITH_MODIFIER(MODIFIER, TYPE)\
    DEFINE_SET_INTERFACE_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, TYPE);\
    DEFINE_SET_INTERFACE_ITERATOR_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, TYPE);\
    DEFINE_SET_CONST_INTERFACE_ITERATOR_VTABLE_VARIABLE_WITH_MODIFIER(MODIFIER, TYPE)
