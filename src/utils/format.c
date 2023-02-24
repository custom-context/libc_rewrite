#include "format.h"

#include <utils/string/comparators_impl.h>
#include <utils/string/numeric_type_to_string_impl.h>

#include <utils/string/helpers.h>
#include <containers/dynamic/vector/vector.h>

#include <utils/macros.h>

#define NAMESPACE(NAME) utils__##NAME
#define LOCAL_NAMESPACE(NAME) NAMESPACE(format_string__##NAME)
#define UTILS_STR_NAMESPACE(NAME) NAMESPACE(string__##NAME)

#define STRUCT_FN(STRUCT_NAME, FN_NAME) TYPE_METHOD(STRUCT_NAME, FN_NAME)

enum LOCAL_NAMESPACE(format_string_pattern_type) {
    ESCAPED_PERCENT,
    CHARACTER,
    NULL_TERMINATED_STRING,
    SIGNED_INTEGER_TO_DECIMAL
};

typedef struct LOCAL_NAMESPACE(pattern) {
    struct STRING_TYPE() _string_representation;
    enum LOCAL_NAMESPACE(format_string_pattern_type) _type;
} LOCAL_NAMESPACE(pattern);
#define PATTERN_FN(FN_NAME) STRUCT_FN(LOCAL_NAMESPACE(pattern), FN_NAME)

struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(construct_at)(struct LOCAL_NAMESPACE(pattern) * const this) {
    ASSERT(this);
    return this;
}
struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(construct_copy_at)(struct LOCAL_NAMESPACE(pattern) * const this, struct LOCAL_NAMESPACE(pattern) const* const src) {
    ASSERT(this);
    ASSERT(src);
    STRING_METHOD(construct_copy_at)(&this->_string_representation, &src->_string_representation);
    this->_type = src->_type;
    return this;
}
void* PATTERN_FN(destroy_at)(struct LOCAL_NAMESPACE(pattern) * const this) {
    ASSERT(this);
    STRING_METHOD(destroy_at)(&this->_string_representation);
    return this;
}

struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(construct_with_values_at)(struct LOCAL_NAMESPACE(pattern) * const this,
    enum LOCAL_NAMESPACE(format_string_pattern_type) type, char const* const pattern_string_representation) {
    STRING_METHOD(construct_from_c_string_at)(&this->_string_representation, pattern_string_representation);
    this->_type = type;
    return this;
}

DECLARE_VECTOR(LOCAL_NAMESPACE(pattern));
IMPLEMENT_VECTOR(LOCAL_NAMESPACE(pattern));

typedef struct LOCAL_NAMESPACE(patterns) {
    struct VECTOR_TYPE(LOCAL_NAMESPACE(pattern)) _patterns;
} LOCAL_NAMESPACE(patterns);
#define PATTERNS_FN(FN_NAME) STRUCT_FN(LOCAL_NAMESPACE(patterns), FN_NAME)

struct LOCAL_NAMESPACE(patterns) * PATTERNS_FN(construct_at)(struct LOCAL_NAMESPACE(patterns) * const this) {
    struct VECTOR_TYPE(LOCAL_NAMESPACE(pattern)) * patterns = &this->_patterns;

    VECTOR_METHOD(LOCAL_NAMESPACE(pattern), construct_at)(patterns);

    struct LOCAL_NAMESPACE(pattern) pattern;
    { // "%%"
        PATTERN_FN(construct_with_values_at)(&pattern, ESCAPED_PERCENT, "%%");
        VECTOR_METHOD(LOCAL_NAMESPACE(pattern), push_back)(patterns, &pattern);
        PATTERN_FN(destroy_at)(&pattern);
    }
    { // "%c"
        PATTERN_FN(construct_with_values_at)(&pattern, CHARACTER, "%c");
        VECTOR_METHOD(LOCAL_NAMESPACE(pattern), push_back)(patterns, &pattern);
        PATTERN_FN(destroy_at)(&pattern);
    }
    { // "%s"
        PATTERN_FN(construct_with_values_at)(&pattern, NULL_TERMINATED_STRING, "%s");
        VECTOR_METHOD(LOCAL_NAMESPACE(pattern), push_back)(patterns, &pattern);
        PATTERN_FN(destroy_at)(&pattern);
    }
    { // "%d"
        PATTERN_FN(construct_with_values_at)(&pattern, SIGNED_INTEGER_TO_DECIMAL, "%d");
        VECTOR_METHOD(LOCAL_NAMESPACE(pattern), push_back)(patterns, &pattern);
        PATTERN_FN(destroy_at)(&pattern);
    }
    { // "%i"
        PATTERN_FN(construct_with_values_at)(&pattern, SIGNED_INTEGER_TO_DECIMAL, "%i");
        VECTOR_METHOD(LOCAL_NAMESPACE(pattern), push_back)(patterns, &pattern);
        PATTERN_FN(destroy_at)(&pattern);
    }
    return this;
}
void* PATTERNS_FN(destroy_at)(struct LOCAL_NAMESPACE(patterns) * const this) {
    ASSERT(this);
    struct VECTOR_TYPE(LOCAL_NAMESPACE(pattern)) * patterns = &this->_patterns;
    VECTOR_METHOD(LOCAL_NAMESPACE(pattern), destroy_at)(patterns);
    return this;
}

