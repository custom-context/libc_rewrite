#pragma once

#include <concurrent/common.h>

#define NAMESPACE_CONCURRENT_ATOMIC(NAME)\
    NAMESPACE_CONCURRENT(NAMESPACE(atomic, NAME))
