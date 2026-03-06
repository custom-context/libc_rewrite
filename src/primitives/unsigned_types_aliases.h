#pragma once

#include <utils/macros.h>

// --- defnition for numeric helpers ---
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

DECLARE_STRUCT_SUBTYPE(char, value_type, char);
DECLARE_STRUCT_SUBTYPE(uchar, value_type, uchar);
DECLARE_STRUCT_SUBTYPE(short, value_type, short);
DECLARE_STRUCT_SUBTYPE(ushort, value_type, ushort);
DECLARE_STRUCT_SUBTYPE(int, value_type, int);
DECLARE_STRUCT_SUBTYPE(uint, value_type, uint);
DECLARE_STRUCT_SUBTYPE(long, value_type, long);
DECLARE_STRUCT_SUBTYPE(ulong, value_type, ulong);

typedef long long llong;
typedef unsigned long long ullong;

DECLARE_STRUCT_SUBTYPE(llong, value_type, llong);
DECLARE_STRUCT_SUBTYPE(ullong, value_type, ullong);
