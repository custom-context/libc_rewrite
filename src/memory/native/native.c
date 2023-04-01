#include "native.h"

#include <utils/macros.h>
#include <stdlib.h>

#if defined(_WIN32)
    #include <malloc.h>
#endif

void* NAMESPACE_MEMORY_NATIVE(malloc)(usize size) {
    return malloc(size);
}

void* NAMESPACE_MEMORY_NATIVE(realloc)(void* pointer, usize new_size) {
    return realloc(pointer, new_size);
}

void NAMESPACE_MEMORY_NATIVE(free)(void* pointer) {
    free(pointer);
}
