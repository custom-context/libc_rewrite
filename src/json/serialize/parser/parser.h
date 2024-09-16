#pragma once

#include "parser_abstract_syntax_tree.h"
#include "parser_errors.h"
#include "parser_state.h"
#include <containers/optional/optional.h>
#include <containers/dynamic/array/array.h>
#include <json/common.h>

#define JSON_PARSER_TYPE() NAMESPACE_JSON(parser)
#define JSON_PARSER_METHOD(METHOD) TYPE_METHOD(JSON_PARSER_TYPE(), METHOD)

DEFINE_OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE());
DECLARE_OPTIONAL_METHODS_WITH_COMMON_MODIFIER(extern, JSON_PARSER_ERROR_TYPE());

typedef struct JSON_PARSER_TYPE() {
    struct JSON_PARSER_AST_TYPE() abstract_syntax_tree;
    struct JSON_PARSER_AST_ITERATOR_TYPE() ast_iterator;
    enum JSON_PARSER_STATE_ENUM_TYPE() parse_state;
} JSON_PARSER_TYPE();

struct JSON_PARSER_TYPE()* JSON_PARSER_METHOD(construct_at)(struct JSON_PARSER_TYPE()* const this);
void* JSON_PARSER_METHOD(destroy_at)(struct JSON_PARSER_TYPE()* const this);

struct OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE()) JSON_PARSER_METHOD(push_copy_token)(struct JSON_PARSER_TYPE()* const this, struct JSON_LEXER_TOKEN_TYPE() const* const token);
struct OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE()) JSON_PARSER_METHOD(push_move_token)(struct JSON_PARSER_TYPE()* const this, struct JSON_LEXER_TOKEN_TYPE()* const token);

struct JSON_PARSER_AST_TYPE() const* JSON_PARSER_METHOD(abstract_syntax_tree)(struct JSON_PARSER_TYPE() const* const this);
struct JSON_PARSER_AST_TYPE()* JSON_PARSER_METHOD(mut_abstract_syntax_tree)(struct JSON_PARSER_TYPE()* const this);
