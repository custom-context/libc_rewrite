#pragma once

#include <construct/numeric_helpers.h>
#include <utils/macros.h>

#define NAMESPACE_FS(NAME) CONCAT3(fs, __, NAME)
#define NAMESPACE_FS_FILE(NAME) NAMESPACE_FS(CONCAT3(file, __, NAME))

#define UTF_ENCODING_ENUM() NAMESPACE_FS_FILE(ENUM_TYPE(UTF_ENCODING))
#define UTF_ENCODING_ENUM_VALUE(VALUE) ENUM_VALUE(UTF_ENCODING_ENUM(), VALUE)

// some how check the encoding of file (UTF-8/16/32)
// article: http://unicode.org/faq/utf_bom.html#BOM

typedef enum UTF_ENCODING_ENUM() {
    // BOM encoding
    UTF_ENCODING_ENUM_VALUE(UTF32_BE_BOM), // 00 00 FE FF    UTF-32, big-endian, BOM
    UTF_ENCODING_ENUM_VALUE(UTF32_LE_BOM), // FF FE 00 00    UTF-32, little-endian, BOM
    UTF_ENCODING_ENUM_VALUE(UTF16_BE_BOM), // FE FF xx xx    UTF-16, big-endian, BOM
    UTF_ENCODING_ENUM_VALUE(UTF16_LE_BOM), // FF FE xx xx    UTF-16, little-endian, BOM
    UTF_ENCODING_ENUM_VALUE(UTF8_BOM),     // EF BB BF xx    UTF-8, BOM
    // non-BOM encoding (JSON files for example have non-BOM format)
    UTF_ENCODING_ENUM_VALUE(UTF32_BE),     // 00 00 00 xx    UTF-32, big-endian
    UTF_ENCODING_ENUM_VALUE(UTF32_LE),     // xx 00 00 00    UTF-32, little-endian
    UTF_ENCODING_ENUM_VALUE(UTF16_BE),     // 00 xx xx xx    UTF-16, big-endian
    UTF_ENCODING_ENUM_VALUE(UTF16_LE),     // xx 00 xx xx    UTF-16, little-endian
    UTF_ENCODING_ENUM_VALUE(UTF8)          // xx xx xx xx    UTF-8
} UTF_ENCODING_ENUM();

enum UTF_ENCODING_ENUM() NAMESPACE_FS_FILE(get_encoding)(uint const header_bytes_size, char const* const header_bytes);
