#include "lexer_token.h"

struct JSON_LEXER_TOKEN_TYPE()*
    JSON_LEXER_TOKEN_METHOD(construct_at)(
        struct JSON_LEXER_TOKEN_TYPE()* const this) {
    ASSERT(this);
    this->token_type = JSON_LEXER_TOKEN_ENUM_VALUE(UNKNOWN);
    return this;
}
struct JSON_LEXER_TOKEN_TYPE()*
    JSON_LEXER_TOKEN_METHOD(construct_copy_at)(
        struct JSON_LEXER_TOKEN_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    this->token_type = source->token_type;
    this->position = source->position;
    if (source->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)) {
        TYPE_METHOD(STRING_TYPE(), construct_copy_at)(&this->string, &source->string);
    }
    if (source->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL)) {
        this->number = source->number;
    }
    if (source->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL)) {
        this->boolean = source->boolean;
    }
    return this;
}
struct JSON_LEXER_TOKEN_TYPE()*
    JSON_LEXER_TOKEN_METHOD(construct_move_at)(
        struct JSON_LEXER_TOKEN_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    this->token_type = source->token_type;
    this->position = source->position;
    if (source->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)) {
        TYPE_METHOD(STRING_TYPE(), construct_move_at)(&this->string, &source->string);
    }
    if (source->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL)) {
        this->number = source->number;
    }
    if (source->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL)) {
        this->boolean = source->boolean;
    }
    return this;
}
struct JSON_LEXER_TOKEN_TYPE()*
    JSON_LEXER_TOKEN_METHOD(assign_copy_at)(
        struct JSON_LEXER_TOKEN_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    struct JSON_LEXER_TOKEN_TYPE() temporary;
    JSON_LEXER_TOKEN_METHOD(construct_copy_at)(&temporary, source);
    JSON_LEXER_TOKEN_METHOD(swap)(this, &temporary);
    JSON_LEXER_TOKEN_METHOD(destroy_at)(&temporary);
    return this;
}
struct JSON_LEXER_TOKEN_TYPE()*
    JSON_LEXER_TOKEN_METHOD(assign_move_at)(
        struct JSON_LEXER_TOKEN_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    struct JSON_LEXER_TOKEN_TYPE() temporary;
    JSON_LEXER_TOKEN_METHOD(construct_move_at)(&temporary, source);
    JSON_LEXER_TOKEN_METHOD(swap)(this, &temporary);
    JSON_LEXER_TOKEN_METHOD(destroy_at)(&temporary);
    return this;
}

static void swap_tokens(enum JSON_LEXER_TOKEN_ENUM_TYPE()* const, enum JSON_LEXER_TOKEN_ENUM_TYPE()* const);
static void swap_positions(usize* const, usize* const);
static void swap_values_with_first_string_holder(struct JSON_LEXER_TOKEN_TYPE()* const, struct JSON_LEXER_TOKEN_TYPE()* const);

void
    JSON_LEXER_TOKEN_METHOD(swap)(
        struct JSON_LEXER_TOKEN_TYPE()* const this,
        struct JSON_LEXER_TOKEN_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);

    if (this->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)) {
        swap_values_with_first_string_holder(this, source);
        goto json_lexer_token_swap_non_union_values;
    }
    if (source->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)) {
        swap_values_with_first_string_holder(source, this);
        goto json_lexer_token_swap_non_union_values;
    }

    if (
        this->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL) ||
        this->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL)) {
        STATIC_ASSERT(sizeof(this->number) >= sizeof(this->boolean));
        STATIC_ASSERT(sizeof(double) == sizeof(uint64));
        *(uint64*)(&this->number) ^= *(uint64*)(&source->number);
        *(uint64*)(&source->number) ^= *(uint64*)(&this->number);
        *(uint64*)(&this->number) ^= *(uint64*)(&source->number);
    }

    json_lexer_token_swap_non_union_values:
        swap_tokens(&this->token_type, &source->token_type);
        swap_positions(&this->position, &source->position);
}
void* JSON_LEXER_TOKEN_METHOD(destroy_at)(struct JSON_LEXER_TOKEN_TYPE()* const this) {
    ASSERT(this);
    if (this->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)) {
        TYPE_METHOD(STRING_TYPE(), destroy_at)(&this->string);
    }
    return this;
}


static void swap_tokens(
    enum JSON_LEXER_TOKEN_ENUM_TYPE()* const ptoken1,
    enum JSON_LEXER_TOKEN_ENUM_TYPE()* const ptoken2) {
    *ptoken1 ^= *ptoken2;
    *ptoken2 ^= *ptoken1;
    *ptoken1 ^= *ptoken2;
}

static void swap_positions(
    usize* const pposition1,
    usize* const pposition2) {
    *pposition1 ^= *pposition2;
    *pposition2 ^= *pposition1;
    *pposition1 ^= *pposition2;
}


static void swap_values_with_first_string_holder(
    struct JSON_LEXER_TOKEN_TYPE()* const string_holder,
    struct JSON_LEXER_TOKEN_TYPE()* const another_holder) {
    if (another_holder->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL)) {
        STRING_METHOD(swap)(&string_holder->string, &another_holder->string);
        return;
    }
    if (another_holder->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL)) {
        double temporary = another_holder->number;
        STRING_METHOD(construct_move_at)(&another_holder->string, &string_holder->string);
        string_holder->number = temporary;
        return;
    }
    if (another_holder->token_type == JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL)) {
        bool temporary = another_holder->boolean;
        STRING_METHOD(construct_move_at)(&another_holder->string, &string_holder->string);
        another_holder->boolean = temporary;
        return;
    }
    STRING_METHOD(construct_move_at)(&another_holder->string, &string_holder->string);
}
