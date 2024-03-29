#include "encoding.h"
#include <stddef.h>

static char is_UTF32_BE_BOM(char unsigned const* const head_bytes);
static char is_UTF32_LE_BOM(char unsigned const* const head_bytes);
static char is_UTF16_BE_BOM(char unsigned const* const head_bytes);
static char is_UTF16_LE_BOM(char unsigned const* const head_bytes);
static char is_UTF8_BOM(char unsigned const* const head_bytes);

static char is_UTF32_BE(char unsigned const* const head_bytes);
static char is_UTF32_LE(char unsigned const* const head_bytes);
static char is_UTF16_BE(char unsigned const* const head_bytes);
static char is_UTF16_LE(char unsigned const* const head_bytes);

enum UTF_ENCODING_ENUM() NAMESPACE_FS_FILE(get_encoding)(uint const header_bytes_size, char const* const header_bytes) {
    if (header_bytes_size >= 4) {
        if (is_UTF32_BE_BOM((char unsigned const* const)header_bytes)) {
            return UTF_ENCODING_ENUM_VALUE(UTF32_BE_BOM);
        }
        if (is_UTF32_LE_BOM((char unsigned const* const)header_bytes)) {
            return UTF_ENCODING_ENUM_VALUE(UTF32_LE_BOM);
        }

        if (is_UTF32_BE((char unsigned const* const)header_bytes)) {
            return UTF_ENCODING_ENUM_VALUE(UTF32_BE);
        }
        if (is_UTF32_LE((char unsigned const* const)header_bytes)) {
            return UTF_ENCODING_ENUM_VALUE(UTF32_LE);
        }
    }

    if (header_bytes_size >= 3) {
        if (is_UTF8_BOM((char unsigned const* const)header_bytes)) {
            return UTF_ENCODING_ENUM_VALUE(UTF8_BOM);
        }
    }

    if (header_bytes_size >= 2) {
        if (is_UTF16_BE((char unsigned const* const)header_bytes)) {
            return UTF_ENCODING_ENUM_VALUE(UTF16_BE);
        }
        if (is_UTF16_LE((char unsigned const* const)header_bytes)) {
            return UTF_ENCODING_ENUM_VALUE(UTF16_LE);
        }

        if (is_UTF16_BE_BOM((char unsigned const* const)header_bytes)) {
            return UTF_ENCODING_ENUM_VALUE(UTF16_BE_BOM);
        }
        if (is_UTF16_LE_BOM((char unsigned const* const)header_bytes)) {
            return UTF_ENCODING_ENUM_VALUE(UTF16_LE_BOM);
        }
    }

    return UTF_ENCODING_ENUM_VALUE(UTF8);
}

static char is_UTF32_BE_BOM(char unsigned const* const head_bytes) {
    return
        head_bytes[0] == 0x00 &&
        head_bytes[1] == 0x00 &&
        head_bytes[2] == 0xFE &&
        head_bytes[3] == 0xFF;
}

static char is_UTF32_LE_BOM(char unsigned const* const head_bytes) {
    return
        head_bytes[3] == 0x00 &&
        head_bytes[2] == 0x00 &&
        head_bytes[1] == 0xFE &&
        head_bytes[0] == 0xFF;
}

static char is_UTF16_BE_BOM(char unsigned const* const head_bytes) {
    return
        head_bytes[0] == 0xFE &&
        head_bytes[1] == 0xFF;
}

static char is_UTF16_LE_BOM(char unsigned const* const head_bytes) {
    return
        head_bytes[1] == 0xFE &&
        head_bytes[0] == 0xFF;
}

static char is_UTF8_BOM(char unsigned const* const head_bytes) {
    return
        head_bytes[0] == 0xEF &&
        head_bytes[1] == 0xBB &&
        head_bytes[2] == 0xBF;
}

static char is_UTF32_BE(char unsigned const* const head_bytes) {
    return
        head_bytes[0] == 0x00 &&
        head_bytes[1] == 0x00 &&
        head_bytes[2] == 0x00;
}

static char is_UTF32_LE(char unsigned const* const head_bytes) {
    return
        head_bytes[3] == 0x00 &&
        head_bytes[2] == 0x00 &&
        head_bytes[1] == 0x00;
}

static char is_UTF16_BE(char unsigned const* const head_bytes) {
    return
        head_bytes[0] == 0x00;
}

static char is_UTF16_LE(char unsigned const* const head_bytes) {
    return
        head_bytes[1] == 0x00;
}

