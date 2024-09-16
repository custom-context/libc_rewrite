#include "parser_abstract_syntax_tree.h"

DEFINE_DEFAULT_ALLOCATOR_STATIC_METHODS(JSON_PARSER_AST_NODE_TYPE())
DECLARE_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(JSON_PARSER_AST_NODE_TYPE());
IMPLEMENT_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(JSON_PARSER_AST_NODE_TYPE())

struct JSON_PARSER_AST_TYPE()* JSON_PARSER_AST_METHOD(construct_at)(struct JSON_PARSER_AST_TYPE()* const this) {
    ASSERT(this);

    this->root = NULL;

    return this;
}

void* JSON_PARSER_AST_METHOD(destroy_at)(struct JSON_PARSER_AST_TYPE()* const this) {
    ASSERT(this);

    if (this->root) {
        JSON_PARSER_AST_NODE_METHOD(destroy_at)(this->root);
        struct DEFAULT_ALLOCATOR_TYPE(JSON_PARSER_AST_NODE_TYPE()) default_allocator;
        DEFAULT_ALLOCATOR_METHOD(JSON_PARSER_AST_NODE_TYPE(), deallocate)(&default_allocator, this->root, 1u);
    }
    return this;
}

struct JSON_PARSER_AST_ITERATOR_TYPE() JSON_PARSER_AST_METHOD(root)(struct JSON_PARSER_AST_TYPE()* const this) {
    ASSERT(this);

    struct JSON_PARSER_AST_ITERATOR_TYPE() iterator = {
        .node = this->root
    };

    return iterator;
}

bool JSON_PARSER_AST_METHOD(empty)(struct JSON_PARSER_AST_TYPE() const* const this) {
    ASSERT(this);

    return !this->root;
}

struct JSON_PARSER_AST_ITERATOR_TYPE()
    JSON_PARSER_AST_METHOD(push_copy_token_by_iterator)(
        struct JSON_PARSER_AST_TYPE()* const this,
        struct JSON_PARSER_AST_ITERATOR_TYPE()* const iterator,
        enum JSON_PARSER_EXPRESSION_ENUM_TYPE() expression_type,
        struct JSON_LEXER_TOKEN_TYPE()* const token) {
    ASSERT(this);
    ASSERT(iterator);
    ASSERT(token);

    struct JSON_LEXER_TOKEN_TYPE() temporary;
    JSON_LEXER_TOKEN_METHOD(construct_copy_at)(&temporary, token);

    struct JSON_PARSER_AST_ITERATOR_TYPE() result =
        JSON_PARSER_AST_METHOD(push_move_token_by_iterator)(this, iterator, expression_type, &temporary);

    JSON_LEXER_TOKEN_METHOD(destroy_at)(&temporary);
    return result;
}

struct JSON_PARSER_AST_ITERATOR_TYPE()
    JSON_PARSER_AST_METHOD(push_move_token_by_iterator)(
        struct JSON_PARSER_AST_TYPE()* const this,
        struct JSON_PARSER_AST_ITERATOR_TYPE()* const iterator,
        enum JSON_PARSER_EXPRESSION_ENUM_TYPE() expression_type,
        struct JSON_LEXER_TOKEN_TYPE()* const token) {
    ASSERT(this);
    ASSERT(iterator);
    ASSERT(token);

    // #define NodeArrayType DYNAMIC_ARRAY_TYPE(JSON_PARSER_AST_NODE_TYPE())
    #define NodeArrayMethod(METHOD) DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), METHOD)
    #define NodeArrayRevIteratorType DYNAMIC_ARRAY_REVERSE_ITERATOR_TYPE(JSON_PARSER_AST_NODE_TYPE())
    #define NodeArrayRevIteratorMethod(METHOD) DYNAMIC_ARRAY_REVERSE_ITERATOR_METHOD(JSON_PARSER_AST_NODE_TYPE(), METHOD)

    // cache iterator's value as parent node
    struct JSON_PARSER_AST_NODE_TYPE()* parent_node = JSON_PARSER_AST_ITERATOR_METHOD(mut_value)(iterator);

    struct JSON_PARSER_AST_NODE_TYPE() node;
    switch (expression_type) {
        case JSON_PARSER_EXPRESSION_ENUM_VALUE(VALUE_TERMINAL): {
            // construct node using iterator's node as parent node & token pointer
            JSON_PARSER_AST_NODE_METHOD(PRIVATE(construct_move_from_token_at))(&node, parent_node, expression_type, token);
        } break;
        case JSON_PARSER_EXPRESSION_ENUM_VALUE(ARRAY_EXPRESSION):
        case JSON_PARSER_EXPRESSION_ENUM_VALUE(OBJECT_EXPRESSION):
        case JSON_PARSER_EXPRESSION_ENUM_VALUE(KEY_VALUE_EXPRESSION): {
            // construct node using iterator's node as parent node
            JSON_PARSER_AST_NODE_METHOD(PRIVATE(construct_at))(&node, parent_node, expression_type);
        } break;
    }

    struct JSON_PARSER_AST_NODE_TYPE()* target_node;
    if (!this->root) {
        ASSERT(!parent_node);
        struct DEFAULT_ALLOCATOR_TYPE(JSON_PARSER_AST_NODE_TYPE()) default_allocator;
        this->root = DEFAULT_ALLOCATOR_METHOD(JSON_PARSER_AST_NODE_TYPE(), allocate)(&default_allocator, 1u);
        JSON_PARSER_AST_NODE_METHOD(construct_move_at)(this->root, &node);
        target_node = this->root;
    } else {
        // insert node to iterator's nodes
        NodeArrayMethod(push_back_by_moving)(&parent_node->nodes, &node);
        // return iterator that points to inserted node
        struct NodeArrayRevIteratorType node_iterator = NodeArrayMethod(rbegin)(&parent_node->nodes);
        target_node = NodeArrayRevIteratorMethod(value)(&node_iterator);
    }

    struct JSON_PARSER_AST_ITERATOR_TYPE() result = {
        .node = target_node
    };
    JSON_PARSER_AST_NODE_METHOD(destroy_at)(&node);
    return result;

}

