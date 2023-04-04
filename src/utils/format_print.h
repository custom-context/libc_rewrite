#pragma once

#include <utils/common.h>
#include <stdarg.h>
#include <primitives/primitives.h>

/**
 * @brief 
 * * NAMESPACE_UTILS(format_print) function works as printf but using unix/write syscall
 * @param format_string
 * * null terminated format string
 * @param ... 
 * @return
 * * int 
 */
int NAMESPACE_UTILS(cformat_print)(char const* const format_string, ...);
int NAMESPACE_UTILS(wformat_print)(wchar const* const format_string, ...);

#if defined(_WIN32)
#define utils__format_print(FORMAT_STRING, ...)\
_Generic((0,FORMAT_STRING),\
    char const*: NAMESPACE_UTILS(cformat_print),\
    char*: NAMESPACE_UTILS(cformat_print),\
    wchar const*: NAMESPACE_UTILS(wformat_print),\
    wchar*: NAMESPACE_UTILS(wformat_print)\
)(FORMAT_STRING, __VA_ARGS__)
#else
#define utils__format_print(FORMAT_STRING, ...)\
_Generic((FORMAT_STRING),\
    char const*: NAMESPACE_UTILS(cformat_print),\
    char*: NAMESPACE_UTILS(cformat_print),\
    wchar const*: NAMESPACE_UTILS(wformat_print),\
    wchar*: NAMESPACE_UTILS(wformat_print)\
)(FORMAT_STRING, __VA_ARGS__)
#endif
/**
 * @brief 
 * * variadic helper for format_print function that declared above
 * @param format_string
 * * null terminated format string
 * @param args
 * * list of variadic arguments
 * @return
 * * int 
 */
int NAMESPACE_UTILS(va_cformat_print)(char const* const format_string, va_list args);
int NAMESPACE_UTILS(va_wformat_print)(wchar const* const format_string, va_list args);

#if defined(_WIN32)
#define utils__va_format_print(FORMAT_STRING, ...)\
_Generic((0,FORMAT_STRING),\
    char const*: NAMESPACE_UTILS(va_cformat_print),\
    char*: NAMESPACE_UTILS(va_cformat_print),\
    wchar const*: NAMESPACE_UTILS(va_wformat_print),\
    wchar*: NAMESPACE_UTILS(va_wformat_print)\
)(FORMAT_STRING, __VA_ARGS__)
#else
#define utils__va_format_print(FORMAT_STRING, ...)\
_Generic((FORMAT_STRING),\
    char const*: NAMESPACE_UTILS(va_cformat_print),\
    char*: NAMESPACE_UTILS(va_cformat_print),\
    wchar const*: NAMESPACE_UTILS(va_wformat_print),\
    wchar*: NAMESPACE_UTILS(va_wformat_print)\
)(FORMAT_STRING, __VA_ARGS__)
#endif
