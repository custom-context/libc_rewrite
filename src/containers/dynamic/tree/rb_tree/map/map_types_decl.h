#pragma once

#include <containers/interface/map/map.h>
#include <containers/dynamic/tree/common.h>
#include <utils/comparator/comparator.h>

// red-black tree map type
#define RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)\
    NAMESPACE_CONTAINERS_DYNAMIC(CONCAT9(red_black_tree, __, KEY, _to_, VALUE, _with_comparator_, COMPARATOR, _and_allocator_, ALLOCATOR))

#define RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR(KEY, VALUE, COMPARATOR)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, DEFAULT_ALLOCATOR_TYPE(KEY, VALUE))

#define RED_BLACK_TREE_MAP_TYPE(KEY, VALUE)\
    RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR(KEY, VALUE, LESS_COMPARATOR_TYPE(KEY, VALUE))

// red-black tree map type node
#define RED_BLACK_TREE_MAP_NODE_TYPE(KEY, VALUE)\
    NAMESPACE_CONTAINERS_DYNAMIC(CONCAT7(red_black_tree, __, KEY, _to_, VALUE, __, node))

// red-black tree map type node color enumeration
#define RED_BLACK_TREE_MAP_NODE_COLOR_ENUM(KEY, VALUE)\
    TYPE_MEMBER(RED_BLACK_TREE_MAP_NODE_TYPE(KEY, VALUE), ENUM_TYPE(COLOR))

#define RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, ENUM_VAL)\
    ENUM_VALUE(RED_BLACK_TREE_MAP_NODE_COLOR_ENUM(KEY, VALUE), ENUM_VAL)

// red-black tree map type iterator
#define RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)\
    ITERATOR_TYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR))

// red-black tree map type const iterator
#define RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)\
    CONST_ITERATOR_TYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR))

#define DECLARE_RED_BLACK_TREE_MAP_NODE_TYPE(KEY, VALUE)\
/* red-black tree map type node 'color'*/\
typedef enum RED_BLACK_TREE_MAP_NODE_COLOR_ENUM(KEY, VALUE) {\
    RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, RED),\
    RED_BLACK_TREE_MAP_NODE_COLOR_ENUM_VALUE(KEY, VALUE, BLACK),\
} RED_BLACK_TREE_MAP_NODE_COLOR_ENUM(KEY, VALUE);\
/* red-black tree map type node*/\
typedef struct RED_BLACK_TREE_MAP_NODE_TYPE(KEY, VALUE) {\
    struct RED_BLACK_TREE_MAP_NODE_TYPE(KEY, VALUE)* parent;\
    struct RED_BLACK_TREE_MAP_NODE_TYPE(KEY, VALUE)* child[2];\
    enum RED_BLACK_TREE_MAP_NODE_COLOR_ENUM(KEY, VALUE) color;\
    struct PAIR_TYPE(KEY, VALUE) value;\
} RED_BLACK_TREE_MAP_NODE_TYPE(KEY, VALUE)

#define DECLARE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)\
/* red-black tree set type iterator */\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type, KEY const);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type, VALUE);\
typedef struct RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) {\
    DEFINE_STRUCT_ADAPTER(MAP_INTERFACE_ITERATOR_TYPE(KEY, VALUE));\
} RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR);\
/* red-black tree set type const iterator */\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type, KEY const);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type, VALUE const);\
typedef struct RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) {\
    DEFINE_STRUCT_ADAPTER(MAP_INTERFACE_CONST_ITERATOR_TYPE(KEY, VALUE));\
} RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR);\
/* red-black tree set type */\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), size_type,\
    size_t);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), key_type, KEY);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), mapped_type, VALUE);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), value_type, PAIR_TYPE(\
    KEY,\
    VALUE\
));\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type,\
    RED_BLACK_TREE_MAP_NODE_TYPE(KEY, VALUE));\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), allocator_type,\
    ALLOCATOR);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), comparator_type,\
    COMPARATOR);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), iterator_type,\
    RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR));\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), const_iterator_type,\
    RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR));\
DEFINE_PAIR_TYPE(RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), char);\
typedef struct RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR) {\
    DEFINE_STRUCT_ADAPTER(MAP_INTERFACE_TYPE(KEY, VALUE));\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), node_type)* root;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), size_type) size;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), allocator_type) allocator;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR), comparator_type) comparator;\
} RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, ALLOCATOR)

#define DECLARE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR(KEY, VALUE, COMPARATOR)\
    DECLARE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(KEY, VALUE, COMPARATOR, DEFAULT_ALLOCATOR_TYPE(KEY, VALUE))

#define DECLARE_RED_BLACK_TREE_MAP_TYPE(KEY, VALUE)\
    DECLARE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR(KEY, VALUE, LESS_COMPARATOR_TYPE(KEY, VALUE))

// Declaration order:
// DECLARE_RED_BLACK_TREE_MAP_NODE_TYPE(Type)
// DECLARE_ALLOCATOR_TYPE(Allocator, RED_BLACK_TREE_MAP_NODE_TYPE(Type));
// DECLARE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(Type, Comparator, Allocator);