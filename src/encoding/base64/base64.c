#include "base64.h"

IMPLEMENT_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS_WITH_MODIFIER(, uint8, DEFAULT_ALLOCATOR_TYPE(uint8))

enum {
    window_size = 6u,
    bits_in_block = sizeof(uint8) * CHAR_BIT,
};

typedef struct BitsReader {
    uint8 const* source;
    usize source_size;
    usize source_index;

    uint8 window_size;
    uint8 bits_shift;
} BitsReader;

static struct BitsReader* TYPE_METHOD(BitsReader, construct_custom_at)(BitsReader* const this,
    uint8 const* const source, usize const source_size);
static uint8 TYPE_METHOD(BitsReader, next)(struct BitsReader* const this);
static struct BitsReader TYPE_METHOD(BitsReader, end)(struct BitsReader const* const this);
static bool TYPE_METHOD(BitsReader, are_equals)(struct BitsReader const* const this, struct BitsReader const* const source);
static void* TYPE_METHOD(BitsReader, destroy_at)(BitsReader* const this);

static STRUCT_SUBTYPE(STRING_TYPE(), char_type) code_to_letter(uint8 code);

struct STRING_TYPE() NAMESPACE_ENCODING_BASE64(encode)(uint8 const* const source, usize source_size) {
    ASSERT(source);
    struct STRING_TYPE() result;
    TYPE_METHOD(STRING_TYPE(), construct_at)(&result);

    TYPE_METHOD(STRING_TYPE(), reserve)(&result, source_size * (sizeof(uint8) * CHAR_BIT) / window_size);

    struct BitsReader bits_reader;
    TYPE_METHOD(BitsReader, construct_custom_at)(&bits_reader, source, source_size);

    struct BitsReader end_value = TYPE_METHOD(BitsReader, end)(&bits_reader);
    while (!TYPE_METHOD(BitsReader, are_equals)(&bits_reader, &end_value)) {
        char value = code_to_letter(TYPE_METHOD(BitsReader, next)(&bits_reader));
        TYPE_METHOD(STRING_TYPE(), push_back)(&result, &value);
    }

    TYPE_METHOD(BitsReader, destroy_at)(&bits_reader);

    return result;
}

static uint8 letter_to_code(STRUCT_SUBTYPE(STRING_TYPE(), char_type) letter);

struct DYNAMIC_ARRAY_TYPE(uint8) NAMESPACE_ENCODING_BASE64(decode)(char const* const source, usize source_size) {
    ASSERT(source);
    struct DYNAMIC_ARRAY_TYPE(uint8) result;
    TYPE_METHOD(DYNAMIC_ARRAY_TYPE(uint8), construct_at)(&result);
    TYPE_METHOD(DYNAMIC_ARRAY_TYPE(uint8), reserve)(&result, source_size * window_size / bits_in_block);

    uint8 result_bits_shift = 0u;
    uint8 value = 0u;
    for (usize source_index = 0u; source_index < source_size; ++source_index) {
        uint8 code = letter_to_code(source[source_index]);
        if (source[source_index] == '=') {
            if (!result_bits_shift) {
                ASSERT(false);
                return result;
            }
            // skip all paddings & continue
            do {
                ++source_index;
                result_bits_shift = (result_bits_shift + window_size) % bits_in_block;
            } while (result_bits_shift && source_index < source_size && source[source_index] == '=');
            if (result_bits_shift && (source_index >= source_size || source[source_index] != '=')) {
                ASSERT(false);
                return result;
            }
            if (!result_bits_shift && (source_index < source_size && source[source_index] == '=')) {
                ASSERT(false);
                return result;
            }
            // decrement source_index for for-loop internal incrementation
            --source_index;
            continue;
        }
        if ((bits_in_block - window_size) > result_bits_shift) {
            value |= code << ((bits_in_block - window_size) - result_bits_shift);
        } else {
            value |= code >> (result_bits_shift - (bits_in_block - window_size));
        }
        result_bits_shift += window_size;
        if (result_bits_shift >= bits_in_block) {
            TYPE_METHOD(DYNAMIC_ARRAY_TYPE(uint8), push_back_by_copying)(&result, &value);
            result_bits_shift %= bits_in_block;
            value = (uint8)(code << (bits_in_block - result_bits_shift));
        }
    }

