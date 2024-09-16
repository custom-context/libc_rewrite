#include "deserialization_errors.h"

#include <utils/format.h>
#include <utils/string/raw_string/convert.h>

struct JSON_DESERIALIZATION_ERROR_TYPE()*
    TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), construct_from_lexer_error_at)(
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const this,
        struct JSON_LEXER_ERROR_TYPE() const* const perror) {
    ASSERT(this);
    ASSERT(perror);
    
    struct CSTRING_VIEW_TYPE() perror_message_view = JSON_LEXER_ERROR_METHOD(message)(perror);

    this->message =
        NAMESPACE_UTILS(format)(
            "[Tokenizer] %vs",
            &perror_message_view);

    CSTRING_VIEW_METHOD(destroy_at)(&perror_message_view);

    return this;
}

struct JSON_DESERIALIZATION_ERROR_TYPE()*
    TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), construct_from_parser_error_at)(
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const this,
        struct CSTRING_VIEW_TYPE() const source_view,
        struct JSON_PARSER_ERROR_TYPE() const* const perror) {
    ASSERT(this);
    ASSERT(perror);

    struct CSTRING_VIEW_TYPE() perror_message_view = JSON_PARSER_ERROR_METHOD(message)(perror);
    struct CSTRING_VIEW_TYPE() source_prefix_view, source_suffix_view;
    CSTRING_VIEW_METHOD(construct_from_buffer_at)(&source_prefix_view,
        CSTRING_VIEW_METHOD(data)(&source_view) + (perror->token.position > 10u ? perror->token.position - 10u : 0u),
        (perror->token.position > 10u ? 10u : perror->token.position)
    );
    CSTRING_VIEW_METHOD(construct_from_buffer_at)(&source_suffix_view,
        CSTRING_VIEW_METHOD(data)(&source_view) + perror->token.position + 1u,
        ((CSTRING_VIEW_METHOD(size)(&source_view) - perror->token.position) > 20u ? 20u : (CSTRING_VIEW_METHOD(size)(&source_view) - perror->token.position - 1u))
    );

    this->message =
        NAMESPACE_UTILS(format)(
            "[Parser] Error occured at: ...%vs%c\033%vs...\n\terror_message: %vs",
            &source_prefix_view,
            *CSTRING_VIEW_METHOD(at)(&source_view, perror->token.position),
            &source_suffix_view,
            &perror_message_view);

    CSTRING_VIEW_METHOD(destroy_at)(&source_prefix_view);
    CSTRING_VIEW_METHOD(destroy_at)(&source_suffix_view);
    CSTRING_VIEW_METHOD(destroy_at)(&perror_message_view);
    return this;
}

struct JSON_DESERIALIZATION_ERROR_TYPE()*
    TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), construct_at)(
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const this) {
    ASSERT(this);
    STRING_METHOD(construct_at)(&this->message);
    return this;
}
struct JSON_DESERIALIZATION_ERROR_TYPE()*
    TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), construct_copy_at)(
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const this,
        struct JSON_DESERIALIZATION_ERROR_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    TYPE_METHOD(STRING_TYPE(), construct_copy_at)(&this->message, &source->message);
    return this;
}
struct JSON_DESERIALIZATION_ERROR_TYPE()*
    TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), construct_move_at)(
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const this,
        struct JSON_DESERIALIZATION_ERROR_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    TYPE_METHOD(STRING_TYPE(), construct_move_at)(&this->message, &source->message);
    return this;
}
void* TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), destroy_at)(struct JSON_DESERIALIZATION_ERROR_TYPE()* const this) {
    ASSERT(this);
    TYPE_METHOD(STRING_TYPE(), destroy_at)(&this->message);
    return this;
}

struct CSTRING_VIEW_TYPE() TYPE_METHOD(JSON_DESERIALIZATION_ERROR_TYPE(), message)(struct JSON_DESERIALIZATION_ERROR_TYPE() const* const this) {
    ASSERT(this);
    struct CSTRING_VIEW_TYPE() result;
    return *TYPE_METHOD(CSTRING_VIEW_TYPE(), construct_from_buffer_at)(&result,
        TYPE_METHOD(STRING_TYPE(), data)(&this->message),
        TYPE_METHOD(STRING_TYPE(), size)(&this->message));
}
