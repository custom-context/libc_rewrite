#include "lexer_errors.h"

#include <utils/format.h>

struct JSON_LEXER_ERROR_TYPE()*
    JSON_LEXER_ERROR_METHOD(construct_custom_at)(
        struct JSON_LEXER_ERROR_TYPE()* const this,
        struct CSTRING_VIEW_TYPE() substring, usize position, usize size) {
    ASSERT(this);
    
    this->message =
        NAMESPACE_UTILS(format)(
            "Error occured while parsing lexeme from json string. "
            "position=%zu, "
            "size=%zu, "
            "substring=\"%vs\".",
            position, size,
            &substring);

    return this;
}
struct JSON_LEXER_ERROR_TYPE()*
    JSON_LEXER_ERROR_METHOD(construct_at)(
        struct JSON_LEXER_ERROR_TYPE()* const this) {
    ASSERT(this);
    TYPE_METHOD(STRING_TYPE(), construct_at)(&this->message);
    return this;
}
struct JSON_LEXER_ERROR_TYPE()*
    JSON_LEXER_ERROR_METHOD(construct_copy_at)(
        struct JSON_LEXER_ERROR_TYPE()* const this,
        struct JSON_LEXER_ERROR_TYPE() const* const source) {
    ASSERT(this);
    ASSERT(source);
    TYPE_METHOD(STRING_TYPE(), construct_copy_at)(&this->message, &source->message);
    return this;
}
struct JSON_LEXER_ERROR_TYPE()*
    JSON_LEXER_ERROR_METHOD(construct_move_at)(
        struct JSON_LEXER_ERROR_TYPE()* const this,
        struct JSON_LEXER_ERROR_TYPE()* const source) {
    ASSERT(this);
    ASSERT(source);
    TYPE_METHOD(STRING_TYPE(), construct_move_at)(&this->message, &source->message);
    return this;
}
void* JSON_LEXER_ERROR_METHOD(destroy_at)(struct JSON_LEXER_ERROR_TYPE()* const this) {
    ASSERT(this);
    TYPE_METHOD(STRING_TYPE(), destroy_at)(&this->message);
    return this;
}

struct CSTRING_VIEW_TYPE() JSON_LEXER_ERROR_METHOD(message)(struct JSON_LEXER_ERROR_TYPE() const* const this) {
    ASSERT(this);
    struct CSTRING_VIEW_TYPE() result;
    TYPE_METHOD(CSTRING_VIEW_TYPE(), construct_from_buffer_at)(&result,
        TYPE_METHOD(STRING_TYPE(), data)(&this->message),
        TYPE_METHOD(STRING_TYPE(), size)(&this->message));
    return result;
}
