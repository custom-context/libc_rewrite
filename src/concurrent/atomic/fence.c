#include "fence.h"

#include <stdatomic.h>

void NAMESPACE_CONCURRENT_ATOMIC(thread_fence)(enum ATOMIC_MEMORY_ORDER_ENUM_TYPE() memory_order) {
    atomic_thread_fence(memory_order);
}
