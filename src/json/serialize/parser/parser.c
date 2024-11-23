#include "parser.h"

DEFINE_OPTIONAL_METHODS_WITH_COMMON_MODIFIER(, JSON_PARSER_ERROR_TYPE())

struct JSON_PARSER_TYPE()* JSON_PARSER_METHOD(construct_at)(struct JSON_PARSER_TYPE()* const this) {
    ASSERT(this);
    JSON_PARSER_AST_METHOD(construct_at)(&this->abstract_syntax_tree);
    this->ast_iterator = JSON_PARSER_AST_METHOD(root)(&this->abstract_syntax_tree);
    this->parse_state = JSON_PARSER_STATE_ENUM_VALUE(NONE);
    return this;
}

void* JSON_PARSER_METHOD(destroy_at)(struct JSON_PARSER_TYPE()* const this) {
    ASSERT(this);
    JSON_PARSER_AST_ITERATOR_METHOD(destroy_at)(&this->ast_iterator);
    JSON_PARSER_AST_METHOD(destroy_at)(&this->abstract_syntax_tree);
    return this;
}

struct OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE())
    JSON_PARSER_METHOD(push_copy_token)(
        struct JSON_PARSER_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE() const* const token) {
    ASSERT(this);

    struct JSON_LEXER_TOKEN_TYPE() temporary_token;
    JSON_LEXER_TOKEN_METHOD(construct_copy_at)(&temporary_token, token);

    struct OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE()) result = JSON_PARSER_METHOD(push_move_token)(this, &temporary_token);

    JSON_LEXER_TOKEN_METHOD(destroy_at)(&temporary_token);
    return result;
}

static OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE()) create_error_opt(struct JSON_LEXER_TOKEN_TYPE()* const token);

