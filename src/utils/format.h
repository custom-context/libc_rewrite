#pragma once

#include <containers/dynamic/string/string.h>
#include <utils/common.h>
#include <stdarg.h>

/**
 * @brief 
 * * format function works as c format in printf but returns string type struct as result 
 * @param format_string
 * * null terminated format string
 * @param ...
 * @return
 * * struct STRING_TYPE() - formatted string
 */

struct STRING_TYPE() NAMESPACE_UTILS(cformat)(char const* const format_string, ...);
struct WSTRING_TYPE() NAMESPACE_UTILS(wformat)(wchar const* const format_string, ...);

#if defined(_WIN32)
#define utils__format(FORMAT_STRING, ...)\
_Generic((0,FORMAT_STRING),\
    char const*: NAMESPACE_UTILS(cformat),\
    char*: NAMESPACE_UTILS(cformat),\
    wchar const*: NAMESPACE_UTILS(wformat),\
    wchar*: NAMESPACE_UTILS(wformat)\
)(FORMAT_STRING, __VA_ARGS__)
#else
#define utils__format(FORMAT_STRING, ...)\
_Generic((FORMAT_STRING),\
    char const*: NAMESPACE_UTILS(cformat),\
    char*: NAMESPACE_UTILS(cformat),\
    wchar const*: NAMESPACE_UTILS(wformat),\
    wchar*: NAMESPACE_UTILS(wformat)\
)(FORMAT_STRING, __VA_ARGS__)
#endif

/**
 * @brief 
 * * variadic helper for format function that declared above  
 * @param format_string
 * * null terminated format string
 * @param args
 * * list of variadic arguments
 * @return
 * * struct STRING_TYPE() - formatted string
 */
struct STRING_TYPE() NAMESPACE_UTILS(va_cformat)(char const* const format_string, va_list args);
struct WSTRING_TYPE() NAMESPACE_UTILS(va_wformat)(wchar const* const format_string, va_list args);

#if defined(_WIN32)
#define utils__va_format(FORMAT_STRING, ...)\
_Generic((0,FORMAT_STRING),\
    char const*: NAMESPACE_UTILS(va_cformat),\
    char*: NAMESPACE_UTILS(va_cformat),\
    wchar const*: NAMESPACE_UTILS(va_wformat),\
    wchar*: NAMESPACE_UTILS(va_wformat)\
)
#else
#define utils__va_format(FORMAT_STRING, ...)\
_Generic((FORMAT_STRING),\
    char const*: NAMESPACE_UTILS(va_cformat),\
    char*: NAMESPACE_UTILS(va_cformat),\
    wchar const*: NAMESPACE_UTILS(va_wformat),\
    wchar*: NAMESPACE_UTILS(va_wformat)\
)
#endif
