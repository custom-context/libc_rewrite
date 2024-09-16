#pragma once

#include "parser_ast_expression.h"

#include <json/serialize/lexer/lexer_token.h>
#include <json/value/value.h>
#include <json/common.h>

#include <containers/dynamic/array/array.h>

#define JSON_PARSER_AST_TYPE() NAMESPACE_JSON(parser_abstract_syntax_tree)
#define JSON_PARSER_AST_METHOD(METHOD) TYPE_METHOD(JSON_PARSER_AST_TYPE(), METHOD)

#define JSON_PARSER_AST_NODE_TYPE() CONCAT3(JSON_PARSER_AST_TYPE(), __, node)
#define JSON_PARSER_AST_NODE_METHOD(METHOD) TYPE_METHOD(JSON_PARSER_AST_NODE_TYPE(), METHOD)

#define JSON_PARSER_AST_ITERATOR_TYPE() CONCAT3(JSON_PARSER_AST_TYPE(), __, iterator)
#define JSON_PARSER_AST_ITERATOR_METHOD(METHOD) TYPE_METHOD(JSON_PARSER_AST_ITERATOR_TYPE(), METHOD)

typedef struct JSON_PARSER_AST_NODE_TYPE() JSON_PARSER_AST_NODE_TYPE();
DEFINE_DEFAULT_ALLOCATOR_TYPE(JSON_PARSER_AST_NODE_TYPE());
DECLARE_DYNAMIC_ARRAY_TYPE(JSON_PARSER_AST_NODE_TYPE());

typedef struct JSON_PARSER_AST_NODE_TYPE() {
    struct DYNAMIC_ARRAY_TYPE(JSON_PARSER_AST_NODE_TYPE()) nodes;
    struct JSON_PARSER_AST_NODE_TYPE()* parent;
    struct JSON_LEXER_TOKEN_TYPE() token;
    enum JSON_PARSER_EXPRESSION_ENUM_TYPE() expression_type;
} JSON_PARSER_AST_NODE_TYPE();

typedef struct JSON_PARSER_AST_TYPE() {
    struct JSON_PARSER_AST_NODE_TYPE()* root;
} JSON_PARSER_AST_TYPE();

typedef struct JSON_PARSER_AST_ITERATOR_TYPE() {
    struct JSON_PARSER_AST_NODE_TYPE()* node;
} JSON_PARSER_AST_ITERATOR_TYPE();

struct JSON_PARSER_AST_TYPE()* JSON_PARSER_AST_METHOD(construct_at)(struct JSON_PARSER_AST_TYPE()* const this);
void* JSON_PARSER_AST_METHOD(destroy_at)(struct JSON_PARSER_AST_TYPE()* const this);

struct JSON_PARSER_AST_ITERATOR_TYPE() JSON_PARSER_AST_METHOD(root)(struct JSON_PARSER_AST_TYPE()* const this);
bool JSON_PARSER_AST_METHOD(empty)(struct JSON_PARSER_AST_TYPE() const* const this);

struct JSON_PARSER_AST_ITERATOR_TYPE()
    JSON_PARSER_AST_METHOD(push_copy_token_by_iterator)(
        struct JSON_PARSER_AST_TYPE()* const this,
        struct JSON_PARSER_AST_ITERATOR_TYPE()* const iterator,
        enum JSON_PARSER_EXPRESSION_ENUM_TYPE() expression_type,
        struct JSON_LEXER_TOKEN_TYPE()* const token);

struct JSON_PARSER_AST_ITERATOR_TYPE()
    JSON_PARSER_AST_METHOD(push_move_token_by_iterator)(
        struct JSON_PARSER_AST_TYPE()* const this,
        struct JSON_PARSER_AST_ITERATOR_TYPE()* const iterator,
        enum JSON_PARSER_EXPRESSION_ENUM_TYPE() expression_type,
        struct JSON_LEXER_TOKEN_TYPE()* const token);

struct JSON_VALUE_TYPE() JSON_PARSER_AST_METHOD(shrink_to_value)(struct JSON_PARSER_AST_TYPE()* const this);

struct JSON_PARSER_AST_ITERATOR_TYPE()*
    JSON_PARSER_AST_ITERATOR_METHOD(construct_move_at)(
        struct JSON_PARSER_AST_ITERATOR_TYPE()* const this,
        struct JSON_PARSER_AST_ITERATOR_TYPE()* const source);

bool JSON_PARSER_AST_ITERATOR_METHOD(empty)(struct JSON_PARSER_AST_ITERATOR_TYPE() const* const this);
struct JSON_PARSER_AST_ITERATOR_TYPE()
    JSON_PARSER_AST_ITERATOR_METHOD(mut_parent)(
        struct JSON_PARSER_AST_ITERATOR_TYPE()* const this);

struct JSON_PARSER_AST_NODE_TYPE() const*
    JSON_PARSER_AST_ITERATOR_METHOD(value)(struct JSON_PARSER_AST_ITERATOR_TYPE() const* const this);
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_ITERATOR_METHOD(mut_value)(struct JSON_PARSER_AST_ITERATOR_TYPE()* const this);

void* JSON_PARSER_AST_ITERATOR_METHOD(destroy_at)(struct JSON_PARSER_AST_ITERATOR_TYPE()* const this);

// node related methods
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(PRIVATE(construct_at))(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE()* const parent,
        enum JSON_PARSER_EXPRESSION_ENUM_TYPE() expression_type);
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(PRIVATE(construct_move_from_token_at))(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE()* const parent,
        enum JSON_PARSER_EXPRESSION_ENUM_TYPE() expression_type,
        struct JSON_LEXER_TOKEN_TYPE()* const token);

struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(construct_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this);
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(construct_copy_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE() const* const source);
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(construct_move_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE()* const source);
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(assign_copy_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE() const* const source);
struct JSON_PARSER_AST_NODE_TYPE()*
    JSON_PARSER_AST_NODE_METHOD(assign_move_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this,
        struct JSON_PARSER_AST_NODE_TYPE()* const source);
void*
    JSON_PARSER_AST_NODE_METHOD(destroy_at)(
        struct JSON_PARSER_AST_NODE_TYPE()* const this);

struct JSON_VALUE_TYPE() JSON_PARSER_AST_NODE_METHOD(PRIVATE(shrink_to_value))(struct JSON_PARSER_AST_NODE_TYPE()* const this);
