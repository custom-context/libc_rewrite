#pragma once
#include <sys/types.h>
#include <pthread.h>

#include <concurrent/thread/native/common.h>

DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type, pthread_t);
DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type, pthread_t);
DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type, int);

typedef struct NATIVE_THREAD_TYPE() {
    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type) native_handler;
} NATIVE_THREAD_TYPE();

