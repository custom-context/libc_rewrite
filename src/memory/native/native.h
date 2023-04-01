#pragma once

#include <memory/common.h>
#include <primitives/data_model_types_aliases.h>

#define NAMESPACE_MEMORY_NATIVE(NAME) NAMESPACE_MEMORY(CONCAT3(native, __, NAME))

void* NAMESPACE_MEMORY_NATIVE(malloc)(usize size);
void* NAMESPACE_MEMORY_NATIVE(realloc)(void* pointer, usize new_size);
void NAMESPACE_MEMORY_NATIVE(free)(void* pointer);
