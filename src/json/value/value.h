#pragma once

#include <json/common.h>
#include <containers/dynamic/string/string.h>
#include <containers/dynamic/array/array.h>
#include <containers/dynamic/tree/rb_tree/map/map.h>
#include <memory/allocator/allocator.h>
#include <containers/pair/pair.h>
#include <utils/string/helpers.h>

#define JSON_VALUE_TYPE() NAMESPACE_JSON(value)

typedef struct JSON_VALUE_TYPE() JSON_VALUE_TYPE();

// dynamic array related declarations & definitions
DEFINE_DEFAULT_ALLOCATOR_TYPE(JSON_VALUE_TYPE());
DECLARE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(extern, JSON_VALUE_TYPE());
DECLARE_DYNAMIC_ARRAY_TYPE(JSON_VALUE_TYPE());
DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS_WITH_MODIFIER(extern, JSON_VALUE_TYPE(), DEFAULT_ALLOCATOR_TYPE(JSON_VALUE_TYPE()));

// map related declarations & definitions
typedef struct RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()) RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE());
typedef struct PAIR_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()) PAIR_TYPE(STRING_TYPE(), JSON_VALUE_TYPE());
/// allocator<node<string, json::value>>
DEFINE_DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()));
DECLARE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(extern, RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()));

/// comparator(string, string)
typedef struct COMPARATOR_TYPE(json_object_string_comparator, STRING_TYPE()) {
    char bit:1;
} COMPARATOR_TYPE(json_object_string_comparator, STRING_TYPE());
DECLARE_COMPARATOR_METHODS_WITH_MODIFIER(extern, json_object_string_comparator, STRING_TYPE());

/// map<string, json_value>
DECLARE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(
    STRING_TYPE(), JSON_VALUE_TYPE(),
    COMPARATOR_TYPE(json_object_string_comparator, STRING_TYPE()),
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()))
);
DECLARE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(extern,
    STRING_TYPE(), JSON_VALUE_TYPE(),
    COMPARATOR_TYPE(json_object_string_comparator, STRING_TYPE()),
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()))
);

// json::value type & json::value:* types
#define JSON__boolean_type bool
#define JSON__number_type double
#define JSON__string_type STRING_TYPE()
#define JSON__array_type DYNAMIC_ARRAY_TYPE(JSON_VALUE_TYPE())
#define JSON__object_type RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(\
    STRING_TYPE(), JSON_VALUE_TYPE(),\
    COMPARATOR_TYPE(json_object_string_comparator, STRING_TYPE()),\
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()))\
)
#define JSON__object__iterator_type RED_BLACK_TREE_MAP_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(\
    STRING_TYPE(), JSON_VALUE_TYPE(),\
    COMPARATOR_TYPE(json_object_string_comparator, STRING_TYPE()),\
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()))\
)
#define JSON__object__const_iterator_type RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(\
    STRING_TYPE(), JSON_VALUE_TYPE(),\
    COMPARATOR_TYPE(json_object_string_comparator, STRING_TYPE()),\
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()))\
)

#define JSON__key_type STRING_TYPE()

DECLARE_STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type, JSON__boolean_type);
DECLARE_STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type, JSON__number_type);
DECLARE_STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type, JSON__string_type);
DECLARE_STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type, JSON__array_type);
DECLARE_STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type, JSON__object_type);
DECLARE_STRUCT_SUBTYPE(JSON_VALUE_TYPE(), size_type, usize);
DECLARE_STRUCT_SUBTYPE(JSON_VALUE_TYPE(), key_type, JSON__key_type);
typedef struct JSON_VALUE_TYPE() {
    union {
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type) boolean;
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) number;
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) string;
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) array;
        STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) object;
    };
    enum JSON_ENUM_TYPE() type;
} JSON_VALUE_TYPE();

// map related declarations & definitions
/// pair<string, json::value>
DEFINE_PAIR_TYPE(STRING_TYPE(), JSON_VALUE_TYPE());
DECLARE_PAIR_METHODS_WITH_MODIFIER(extern, STRING_TYPE(), JSON_VALUE_TYPE());

/// node<string, json::value>
DECLARE_RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE());

// json::value methods declaration
#define JSON_VALUE_METHOD(METHOD) TYPE_METHOD(JSON_VALUE_TYPE(), METHOD)

