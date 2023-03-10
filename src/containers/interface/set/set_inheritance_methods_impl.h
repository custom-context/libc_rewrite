#pragma once

#include "set_inheritance_methods_decl.h"

// set non-dynamic 'dynamic' inner methods implementation
#define DEFINE_SET_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* SET_INTERFACE_METHOD(TYPE, VTABLE_MEMBER(destroy_at))(\
    struct SET_INTERFACE_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    return this;\
}\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* SET_INTERFACE_ITERATOR_METHOD(TYPE, VTABLE_MEMBER(destroy_at))(\
    struct SET_INTERFACE_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    return this;\
}\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* SET_INTERFACE_CONST_ITERATOR_METHOD(TYPE, VTABLE_MEMBER(destroy_at))(\
    struct SET_INTERFACE_CONST_ITERATOR_TYPE(TYPE)* const this) {\
    ASSERT(this);\
    return this;\
}\

#define DEFINE_SET_INTERFACE_INHERITANCE_METHODS(TYPE) DEFINE_SET_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(, TYPE)
#define DEFINE_SET_INTERFACE_STATIC_INHERITANCE_METHODS(TYPE) DEFINE_SET_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(static, TYPE)
#define DEFINE_SET_INTERFACE_INLINE_INHERITANCE_METHODS(TYPE) DEFINE_SET_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(inline, TYPE)
