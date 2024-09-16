#include "lexer.h"

#include <utils/character/character.h>
#include <utils/string/raw_string/convert.h>

DEFINE_OPTIONAL_STATIC_METHODS(JSON_LEXER_TOKEN_TYPE())

#define TRY_PARSE_LITERAL_FN_(LITERAL) CONCAT3(try_parse, LITERAL, _literal)

static struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) try_parse_separator_literal(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes);
static struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) try_parse_whitespace_literal(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes);

#define DECLARE_TRY_PARSE_LITERAL_FN(MODIFIER, LITERAL)\
MODIFIER struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) TRY_PARSE_LITERAL_FN_(_ ## LITERAL)(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes)
DECLARE_TRY_PARSE_LITERAL_FN(static, null);
DECLARE_TRY_PARSE_LITERAL_FN(static, false);
DECLARE_TRY_PARSE_LITERAL_FN(static, true);
static struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) try_parse_number_literal(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes);
static struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) try_parse_string_literal(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes);

typedef struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) (*try_map_lexeme_to_token)(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes);
// ascii mapping of keywords (it would be good to change it to associative array)
static try_map_lexeme_to_token try_map_lexeme_to_token_mapping[1 << CHAR_BIT] = { 0 };

void JSON_LEXER_TOKEN_METHOD(PRIVATE(initialize_token_mapping_table))(void) {
    try_map_lexeme_to_token_mapping['-'] = &try_parse_number_literal;
    for (usize i = 0u; i < 10u; ++i) {
        try_map_lexeme_to_token_mapping['0' + i] = &try_parse_number_literal;
    }
    try_map_lexeme_to_token_mapping['\"'] = &try_parse_string_literal;
    
    unsigned char const separators_literals[] = {'[', ']', '{', '}', ',', ':'};
    for (usize i = 0u; i < sizeof(separators_literals) / sizeof(*separators_literals); ++i) {
        try_map_lexeme_to_token_mapping[separators_literals[i]] = &try_parse_separator_literal;
    }

    unsigned char const whitespaces_literals[] = {' ', '\t', '\n'};
    for (usize i = 0u; i < sizeof(whitespaces_literals) / sizeof(*whitespaces_literals); ++i) {
        try_map_lexeme_to_token_mapping[whitespaces_literals[i]] = &try_parse_whitespace_literal;
    }
    // null, false, true
    try_map_lexeme_to_token_mapping['n'] = &try_parse_null_literal;
    try_map_lexeme_to_token_mapping['f'] = &try_parse_false_literal;
    try_map_lexeme_to_token_mapping['t'] = &try_parse_true_literal;
}

struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE())
    JSON_LEXER_METHOD(PRIVATE(try_map_lexeme_to_token))(struct JSON_LEXER_TYPE() const* const this, usize* const count_read_bytes) {
    ASSERT(this);

    try_map_lexeme_to_token pmapper = try_map_lexeme_to_token_mapping[(unsigned char)*CSTRING_VIEW_METHOD(at)(&this->source, this->source_index)];

    if (!pmapper) {
        struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) result;
        OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), construct_at)(&result);
        return result;
    }

    return (*pmapper)(this->source, this->source_index, count_read_bytes);
}

static struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) try_parse_separator_literal(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes) {
    ASSERT(count_read_bytes);

    struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) result;
    OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), construct_at)(&result);

    struct JSON_LEXER_TOKEN_TYPE() token;
    JSON_LEXER_TOKEN_METHOD(construct_at)(&token);
    token.position = index;

    switch (*CSTRING_VIEW_METHOD(at)(&view, index)) {
        case '{': {
            token.token_type = JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_BEGIN);
        } break;
        case '}': {
            token.token_type = JSON_LEXER_TOKEN_ENUM_VALUE(OBJECT_END);
        } break;
        case '[': {
            token.token_type = JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_BEGIN);
        } break;
        case ']': {
            token.token_type = JSON_LEXER_TOKEN_ENUM_VALUE(ARRAY_END);
        } break;
        case ':': {
            token.token_type = JSON_LEXER_TOKEN_ENUM_VALUE(COLON_SEPARATOR);
        } break;
        case ',': {
            token.token_type = JSON_LEXER_TOKEN_ENUM_VALUE(COMMA_SEPARATOR);
        } break;
        default: {
            JSON_LEXER_TOKEN_METHOD(destroy_at)(&token);
            return result;
        }
    }

    OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), assign_move_from_value_at)(&result, &token);
    *count_read_bytes = 1u;
    JSON_LEXER_TOKEN_METHOD(destroy_at)(&token);

    return result;
}
static struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) try_parse_whitespace_literal(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes) {
    ASSERT(count_read_bytes);

    struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) result;
    OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), construct_at)(&result);

    struct JSON_LEXER_TOKEN_TYPE() token;
    JSON_LEXER_TOKEN_METHOD(construct_at)(&token);
    token.position = index;

    switch (*CSTRING_VIEW_METHOD(at)(&view, index)) {
        case '\t': case '\r': case '\n': case ' ': {
            token.token_type = JSON_LEXER_TOKEN_ENUM_VALUE(WHITESPACE);
            OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), assign_move_from_value_at)(&result, &token);
            *count_read_bytes = 1u;
        } break;
    }

    JSON_LEXER_TOKEN_METHOD(destroy_at)(&token);
    return result;
}

#define DEFINE_TRY_PARSE_LITERAL_FN(MODIFIER, LITERAL, TOKEN_ENUM_VALUE, TOKEN_BOOLEAN_VALUE)\
MODIFIER struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) TRY_PARSE_LITERAL_FN_(_ ## LITERAL)(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes) {\
    ASSERT(count_read_bytes);\
    \
    STRUCT_SUBTYPE(CSTRING_VIEW_TYPE(), char_type) const target_value[] = # LITERAL;\
    struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) result;\
    OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), construct_at)(&result);\
    struct CSTRING_VIEW_TYPE() target_view;\
    CSTRING_VIEW_METHOD(construct_from_buffer_at)(&target_view, target_value, sizeof(target_value) / sizeof(char) - 1u);\
    if (CSTRING_VIEW_METHOD(size)(&view) - index < CSTRING_VIEW_METHOD(size)(&target_view)) {\
        *count_read_bytes = 0u;\
        CSTRING_VIEW_METHOD(destroy_at)(&target_view);\
        return result;\
    }\
    for (usize i = 0u; i < CSTRING_VIEW_METHOD(size)(&target_view); ++i) {\
        if (*TYPE_METHOD(CSTRING_VIEW_TYPE(), at)(&view, index + i) == *CSTRING_VIEW_METHOD(at)(&target_view, i)) {\
            continue;\
        }\
        *count_read_bytes = i;\
        CSTRING_VIEW_METHOD(destroy_at)(&target_view);\
        return result;\
    }\
    *count_read_bytes = CSTRING_VIEW_METHOD(size)(&target_view);\
    struct JSON_LEXER_TOKEN_TYPE() token = {\
        .token_type = (TOKEN_ENUM_VALUE),\
        .boolean = (TOKEN_BOOLEAN_VALUE),\
        .position = index\
    };\
    OPTIONAL_METHOD(JSON_LEXER_TOKEN_TYPE(), assign_move_from_value_at)(&result, &token);\
    CSTRING_VIEW_METHOD(destroy_at)(&target_view);\
    JSON_LEXER_TOKEN_METHOD(destroy_at)(&token);\
    return result;\
}
DEFINE_TRY_PARSE_LITERAL_FN(static, null, JSON_LEXER_TOKEN_ENUM_VALUE(NULL_LITERAL), false)
DEFINE_TRY_PARSE_LITERAL_FN(static, false, JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL), false)
DEFINE_TRY_PARSE_LITERAL_FN(static, true, JSON_LEXER_TOKEN_ENUM_VALUE(BOOLEAN_LITERAL), true)

static struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) try_parse_number_literal(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes) {
    ASSERT(count_read_bytes);

    // number literal: .-({1-9}{0-9}*|0).\..{(e|E)(+|-){0-9}+}
    usize const string_view_size = TYPE_METHOD(CSTRING_VIEW_TYPE(), size)(&view);
    usize const start_index = index;
    struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) result;
    TYPE_METHOD(OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()), construct_at)(&result);
    enum State {
        TRY_READ_LITERALS_BEGIN, // (-|0|{1,9})
        TRY_READ_LEAD_DIGIT, // {0,9}
        TRY_READ_LEAD_DIGITS, // {0,9}*
        LEAD_DIGITS_READ, // lead digits were read
        START_READ_FRACTION, // '.' already read - fraction must be read now
        READ_FRACTION_DIGITS,
        START_READ_EXPONENT, // (e|E) already read - exponent must be read now (+|-)
        START_READ_EXPONENT_DIGITS, // (e|E)(+|-) already read - exponent digits must be read now
        READ_EXPONENT_DIGITS // try read next digits
    } current_state = TRY_READ_LITERALS_BEGIN;

    double buffer = 0;
    double fraction = 0;
    usize fraction_size = 0u, exponent_value = 0u;
    bool is_negative = false, is_exponent_negative = false;
    for (; index < string_view_size; ++index) {
        STRUCT_SUBTYPE(CSTRING_VIEW_TYPE(), char_type) const character = *CSTRING_VIEW_METHOD(at)(&view, index);
        if (current_state == TRY_READ_LITERALS_BEGIN) {
            if (character == '-') {
                is_negative = true;
                current_state = TRY_READ_LEAD_DIGIT;
                continue;
            }
            if (character == '0') {
                current_state = LEAD_DIGITS_READ;
                continue;
            }
            if ('1' <= character && character <= '9') {
                buffer = character - '0';
                current_state = TRY_READ_LEAD_DIGITS;
                continue;
            }
            // error
            goto parse_number_return_error;
        }
        if (current_state == TRY_READ_LEAD_DIGIT) {
            if (character == '0') {
                current_state = LEAD_DIGITS_READ;
                continue;
            }
            if ('1' <= character && character <= '9') {
                buffer = character - '0';
                current_state = TRY_READ_LEAD_DIGITS;
                continue;
            }
            // error
            goto parse_number_return_error;
        }
        if (current_state == TRY_READ_LEAD_DIGITS) {
            if (character == '.') {
                current_state = START_READ_FRACTION;
                continue;
            }
            if (character == 'e' || character == 'E') {
                current_state = START_READ_EXPONENT;
                continue;
            }
            if (NAMESPACE_UTILS_CHARACTER(is_digit)(character)) {
                buffer = buffer * 10 + (character - '0');
                continue;
            }
            goto parse_number_return_value;
        }
        if (current_state == LEAD_DIGITS_READ) {
            if (character == '.') {
                current_state = START_READ_FRACTION;
                continue;
            }
            if (character == 'e' || character == 'E') {
                current_state = START_READ_EXPONENT;
                continue;
            }
            goto parse_number_return_value;
        }
        if (current_state == START_READ_FRACTION) {
            if (NAMESPACE_UTILS_CHARACTER(is_digit)(character)) {
                fraction = character - '0';
                ++fraction_size;
                current_state = READ_FRACTION_DIGITS;
                continue;
            }
            // error
            goto parse_number_return_error;
        }
        if (current_state == READ_FRACTION_DIGITS) {
            if (NAMESPACE_UTILS_CHARACTER(is_digit)(character)) {
                fraction = fraction * 10 + (character - '0');
                ++fraction_size;
                current_state = READ_FRACTION_DIGITS;
                continue;
            }
            if (character == 'e' || character == 'E') {
                current_state = START_READ_EXPONENT;
                continue;
            }
            goto parse_number_return_value;
        }
        if (current_state == START_READ_EXPONENT) {
            if (character == '-') {
                is_exponent_negative = true;
                current_state = START_READ_EXPONENT_DIGITS;
                continue;
            }
            if (character == '+') {
                current_state = START_READ_EXPONENT_DIGITS;
                continue;
            }
            // error
            goto parse_number_return_error;
        }
        if (current_state == START_READ_EXPONENT_DIGITS) {
            if (NAMESPACE_UTILS_CHARACTER(is_digit)(character)) {
                exponent_value = (usize)(character - '0');
                current_state = READ_EXPONENT_DIGITS;
                continue;
            }
            // error
            goto parse_number_return_error;
        }
        if (current_state == READ_EXPONENT_DIGITS) {
            if (NAMESPACE_UTILS_CHARACTER(is_digit)(character)) {
                exponent_value = exponent_value * 10 + (usize)(character - '0');
                current_state = READ_EXPONENT_DIGITS;
                continue;
            }
            goto parse_number_return_value;
        }
        // error
        goto parse_number_return_error;
    }

    parse_number_return_value:

        // convert fraction leads digits to fraction part of buffer
        while (fraction_size--) {
            fraction /= 10;
        }
        buffer += fraction;

        // convert exponent_value to buffer's exponent
        if (is_exponent_negative) {
            while (exponent_value--) {
                buffer /= 10;
            }
        } else {
            while (exponent_value--) {
                buffer *= 10;
            }
        }

        // literal reading ends here
        if (is_negative) {
            buffer = -buffer;
        }

        {
            struct JSON_LEXER_TOKEN_TYPE() token = {
                .number = buffer,
                .token_type = JSON_LEXER_TOKEN_ENUM_VALUE(NUMBER_LITERAL),
                .position = start_index
            };

            TYPE_METHOD(OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()), assign_move_from_value_at)(&result, &token);

            JSON_LEXER_TOKEN_METHOD(destroy_at)(&token);
        }

    parse_number_return_error:
        *count_read_bytes = index - start_index;

    return result;
}

static struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) try_parse_string_literal(struct CSTRING_VIEW_TYPE() view, usize index, usize* const count_read_bytes) {
    ASSERT(count_read_bytes);

    // string literal: "..."
    usize const string_view_size = TYPE_METHOD(CSTRING_VIEW_TYPE(), size)(&view);
    usize const start_index = index;
    struct OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()) result;
    TYPE_METHOD(OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()), construct_at)(&result);
    enum State {
        TRY_READ_LITERALS_BEGIN,
        TRY_READ_ESCAPED_CHARACTERS_SEQUENCE,
        TRY_READ_UNICODE_CHARACTER_HEX_DIGITS,
        LITERALS_BEGIN_READ
    } current_state = TRY_READ_LITERALS_BEGIN;

    struct STRING_TYPE() buffer;
    TYPE_METHOD(STRING_TYPE(), construct_at)(&buffer);
    uint8 count_codepoints_read = 0u;
    while (index < string_view_size) {
        char32 unicode_character =
            NAMESPACE_UTILS_STRING(CONVERT(utf_codepoints, unicode_character))(
                TYPE_METHOD(CSTRING_VIEW_TYPE(), data)(&view) + index,
                &count_codepoints_read);
        if (count_codepoints_read > 4) {
            // error
            break;
        }
        index += count_codepoints_read;
        if (current_state == TRY_READ_LITERALS_BEGIN && unicode_character == '"') {
            current_state = LITERALS_BEGIN_READ;
            continue;
        }
        if (current_state == LITERALS_BEGIN_READ) {
            if (unicode_character == '\\') {
                current_state = TRY_READ_ESCAPED_CHARACTERS_SEQUENCE;
                continue;
            }
            // end of reading
            if (unicode_character == '"') {
                struct JSON_LEXER_TOKEN_TYPE() token = {
                    .token_type = JSON_LEXER_TOKEN_ENUM_VALUE(STRING_LITERAL),
                    .position = start_index
                };
                STRING_METHOD(construct_move_at)(&token.string, &buffer);
                TYPE_METHOD(OPTIONAL_TYPE(JSON_LEXER_TOKEN_TYPE()), assign_move_from_value_at)(&result, &token);
                JSON_LEXER_TOKEN_METHOD(destroy_at)(&token);
                break;
            }
            TYPE_METHOD(STRING_TYPE(), append_buffer)(&buffer,
                TYPE_METHOD(CSTRING_VIEW_TYPE(), data)(&view) + (index - count_codepoints_read),
                count_codepoints_read);
            continue;
        }
        if (current_state == TRY_READ_ESCAPED_CHARACTERS_SEQUENCE) {
            switch (unicode_character) {
            case '"': {
                TYPE_METHOD(STRING_TYPE(), push_back)(&buffer, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'"'});
                current_state = LITERALS_BEGIN_READ;
            } break;
            case '\\': {
                TYPE_METHOD(STRING_TYPE(), push_back)(&buffer, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'\\'});
                current_state = LITERALS_BEGIN_READ;
            } break;
            case '/': {
                TYPE_METHOD(STRING_TYPE(), push_back)(&buffer, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'/'});
                current_state = LITERALS_BEGIN_READ;
            } break;
            case 'b': {
                TYPE_METHOD(STRING_TYPE(), push_back)(&buffer, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'\b'});
                current_state = LITERALS_BEGIN_READ;
            } break;
            case 'f': {
                TYPE_METHOD(STRING_TYPE(), push_back)(&buffer, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'\f'});
                current_state = LITERALS_BEGIN_READ;
            } break;
            case 'n': {
                TYPE_METHOD(STRING_TYPE(), push_back)(&buffer, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'\n'});
                current_state = LITERALS_BEGIN_READ;
            } break;
            case 'r': {
                TYPE_METHOD(STRING_TYPE(), push_back)(&buffer, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'\r'});
                current_state = LITERALS_BEGIN_READ;
            } break;
            case 't': {
                TYPE_METHOD(STRING_TYPE(), push_back)(&buffer, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'\t'});
                current_state = LITERALS_BEGIN_READ;
            } break;
            case 'u': {
                current_state = TRY_READ_UNICODE_CHARACTER_HEX_DIGITS;
            } break;
            default:
                TYPE_METHOD(STRING_TYPE(), push_back)(&buffer, &(STRUCT_SUBTYPE(STRING_TYPE(), char_type)){'\\'});
                TYPE_METHOD(STRING_TYPE(), append_buffer)(&buffer,
                    TYPE_METHOD(CSTRING_VIEW_TYPE(), data)(&view) + (index - count_codepoints_read),
                    count_codepoints_read);
                current_state = LITERALS_BEGIN_READ;
                break;
            }
            continue;
        }
        if (current_state == TRY_READ_UNICODE_CHARACTER_HEX_DIGITS) {
            // TRY_READ_UNICODE_CHARACTER_HEX_DIGITS state comes from {'\', 'u' } read prefix 
            // NAMESPACE_UTILS_STRING(CONVERT(unicode_character_buffer, unicode_character)) could process surrogate pairs
            // to read it, we must provide unicode sequence from {'\', 'u' } prefix
            // to make it, we substruct it's length (= 2) from starting index 
            usize const shifted_by_prefix_index = index - 2u;
            struct OPTIONAL_TYPE(char32) value_opt =
                NAMESPACE_UTILS_STRING(CONVERT(unicode_character_buffer, unicode_character))(
                    TYPE_METHOD(CSTRING_VIEW_TYPE(), data)(&view) + shifted_by_prefix_index,
                    TYPE_METHOD(CSTRING_VIEW_TYPE(), size)(&view) - shifted_by_prefix_index);
            if (!TYPE_METHOD(OPTIONAL_TYPE(char32), has_value)(&value_opt)) {
                // error
                break;
            }
            char32 value = *TYPE_METHOD(OPTIONAL_TYPE(char32), value)(&value_opt);
            TYPE_METHOD(OPTIONAL_TYPE(char32), destroy_at)(&value_opt);
            // encode unicode symbol to utf-8 sequence
            char utf8_buffer[4];
            uint8 const read_codepoints_count = NAMESPACE_UTILS_STRING(CONVERT(unicode_character, utf_codepoints))(value, utf8_buffer);
            if (!read_codepoints_count) {
                // error
                break;
            }
            // push utf8 sequence to result buffer
            TYPE_METHOD(STRING_TYPE(), append_buffer)(&buffer, utf8_buffer, read_codepoints_count);
            // add encoding length to index
            // - if value >= 0x10000 => there was parsed surrogate pair, that consists of two utf16 encoded symbols
            index += 4u + (value >= 0x10000 ? 6u : 0u);
            current_state = LITERALS_BEGIN_READ;
            continue;
        }
        // error
        break;
    }

    *count_read_bytes = index - start_index;

    TYPE_METHOD(STRING_TYPE(), destroy_at)(&buffer);
    return result;
}
