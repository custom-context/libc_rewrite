#pragma once

#include "characters_types_aliases.h"
#include "unsigned_types_aliases.h"

#include <stdint.h>

#define ALIAS_SIGNED_TYPE_T_AS_TYPE_AND_UNSIGNED_TYPE(TYPE) \
    typedef TYPE##_t TYPE;\
    typedef u##TYPE##_t u##TYPE

ALIAS_SIGNED_TYPE_T_AS_TYPE_AND_UNSIGNED_TYPE(int8);
ALIAS_SIGNED_TYPE_T_AS_TYPE_AND_UNSIGNED_TYPE(int16);
ALIAS_SIGNED_TYPE_T_AS_TYPE_AND_UNSIGNED_TYPE(int32);
ALIAS_SIGNED_TYPE_T_AS_TYPE_AND_UNSIGNED_TYPE(int64);


#undef ALIAS_SIGNED_TYPE_T_AS_TYPE_AND_UNSIGNED_TYPE
