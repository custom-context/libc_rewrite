#pragma once

// type's minimum/maximum value that it could hold
#define MAX_VALUE(TYPE) CONCAT3(MAX_VALUE_OF, __, TYPE)
#define MIN_VALUE(TYPE) CONCAT3(MIN_VALUE_OF, __, TYPE)
