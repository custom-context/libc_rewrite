#pragma once

#include <Windows.h>
#include <processthreadsapi.h>

#include <concurrent/thread/native/common.h>

DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type, HANDLE);
DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type, DWORD);
DECLARE_STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), thread_state_type, DWORD);

typedef struct NATIVE_THREAD_TYPE() {
    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_handler_type) native_handler;
    STRUCT_SUBTYPE(NATIVE_THREAD_TYPE(), native_id_type) native_id;
} NATIVE_THREAD_TYPE();


