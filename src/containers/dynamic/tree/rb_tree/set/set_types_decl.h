#pragma once

#include <containers/dynamic/tree/common.h>
#include <utils/comparator/comparator.h>
#include <containers/iterator/iterator.h>

// red-black tree set type
#define RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)\
    NAMESPACE_CONTAINERS_DYNAMIC(CONCAT7(red_black_tree, __, TYPE, _with_comparator_, COMPARATOR, _and_allocator_, ALLOCATOR))

#define RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR(TYPE, COMPARATOR)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, DEFAULT_ALLOCATOR_TYPE(TYPE))

#define RED_BLACK_TREE_SET_TYPE(TYPE)\
    RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR(TYPE, LESS_COMPARATOR_TYPE(TYPE))

// red-black tree set type node
#define RED_BLACK_TREE_SET_NODE_TYPE(TYPE)\
    NAMESPACE_CONTAINERS_DYNAMIC(CONCAT5(red_black_tree, __, TYPE, __, node))

// red-black tree set type node color enumeration
#define RED_BLACK_TREE_SET_NODE_COLOR_ENUM(TYPE)\
    TYPE_MEMBER(RED_BLACK_TREE_SET_NODE_TYPE(TYPE), ENUM_TYPE(COLOR))

#define RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, VALUE)\
    ENUM_VALUE(RED_BLACK_TREE_SET_NODE_COLOR_ENUM(TYPE), VALUE)

// red-black tree set type iterator
#define RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)\
    ITERATOR_TYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR))

// red-black tree set type const iterator
#define RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)\
    CONST_ITERATOR_TYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR))

#define DECLARE_RED_BLACK_TREE_SET_NODE_TYPE(TYPE)\
/* red-black tree set type node 'color'*/\
typedef enum RED_BLACK_TREE_SET_NODE_COLOR_ENUM(TYPE) {\
    RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, RED),\
    RED_BLACK_TREE_SET_NODE_COLOR_ENUM_VALUE(TYPE, BLACK),\
} RED_BLACK_TREE_SET_NODE_COLOR_ENUM(TYPE);\
/* red-black tree set type node*/\
typedef struct RED_BLACK_TREE_SET_NODE_TYPE(TYPE) {\
    struct RED_BLACK_TREE_SET_NODE_TYPE(TYPE)* parent;\
    struct RED_BLACK_TREE_SET_NODE_TYPE(TYPE)* child[2];\
    enum RED_BLACK_TREE_SET_NODE_COLOR_ENUM(TYPE) color;\
    TYPE value;\
} RED_BLACK_TREE_SET_NODE_TYPE(TYPE)

#define DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)\
/* red-black tree set type iterator */\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type, TYPE);\
typedef struct RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) {\
    struct RED_BLACK_TREE_SET_NODE_TYPE(TYPE)* element_storage;\
} RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR);\
/* red-black tree set type const iterator */\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type, TYPE const);\
typedef struct RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) {\
    struct RED_BLACK_TREE_SET_NODE_TYPE(TYPE) const* element_storage;\
} RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR);\
/* red-black tree set type */\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), size_type,\
    usize);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), value_type,\
    TYPE);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type,\
    RED_BLACK_TREE_SET_NODE_TYPE(TYPE));\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), allocator_type,\
    ALLOCATOR);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), comparator_type,\
    COMPARATOR);\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), iterator_type,\
    RED_BLACK_TREE_SET_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR));\
DECLARE_STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), const_iterator_type,\
    RED_BLACK_TREE_SET_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR));\
typedef struct RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR) {\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), node_type)* root;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), size_type) size;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), allocator_type) allocator;\
    STRUCT_SUBTYPE(RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR), comparator_type) comparator;\
} RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, ALLOCATOR)

#define DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR(TYPE, COMPARATOR)\
    DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(TYPE, COMPARATOR, DEFAULT_ALLOCATOR_TYPE(TYPE))

#define DECLARE_RED_BLACK_TREE_SET_TYPE(TYPE)\
    DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR(TYPE, LESS_COMPARATOR_TYPE(TYPE))

// Declaration order:
// DECLARE_RED_BLACK_TREE_SET_NODE_TYPE(Type)
// DECLARE_ALLOCATOR_TYPE(Allocator, RED_BLACK_TREE_SET_NODE_TYPE(Type));
// DECLARE_RED_BLACK_TREE_SET_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(Type, Comparator, Allocator);