struct OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE())
    JSON_PARSER_METHOD(push_move_token)(
        struct JSON_PARSER_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE()* const token) {
    ASSERT(this);

    #define ASTMethod(METHOD) JSON_PARSER_AST_METHOD(METHOD)

    #define ASTIteratorType JSON_PARSER_AST_ITERATOR_TYPE()
    #define ASTIteratorMethod(METHOD) JSON_PARSER_AST_ITERATOR_METHOD(METHOD)

    #define StateType JSON_PARSER_STATE_ENUM_TYPE()
    #define StateValue(VALUE) JSON_PARSER_STATE_ENUM_VALUE(VALUE)

    #define ExpressionValue(VALUE) JSON_PARSER_EXPRESSION_ENUM_VALUE(VALUE)

    #define TokenType JSON_LEXER_TOKEN_ENUM_TYPE()
    #define TokenValue(VALUE) JSON_LEXER_TOKEN_ENUM_VALUE(VALUE)


    if (ASTIteratorMethod(empty)(&this->ast_iterator) && !ASTMethod(empty)(&this->abstract_syntax_tree)) {
        return create_error_opt(token);
    }

    enum StateType const current_state = this->parse_state;
    enum TokenType const token_type = token->token_type;

    switch (current_state) {
        case StateValue(NONE): {
            /**
             * NONE state expects compound type
             * -----AST::root-----
             * v                 v
             * Node::ArrayType   Node::ObjectType
             */
            switch (token_type) {
                case TokenValue(ARRAY_BEGIN): {
                    this->parse_state = StateValue(ARRAY_EXPRESSION);
                    this->ast_iterator = ASTMethod(push_move_token_by_iterator)(&this->abstract_syntax_tree,
                        &this->ast_iterator,
                        ExpressionValue(ARRAY_EXPRESSION),
                        token);
                } break;
                case TokenValue(OBJECT_BEGIN): {
                    this->parse_state = StateValue(OBJECT_EXPRESSION);
                    this->ast_iterator = ASTMethod(push_move_token_by_iterator)(
                        &this->abstract_syntax_tree,
                        &this->ast_iterator,
                        ExpressionValue(OBJECT_EXPRESSION),
                        token);
                } break;
                default: {
                    return create_error_opt(token);
                }
            }
        } break;
        case StateValue(OBJECT_EXPRESSION): {
            /**
             * OBJECT_EXPRESSION state expects object's key or end of object
             * ---Node::ObjectType[end]--- (from here)
             * v                         v
             * ---Node::KeyValue---      goto parent <(or here)
             * v
             * Node::StringType <(here)
             */
            switch (token_type) {
                case TokenValue(STRING_LITERAL): {
                    this->parse_state = StateValue(KEY_VALUE_EXPRESSION);
                    this->ast_iterator = ASTMethod(push_copy_token_by_iterator)(
                        &this->abstract_syntax_tree,
                        &this->ast_iterator,
                        ExpressionValue(KEY_VALUE_EXPRESSION),
                        token);
                    this->ast_iterator = ASTMethod(push_move_token_by_iterator)(
                        &this->abstract_syntax_tree,
                        &this->ast_iterator,
                        ExpressionValue(VALUE_TERMINAL),
                        token);
                } break;
                case TokenValue(OBJECT_END): {
                    if (ASTIteratorMethod(value)(&this->ast_iterator)->expression_type != ExpressionValue(OBJECT_EXPRESSION)) {
                        return create_error_opt(token);
                    }
                    ASTIteratorType temporary = ASTIteratorMethod(mut_parent)(&this->ast_iterator);
                    if (ASTIteratorMethod(empty)(&temporary)) {
                        ASTIteratorMethod(construct_move_at)(&this->ast_iterator, &temporary);
                        // do nothing, 'couse this->ast_iterator points to nothing
                        ASTIteratorMethod(destroy_at)(&temporary);
                        break;
                    }
                    if (ASTIteratorMethod(value)(&this->ast_iterator)->expression_type == ExpressionValue(ARRAY_EXPRESSION)) {
                        this->parse_state = StateValue(VALUE_EXPRESSION);
                        ASTIteratorMethod(destroy_at)(&temporary);
                        break;
                    }
                    if (ASTIteratorMethod(value)(&this->ast_iterator)->expression_type == ExpressionValue(OBJECT_EXPRESSION)) {
                        this->parse_state = StateValue(VALUE_EXPRESSION);
                        ASTIteratorMethod(destroy_at)(&temporary);
                        break;
                    }
                    ASTIteratorMethod(destroy_at)(&temporary);
                    return create_error_opt(token);
                }
                default: return create_error_opt(token);
            }
        } break;
        case StateValue(ARRAY_EXPRESSION): {
            /**
             * ARRAY_EXPRESSION state expects arrays's value or end of object
             * ----Node::ArrayType[end]----
             * v                          v
             * Node::ValueType <(here)    go to parent
             */
            switch (token_type) {
                case TokenValue(NULL_LITERAL):
                case TokenValue(BOOLEAN_LITERAL):
                case TokenValue(NUMBER_LITERAL):
                case TokenValue(STRING_LITERAL):
                {
                    this->parse_state = StateValue(VALUE_EXPRESSION);
                    this->ast_iterator = ASTMethod(push_move_token_by_iterator)(
                        &this->abstract_syntax_tree,
                        &this->ast_iterator,
                        ExpressionValue(VALUE_TERMINAL),
                        token);
                } break;
                case TokenValue(OBJECT_BEGIN): {
                    this->parse_state = StateValue(OBJECT_EXPRESSION);
                    this->ast_iterator = ASTMethod(push_move_token_by_iterator)(
                        &this->abstract_syntax_tree,
                        &this->ast_iterator,
                        ExpressionValue(OBJECT_EXPRESSION),
                        token);
                } break;
                case TokenValue(ARRAY_BEGIN): {
                    this->parse_state = StateValue(ARRAY_EXPRESSION);
                    this->ast_iterator = ASTMethod(push_move_token_by_iterator)(
                        &this->abstract_syntax_tree,
                        &this->ast_iterator,
                        ExpressionValue(ARRAY_EXPRESSION),
                        token);
                } break;
                case TokenValue(ARRAY_END): {
                    if (ASTIteratorMethod(value)(&this->ast_iterator)->expression_type != ExpressionValue(ARRAY_EXPRESSION)) {
                        return create_error_opt(token);
                    }
                    this->ast_iterator = ASTIteratorMethod(mut_parent)(&this->ast_iterator);
                    if (ASTIteratorMethod(empty)(&this->ast_iterator)) {
                        // do nothing, 'couse this->ast_iterator points to nothing
                        break;
                    }
                    if (ASTIteratorMethod(value)(&this->ast_iterator)->expression_type == ExpressionValue(ARRAY_EXPRESSION)) {
                        this->parse_state = StateValue(ARRAY_EXPRESSION);
                        break;
                    }
                    if (ASTIteratorMethod(value)(&this->ast_iterator)->expression_type == ExpressionValue(OBJECT_EXPRESSION)) {
                        this->parse_state = StateValue(OBJECT_EXPRESSION);
                        break;
                    }
                    return create_error_opt(token);
                }
                default: return create_error_opt(token);
            }
        } break;
        case StateValue(KEY_VALUE_EXPRESSION): {
            /**
             * KEY_VALUE_EXPRESSION state expects colon separator
             * ---Node::ObjectType[last]---
             * v
             * Node::KeyValue <(here)
             * ^
             * Node::StringType (from here)
             */
            switch (token_type) {
                case TokenValue(COLON_SEPARATOR): {
                    this->parse_state = StateValue(KEY_VALUE_AWAIT_FOR_VALUE_EXPRESSION);
                    this->ast_iterator = ASTIteratorMethod(mut_parent)(&this->ast_iterator);
                } break;
                default: return create_error_opt(token);
            }
        } break;
        case StateValue(VALUE_EXPRESSION): {
            /**
             * VALUE_EXPRESSION state expects comma separator or end of object
             * Node:CompoundType or null
             * v
             * Node::CompoundType[last] <(here)
             * v
             * Node::ValueType (from)
             */
            switch (token_type) {
                case TokenValue(COMMA_SEPARATOR): {
                    this->ast_iterator = ASTIteratorMethod(mut_parent)(&this->ast_iterator);
                    if (!ASTIteratorMethod(empty)(&this->ast_iterator) && ASTIteratorMethod(value)(&this->ast_iterator)->expression_type == ExpressionValue(KEY_VALUE_EXPRESSION)) {
                        this->ast_iterator = ASTIteratorMethod(mut_parent)(&this->ast_iterator);
                    }
                    if (ASTIteratorMethod(empty)(&this->ast_iterator)) {
                        return create_error_opt(token);
                    }
                    if (ASTIteratorMethod(value)(&this->ast_iterator)->expression_type == ExpressionValue(ARRAY_EXPRESSION)) {
                        this->parse_state = StateValue(ARRAY_EXPRESSION);
                        break;
                    }
                    if (ASTIteratorMethod(value)(&this->ast_iterator)->expression_type == ExpressionValue(OBJECT_EXPRESSION)) {
                        this->parse_state = StateValue(OBJECT_EXPRESSION);
                        break;
                    }
                    return create_error_opt(token);
                }
                case TokenValue(OBJECT_END): {
                    this->ast_iterator = ASTIteratorMethod(mut_parent)(&this->ast_iterator);
                    if (ASTIteratorMethod(empty)(&this->ast_iterator) || ASTIteratorMethod(value)(&this->ast_iterator)->expression_type != ExpressionValue(KEY_VALUE_EXPRESSION)) {
                        return create_error_opt(token);
                    }
                    this->ast_iterator = ASTIteratorMethod(mut_parent)(&this->ast_iterator);
                    if (ASTIteratorMethod(empty)(&this->ast_iterator) || ASTIteratorMethod(value)(&this->ast_iterator)->expression_type != ExpressionValue(OBJECT_EXPRESSION)) {
                        return create_error_opt(token);
                    }
                    this->parse_state = StateValue(VALUE_EXPRESSION);
                } break;
                case TokenValue(ARRAY_END): {
                    this->ast_iterator = ASTIteratorMethod(mut_parent)(&this->ast_iterator);
                    if (ASTIteratorMethod(empty)(&this->ast_iterator) || ASTIteratorMethod(value)(&this->ast_iterator)->expression_type != ExpressionValue(ARRAY_EXPRESSION)) {
                        return create_error_opt(token);
                    }
                    this->parse_state = StateValue(VALUE_EXPRESSION);
                } break;
                default: return create_error_opt(token);
            }
        } break;
        case StateValue(KEY_VALUE_AWAIT_FOR_VALUE_EXPRESSION): {
            /**
             * KEY_VALUE_AWAIT_FOR_VALUE_EXPRESSION state expects value
             * ---Node::ObjectType[last]---
             * v
             * Node::KeyValue (from here)
             * v
             * Node::ValueType <(here)
             */
            switch (token_type) {
                case TokenValue(NULL_LITERAL):
                case TokenValue(BOOLEAN_LITERAL):
                case TokenValue(NUMBER_LITERAL):
                case TokenValue(STRING_LITERAL):
                {
                    this->parse_state = StateValue(VALUE_EXPRESSION);
                    this->ast_iterator = ASTMethod(push_move_token_by_iterator)(
                        &this->abstract_syntax_tree,
                        &this->ast_iterator,
                        ExpressionValue(VALUE_TERMINAL),
                        token);
                } break;
                case TokenValue(OBJECT_BEGIN): {
                    this->parse_state = StateValue(OBJECT_EXPRESSION);
                    this->ast_iterator = ASTMethod(push_move_token_by_iterator)(
                        &this->abstract_syntax_tree,
                        &this->ast_iterator,
                        ExpressionValue(OBJECT_EXPRESSION),
                        token);
                } break;
                case TokenValue(ARRAY_BEGIN): {
                    this->parse_state = StateValue(ARRAY_EXPRESSION);
                    this->ast_iterator = ASTMethod(push_move_token_by_iterator)(
                        &this->abstract_syntax_tree,
                        &this->ast_iterator,
                        ExpressionValue(ARRAY_EXPRESSION),
                        token);
                } break;
                default: return create_error_opt(token);
            }
        } break;
        default: {
            // error
            ASSERT(false && "Unnhadled parse state");
        }
    }
    
    struct OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE()) result;
    OPTIONAL_METHOD(JSON_PARSER_ERROR_TYPE(), construct_at)(&result);
    return result;
}

static OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE()) create_error_opt(struct JSON_LEXER_TOKEN_TYPE()* const token) {
    struct JSON_PARSER_ERROR_TYPE() error;
    JSON_PARSER_ERROR_METHOD(construct_custom_at)(&error, token);

    struct OPTIONAL_TYPE(JSON_PARSER_ERROR_TYPE()) result;
    OPTIONAL_METHOD(JSON_PARSER_ERROR_TYPE(), construct_move_from_value_at)(&result, &error);

    JSON_PARSER_ERROR_METHOD(destroy_at)(&error);
    return result;
}

struct JSON_PARSER_AST_TYPE() const* JSON_PARSER_METHOD(abstract_syntax_tree)(struct JSON_PARSER_TYPE() const* const this) {
    ASSERT(this);
    return &this->abstract_syntax_tree;
}
struct JSON_PARSER_AST_TYPE()* JSON_PARSER_METHOD(mut_abstract_syntax_tree)(struct JSON_PARSER_TYPE()* const this) {
    ASSERT(this);
    return &this->abstract_syntax_tree;
}
