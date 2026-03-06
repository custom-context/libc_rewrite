#pragma once

#include <stdint.h>
#include <stddef.h>

typedef intptr_t intptr;
typedef uintptr_t uintptr;
DECLARE_STRUCT_SUBTYPE(intptr, value_type, intptr);
DECLARE_STRUCT_SUBTYPE(uintptr, value_type, uintptr);

typedef size_t usize;
typedef ptrdiff_t ptrdiff;
DECLARE_STRUCT_SUBTYPE(usize, value_type, usize);
DECLARE_STRUCT_SUBTYPE(ptrdiff, value_type, ptrdiff);

typedef void* voidptr;
DECLARE_STRUCT_SUBTYPE(voidptr, value_type, voidptr);
