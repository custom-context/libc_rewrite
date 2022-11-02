#include "format.h"

#include <utils/string/comparators_impl.h>
#include <utils/string/numeric_type_to_string_impl.h>

#include <utils/string/helpers.h>
#include <containers/vector.h>

#include <utils/macros.h>

#define NAMESPACE(NAME) utils__##NAME
#define LOCAL_NAMESPACE(NAME) NAMESPACE(format_string__##NAME)
#define UTILS_STR_NAMESPACE(NAME) NAMESPACE(string__##NAME)

#define STRUCT_FN(STRUCT_NAME, FN_NAME) CONCAT3(STRUCT_NAME, _, FN_NAME)

#define DECLARE(TYPE, NAME) DECLARE_##TYPE(NAME)
#define IMPLEMENT(TYPE, NAME) IMPLEMENT_##TYPE(NAME)

enum LOCAL_NAMESPACE(format_string_pattern_type) {
    ESCAPED_PERCENT,
    CHARACTER,
    NULL_TERMINATED_STRING,
    SIGNED_INTEGER_TO_DECIMAL
};

typedef struct LOCAL_NAMESPACE(pattern) {
    string_char _string_representation;
    enum LOCAL_NAMESPACE(format_string_pattern_type) _type;
} LOCAL_NAMESPACE(pattern);
#define PATTERN_FN(FN_NAME) STRUCT_FN(LOCAL_NAMESPACE(pattern), FN_NAME)

struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(construct_at)(struct LOCAL_NAMESPACE(pattern) * const this) {
    assert(this);
    return this;
}
struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(construct_copy_at)(struct LOCAL_NAMESPACE(pattern) * const this, struct LOCAL_NAMESPACE(pattern) const* const src) {
    assert(("`this` pointer must have non-nullable value", this));
    assert(src);
    string_char_construct_copy_at(&this->_string_representation, &src->_string_representation);
    this->_type = src->_type;
    return this;
}
void PATTERN_FN(destroy_at)(struct LOCAL_NAMESPACE(pattern) * const this) {
    assert(this);
    string_char_destroy_at(&this->_string_representation);
}

struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(construct_with_values_at)(struct LOCAL_NAMESPACE(pattern) * const this,
    enum LOCAL_NAMESPACE(format_string_pattern_type) type, char const* const pattern_string_representation) {
    string_char_construct_from_c_string_at(&this->_string_representation, pattern_string_representation);
    this->_type = type;
    return this;
}

DECLARE(VECTOR, LOCAL_NAMESPACE(pattern));
IMPLEMENT(VECTOR, LOCAL_NAMESPACE(pattern));
#define VECTOR_OF_PATTERNS CONCAT2(vector_, LOCAL_NAMESPACE(pattern))
#define VECTOR_OF_PATTERNS_FN(FN_NAME) CONCAT2(VECTOR_OF_PATTERNS, _##FN_NAME)

typedef struct LOCAL_NAMESPACE(patterns) {
    struct VECTOR_OF_PATTERNS _patterns;
} LOCAL_NAMESPACE(patterns);
#define PATTERNS_FN(FN_NAME) STRUCT_FN(LOCAL_NAMESPACE(patterns), FN_NAME)

struct LOCAL_NAMESPACE(patterns) * PATTERNS_FN(construct_at)(struct LOCAL_NAMESPACE(patterns) * const this) {
    VECTOR_OF_PATTERNS * patterns = &this->_patterns;

    VECTOR_OF_PATTERNS_FN(construct_at)(patterns);

    struct LOCAL_NAMESPACE(pattern) pattern;
    { // "%%"
        PATTERN_FN(construct_with_values_at)(&pattern, ESCAPED_PERCENT, "%%");
        VECTOR_OF_PATTERNS_FN(push_back)(patterns, &pattern);
        PATTERN_FN(destroy_at)(&pattern);
    }
    { // "%c"
        PATTERN_FN(construct_with_values_at)(&pattern, CHARACTER, "%c");
        VECTOR_OF_PATTERNS_FN(push_back)(patterns, &pattern);
        PATTERN_FN(destroy_at)(&pattern);
    }
    { // "%s"
        PATTERN_FN(construct_with_values_at)(&pattern, NULL_TERMINATED_STRING, "%s");
        VECTOR_OF_PATTERNS_FN(push_back)(patterns, &pattern);
        PATTERN_FN(destroy_at)(&pattern);
    }
    { // "%d"
        PATTERN_FN(construct_with_values_at)(&pattern, SIGNED_INTEGER_TO_DECIMAL, "%d");
        VECTOR_OF_PATTERNS_FN(push_back)(patterns, &pattern);
        PATTERN_FN(destroy_at)(&pattern);
    }
    { // "%i"
        PATTERN_FN(construct_with_values_at)(&pattern, SIGNED_INTEGER_TO_DECIMAL, "%i");
        VECTOR_OF_PATTERNS_FN(push_back)(patterns, &pattern);
        PATTERN_FN(destroy_at)(&pattern);
    }
    return this;
}
struct LOCAL_NAMESPACE(patterns) * PATTERNS_FN(destroy_at)(struct LOCAL_NAMESPACE(patterns) * const this) {
    assert(this);
    VECTOR_OF_PATTERNS * patterns = &this->_patterns;
    VECTOR_OF_PATTERNS_FN(destroy_at)(patterns);
    return this;
}

