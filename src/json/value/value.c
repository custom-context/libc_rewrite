#include "value.h"

// dynamic array related declarations & definitions
DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(, JSON_VALUE_TYPE())
IMPLEMENT_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS_WITH_MODIFIER(, JSON_VALUE_TYPE(), DEFAULT_ALLOCATOR_TYPE(JSON_VALUE_TYPE()))

// map related declarations & definitions
/// allocator<node<string, json::value>>
DEFINE_DEFAULT_ALLOCATOR_METHODS_WITH_MODIFIER(, RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()))

/// comparator(string, string)
DEFINE_DEFAULT_COMPARATOR_METHODS_WITH_MODIFIER(, json_object_string_comparator, STRING_TYPE()) {
    return STRING_FUNCTION(STRING_TYPE(), compare)(value1, value2) > 0;
}

/// map<string, json_value>
DEFINE_RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR_AND_MODIFIER_METHODS(,
    STRING_TYPE(), JSON_VALUE_TYPE(),
    COMPARATOR_TYPE(json_object_string_comparator, STRING_TYPE()),
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()))
)

/// pair<string, json::value>
DEFINE_PAIR_METHODS_WITH_MODIFIER(, STRING_TYPE(), JSON_VALUE_TYPE())

// json::value local macro helpers
#define JSON_STRING_TYPE STRING_TYPE()
#define JSON_ARRAY_TYPE DYNAMIC_ARRAY_TYPE(JSON_VALUE_TYPE())
#define JSON_OBJECT_TYPE RED_BLACK_TREE_MAP_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(\
    STRING_TYPE(), JSON_VALUE_TYPE(),\
    COMPARATOR_TYPE(json_object_string_comparator, STRING_TYPE()),\
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()))\
)
#define JSON_OBJECT_CONST_ITERATOR_TYPE RED_BLACK_TREE_MAP_CONST_ITERATOR_TYPE_WITH_COMPARATOR_AND_ALLOCATOR(\
    STRING_TYPE(), JSON_VALUE_TYPE(),\
    COMPARATOR_TYPE(json_object_string_comparator, STRING_TYPE()),\
    DEFAULT_ALLOCATOR_TYPE(RED_BLACK_TREE_MAP_NODE_TYPE(STRING_TYPE(), JSON_VALUE_TYPE()))\
)
// json::value methods declaration
// default construction/destruction/assign methods group
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_at)(struct JSON_VALUE_TYPE()* const this) {
    ASSERT(this);
    this->type = JSON_ENUM_VALUE(null);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_copy_at)(struct JSON_VALUE_TYPE()* const this, struct JSON_VALUE_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    switch (source->type) {
        case JSON_ENUM_VALUE(null): break;
        case JSON_ENUM_VALUE(boolean): {
            this->boolean = source->boolean;
        } break;
        case JSON_ENUM_VALUE(number): {
            this->number = source->number;
        } break;
        case JSON_ENUM_VALUE(string): {
            TYPE_METHOD(JSON_STRING_TYPE, construct_copy_at)(&this->string, &source->string);
        } break;
        case JSON_ENUM_VALUE(array): {
            TYPE_METHOD(JSON_ARRAY_TYPE, construct_copy_at)(&this->array, &source->array);
        } break;
        case JSON_ENUM_VALUE(object): {
            TYPE_METHOD(JSON_OBJECT_TYPE, construct_copy_at)(&this->object, &source->object);
        } break;
    }
    this->type = source->type;
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_move_at)(struct JSON_VALUE_TYPE()* const this, struct JSON_VALUE_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    switch (source->type) {
        case JSON_ENUM_VALUE(null): break;
        case JSON_ENUM_VALUE(boolean): {
            this->boolean = source->boolean;
        } break;
        case JSON_ENUM_VALUE(number): {
            this->number = source->number;
        } break;
        case JSON_ENUM_VALUE(string): {
            TYPE_METHOD(JSON_STRING_TYPE, construct_move_at)(&this->string, &source->string);
        } break;
        case JSON_ENUM_VALUE(array): {
            TYPE_METHOD(JSON_ARRAY_TYPE, construct_move_at)(&this->array, &source->array);
        } break;
        case JSON_ENUM_VALUE(object): {
            TYPE_METHOD(JSON_OBJECT_TYPE, construct_move_at)(&this->object, &source->object);
        } break;
    }
    this->type = source->type;
    return this;
}
void* JSON_VALUE_METHOD(destroy_at)(struct JSON_VALUE_TYPE()* const this) {
    ASSERT(this);
    switch (this->type) {
        case JSON_ENUM_VALUE(null):
        case JSON_ENUM_VALUE(boolean):
        case JSON_ENUM_VALUE(number): break;
        case JSON_ENUM_VALUE(string): {
            TYPE_METHOD(JSON_STRING_TYPE, destroy_at)(&this->string);
        } break;
        case JSON_ENUM_VALUE(array): {
            TYPE_METHOD(JSON_ARRAY_TYPE, destroy_at)(&this->array);
        } break;
        case JSON_ENUM_VALUE(object): {
            TYPE_METHOD(JSON_OBJECT_TYPE, destroy_at)(&this->object);
        } break;
    }
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_copy_at)(struct JSON_VALUE_TYPE()* const this, struct JSON_VALUE_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    switch (source->type) {
        case JSON_ENUM_VALUE(null): break;
        case JSON_ENUM_VALUE(boolean): {
            this->boolean = source->boolean;
        } break;
        case JSON_ENUM_VALUE(number): {
            this->number = source->number;
        } break;
        case JSON_ENUM_VALUE(string): {
            TYPE_METHOD(JSON_STRING_TYPE, assign_copy_at)(&this->string, &source->string);
        } break;
        case JSON_ENUM_VALUE(array): {
            TYPE_METHOD(JSON_ARRAY_TYPE, assign_copy_at)(&this->array, &source->array);
        } break;
        case JSON_ENUM_VALUE(object): {
            TYPE_METHOD(JSON_OBJECT_TYPE, assign_copy_at)(&this->object, &source->object);
        } break;
    }
    this->type = source->type;
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_move_at)(struct JSON_VALUE_TYPE()* const this, struct JSON_VALUE_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    switch (source->type) {
        case JSON_ENUM_VALUE(null): break;
        case JSON_ENUM_VALUE(boolean): {
            this->boolean = source->boolean;
        } break;
        case JSON_ENUM_VALUE(number): {
            this->number = source->number;
        } break;
        case JSON_ENUM_VALUE(string): {
            TYPE_METHOD(JSON_STRING_TYPE, assign_move_at)(&this->string, &source->string);
        } break;
        case JSON_ENUM_VALUE(array): {
            TYPE_METHOD(JSON_ARRAY_TYPE, assign_move_at)(&this->array, &source->array);
        } break;
        case JSON_ENUM_VALUE(object): {
            TYPE_METHOD(JSON_OBJECT_TYPE, assign_move_at)(&this->object, &source->object);
        } break;
    }
    this->type = source->type; source->type = JSON_ENUM_VALUE(null);
    return this;
}
void JSON_VALUE_METHOD(swap)(struct JSON_VALUE_TYPE()* const this, struct JSON_VALUE_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    switch (source->type) {
        case JSON_ENUM_VALUE(null): break;
        case JSON_ENUM_VALUE(boolean): {
            bool temporary = this->boolean;
            this->boolean = source->boolean;
            source->boolean = temporary;
        } break;
        case JSON_ENUM_VALUE(number): {
            double temporary = this->number;
            this->number = source->number;
            source->number = temporary;
        } break;
        case JSON_ENUM_VALUE(string): {
            TYPE_METHOD(JSON_STRING_TYPE, swap)(&this->string, &source->string);
        } break;
        case JSON_ENUM_VALUE(array): {
            TYPE_METHOD(JSON_ARRAY_TYPE, swap)(&this->array, &source->array);
        } break;
        case JSON_ENUM_VALUE(object): {
            TYPE_METHOD(JSON_OBJECT_TYPE, swap)(&this->object, &source->object);
        } break;
    }
    {
        enum JSON_ENUM_TYPE() temporary = this->type;
        this->type = source->type;
        source->type = temporary;
    }
}
// non-default methods
/// construct_from_value
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_from_type_at)(struct JSON_VALUE_TYPE()* const this, enum JSON_ENUM_TYPE() type) {
    ASSERT(this);
    switch (type) {
        case JSON_ENUM_VALUE(null):
        case JSON_ENUM_VALUE(boolean): {
            this->boolean = false;
        } break;
        case JSON_ENUM_VALUE(number): {
            this->number = 0;
        } break;
        case JSON_ENUM_VALUE(string): {
            TYPE_METHOD(JSON_STRING_TYPE, construct_at)(&this->string);
        } break;
        case JSON_ENUM_VALUE(array): {
            TYPE_METHOD(JSON_ARRAY_TYPE, construct_at)(&this->array);
        } break;
        case JSON_ENUM_VALUE(object): {
            TYPE_METHOD(JSON_OBJECT_TYPE, construct_at)(&this->object);
        } break;
    }
    this->type = type;
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_from_boolean_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type) value) {
    ASSERT(this);
    this->boolean = value;
    this->type = JSON_ENUM_VALUE(boolean);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_from_number_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) value) {
    ASSERT(this);
    this->number = value;
    this->type = JSON_ENUM_VALUE(number);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_copy_from_string_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* const value) {
    ASSERT(this);
    TYPE_METHOD(JSON_STRING_TYPE, construct_copy_at)(&this->string, value);
    this->type = JSON_ENUM_VALUE(string);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_move_from_string_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type)* const value) {
    ASSERT(this);
    TYPE_METHOD(JSON_STRING_TYPE, construct_move_at)(&this->string, value);
    this->type = JSON_ENUM_VALUE(string);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_copy_from_array_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* const value) {
    ASSERT(this);
    TYPE_METHOD(JSON_ARRAY_TYPE, construct_copy_at)(&this->array, value);
    this->type = JSON_ENUM_VALUE(array);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_move_from_array_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type)* const value) {
    ASSERT(this);
    TYPE_METHOD(JSON_ARRAY_TYPE, construct_move_at)(&this->array, value);
    this->type = JSON_ENUM_VALUE(array);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_copy_from_object_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const* const value) {
    ASSERT(this);
    TYPE_METHOD(JSON_OBJECT_TYPE, construct_copy_at)(&this->object, value);
    this->type = JSON_ENUM_VALUE(object);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(construct_move_from_object_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type)* const value) {
    ASSERT(this);
    TYPE_METHOD(JSON_OBJECT_TYPE, construct_move_at)(&this->object, value);
    this->type = JSON_ENUM_VALUE(object);
    return this;
}
/// assign_from_value
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_from_type_at)(struct JSON_VALUE_TYPE()* const this, enum JSON_ENUM_TYPE() type) {
    ASSERT(this);
    struct JSON_VALUE_TYPE() temporary;
    JSON_VALUE_METHOD(construct_from_type_at)(&temporary, type);
    JSON_VALUE_METHOD(swap)(&temporary, this);
    JSON_VALUE_METHOD(destroy_at)(&temporary);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_from_boolean_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type) value) {
    ASSERT(this);
    struct JSON_VALUE_TYPE() temporary;
    JSON_VALUE_METHOD(construct_from_value_at)(&temporary, value);
    JSON_VALUE_METHOD(swap)(&temporary, this);
    JSON_VALUE_METHOD(destroy_at)(&temporary);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_from_number_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) value) {
    ASSERT(this);
    struct JSON_VALUE_TYPE() temporary;
    JSON_VALUE_METHOD(construct_from_value_at)(&temporary, value);
    JSON_VALUE_METHOD(swap)(&temporary, this);
    JSON_VALUE_METHOD(destroy_at)(&temporary);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_copy_from_string_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* const value) {
    ASSERT(this);
    struct JSON_VALUE_TYPE() temporary;
    JSON_VALUE_METHOD(construct_from_value_at)(&temporary, value);
    JSON_VALUE_METHOD(swap)(&temporary, this);
    JSON_VALUE_METHOD(destroy_at)(&temporary);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_move_from_string_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type)* const value) {
    ASSERT(this);
    struct JSON_VALUE_TYPE() temporary;
    JSON_VALUE_METHOD(construct_from_value_at)(&temporary, value);
    JSON_VALUE_METHOD(swap)(&temporary, this);
    JSON_VALUE_METHOD(destroy_at)(&temporary);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_copy_from_array_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* const value) {
    ASSERT(this);
    struct JSON_VALUE_TYPE() temporary;
    JSON_VALUE_METHOD(construct_from_value_at)(&temporary, value);
    JSON_VALUE_METHOD(swap)(&temporary, this);
    JSON_VALUE_METHOD(destroy_at)(&temporary);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_move_from_array_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type)* const value) {
    ASSERT(this);
    struct JSON_VALUE_TYPE() temporary;
    JSON_VALUE_METHOD(construct_from_value_at)(&temporary, value);
    JSON_VALUE_METHOD(swap)(&temporary, this);
    JSON_VALUE_METHOD(destroy_at)(&temporary);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_copy_from_object_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const* const value) {
    ASSERT(this);
    struct JSON_VALUE_TYPE() temporary;
    JSON_VALUE_METHOD(construct_from_value_at)(&temporary, value);
    JSON_VALUE_METHOD(swap)(&temporary, this);
    JSON_VALUE_METHOD(destroy_at)(&temporary);
    return this;
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(assign_move_from_object_at)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type)* const value) {
    ASSERT(this);
    struct JSON_VALUE_TYPE() temporary;
    JSON_VALUE_METHOD(construct_from_value_at)(&temporary, value);
    JSON_VALUE_METHOD(swap)(&temporary, this);
    JSON_VALUE_METHOD(destroy_at)(&temporary);
    return this;
}
/// type() -> enum type value
enum JSON_ENUM_TYPE() JSON_VALUE_METHOD(type)(struct JSON_VALUE_TYPE() const* const this) {
    ASSERT(this);
    return this->type;
}
/// as<Type>
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type) const* JSON_VALUE_METHOD(as_boolean)(struct JSON_VALUE_TYPE() const* const this) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(boolean));
    return &this->boolean;
}
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), boolean_type)* JSON_VALUE_METHOD(as_mut_boolean)(struct JSON_VALUE_TYPE()* const this) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(boolean));
    return &this->boolean;
}
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type) const* JSON_VALUE_METHOD(as_number)(struct JSON_VALUE_TYPE() const* const this) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(number));
    return &this->number;
}
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), number_type)* JSON_VALUE_METHOD(as_mut_number)(struct JSON_VALUE_TYPE()* const this) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(number));
    return &this->number;
}
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type) const* JSON_VALUE_METHOD(as_string)(struct JSON_VALUE_TYPE() const* const this) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(string));
    return &this->string;
}
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), string_type)* JSON_VALUE_METHOD(as_mut_string)(struct JSON_VALUE_TYPE()* const this) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(string));
    return &this->string;
}
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) const* JSON_VALUE_METHOD(as_array)(struct JSON_VALUE_TYPE() const* const this) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(array));
    return &this->array;
}
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type)* JSON_VALUE_METHOD(as_mut_array)(struct JSON_VALUE_TYPE()* const this) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(array));
    return &this->array;
}
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) const* JSON_VALUE_METHOD(as_object)(struct JSON_VALUE_TYPE() const* const this) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(object));
    return &this->object;
}
STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type)* JSON_VALUE_METHOD(as_mut_object)(struct JSON_VALUE_TYPE()* const this) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(object));
    return &this->object;
}
/// get_by_index, get_by_key
struct JSON_VALUE_TYPE() const* JSON_VALUE_METHOD(at_by_index)(struct JSON_VALUE_TYPE() const* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), size_type) index) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(array));
    return TYPE_METHOD(JSON_ARRAY_TYPE, at)(&this->array, index);
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(mut_at_by_index)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), size_type) index) {
    ASSERT(this);
    ASSERT(this->type == JSON_ENUM_VALUE(array));
    return TYPE_METHOD(JSON_ARRAY_TYPE, mut_at)(&this->array, index);
}
struct JSON_VALUE_TYPE() const* JSON_VALUE_METHOD(at_by_key)(struct JSON_VALUE_TYPE() const* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), key_type) const* const key) {
    ASSERT(this);
    ASSERT(key);
    ASSERT(this->type == JSON_ENUM_VALUE(object));
    return TYPE_METHOD(JSON_OBJECT_TYPE, at)(&this->object, key);
}
struct JSON_VALUE_TYPE()* JSON_VALUE_METHOD(mut_at_by_key)(struct JSON_VALUE_TYPE()* const this, STRUCT_SUBTYPE(JSON_VALUE_TYPE(), key_type) const* const key) {
    ASSERT(this);
    ASSERT(key);
    ASSERT(this->type == JSON_ENUM_VALUE(object));
    return TYPE_METHOD(JSON_OBJECT_TYPE, mut_at)(&this->object, key);
}

