#pragma once

#ifdef DEBUG
    #include <stdio.h>
    #define LOG_DEBUG(MSG) puts(MSG)
    #define LOG_DEBUG_FORMAT(FORMAT_STRING, ...) printf(FORMAT_STRING, __VA_ARGS__)
#else
    #define LOG_DEBUG(MSG) (0)
    #define LOG_DEBUG_FORMAT(FORMAT_STRING, ...) (0)
#endif
