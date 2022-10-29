#pragma once

#ifdef DEBUG
    #include <stdio.h>
    #define LOG_DEBUG(MSG) printf(MSG)
    #define LOG_DEBUG_FORMAT(FORMAT_STRING, ...) printf(FORMAT_STRING, __VA_ARGS__)
#else
    #define LOG_DEBUG(MSG) (MSG, 0)
    #define LOG_DEBUG_FORMAT(FORMAT_STRING, ...) (FORMAT_STRING, __VA_ARGS__, 0)
#endif
