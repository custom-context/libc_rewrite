#pragma once

#include <encoding/common.h>
#include <containers/dynamic/string/string.h>
#include <containers/dynamic/array/array.h>

#include <primitives/allocator.h>

#define NAMESPACE_ENCODING_BASE64(NAME)\
NAMESPACE_ENCODING(NAMESPACE(base64, NAME))

DECLARE_DYNAMIC_ARRAY_TYPE(uint8);
DECLARE_DYNAMIC_ARRAY_WITH_CUSTOM_ALLOCATOR_TYPE_METHODS_WITH_MODIFIER(extern, uint8, DEFAULT_ALLOCATOR_TYPE(uint8));

extern struct STRING_TYPE() NAMESPACE_ENCODING_BASE64(encode)(uint8 const* const source, size_t source_size);
extern struct DYNAMIC_ARRAY_TYPE(uint8) NAMESPACE_ENCODING_BASE64(decode)(char const* const source, size_t source_size);
