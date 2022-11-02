#pragma once

#include <construct/numeric_helpers.h>
#include <utils/macros.h>

#define NAMESPACE_FS(NAME) CONCAT3(fs, __, NAME)
#define NAMESPACE_FS_FILE(NAME) NAMESPACE_FS(CONCAT3(file, __, NAME))

#define UTF_ENCODING_ENUM() NAMESPACE_FS_FILE(UTF_ENCODING)
#define UTF_ENCODING_ENUM_VALUE(VALUE) CONCAT3(UTF_ENCODING_ENUM(), _, VALUE)

// some how check the encoding of file (UTF-8/16/32)
// article: http://unicode.org/faq/utf_bom.html#BOM

typedef enum NAMESPACE_FS_FILE(UTF_ENCODING) {
    UTF_ENCODING_ENUM_VALUE(UTF32_BE), // 00 00 FE FF    UTF-32, big-endian
    UTF_ENCODING_ENUM_VALUE(UTF32_LE), // FF FE 00 00    UTF-32, little-endian
    UTF_ENCODING_ENUM_VALUE(UTF16_BE), // FE FF          UTF-16, big-endian
    UTF_ENCODING_ENUM_VALUE(UTF16_LE), // FF FE          UTF-16, little-endian
    UTF_ENCODING_ENUM_VALUE(UTF8_BOM), // EF BB BF       UTF-8, BOM
    UTF_ENCODING_ENUM_VALUE(UTF8),     // ELSE           UTF-8
} NAMESPACE_FS_FILE(UTF_ENCODING);

enum NAMESPACE_FS_FILE(UTF_ENCODING) NAMESPACE_FS_FILE(get_encoding)(uint const header_bytes_size, char const* const header_bytes);