typedef struct LOCAL_NAMESPACE(format_string_pattern_occurrence_index) {
    LOCAL_NAMESPACE(pattern) const* _pattern;
    uint _index;
} LOCAL_NAMESPACE(format_string_pattern_occurrence_index);
struct LOCAL_NAMESPACE(format_string_pattern_occurrence_index) LOCAL_NAMESPACE(search_pattern_occurence)(char const* const format_string, LOCAL_NAMESPACE(patterns) const* const patterns) {
    LOCAL_NAMESPACE(format_string_pattern_occurrence_index) result = {._pattern = NULL, ._index = 0u};
    for (; format_string[result._index] != '\0'; ++result._index) {
        for (uint vec_index = 0u; vec_index < VECTOR_OF_PATTERNS_FN(size)(&patterns->_patterns); ++vec_index) {
            result._pattern = VECTOR_OF_PATTERNS_FN(at)(&patterns->_patterns, vec_index);
            if (!utils__string__compare_string_char_with_buffer(
                &result._pattern->_string_representation,
                string_char_size(&result._pattern->_string_representation),
                format_string + result._index)
            ) {
                return result;
            }
        }
    }
    result._pattern = NULL;
    return result;
}

struct string_char NAMESPACE(format)(char const* const format_string, ...) {
    va_list args;
    va_start(args, format_string);
    struct string_char result = NAMESPACE(va_format)(format_string, args);
    va_end(args);

    return result;
}

struct string_char NAMESPACE(va_format)(char const* const format_string, va_list args) {
    const uint format_string_size = UTILS_STR_NAMESPACE(string_length)(format_string);
    string_char formatted_string;
    string_char_construct_at(&formatted_string);

    struct LOCAL_NAMESPACE(patterns) patterns;
    PATTERNS_FN(construct_at)(&patterns);
    for (uint format_string_index = 0u; format_string[format_string_index] != '\0';) {
        // find index of first pattern occurrence & return pointer to pattern
        LOCAL_NAMESPACE(format_string_pattern_occurrence_index) pattern_n_index = LOCAL_NAMESPACE(search_pattern_occurence)(format_string + format_string_index, &patterns);
        // copy passed substring from format_string
        for (uint index = 0u; index < pattern_n_index._index; ++index, ++format_string_index) {
            string_char_push_back(&formatted_string, &format_string[format_string_index]);
        }
        LOCAL_NAMESPACE(pattern) const* const pattern = pattern_n_index._pattern;
        // stop if no patterns matched
        if (!pattern) {
            break;
        }
        switch (pattern->_type) {
            case ESCAPED_PERCENT: {
                char value = '%';
                string_char_push_back(&formatted_string, &value);
            } break;
            case CHARACTER: {
                char value = va_arg(args, int);
                string_char_push_back(&formatted_string, &value);
            } break;
            case NULL_TERMINATED_STRING: {
                char const* const null_terminated_string = va_arg(args, char*);
                for (uint index = 0u; null_terminated_string[index] != '\0'; ++index) {
                    string_char_push_back(&formatted_string, &null_terminated_string[index]);
                }
            } break;
            case SIGNED_INTEGER_TO_DECIMAL: {
                string_char result = utils__string__int_to_string_char(va_arg(args, int));
                for (uint index = 0u; index < string_char_size(&result); ++index) {
                    string_char_push_back(&formatted_string, string_char_at(&result, index));
                }
                string_char_destroy_at(&result);
            } break;
        }
        format_string_index += string_char_size(&pattern->_string_representation);
    }
    PATTERNS_FN(destroy_at)(&patterns);

    return formatted_string;
}
