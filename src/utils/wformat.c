#include "format.h"

#include <containers/static/string_view/string_view.h>
#include <utils/string/helpers.h>
#include <containers/dynamic/array/array.h>

#include <utils/macros.h>

#define LOCAL_NAMESPACE(NAME) NAMESPACE_UTILS(CONCAT3(format_string, __, NAME))

#define PATTERN_ENUM_TYPE() LOCAL_NAMESPACE(ENUM_TYPE(pattern))
#define PATTERN_ENUM_VALUE(VALUE) ENUM_VALUE(PATTERN_ENUM_TYPE(), VALUE)

typedef enum PATTERN_ENUM_TYPE() {
    PATTERN_ENUM_VALUE(ESCAPED_PERCENT) = 0u,
    PATTERN_ENUM_VALUE(CHARACTER),
    PATTERN_ENUM_VALUE(NULL_TERMINATED_STRING),
    PATTERN_ENUM_VALUE(STRING_VIEW),
    PATTERN_ENUM_VALUE(USIZE_TO_DECIMAL),
    PATTERN_ENUM_VALUE(INT_TO_DECIMAL),
    PATTERN_ENUM_VALUE(DOUBLE)
} PATTERN_ENUM_TYPE();

typedef struct LOCAL_NAMESPACE(pattern) {
    struct WSTRING_VIEW_TYPE() view;
    enum PATTERN_ENUM_TYPE() type;
} LOCAL_NAMESPACE(pattern);

#define PATTERN_METHOD(FN_NAME) TYPE_METHOD(LOCAL_NAMESPACE(pattern), FN_NAME)

static struct LOCAL_NAMESPACE(pattern)* PATTERN_METHOD(construct_at)(struct LOCAL_NAMESPACE(pattern) * const this) {
    ASSERT(this);
    ASSERT(false);
    return this;
}
static struct LOCAL_NAMESPACE(pattern)* PATTERN_METHOD(construct_copy_at)(struct LOCAL_NAMESPACE(pattern) * const this, struct LOCAL_NAMESPACE(pattern) const* const src) {
    ASSERT(this);
    ASSERT(src);
    WSTRING_VIEW_METHOD(construct_copy_at)(&this->view, &src->view);
    this->type = src->type;
    return this;
}
static struct LOCAL_NAMESPACE(pattern)* PATTERN_METHOD(construct_move_at)(struct LOCAL_NAMESPACE(pattern) * const this, struct LOCAL_NAMESPACE(pattern)* const src) {
    ASSERT(this);
    ASSERT(src);
    WSTRING_VIEW_METHOD(construct_move_at)(&this->view, &src->view);
    this->type = src->type;
    return this;
}
static struct LOCAL_NAMESPACE(pattern)* PATTERN_METHOD(assign_copy_at)(struct LOCAL_NAMESPACE(pattern) * const this, struct LOCAL_NAMESPACE(pattern) const* const src) {
    ASSERT(this);
    ASSERT(src);
    WSTRING_VIEW_METHOD(assign_copy_at)(&this->view, &src->view);
    this->type = src->type;
    return this;
}
static struct LOCAL_NAMESPACE(pattern)* PATTERN_METHOD(assign_move_at)(struct LOCAL_NAMESPACE(pattern) * const this, struct LOCAL_NAMESPACE(pattern)* const src) {
    ASSERT(this);
    ASSERT(src);
    WSTRING_VIEW_METHOD(assign_move_at)(&this->view, &src->view);
    this->type = src->type;
    return this;
}
static void* PATTERN_METHOD(destroy_at)(struct LOCAL_NAMESPACE(pattern) * const this) {
    ASSERT(this);
    WSTRING_VIEW_METHOD(destroy_at)(&this->view);
    return this;
}

static struct LOCAL_NAMESPACE(pattern)* PATTERN_METHOD(construct_with_values_at)(struct LOCAL_NAMESPACE(pattern) * const this,
    enum PATTERN_ENUM_TYPE() type, wchar const* const pattern_string_representation) {
    WSTRING_VIEW_METHOD(construct_from_raw_string_at)(&this->view, pattern_string_representation);
    this->type = type;
    return this;
}

DEFINE_DEFAULT_ALLOCATOR_TYPE(LOCAL_NAMESPACE(pattern));
DEFINE_DEFAULT_ALLOCATOR_STATIC_METHODS(LOCAL_NAMESPACE(pattern))

DECLARE_DYNAMIC_ARRAY_TYPE(LOCAL_NAMESPACE(pattern));
DECLARE_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(LOCAL_NAMESPACE(pattern));
IMPLEMENT_DYNAMIC_ARRAY_TYPE_STATIC_METHODS(LOCAL_NAMESPACE(pattern))