// default construction/destruction/assign methods group
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_at)(struct JSON_VALUE_TYPE()* const this);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_copy_at)(struct JSON_VALUE_TYPE()* const this, struct JSON_VALUE_TYPE() const* const source);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_move_at)(struct JSON_VALUE_TYPE()* const this, struct JSON_VALUE_TYPE()* const source);
void* JSON_VALUE_METHOD(destroy_at)(struct JSON_VALUE_TYPE()* const this);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_copy_at)(struct JSON_VALUE_TYPE()* const this, struct JSON_VALUE_TYPE() const* const source);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_move_at)(struct JSON_VALUE_TYPE()* const this, struct JSON_VALUE_TYPE()* const source);
void JSON_VALUE_METHOD(swap)(struct JSON_VALUE_TYPE()* const this, struct JSON_VALUE_TYPE()* const source);
// non-default methods
/// construct_from_value
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_from_type_at)(struct JSON_VALUE_TYPE()* const this, enum JSON_ENUM_TYPE() type);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_from_boolean_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type) value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_from_number_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_copy_from_string_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* const value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_move_from_string_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type)* const value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_copy_from_array_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* const value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_move_from_array_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type)* const value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_copy_from_object_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const* const value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_move_from_object_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type)* const value);
/// JSON_VALUE_METHOD(construct_from_value_at)
#define json__value__construct_from_value_at(THIS, VALUE) _Generic((VALUE),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type)      : JSON_VALUE_METHOD(construct_from_boolean_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type)       : JSON_VALUE_METHOD(construct_from_number_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const*: JSON_VALUE_METHOD(construct_copy_from_string_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type)*      : JSON_VALUE_METHOD(construct_move_from_string_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* : JSON_VALUE_METHOD(construct_copy_from_array_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type)*       : JSON_VALUE_METHOD(construct_move_from_array_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const*: JSON_VALUE_METHOD(construct_copy_from_object_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type)*      : JSON_VALUE_METHOD(construct_move_from_object_at)\
)(THIS, VALUE)
/// assign_from_value
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_from_type_at)(struct JSON_VALUE_TYPE()* const this, enum JSON_ENUM_TYPE() type);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_from_boolean_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type) value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_from_number_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_copy_from_string_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* const value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_move_from_string_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type)* const value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_copy_from_array_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* const value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_move_from_array_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type)* const value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_copy_from_object_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const* const value);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_move_from_object_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type)* const value);
/// JSON_VALUE_METHOD(assign_from_value)
#define json__value__assign_from_value(THIS, VALUE) _Generic((VALUE),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type)      : JSON_VALUE_METHOD(assign_from_boolean_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type)       : JSON_VALUE_METHOD(assign_from_number_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const*: JSON_VALUE_METHOD(assign_copy_from_string_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type)*      : JSON_VALUE_METHOD(assign_move_from_string_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* : JSON_VALUE_METHOD(assign_copy_from_array_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type)*       : JSON_VALUE_METHOD(assign_move_from_array_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const*: JSON_VALUE_METHOD(assign_copy_from_object_at),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type)*      : JSON_VALUE_METHOD(assign_move_from_object_at)\
)(THIS, VALUE)
/// type() -> enum type value
enum JSON_ENUM_TYPE() JSON_VALUE_METHOD(type)(struct JSON_VALUE_TYPE() const* const this);
/// as<Type>
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type) const* JSON_VALUE_METHOD(as_boolean)(struct JSON_VALUE_TYPE() const* const this);
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type)* JSON_VALUE_METHOD(as_mut_boolean)(struct JSON_VALUE_TYPE()* const this);
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) const* JSON_VALUE_METHOD(as_number)(struct JSON_VALUE_TYPE() const* const this);
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type)* JSON_VALUE_METHOD(as_mut_number)(struct JSON_VALUE_TYPE()* const this);
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* JSON_VALUE_METHOD(as_string)(struct JSON_VALUE_TYPE() const* const this);
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type)* JSON_VALUE_METHOD(as_mut_string)(struct JSON_VALUE_TYPE()* const this);
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* JSON_VALUE_METHOD(as_array)(struct JSON_VALUE_TYPE() const* const this);
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type)* JSON_VALUE_METHOD(as_mut_array)(struct JSON_VALUE_TYPE()* const this);
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const* JSON_VALUE_METHOD(as_object)(struct JSON_VALUE_TYPE() const* const this);
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type)* JSON_VALUE_METHOD(as_mut_object)(struct JSON_VALUE_TYPE()* const this);
/// JSON_VALUE_METHOD(as)
#define json__value__as(TYPE) _Generic(((TYPE*)(NULL)),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type) const* : JSON_VALUE_METHOD(as_boolean),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type)*       : JSON_VALUE_METHOD(as_mut_boolean),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) const*  : JSON_VALUE_METHOD(as_number),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type)*        : JSON_VALUE_METHOD(as_mut_number),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const*  : JSON_VALUE_METHOD(as_string),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type)*        : JSON_VALUE_METHOD(as_mut_string),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const*   : JSON_VALUE_METHOD(as_array),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type)*         : JSON_VALUE_METHOD(as_mut_array),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const*  : JSON_VALUE_METHOD(as_object),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type)*        : JSON_VALUE_METHOD(as_mut_object)\
)

/// get_by_index, get_by_key
struct JSON_VALUE_TYPE() const* JSON_VALUE_METHOD(at_by_index)(struct JSON_VALUE_TYPE() const* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), size_type) index);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(mut_at_by_index)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), size_type) index);
struct JSON_VALUE_TYPE() const* JSON_VALUE_METHOD(at_by_key)(struct JSON_VALUE_TYPE() const* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), key_type) const* const key);
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(mut_at_by_key)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), key_type) const* const key);
/// JSON_VALUE_METHOD(assign_from_value)
#define json__value__at(THIS, VALUE) _Generic((VALUE),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), size_type): _Generic((THIS),\
        struct JSON_VALUE_TYPE() const*: JSON_VALUE_METHOD(at_by_index),\
        struct JSON_VALUE_TYPE()*      : JSON_VALUE_METHOD(mut_at_by_index)\
    ),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), key_type) const*: _Generic((THIS),\
        struct JSON_VALUE_TYPE() const*: JSON_VALUE_METHOD(at_by_key),\
        struct JSON_VALUE_TYPE()*      : JSON_VALUE_METHOD(mut_at_by_key)\
    ),\
    STRUCT_SUBTYPE(JSON_VALUE_TYPE(), key_type)*: _Generic((THIS),\
        struct JSON_VALUE_TYPE() const*: JSON_VALUE_METHOD(at_by_key),\
        struct JSON_VALUE_TYPE()*      : JSON_VALUE_METHOD(mut_at_by_key)\
    )\
)(THIS, VALUE)

/// helper functions
struct STRING_TYPE() NAMESPACE_UTILS_STRING(CONVERT(JSON_VALUE_TYPE(), STRING_TYPE()))(struct JSON_VALUE_TYPE() const* const json);
