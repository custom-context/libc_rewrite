#pragma once

#include "lexer_errors.h"
#include "lexer_token.h"
#include <json/common.h>
#include <containers/static/string_view/string_view.h>
#include <containers/optional/optional.h>
#include <utils/result.h>

#define JSON_LEXER_TYPE() NAMESPACE_JSON(lexer)
#define JSON_LEXER_METHOD(METHOD) TYPE_METHOD(JSON_LEXER_TYPE(), METHOD)

typedef struct JSON_LEXER_TYPE() {
    struct CSTRING_VIEW_TYPE() source;
    usize source_index;
} JSON_LEXER_TYPE();

DEFINE_RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE());
DECLARE_RESULT_TYPE_METHODS_WITH_COMMON_MODIFIER(extern, JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE());

struct JSON_LEXER_TYPE()*
    JSON_LEXER_METHOD(construct_from_value_at)(
        struct JSON_LEXER_TYPE()* const this,
        struct CSTRING_VIEW_TYPE() const source);
DEFINE_OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE());
void*
    JSON_LEXER_METHOD(destroy_at)(
        struct JSON_LEXER_TYPE()* const this);
struct RESULT_TYPE(JSON_LEXER_TOKEN_TYPE(), JSON_LEXER_ERROR_TYPE())
    JSON_LEXER_METHOD(get_next_token)(
        struct JSON_LEXER_TYPE()* const this);
struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE())
    JSON_LEXER_METHOD(PRIVATE(try_map_lexeme_to_token))(struct JSON_LEXER_TYPE() const* const this, usize* const count_read_bytes);
struct JSON_LEXER_TYPE()
    JSON_LEXER_METHOD(end)(
        struct JSON_LEXER_TYPE() const* const this);
bool JSON_LEXER_METHOD(are_equals)(
    struct JSON_LEXER_TYPE() const* const this,
    struct JSON_LEXER_TYPE() const* const source);

void JSON_LEXER_TOKEN_METHOD(PRIVATE(initialize_token_mapping_table))(void);