struct JSON_VALUE_TYPE() JSON_PARSER_AST_METHOD(shrink_to_value)(struct JSON_PARSER_AST_TYPE()* const this) {
    ASSERT(this);
    struct JSON_VALUE_TYPE() result = JSON_PARSER_AST_NODE_METHOD(PRIVATE(shrink_to_value))(this->root);
    JSON_PARSER_AST_METHOD(destroy_at)(this); JSON_PARSER_AST_METHOD(construct_at)(this);
    return result;
}

struct JSON_PARSER_AST_ITERATOR_TYPE()*
    JSON_PARSER_AST_ITERATOR_METHOD(construct_move_at)(
        struct JSON_PARSER_AST_ITERATOR_TYPE()* const this,
        struct JSON_PARSER_AST_ITERATOR_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    this->node = source->node;
    return this;
}
bool JSON_PARSER_AST_ITERATOR_METHOD(empty)(struct JSON_PARSER_AST_ITERATOR_TYPE() const* const this) {
    ASSERT(this);
    return !this->node;
}
struct JSON_PARSER_AST_ITERATOR_TYPE() JSON_PARSER_AST_ITERATOR_METHOD(mut_parent)(struct JSON_PARSER_AST_ITERATOR_TYPE()* const this) {
    ASSERT(this);

    struct JSON_PARSER_AST_ITERATOR_TYPE() result = {
        .node = (this->node && this->node->parent) ? this->node->parent : NULL
    };

    return result;
}

struct JSON_PARSER_AST_NODE_TYPE() const*
    JSON_PARSER_AST_ITERATOR_METHOD(value)(struct JSON_PARSER_AST_ITERATOR_TYPE() const* const this) {
    ASSERT(this);
    return this->node;
}
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_ITERATOR_METHOD(mut_value)(struct JSON_PARSER_AST_ITERATOR_TYPE()* const this) {
    ASSERT(this);
    return this->node;    
}

void* JSON_PARSER_AST_ITERATOR_METHOD(destroy_at)(struct JSON_PARSER_AST_ITERATOR_TYPE()* const this) {
    ASSERT(this);
    return this;
}

struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(PRIVATE(construct_at))(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE()* const parent,
        enum JSON_PARSER_EXPRESSION_ENUM_TYPE() expression_type) {
    ASSERT(this);
    DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), construct_at)(&this->nodes);
    this->parent = parent;
    JSON_LEXER_TOKEN_METHOD(construct_at)(&this->token);
    this->expression_type = expression_type;
    return this;
}
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(PRIVATE(construct_move_from_token_at))(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE()* const parent,
        enum JSON_PARSER_EXPRESSION_ENUM_TYPE() expression_type,
        struct JSON_LEXER_TOKEN_TYPE()* const token) {
    ASSERT(this);
    ASSERT(token);
    JSON_PARSER_AST_NODE_METHOD(PRIVATE(construct_at))(this, parent, expression_type);
    JSON_LEXER_TOKEN_METHOD(construct_move_at)(&this->token, token);
    return this;
}

struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(construct_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this) {
    ASSERT(this);
    ASSERT(false);
    return this;
}
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(construct_copy_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    ASSERT(false);
    return this;
}
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(construct_move_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);

    DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), construct_move_at)(&this->nodes, &source->nodes);
    this->parent = source->parent;
    this->expression_type = source->expression_type;
    JSON_LEXER_TOKEN_METHOD(construct_move_at)(&this->token, &source->token);

    return this;
}
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(assign_copy_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    ASSERT(false);
    return this;
}
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(assign_move_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    ASSERT(false);
    return this;
}
void*
    JSON_PARSER_AST_NODE_METHOD(destroy_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this) {
    ASSERT(this);
    DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), destroy_at)(&this->nodes);
    JSON_LEXER_TOKEN_METHOD(destroy_at)(&this->token);
    return this;
}

