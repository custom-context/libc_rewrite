#include "format_print.h"

#include "format.h"
#if defined(__unix__) || defined(__APPLE__)
    #include <unistd.h>
#elif defined(_WIN32)
    #include <Windows.h>
#endif

int NAMESPACE_UTILS(cformat_print)(char const* const format_string, ...) {
    va_list args;
    va_start(args, format_string);
    int result = NAMESPACE_UTILS(va_cformat_print)(format_string, args);
    va_end(args);
    return result;
}

int NAMESPACE_UTILS(wformat_print)(wchar const* const format_string, ...) {
    va_list args;
    va_start(args, format_string);
    int result = NAMESPACE_UTILS(va_wformat_print)(format_string, args);
    va_end(args);
    return result;
}

int NAMESPACE_UTILS(va_cformat_print)(char const* const format_string, va_list args) {
    struct STRING_TYPE() formatted_string = NAMESPACE_UTILS(va_cformat)(format_string, args);
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

int NAMESPACE_UTILS(va_wformat_print)(wchar const* const format_string, va_list args) {
    struct WSTRING_TYPE() formatted_string = NAMESPACE_UTILS(va_wformat)(format_string, args);
#if defined(__unix__) || defined(__APPLE__)
    write(STDOUT_FILENO, WSTRING_METHOD(data)(&formatted_string), WSTRING_METHOD(size)(&formatted_string) * sizeof(wchar));
#elif defined(_WIN32)
    {
        HANDLE stdout_handler = GetStdHandle(STD_OUTPUT_HANDLE);
        if (stdout_handler == INVALID_HANDLE_VALUE) {
            return 1;
        }
        if (!WriteConsole(stdout_handler, WSTRING_METHOD(data)(&formatted_string),
                         WSTRING_METHOD(size)(&formatted_string), NULL, NULL)) {
            return 2;
        }
    }
#endif
    WSTRING_METHOD(destroy_at)(&formatted_string);
    return 0;    
}