    if (result_bits_shift) { // not padded source
        TYPE_METHOD(DYNAMIC_ARRAY_TYPE(uint8), push_back_by_copying)(&result, &value);
    }

    return result;
}

// BitsReader methods
static struct BitsReader* TYPE_METHOD(BitsReader, construct_custom_at)(BitsReader* const this,
    uint8 const* const source, usize const source_size
) {
    ASSERT(this);
    this->source = source;
    this->source_size = source_size;
    this->source_index = 0u;
    this->bits_shift = 0u;
    return this;
}

static uint8 TYPE_METHOD(BitsReader, next)(struct BitsReader* const this) {
    ASSERT(this);
    if (this->source_index >= this->source_size && this->bits_shift) {
        this->bits_shift = (this->bits_shift + window_size) % bits_in_block;
        return (uint8)((1u << window_size) - 1u);
    }
    uint8 shift = ((bits_in_block - window_size) > this->bits_shift) ?
        (bits_in_block - window_size - this->bits_shift) : 0;
    uint8 result =
        (this->source[this->source_index] >> shift) &
        ((1 << (bits_in_block - this->bits_shift)) - 1);
    this->bits_shift += window_size;
    if (this->bits_shift >= bits_in_block) {
        ++this->source_index;
        this->bits_shift %= bits_in_block;
        shift = bits_in_block - this->bits_shift;
        result <<= this->bits_shift;
        if (this->source_index >= this->source_size) {
            return result;
        }
        result |=
            (this->source[this->source_index] >> shift) &
            ((1 << this->bits_shift) - 1);
    }
    return result;
}

static struct BitsReader TYPE_METHOD(BitsReader, end)(struct BitsReader const* const this) {
    ASSERT(this);
    static BitsReader result;
    result.source = this->source;
    result.source_size = this->source_size;
    result.source_index = this->source_size;
    result.window_size = this->window_size;
    result.bits_shift = 0u;
    return result;
}

static bool TYPE_METHOD(BitsReader, are_equals)(struct BitsReader const* const this, struct BitsReader const* const source) {
    ASSERT(this);
    ASSERT(source);
    return
        source->source == this->source &&
        source->source_size == this->source_size &&
        source->source_index == this->source_index &&
        source->window_size == this->window_size &&
        source->bits_shift == this->bits_shift;
}

static void* TYPE_METHOD(BitsReader, destroy_at)(BitsReader* const this) {
    ASSERT(this);
    return this;
}

static STRUCT_SUBTYPE(STRING_TYPE(), char_type) code_to_letter(uint8 value) {
    if (value == ((1u << window_size) - 1u)) {
        return (STRUCT_SUBTYPE(STRING_TYPE(), char_type))('=');
    }
    if (value <= ('Z' - 'A')) {
        return (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(value + 'A');
    }
    value -= ('Z' - 'A') + 1u;
    if (value <= ('z' - 'a')) {
        return (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(value + 'a');
    }
    value -= ('z' - 'a') + 1u;
    if (value <= ('9' - '0')) {
        return (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(value + '0');
    }
    value -= ('9' - '0') + 1u;
    if (!value) {
        return (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(value + '+');
    }
    if (value == 1) {
        return (STRUCT_SUBTYPE(STRING_TYPE(), char_type))(value + '/');
    }
    ASSERT(false); // code not corresponds to encoding
    return '\0';
}

static uint8 letter_to_code(STRUCT_SUBTYPE(STRING_TYPE(), char_type) letter) {
    if ('A' <= letter && letter <= 'Z') {
        return (uint8)(letter - 'A');
    }
    uint8 shift = ('Z' - 'A') + 1u;
    if ('a' <= letter && letter <= 'z') {
        return (uint8)(letter - 'a') + shift;
    }
    shift += ('z' - 'a') + 1u;
    if ('0' <= letter && letter <= '9') {
        return (uint8)(letter - '0') + shift;
    }
    shift += ('9' - '0') + 1u;
    if (letter == '+') {
        return shift;
    }
    if (letter == '/') {
        return shift + 1u;
    }
    if (letter == '=') {
        return MAX_VALUE(uint8) - 1u;
    }
    ASSERT(false); // letter not corresponds to encoding
    return MAX_VALUE(uint8);
}
