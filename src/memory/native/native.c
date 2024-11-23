#include "native.h"

#include <utils/macros.h>
#include <stdlib.h>
#include <string.h>

void* NAMESPACE_MEMORY_NATIVE(malloc)(usize size) {
    return malloc(size);
}

void* NAMESPACE_MEMORY_NATIVE(realloc)(void* pointer, usize new_size) {
    return realloc(pointer, new_size);
}

void NAMESPACE_MEMORY_NATIVE(free)(void* pointer) {
    free(pointer);
}

#if defined(_WIN32)
    #include <malloc.h>
    void* NAMESPACE_MEMORY_NATIVE(aligned_alloc)(usize alignment, usize size) {
        return _aligned_malloc(size, alignment);
    }
    void* NAMESPACE_MEMORY_NATIVE(aligned_realloc)(void* pointer, usize alignment, usize new_size) {
        return _aligned_realloc(pointer, new_size, alignment);
    }
    void NAMESPACE_MEMORY_NATIVE(aligned_free)(void* pointer) {
        _aligned_free(pointer);
    }
#else
#if defined(__APPLE__) && defined(__MACH__)
    void* NAMESPACE_MEMORY_NATIVE(aligned_alloc)(usize alignment, usize size) {
        void* result;
        // memalign alignment rules:
        // 1. alignment must be power of 2 (1 << X)
        // 2. alignment must be greater or equal to sizeof(void*)
        if (posix_memalign(&result, alignment > sizeof(void*) ? alignment : sizeof(void*), size)) {
            NAMESPACE_MEMORY_NATIVE(aligned_free)(result);
            return NULL;
        }
        return result;
    }
#else
    #include <malloc.h>
    void* NAMESPACE_MEMORY_NATIVE(aligned_alloc)(usize alignment, usize size) {
        return memalign(alignment, size);
    }
#endif
    void* NAMESPACE_MEMORY_NATIVE(aligned_realloc)(void* pointer, usize alignment, usize new_size) {
        void* const reallocated_storage = realloc(pointer, new_size);
        // if reallocated memory is NULL or it has the same alignment => return it
        if (!reallocated_storage || NAMESPACE_MEMORY_NATIVE(is_aligned)(reallocated_storage, alignment)) {
            return reallocated_storage;
        }
        // else allocate new chunk, copy data & free previous chunk
        void* const new_aligned_storage = NAMESPACE_MEMORY_NATIVE(aligned_alloc)(alignment, new_size);
        if (new_aligned_storage) {
            memcpy(new_aligned_storage, reallocated_storage, new_size);
        }
        NAMESPACE_MEMORY_NATIVE(aligned_free)(reallocated_storage);
        return new_aligned_storage;
    }
    void NAMESPACE_MEMORY_NATIVE(aligned_free)(void* pointer) {
        free(pointer);
    }
#endif
