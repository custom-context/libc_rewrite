#include "native.h"

#include <stdlib.h>

void* NAMESPACE_MEMORY_NATIVE(malloc)(size_t size) {
    return malloc(size);
}

void* NAMESPACE_MEMORY_NATIVE(realloc)(void* pointer, size_t new_size) {
    return realloc(pointer, new_size);
}

void NAMESPACE_MEMORY_NATIVE(free)(void* pointer) {
    free(pointer);
}
