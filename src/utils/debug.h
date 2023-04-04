#pragma once

#ifdef DEBUG
    #include <stdio.h>
    #define LOG_DEBUG(MSG) puts(MSG)
    #define LOG_DEBUG_FORMAT(FORMAT_STRING, ...) printf(FORMAT_STRING, __VA_ARGS__)
#else
    #define LOG_DEBUG(MSG) UNUSED(MSG)
    #define LOG_DEBUG_FORMAT(FORMAT_STRING, ...) UNUSED(FORMAT_STRING)
#endif