static void initialize_patterns(struct DYNAMIC_ARRAY_TYPE(LOCAL_NAMESPACE(pattern))* const patterns) {
    ASSERT(patterns);

    struct LOCAL_NAMESPACE(pattern) pattern;
    { // "%%"
        PATTERN_METHOD(construct_with_values_at)(&pattern, PATTERN_ENUM_VALUE(ESCAPED_PERCENT), L"%%");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
        PATTERN_METHOD(destroy_at)(&pattern);
    }
    { // "%c"
        PATTERN_METHOD(construct_with_values_at)(&pattern, PATTERN_ENUM_VALUE(CHARACTER), L"%c");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
        PATTERN_METHOD(destroy_at)(&pattern);
    }
    { // "%s"
        PATTERN_METHOD(construct_with_values_at)(&pattern, PATTERN_ENUM_VALUE(NULL_TERMINATED_STRING), L"%s");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
        PATTERN_METHOD(destroy_at)(&pattern);
    }
    { // "%vs"
        PATTERN_METHOD(construct_with_values_at)(&pattern, PATTERN_ENUM_VALUE(STRING_VIEW), L"%vs");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
        PATTERN_METHOD(destroy_at)(&pattern);
    }
    { // "%d"
        PATTERN_METHOD(construct_with_values_at)(&pattern, PATTERN_ENUM_VALUE(INT_TO_DECIMAL), L"%d");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
        PATTERN_METHOD(destroy_at)(&pattern);
    }
    { // "%zu"
        PATTERN_METHOD(construct_with_values_at)(&pattern, PATTERN_ENUM_VALUE(USIZE_TO_DECIMAL), L"%zu");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
        PATTERN_METHOD(destroy_at)(&pattern);
    }
    { // "%i"
        PATTERN_METHOD(construct_with_values_at)(&pattern, PATTERN_ENUM_VALUE(INT_TO_DECIMAL), L"%i");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
        PATTERN_METHOD(destroy_at)(&pattern);
    }
    { // "%lf"
        PATTERN_METHOD(construct_with_values_at)(&pattern, PATTERN_ENUM_VALUE(DOUBLE), L"%lf");
        DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), push_back_by_moving)(patterns, &pattern);
        PATTERN_METHOD(destroy_at)(&pattern);
    }
}

typedef struct LOCAL_NAMESPACE(format_string_pattern_occurrence_index) {
    LOCAL_NAMESPACE(pattern) const* ppattern;
    usize index;
} LOCAL_NAMESPACE(format_string_pattern_occurrence_index);