struct JSON_VALUE_TYPE() JSON_PARSER_AST_NODE_METHOD(PRIVATE(shrink_to_value))(struct JSON_PARSER_AST_NODE_TYPE()* const this) {
    ASSERT(this);

    switch (this->expression_type) {
        case JSON_PARSER_EXPRESSION_ENUM_VALUE(VALUE_TERMINAL): {
            // add terminal's token
            switch (this->token.token_type) {
                case JSON_LEXER_TOKEN_ENUM_VALUE(NULL_LITERAL): {
                    struct JSON_VALUE_TYPE() result;
                    JSON_VALUE_METHOD(construct_at)(&result);
                    return result;
                }
                case JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL): {
                    struct JSON_VALUE_TYPE() result;
                    JSON_VALUE_METHOD(construct_move_from_value_at)(&result, this->token.boolean);
                    return result;
                }
                case JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL): {
                    struct JSON_VALUE_TYPE() result;
                    JSON_VALUE_METHOD(construct_move_from_value_at)(&result, this->token.number);
                    return result;
                }
                case JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL): {
                    struct JSON_VALUE_TYPE() result;
                    JSON_VALUE_METHOD(construct_move_from_value_at)(&result, &this->token.string);
                    return result;
                }
                default:  {
                    // error
                    ASSERT(false);
                } break;
            }
        } break;
        case JSON_PARSER_EXPRESSION_ENUM_VALUE(ARRAY_EXPRESSION): {
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), array_type) array;
            TYPE_METHOD(JSON__array_type, construct_at)(&array);

            TYPE_METHOD(JSON__array_type, reserve)(&array,
                DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), size)(&this->nodes));
            for (usize i = 0u; i < DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), size)(&this->nodes); ++i) {
                struct JSON_VALUE_TYPE() current_value =
                    JSON_PARSER_AST_NODE_METHOD(PRIVATE(shrink_to_value))(
                        DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), mut_at)(&this->nodes, i));
                TYPE_METHOD(JSON__array_type, push_back_by_moving)(&array, &current_value);
                JSON_VALUE_METHOD(destroy_at)(&current_value);
            }
            struct JSON_VALUE_TYPE() result; JSON_VALUE_METHOD(construct_from_value_at)(&result, &array);
            TYPE_METHOD(JSON__array_type, destroy_at)(&array);
            return result;
        }
        case JSON_PARSER_EXPRESSION_ENUM_VALUE(OBJECT_EXPRESSION): {
            STRUCT_SUBTYPE(JSON_VALUE_TYPE(), object_type) object;
            TYPE_METHOD(JSON__object_type, construct_at)(&object);

            for (usize i = 0u; i < DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), size)(&this->nodes); ++i) {
                struct JSON_PARSER_AST_NODE_TYPE()* const current_node =
                    DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), mut_at)(&this->nodes, i);

                // error
                if (current_node->expression_type != JSON_PARSER_EXPRESSION_ENUM_VALUE(KEY_VALUE_EXPRESSION)) {
                    ASSERT(false);
                    break;
                }
                if (DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), size)(&current_node->nodes) != 2u) {
                    ASSERT(false);
                    break;
                }

                struct JSON_PARSER_AST_NODE_TYPE()* const key_node =
                    DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), mut_at)(&current_node->nodes, 0u);
                // error
                if (key_node->expression_type != JSON_PARSER_EXPRESSION_ENUM_VALUE(VALUE_TERMINAL)) {
                    ASSERT(false);
                    break;
                }
                if (key_node->token.token_type != JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)) {
                    ASSERT(false);
                    break;
                }

                struct JSON_PARSER_AST_NODE_TYPE()* const value_node =
                    DYNAMIC_ARRAY_METHOD(JSON_PARSER_AST_NODE_TYPE(), mut_at)(&current_node->nodes, 1u);
                // [construct] convert value_node content to json_value
                struct JSON_VALUE_TYPE() json_kv_value =
                    JSON_PARSER_AST_NODE_METHOD(PRIVATE(shrink_to_value))(value_node);

                struct PAIR_TYPE(JSON__object__iterator_type, bool) inserted_or_not_iterator =
                    TYPE_METHOD(JSON__object_type, insert_or_assign_with_key_move_value_move)(&object, &key_node->token.string, &json_kv_value);
                if (!inserted_or_not_iterator.second) {
                    // value repeated -> return error
                    ASSERT(false);
                    break;
                }
                TYPE_METHOD(PAIR_TYPE(JSON__object__iterator_type, bool), destroy_at)(&inserted_or_not_iterator);
                JSON_VALUE_METHOD(destroy_at)(&json_kv_value);
            }
            struct JSON_VALUE_TYPE() result; JSON_VALUE_METHOD(construct_from_value_at)(&result, &object);
            TYPE_METHOD(JSON__object_type, destroy_at)(&object);
            return result;
        }
        case JSON_PARSER_EXPRESSION_ENUM_VALUE(KEY_VALUE_EXPRESSION): {
            // error
            ASSERT(false);
        } break;
    }

    struct JSON_VALUE_TYPE() result;
    JSON_VALUE_METHOD(construct_at)(&result);
    return result;
}
