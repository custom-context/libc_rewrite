#include "format_print.h"

#include "format.h"
#if defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#elif defined(_WIN32)
#include <windows.h>
#endif

#define NAMESPACE(NAME) utils__##NAME

int NAMESPACE(format_print)(char const* const format_string, ...) {
    va_list args;
    va_start(args, format_string);    
    int result = utils__va_format_print(format_string, args);
    va_end(args);
    return result;
}

int NAMESPACE(va_format_print)(char const* const format_string, va_list args) {
    string_char formatted_string = utils__va_format(format_string, args);
#if defined(__unix__) || defined(__APPLE__)
    write(STDOUT_FILENO, STRING_METHOD(data)(&formatted_string), STRING_METHOD(size)(&formatted_string));
#elif defined(_WIN32)
    {
        HANDLE stdout_handler = GetStdHandle(STD_OUTPUT_HANDLE);
        if (stdout_handler == INVALID_HANDLE_VALUE) {
            return 1;
        }
        if (!WriteConsole(stdout_handler, STRING_METHOD(data)(&formatted_string),
                         STRING_METHOD(size)(&formatted_string), NULL, NULL)) {
            return 2;
        }
    }
#endif
    STRING_METHOD(destroy_at)(&formatted_string);
    return 0;    
}
