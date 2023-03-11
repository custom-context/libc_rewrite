#pragma once

#include "map_methods_decl.h"

// map non-dynamic 'dynamic' inner methods
#define DECLARE_MAP_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(COMMON_MODIFIER, KEY, VALUE)\
/* --- Set interface methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* MAP_INTERFACE_METHOD(KEY, VALUE, VTABLE_MEMBER(destroy_at))(\
    struct MAP_INTERFACE_TYPE(KEY, VALUE)* const this);\
/* --- Mutable iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* MAP_INTERFACE_ITERATOR_METHOD(KEY, VALUE, VTABLE_MEMBER(destroy_at))(\
    struct MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE)* const this);\
/* --- Const iterator's methods --- */\
/* --- Construction/Destruction functions --- */\
COMMON_MODIFIER void* MAP_INTERFACE_CONST_ITERATOR_METHOD(KEY, VALUE, VTABLE_MEMBER(destroy_at))(\
    struct MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE)* const this);\

#define DECLARE_MAP_INTERFACE_INHERITANCE_METHODS(KEY, VALUE) DECLARE_MAP_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(, KEY, VALUE)
#define DECLARE_MAP_INTERFACE_STATIC_INHERITANCE_METHODS(KEY, VALUE) DECLARE_MAP_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(static, KEY, VALUE)
#define DECLARE_MAP_INTERFACE_INLINE_INHERITANCE_METHODS(KEY, VALUE) DECLARE_MAP_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(inline, KEY, VALUE)
#define DECLARE_MAP_INTERFACE_EXTERNAL_INHERITANCE_METHODS(KEY, VALUE) DECLARE_MAP_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(extern, KEY, VALUE)
#define DECLARE_MAP_INTERFACE_EXTERNAL_INLINE_INHERITANCE_METHODS(KEY, VALUE) DECLARE_MAP_INTERFACE_INHERITANCE_METHODS_WITH_MODIFIER(extern inline, KEY, VALUE)
