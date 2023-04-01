#pragma once

#include "common.h"
#include <stdatomic.h>

#define ATOMIC_MEMORY_ORDER_ENUM_TYPE()\
    NAMESPACE_CONCURRENT_ATOMIC(ENUM_TYPE(memory_order))

#define ATOMIC_MEMORY_ORDER_ENUM_VALUE(VALUE)\
    ENUM_VALUE(NAMESPACE_CONCURRENT_ATOMIC(ENUM_TYPE(memory_order)), VALUE)


typedef enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() {
    ATOMIC_MEMORY_ORDER_ENUM_VALUE(relaxed) = memory_order_relaxed,
    ATOMIC_MEMORY_ORDER_ENUM_VALUE(consume) = memory_order_consume,
    ATOMIC_MEMORY_ORDER_ENUM_VALUE(acquire) = memory_order_acquire,
    ATOMIC_MEMORY_ORDER_ENUM_VALUE(release) = memory_order_release,
    ATOMIC_MEMORY_ORDER_ENUM_VALUE(acquire_release) = memory_order_acq_rel,
    ATOMIC_MEMORY_ORDER_ENUM_VALUE(sequentially_consistent) = memory_order_seq_cst
} ATOMIC_MEMORY_ORDER_ENUM_TYPE();