/// helper functions
struct STRING_TYPE() NAMESPACE_UTILS_STRING(CONVERT(JSON_VALUE_TYPE(), STRING_TYPE()))(struct JSON_VALUE_TYPE() const* const json) {
    ASSERT(json);
    struct STRING_TYPE() result;
    switch (json->type) {
        case JSON_ENUM_VALUE(null): {
            STRING_METHOD(construct_from_c_string_at)(&result, "null");
            return result;
        }
        case JSON_ENUM_VALUE(boolean): {
            STRING_METHOD(construct_from_c_string_at)(&result, json->boolean ? "true" : "false");
            return result;
        }
        case JSON_ENUM_VALUE(number): {
            return NAMESPACE_UTILS_STRING(CONVERT(double, STRING_TYPE()))(&json->number);
        }
        case JSON_ENUM_VALUE(string): {
            STRUCT_SUBTYPE(STRING_TYPE(), char_type) const value = '\"';
            STRING_METHOD(construct_by_value_at)(&result, 1u, &value);
            STRING_METHOD(append_string)(&result, &json->string);
            STRING_METHOD(push_back)(&result, &value);
            return result;
        }
        case JSON_ENUM_VALUE(array): {
            STRING_METHOD(construct_by_value_at)(&result, 1u, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'['});
            usize const array_size = TYPE_METHOD(JSON_ARRAY_TYPE, size)(&json->array);
            for (usize index = 0u; index < array_size; ++index) {
                struct STRING_TYPE() sub_string = NAMESPACE_UTILS_STRING(CONVERT(JSON_VALUE_TYPE(), STRING_TYPE()))(
                    TYPE_METHOD(JSON_ARRAY_TYPE, at)(&json->array, index)
                );
                STRING_METHOD(append_string)(&result, &sub_string);
                if (index != array_size - 1) {
                    STRING_METHOD(push_back)(&result, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){','});
                }
                STRING_METHOD(destroy_at)(&sub_string);
            }
            STRING_METHOD(push_back)(&result, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){']'});
            return result;
        }
        case JSON_ENUM_VALUE(object): {
            STRING_METHOD(construct_by_value_at)(&result, 1u, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'{'});
            STRUCT_SUBTYPE(JSON_OBJECT_TYPE, const_iterator_type) iterator = TYPE_METHOD(JSON_OBJECT_TYPE, cbegin)(&json->object);
            STRUCT_SUBTYPE(JSON_OBJECT_TYPE, const_iterator_type) const end_iterator = TYPE_METHOD(JSON_OBJECT_TYPE, cend)(&json->object);
            while (!TYPE_METHOD(JSON_OBJECT_CONST_ITERATOR_TYPE, compare)(&iterator, &end_iterator)) {
                struct STRING_TYPE() const* const key = TYPE_METHOD(JSON_OBJECT_CONST_ITERATOR_TYPE, key)(&iterator);
                {
                    STRUCT_SUBTYPE(STRING_TYPE(), char_type) const value = '\"';
                    STRING_METHOD(push_back)(&result, &value);
                    STRING_METHOD(append_string)(&result, key);
                    STRING_METHOD(push_back)(&result, &value);
                }
                STRING_METHOD(push_back)(&result, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){':'});
                struct JSON_VALUE_TYPE() const* const value = TYPE_METHOD(JSON_OBJECT_CONST_ITERATOR_TYPE, const_value)(&iterator);
                {
                    struct STRING_TYPE() sub_string = NAMESPACE_UTILS_STRING(CONVERT(JSON_VALUE_TYPE(), STRING_TYPE()))(value);
                    STRING_METHOD(append_string)(&result, &sub_string);
                    STRING_METHOD(destroy_at)(&sub_string);
                }
                TYPE_METHOD(JSON_OBJECT_CONST_ITERATOR_TYPE, next)(&iterator);
                if (!TYPE_METHOD(JSON_OBJECT_CONST_ITERATOR_TYPE, compare)(&iterator, &end_iterator)) {
                    STRING_METHOD(push_back)(&result, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){','});
                    continue;
                }
                break;
            }
            STRING_METHOD(push_back)(&result, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'}'});
        } break;
    }

    return result;
}
