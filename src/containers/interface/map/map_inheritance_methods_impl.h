#pragma once

#include "map_inheritance_methods_decl.h"

// map non-dynamic 'dynamic' inner methods implementation
#define DEFINE_MAP_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(COMMON_MODIFIER, KEY, VALUE)\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* MAP_INTERFACE_METHOD(KEY, VALUE, VTABLE_MEMBER(destroy_at))(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    return this;\
}\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, VTABLE_MEMBER(destroy_at))(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    return this;\
}\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, VTABLE_MEMBER(destroy_at))(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this) {\
    ASSERT(this);\
    return this;\
}\

#define DEFINE_MAP_INTERFACE_INHERITANCE_METHODS(KEY, VALUE) DEFINE_MAP_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(, KEY, VALUE)
#define DEFINE_MAP_INTERFACE_STATIC_INHERITANCE_METHODS(KEY, VALUE) DEFINE_MAP_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(static, KEY, VALUE)
#define DEFINE_MAP_INTERFACE_INLINE_INHERITANCE_METHODS(KEY, VALUE) DEFINE_MAP_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(inline, KEY, VALUE)
