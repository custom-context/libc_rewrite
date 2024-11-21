#pragma once

#include <memory/common.h>
#include <primitives/data_model_types_aliases.h>
#include <primitives/bool_type_alias.h>

#define NAMESPACE_MEMORY_NATIVE(NAME) NAMESPACE_MEMORY(CONCAT3(native, __, NAME))

void* NAMESPACE_MEMORY_NATIVE(malloc)(usize size);
void* NAMESPACE_MEMORY_NATIVE(realloc)(void* pointer, usize new_size);
void NAMESPACE_MEMORY_NATIVE(free)(void* pointer);

inline static bool NAMESPACE_MEMORY_NATIVE(is_aligned)(const void *restrict pointer, size_t byte_count) {
    return !((uintptr)pointer % byte_count);
}

void* NAMESPACE_MEMORY_NATIVE(aligned_alloc)(usize alignment, usize size);
void* NAMESPACE_MEMORY_NATIVE(aligned_realloc)(void* pointer, usize alignment, usize new_size);
void NAMESPACE_MEMORY_NATIVE(aligned_free)(void* pointer);
