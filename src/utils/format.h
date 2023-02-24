#pragma once

#include <containers/dynamic/string/string_impl.h>

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
struct STRING_TYPE() utils__format(char const* const format_string, ...);

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
struct STRING_TYPE() utils__va_format(char const* const format_string, va_list args);
