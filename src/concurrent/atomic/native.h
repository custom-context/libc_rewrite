#pragma once

#include "common.h"
// compilers itself define atomic instruction set
#include <stdatomic.h>

#define NATIVE_ATOMIC_TYPE(TYPE)\
    CONCAT3(atomic, __, TYPE)

#define DEFINE_NATIVE_ATOMIC_TYPE(TYPE)\
    typedef _Atomic(TYPE) NATIVE_ATOMIC_TYPE(TYPE)

#include "fence.h"
