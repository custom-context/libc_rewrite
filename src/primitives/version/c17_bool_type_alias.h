#pragma once


#if !defined(__has_warning) || __has_warning("-Wc2x-compat")
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wc2x-compat"
#endif
// from C17 stdbool.h header provides this macro & following macro definitions
#ifndef __bool_true_false_are_defined
    typedef unsigned char bool;

    #define true ((bool)1u)

    #define false ((bool)0u)
#endif
#if !defined(__has_warning) || __has_warning("-Wc2x-compat")
    #pragma clang diagnostic pop
#endif
