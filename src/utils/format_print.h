#pragma once

#include <stdarg.h>

/**
 * @brief 
 * * utils__format_print function works as printf but using unix/write syscall
 * @param format_string
 * * null terminated format string
 * @param ... 
 * @return
 * * int 
 */
int utils__format_print(char const* const format_string, ...);

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
int utils__va_format_print(char const* const format_string, va_list args);
