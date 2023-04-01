#pragma once

#include <memory/allocator/proxy_allocator/proxy_allocator.h>
#include <memory/allocator/allocator.h>

typedef struct DebugAllocatorContext {
    usize count_of_allocations;
    usize count_of_deallocations;
    usize count_of_allocated_bytes;
    usize count_of_deallocated_bytes;
} DebugAllocatorContext;

#define DEBUG_PROXY_ALLOCATOR_TYPE(TYPE)\
    PROXY_ALLOCATOR_TYPE(DEFAULT_ALLOCATOR_TYPE(TYPE), DebugAllocatorContext)

#define DEFINE_DEBUG_PROXY_ALLOCATOR_TYPE(TYPE)\
    DEFINE_PROXY_ALLOCATOR_TYPE(DEFAULT_ALLOCATOR_TYPE(TYPE), DebugAllocatorContext)

#define DECLARE_DEBUG_PROXY_ALLOCATOR_METHODS(COMMON_MODIFIER, TYPE)\
    DECLARE_PROXY_ALLOCATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, DEFAULT_ALLOCATOR_TYPE(TYPE), DebugAllocatorContext)

#define DEFINE_DEBUG_PROXY_ALLOCATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, TYPE)\
    DEFINE_PROXY_ALLOCATOR_METHODS_WITH_MODIFIER(COMMON_MODIFIER, DEFAULT_ALLOCATOR_TYPE(TYPE), DebugAllocatorContext)