static struct LOCAL_NAMESPACE(format_string_pattern_occurrence_index)
    LOCAL_NAMESPACE(search_pattern_occurence)(
        struct WSTRING_VIEW_TYPE() const* const pformat_string_view,
        usize const format_string_view_start_index,
        struct DYNAMIC_ARRAY_TYPE(LOCAL_NAMESPACE(pattern)) const* const ppatterns) {
    LOCAL_NAMESPACE(format_string_pattern_occurrence_index) result = {
        .ppattern = NULL
    };

    // TODO: replace to aho-corasick algo
    for (result.index = format_string_view_start_index; result.index < WSTRING_VIEW_METHOD(size)(pformat_string_view); ++result.index) {
        for (usize vec_index = 0u; vec_index < DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), size)(ppatterns); ++vec_index) {
            result.ppattern = DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), at)(ppatterns, vec_index);

            struct WSTRING_VIEW_TYPE() temporary;
            usize const window_size =
                (WSTRING_VIEW_METHOD(size)(&result.ppattern->view) < WSTRING_VIEW_METHOD(size)(pformat_string_view) - result.index) ?
                    WSTRING_VIEW_METHOD(size)(&result.ppattern->view) :
                    (WSTRING_VIEW_METHOD(size)(pformat_string_view) - result.index)
            ;
            TYPE_METHOD(WSTRING_VIEW_TYPE(), construct_from_buffer_at)(&temporary,
                WSTRING_VIEW_METHOD(data)(pformat_string_view) + result.index, window_size);

            if (!STRING_FUNCTION(WSTRING_VIEW_TYPE(), compare)(&result.ppattern->view, &temporary)) {
                TYPE_METHOD(WSTRING_VIEW_TYPE(), destroy_at)(&temporary);
                return result;
            }
            TYPE_METHOD(WSTRING_VIEW_TYPE(), destroy_at)(&temporary);
        }
    }
    result.ppattern = NULL;
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
    struct WSTRING_VIEW_TYPE() format_string_view;
    WSTRING_VIEW_METHOD(construct_from_raw_string_at)(&format_string_view, format_string);

    struct WSTRING_TYPE() formatted_string;
    WSTRING_METHOD(construct_at)(&formatted_string);
    WSTRING_METHOD(reserve)(&formatted_string, WSTRING_VIEW_METHOD(size)(&format_string_view));

    struct DYNAMIC_ARRAY_TYPE(LOCAL_NAMESPACE(pattern)) patterns;
    DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), construct_at)(&patterns);
    initialize_patterns(&patterns);
    for (usize format_string_index = 0u; format_string_index < WSTRING_VIEW_METHOD(size)(&format_string_view);) {
        // find index of first pattern occurrence & return pointer to pattern
        LOCAL_NAMESPACE(format_string_pattern_occurrence_index) pattern_n_index =
            LOCAL_NAMESPACE(search_pattern_occurence)(&format_string_view, format_string_index, &patterns);

        // copy passed substring from format_string before first found pattern
        WSTRING_METHOD(append_buffer)(&formatted_string,
            WSTRING_VIEW_METHOD(data)(&format_string_view) + format_string_index,
            pattern_n_index.index - format_string_index);

        format_string_index = pattern_n_index.index;
        LOCAL_NAMESPACE(pattern) const* const ppattern = pattern_n_index.ppattern;

        // stop if no pattern was matched
        if (!ppattern) {
            break;
        }
        switch (ppattern->type) {
            case PATTERN_ENUM_VALUE(ESCAPED_PERCENT): {
                wchar value = L'%';
                WSTRING_METHOD(push_back)(&formatted_string, &value);
            } break;
            case PATTERN_ENUM_VALUE(CHARACTER): {
                wchar value = (wchar)va_arg(args, int);
                WSTRING_METHOD(push_back)(&formatted_string, &value);
            } break;
            case PATTERN_ENUM_VALUE(NULL_TERMINATED_STRING): {
                wchar const* const null_terminated_string = va_arg(args, wchar const*);
                for (usize index = 0u; null_terminated_string[index] != L'\0'; ++index) {
                    WSTRING_METHOD(push_back)(&formatted_string, &null_terminated_string[index]);
                }
            } break;
            case PATTERN_ENUM_VALUE(STRING_VIEW): {
                struct WSTRING_VIEW_TYPE() const* const view = va_arg(args, WSTRING_VIEW_TYPE() const*);
                for (usize index = 0u; index < WSTRING_VIEW_METHOD(size)(view); ++index) {
                    WSTRING_METHOD(push_back)(&formatted_string, WSTRING_VIEW_METHOD(at)(view, index));
                }
            } break;
            case PATTERN_ENUM_VALUE(USIZE_TO_DECIMAL): {
                usize const value = va_arg(args, usize);
                struct WSTRING_TYPE() result = NAMESPACE_UTILS_STRING(CONVERT(usize, WSTRING_TYPE()))(&value);
                for (usize index = 0u; index < WSTRING_METHOD(size)(&result); ++index) {
                    WSTRING_METHOD(push_back)(&formatted_string, WSTRING_METHOD(at)(&result, index));
                }
                WSTRING_METHOD(destroy_at)(&result);
            } break;
            case PATTERN_ENUM_VALUE(INT_TO_DECIMAL): {
                int const value = va_arg(args, int);
                struct WSTRING_TYPE() result = NAMESPACE_UTILS_STRING(CONVERT(int, WSTRING_TYPE()))(&value);
                for (usize index = 0u; index < WSTRING_METHOD(size)(&result); ++index) {
                    WSTRING_METHOD(push_back)(&formatted_string, WSTRING_METHOD(at)(&result, index));
                }
                WSTRING_METHOD(destroy_at)(&result);
            } break;
            case PATTERN_ENUM_VALUE(DOUBLE): {
                double const value = va_arg(args, double);
                struct WSTRING_TYPE() result = NAMESPACE_UTILS_STRING(CONVERT(double, WSTRING_TYPE()))(&value);
                for (usize index = 0u; index < WSTRING_METHOD(size)(&result); ++index) {
                    WSTRING_METHOD(push_back)(&formatted_string, WSTRING_METHOD(at)(&result, index));
                }
                WSTRING_METHOD(destroy_at)(&result);
            } break;
            default: {
                // error
                ASSERT(false && "Unhandled pattern type");
            } break;
        }
        format_string_index += WSTRING_VIEW_METHOD(size)(&ppattern->view);
    }

    DYNAMIC_ARRAY_METHOD(LOCAL_NAMESPACE(pattern), destroy_at)(&patterns);
    WSTRING_VIEW_METHOD(destroy_at)(&format_string_view);
    return formatted_string;
}
