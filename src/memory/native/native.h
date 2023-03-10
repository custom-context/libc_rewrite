#pragma once

#include <memory/common.h>

#define NAMESPACE_MEMORY_NATIVE(NAME) NAMESPACE_MEMORY(CONCAT3(native, __, NAME))

void* NAMESPACE_MEMORY_NATIVE(malloc)(size_t size);
void* NAMESPACE_MEMORY_NATIVE(realloc)(void* pointer, size_t new_size);
void NAMESPACE_MEMORY_NATIVE(free)(void* pointer);
