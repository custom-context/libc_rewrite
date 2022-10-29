#pragma once

// --- defnition for numeric helpers ---
// unsigned type -> u#type
#define ALIAS_UNSIGNED_NUMERIC_TYPE(TYPE) \
typedef unsigned TYPE u##TYPE

ALIAS_UNSIGNED_NUMERIC_TYPE(char);
ALIAS_UNSIGNED_NUMERIC_TYPE(short);
ALIAS_UNSIGNED_NUMERIC_TYPE(int);
ALIAS_UNSIGNED_NUMERIC_TYPE(long);

typedef long long llong;
typedef unsigned long long ullong;

#undef ALIAS_UNSIGNED_NUMERIC_TYPE
