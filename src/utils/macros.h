#pragma once

#define CONCAT2_(NAME1, NAME2) NAME1##NAME2
#define CONCAT2(NAME1, NAME2) CONCAT2_(NAME1, NAME2)
#define CONCAT3(NAME1, NAME2, NAME3) CONCAT2(CONCAT2(NAME1, NAME2), NAME3)
#define CONCAT4(NAME1, NAME2, NAME3, NAME4) CONCAT2(CONCAT3(NAME1, NAME2, NAME3), NAME4)
#define CONCAT5(NAME1, NAME2, NAME3, NAME4, NAME5) CONCAT4(CONCAT2(NAME1, NAME2), NAME3, NAME4, NAME5)

#define TYPE_METHOD(TYPE, METHOD) CONCAT3(TYPE, _, METHOD)
#define FUNCTION_FOR_TYPE(FUNCTION, TYPE) CONCAT3(FUNCTION, _, TYPE)


#ifdef DEBUG

#include <assert.h>

#define ASSERT(EXPR) assert(EXPR)

#else

#define ASSERT(EXPR)

#endif