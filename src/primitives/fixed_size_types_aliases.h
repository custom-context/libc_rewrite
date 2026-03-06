#pragma once

#include <stdint.h>
#include <utils/macros.h>

typedef int8_t int8;
typedef uint8_t uint8;
DECLARE_STRUCT_SUBTYPE(int8, value_type, int8);
DECLARE_STRUCT_SUBTYPE(uint8, value_type, uint8);

typedef int16_t int16;
typedef uint16_t uint16;
DECLARE_STRUCT_SUBTYPE(int16, value_type, int16);
DECLARE_STRUCT_SUBTYPE(uint16, value_type, uint16);

typedef int32_t int32;
typedef uint32_t uint32;
DECLARE_STRUCT_SUBTYPE(int32, value_type, int32);
DECLARE_STRUCT_SUBTYPE(uint32, value_type, uint32);

typedef int64_t int64;
typedef uint64_t uint64;
DECLARE_STRUCT_SUBTYPE(int64, value_type, int64);
DECLARE_STRUCT_SUBTYPE(uint64, value_type, uint64);