typedef struct LOCAL_NAMESPACE(format_string_pattern_occurrence_index) {
    LOCAL_NAMESPACE(pattern) const* _pattern;
    uint _index;
} LOCAL_NAMESPACE(format_string_pattern_occurrence_index);
struct LOCAL_NAMESPACE(format_string_pattern_occurrence_index) LOCAL_NAMESPACE(search_pattern_occurence)(char const* const format_string, LOCAL_NAMESPACE(patterns) const* const patterns) {
    LOCAL_NAMESPACE(format_string_pattern_occurrence_index) result = {._pattern = NULL, ._index = 0u};
    for (; format_string[result._index] != '\0'; ++result._index) {
        for (uint vec_index = 0u; vec_index < VECTOR_METHOD(LOCAL_NAMESPACE(pattern), size)(&patterns->_patterns); ++vec_index) {
            result._pattern = VECTOR_METHOD(LOCAL_NAMESPACE(pattern), at)(&patterns->_patterns, vec_index);
            if (!NAMESPACE_UTILS_STRING(COMPARE_FUNCTION(STRING_TYPE(), buffer))(
                &result._pattern->_string_representation,
                STRING_METHOD(size)(&result._pattern->_string_representation),
                format_string + result._index)
            ) {
                return result;
            }
        }
    }
    result._pattern = NULL;
    return result;
}

struct STRING_TYPE() NAMESPACE(format)(char const* const format_string, ...) {
    va_list args;
    va_start(args, format_string);
    struct STRING_TYPE() result = NAMESPACE(va_format)(format_string, args);
    va_end(args);

    return result;
}

struct STRING_TYPE() NAMESPACE(va_format)(char const* const format_string, va_list args) {
    struct STRING_TYPE() formatted_string;
    STRING_METHOD(construct_at)(&formatted_string);

    struct LOCAL_NAMESPACE(patterns) patterns;
    PATTERNS_FN(construct_at)(&patterns);
    for (uint format_string_index = 0u; format_string[format_string_index] != '\0';) {
        // find index of first pattern occurrence & return pointer to pattern
        LOCAL_NAMESPACE(format_string_pattern_occurrence_index) pattern_n_index = LOCAL_NAMESPACE(search_pattern_occurence)(format_string + format_string_index, &patterns);
        // copy passed substring from format_string
        for (uint index = 0u; index < pattern_n_index._index; ++index, ++format_string_index) {
            STRING_METHOD(push_back)(&formatted_string, &format_string[format_string_index]);
        }
        LOCAL_NAMESPACE(pattern) const* const pattern = pattern_n_index._pattern;
        // stop if no patterns matched
        if (!pattern) {
            break;
        }
        switch (pattern->_type) {
            case ESCAPED_PERCENT: {
                char value = '%';
                STRING_METHOD(push_back)(&formatted_string, &value);
            } break;
            case CHARACTER: {
                char value = va_arg(args, int);
                STRING_METHOD(push_back)(&formatted_string, &value);
            } break;
            case NULL_TERMINATED_STRING: {
                char const* const null_terminated_string = va_arg(args, char*);
                for (uint index = 0u; null_terminated_string[index] != '\0'; ++index) {
                    STRING_METHOD(push_back)(&formatted_string, &null_terminated_string[index]);
                }
            } break;
            case SIGNED_INTEGER_TO_DECIMAL: {
                struct STRING_TYPE() result = NAMESPACE_UTILS_STRING(CONVERT_FUNCTION(int, STRING_TYPE()))(va_arg(args, int));
                for (uint index = 0u; index < STRING_METHOD(size)(&result); ++index) {
                    STRING_METHOD(push_back)(&formatted_string, STRING_METHOD(at)(&result, index));
                }
                STRING_METHOD(destroy_at)(&result);
            } break;
        }
        format_string_index += STRING_METHOD(size)(&pattern->_string_representation);
    }
    PATTERNS_FN(destroy_at)(&patterns);

    return formatted_string;
}
