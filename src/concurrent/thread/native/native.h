#pragma once

#if defined(_WIN32)
    #include "win/native.h"
#else
    #include "posix/native.h"
#endif

#include "common.h"
#include <primitives/fixed_size_types_aliases.h>
#include <primitives/bool_type_alias.h>

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NATIVE_THREAD_METHOD(thread_create)(
        struct NATIVE_THREAD_TYPE()* const thread,
        STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type) callback,
        void* arg);

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NATIVE_THREAD_METHOD(thread_join)(
        struct NATIVE_THREAD_TYPE()* const thread,
        STRUCT_SUBTYPE(STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type), result_type)* result);

STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type)
    NATIVE_THREAD_METHOD(thread_detach)(
        struct NATIVE_THREAD_TYPE()* const thread);

bool NATIVE_THREAD_METHOD(thread_sleep)(uint32 ms);

bool NATIVE_THREAD_METHOD(thread_yield)(void);
