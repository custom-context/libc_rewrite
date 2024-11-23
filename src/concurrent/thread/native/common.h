#pragma once

#include <concurrent/thread/common.h>

#define NATIVE_THREAD_TYPE() NAMESPACE_CONCURRENT_NATIVE_THREAD(thread)
#define NATIVE_THREAD_METHOD(METHOD) TYPE_METHOD(NATIVE_THREAD_TYPE(), METHOD)

DECLARE_STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type, int, void*);
DECLARE_STRUCT_SUBTYPE(STRUCT_FN_TYPE(NATIVE_THREAD_TYPE(), callback_type), result_type, int);
