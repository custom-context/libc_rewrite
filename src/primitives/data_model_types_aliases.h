#pragma once

#include <stdint.h>
#include <stddef.h>

#define ALIAS_SIGNED_TYPE_T_AS_TYPE_AND_UNSIGNED_TYPE(TYPE) \
    typedef TYPE##_t TYPE;\
    typedef u##TYPE##_t u##TYPE

ALIAS_SIGNED_TYPE_T_AS_TYPE_AND_UNSIGNED_TYPE(intptr);

#undef ALIAS_SIGNED_TYPE_T_AS_TYPE_AND_UNSIGNED_TYPE

typedef size_t usize;
typedef ptrdiff_t ptrdiff;

typedef void* voidptr;
