#include "format.h"

#include <utils/string/helpers.h>
#include <containers/dynamic/array/array.h>

#include <utils/macros.h>

#define LOCAL_NAMESPACE(NAME) NAMESPACE_UTILS(format_string__##NAME)

#define STRUCT_FN(STRUCT_NAME, FN_NAME) TYPE_METHOD(STRUCT_NAME, FN_NAME)

enum LOCAL_NAMESPACE(format_string_pattern_type) {
    ESCAPED_PERCENT,
    CHARACTER,
    NULL_TERMINATED_STRING,
    SIGNED_INTEGER_TO_DECIMAL
};

typedef struct LOCAL_NAMESPACE(pattern) {
    struct WSTRING_TYPE() _string_representation;
    enum LOCAL_NAMESPACE(format_string_pattern_type) _type;
} LOCAL_NAMESPACE(pattern);
#define PATTERN_FN(FN_NAME) STRUCT_FN(LOCAL_NAMESPACE(pattern), FN_NAME)

static struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(construct_at)(struct LOCAL_NAMESPACE(pattern) * const this) {
    ASSERT(this);
    return this;
}
static struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(construct_copy_at)(struct LOCAL_NAMESPACE(pattern) * const this, struct LOCAL_NAMESPACE(pattern) const* const src) {
    ASSERT(this);
    ASSERT(src);
    WSTRING_METHOD(construct_copy_at)(&this->_string_representation, &src->_string_representation);
    this->_type = src->_type;
    return this;
}
static struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(construct_move_at)(struct LOCAL_NAMESPACE(pattern) * const this, struct LOCAL_NAMESPACE(pattern)* const src) {
    ASSERT(this);
    ASSERT(src);
    WSTRING_METHOD(construct_move_at)(&this->_string_representation, &src->_string_representation);
    this->_type = src->_type;
    return this;
}
static struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(assign_copy_at)(struct LOCAL_NAMESPACE(pattern) * const this, struct LOCAL_NAMESPACE(pattern) const* const src) {
    ASSERT(this);
    ASSERT(src);
    WSTRING_METHOD(assign_copy_at)(&this->_string_representation, &src->_string_representation);
    this->_type = src->_type;
    return this;
}
static struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(assign_move_at)(struct LOCAL_NAMESPACE(pattern) * const this, struct LOCAL_NAMESPACE(pattern)* const src) {
    ASSERT(this);
    ASSERT(src);
    WSTRING_METHOD(assign_move_at)(&this->_string_representation, &src->_string_representation);
    this->_type = src->_type;
    return this;
}
static void* PATTERN_FN(destroy_at)(struct LOCAL_NAMESPACE(pattern) * const this) {
    ASSERT(this);
    WSTRING_METHOD(destroy_at)(&this->_string_representation);
    return this;
}

static struct LOCAL_NAMESPACE(pattern)* PATTERN_FN(construct_with_values_at)(struct LOCAL_NAMESPACE(pattern) * const this,
    enum LOCAL_NAMESPACE(format_string_pattern_type) type, wchar const* const pattern_string_representation) {
    WSTRING_METHOD(construct_from_c_string_at)(&this->_string_representation, pattern_string_representation);
    this->_type = type;
    return this;
}

DEFINE_DEFAULT_ALLOCATOR_TYPE(LOCAL_NAMESPACE(pattern));
DEFINE_DEFAULT_ALLOCATOR_STATIC_METHODS(LOCAL_NAMESPACE(pattern))

DECLARE_DYNAMIC_ARRAY_TYPE(LOCAL_NAMESPACE(pattern));
DECLARE_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(LOCAL_NAMESPACE(pattern));
IMPLEMENT_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(LOCAL_NAMESPACE(pattern))

typedef struct LOCAL_NAMESPACE(patterns) {
    struct DYNAMIC_ARRAY_TYPE(LOCAL_NAMESPACE(pattern)) _patterns;
} LOCAL_NAMESPACE(patterns);
#define PATTERNS_FN(FN_NAME) STRUCT_FN(LOCAL_NAMESPACE(patterns), FN_NAME)

static struct LOCAL_NAMESPACE(patterns) * PATTERNS_FN(construct_at)(struct LOCAL_NAMESPACE(patterns) * const this) {
    struct DYNAMIC_ARRAY_TYPE(LOCAL_NAMESPACE(pattern)) * patterns = &this->_patterns;

    DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), construct_at)(patterns);

    struct LOCAL_NAMESPACE(pattern) pattern;
    { // "%%"
        PATTERN_FN(construct_with_values_at)(&pattern, ESCAPED_PERCENT, L"%%");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
    }
    { // "%c"
        PATTERN_FN(construct_with_values_at)(&pattern, CHARACTER, L"%c");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
    }
    { // "%s"
        PATTERN_FN(construct_with_values_at)(&pattern, NULL_TERMINATED_STRING, L"%s");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
    }
    { // "%d"
        PATTERN_FN(construct_with_values_at)(&pattern, SIGNED_INTEGER_TO_DECIMAL, L"%d");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
    }
    { // "%i"
        PATTERN_FN(construct_with_values_at)(&pattern, SIGNED_INTEGER_TO_DECIMAL, L"%i");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
    }
    return this;
}
static void* PATTERNS_FN(destroy_at)(struct LOCAL_NAMESPACE(patterns) * const this) {
    ASSERT(this);
    struct DYNAMIC_ARRAY_TYPE(LOCAL_NAMESPACE(pattern)) * patterns = &this->_patterns;
    DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), destroy_at)(patterns);
    return this;
}

typedef struct LOCAL_NAMESPACE(format_string_pattern_occurrence_index) {
    LOCAL_NAMESPACE(pattern) const* _pattern;
    uint _index;
} LOCAL_NAMESPACE(format_string_pattern_occurrence_index);
static struct LOCAL_NAMESPACE(format_string_pattern_occurrence_index) LOCAL_NAMESPACE(search_pattern_occurence)(wchar const* const format_string, LOCAL_NAMESPACE(patterns) const* const patterns) {
    LOCAL_NAMESPACE(format_string_pattern_occurrence_index) result = {._pattern = NULL, ._index = 0u};
    for (; format_string[result._index] != (wchar)'\0'; ++result._index) {
        for (uint vec_index = 0u; vec_index < DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), size)(&patterns->_patterns); ++vec_index) {
            result._pattern = DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), at)(&patterns->_patterns, vec_index);
            struct WSTRING_TYPE() temporary;
            TYPE_METHOD(WSTRING_TYPE(), construct_from_buffer_at)(&temporary, WSTRING_METHOD(size)(&result._pattern->_string_representation), format_string + result._index);
            if (!STRING_FUNCTION(WSTRING_TYPE(), compare)(&result._pattern->_string_representation, &temporary)) {
                TYPE_METHOD(WSTRING_TYPE(), destroy_at)(&temporary);
                return result;
            }
            TYPE_METHOD(WSTRING_TYPE(), destroy_at)(&temporary);
        }
    }
    result._pattern = NULL;
    return result;
}

struct WSTRING_TYPE() NAMESPACE_UTILS(wformat)(wchar const* const format_string, ...) {
    va_list args;
    va_start(args, format_string);
    struct WSTRING_TYPE() result = NAMESPACE_UTILS(va_wformat)(format_string, args);
    va_end(args);

    return result;
}

struct WSTRING_TYPE() NAMESPACE_UTILS(va_wformat)(wchar const* const format_string, va_list args) {
    struct WSTRING_TYPE() formatted_string;
    WSTRING_METHOD(construct_at)(&formatted_string);

    struct LOCAL_NAMESPACE(patterns) patterns;
    PATTERNS_FN(construct_at)(&patterns);
    for (uint format_string_index = 0u; format_string[format_string_index] != (wchar)'\0';) {
        // find index of first pattern occurrence & return pointer to pattern
        LOCAL_NAMESPACE(format_string_pattern_occurrence_index) pattern_n_index = LOCAL_NAMESPACE(search_pattern_occurence)(format_string + format_string_index, &patterns);
        // copy passed substring from format_string
        for (uint index = 0u; index < pattern_n_index._index; ++index, ++format_string_index) {
            WSTRING_METHOD(push_back)(&formatted_string, &format_string[format_string_index]);
        }
        LOCAL_NAMESPACE(pattern) const* const pattern = pattern_n_index._pattern;
        // stop if no patterns matched
        if (!pattern) {
            break;
        }
        switch (pattern->_type) {
            case ESCAPED_PERCENT: {
                wchar value = '%';
                WSTRING_METHOD(push_back)(&formatted_string, &value);
            } break;
            case CHARACTER: {
                wchar value = (wchar)va_arg(args, int);
                WSTRING_METHOD(push_back)(&formatted_string, &value);
            } break;
            case NULL_TERMINATED_STRING: {
                wchar const* const null_terminated_string = va_arg(args, wchar*);
                for (uint index = 0u; null_terminated_string[index] != (wchar)'\0'; ++index) {
                    WSTRING_METHOD(push_back)(&formatted_string, &null_terminated_string[index]);
                }
            } break;
            case SIGNED_INTEGER_TO_DECIMAL: {
                int const value = va_arg(args, int);
                struct WSTRING_TYPE() result = NAMESPACE_UTILS_STRING(CONVERT(int, WSTRING_TYPE()))(&value);
                for (uint index = 0u; index < WSTRING_METHOD(size)(&result); ++index) {
                    WSTRING_METHOD(push_back)(&formatted_string, WSTRING_METHOD(at)(&result, index));
                }
                WSTRING_METHOD(destroy_at)(&result);
            } break;
        }
        format_string_index += WSTRING_METHOD(size)(&pattern->_string_representation);
    }
    PATTERNS_FN(destroy_at)(&patterns);

    return formatted_string;
}
