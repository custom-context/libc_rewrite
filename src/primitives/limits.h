#pragma once

#include <utils/limits.h>

// common primitive types
#include <limits.h>
#include "unsigned_types_aliases.h"

#define MAX_VALUE_OF__char CHAR_MAX
#define MAX_VALUE_OF__short SHRT_MAX
#define MAX_VALUE_OF__int INT_MAX
#define MAX_VALUE_OF__long LONG_MAX
#define MAX_VALUE_OF__llong LLONG_MAX

#define MIN_VALUE_OF__char CHAR_MIN
#define MIN_VALUE_OF__short SHRT_MIN
#define MIN_VALUE_OF__int INT_MIN
#define MIN_VALUE_OF__long LONG_MIN
#define MIN_VALUE_OF__llong LLONG_MIN

#define MAX_VALUE_OF__uchar UCHAR_MAX
#define MAX_VALUE_OF__ushort USHRT_MAX
#define MAX_VALUE_OF__uint UINT_MAX
#define MAX_VALUE_OF__ulong ULONG_MAX
#define MAX_VALUE_OF__ullong ULLONG_MAX

#define MIN_VALUE_OF__uchar (uchar)(0)
#define MIN_VALUE_OF__ushort (ushort)(0)
#define MIN_VALUE_OF__uint (uint)(0)
#define MIN_VALUE_OF__ulong (ulong)(0)
#define MIN_VALUE_OF__ullong (ullong)(0)

// fixed-width integers
#include <stdint.h>
#include "types_aliases.h"
#define MAX_VALUE_OF__int8 INT8_MAX
#define MAX_VALUE_OF__int16 INT16_MAX
#define MAX_VALUE_OF__int32 INT32_MAX
#define MAX_VALUE_OF__int64 INT64_MAX

#define MIN_VALUE_OF__int8 INT8_MIN
#define MIN_VALUE_OF__int16 INT16_MIN
#define MIN_VALUE_OF__int32 INT32_MIN
#define MIN_VALUE_OF__int64 INT64_MIN

#define MAX_VALUE_OF__uint8 UINT8_MAX
#define MAX_VALUE_OF__uint16 UINT16_MAX
#define MAX_VALUE_OF__uint32 UINT32_MAX
#define MAX_VALUE_OF__uint64 UINT64_MAX

#define MIN_VALUE_OF__uint8 (uint8)0
#define MIN_VALUE_OF__uint16 (uint16)0
#define MIN_VALUE_OF__uint32 (uint32)0
#define MIN_VALUE_OF__uint64 (uint64)0

// character types
#include "characters_types_aliases.h"
#define MAX_VALUE_OF__char8 UINT8_MAX
#define MAX_VALUE_OF__char16 UINT16_MAX
#define MAX_VALUE_OF__char32 UINT32_MAX
#define MAX_VALUE_OF__char64 UINT64_MAX
#define MAX_VALUE_OF__wchar WCHAR_MAX

#define MIN_VALUE_OF__char8 (char8)0
#define MIN_VALUE_OF__char16 (char16)0
#define MIN_VALUE_OF__char32 (char32)0
#define MIN_VALUE_OF__char64 (char64)0
#define MIN_VALUE_OF__wchar WCHAR_MIN

// windows character type
#if defined(_WIN32)
    #ifdef _UNICODE
        #define MAX_VALUE_OF__winchar WCHAR_MAX
        #define MIN_VALUE_OF__winchar WCHAR_MIN
    #else
        #define MAX_VALUE_OF__winchar CHAR_MAX
        #define MIN_VALUE_OF__winchar CHAR_MIN
    #endif
#endif


// pointer/data related types
#define MAX_VALUE_OF__size_t SIZE_MAX
#define MIN_VALUE_OF__size_t (size_t)0

#define MAX_VALUE_OF__ptrdiff_t PTRDIFF_MAX
#define MIN_VALUE_OF__ptrdiff_t PTRDIFF_MIN
