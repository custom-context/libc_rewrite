#include "format.h"

#include <utils/format.h>
#include <primitives/primitives.h>

IMPLEMENT_TYPE_TESTS(format) {
    TEST_BLOCK("format c string") {
        char const* const cstr = "some string that must be inserted to format string";
        int value = 232345;
        char character = 'a';
        char const* const reference_string = "inserted string: some string that must be inserted to format string, int value: 232345, character: a\n";
        struct STRING_TYPE() formatted_string = NAMESPACE_UTILS(cformat)("inserted string: %s, int value: %d, character: %c\n", cstr, value, character);
        CHECK(!RAW_STRING_FUNCTION(char, compare)(STRING_METHOD(data)(&formatted_string), reference_string));
        STRING_METHOD(destroy_at)(&formatted_string);
    }
    TEST_BLOCK("format w string") {
        wchar const* const cstr = L"some string that must be inserted to format string";
        int value = 232345;
        wchar character = 'a';
        wchar const* const reference_string = L"inserted string: some string that must be inserted to format string, int value: 232345, character: a\n";
        struct WSTRING_TYPE() formatted_string = NAMESPACE_UTILS(wformat)(L"inserted string: %s, int value: %d, character: %c\n", cstr, value, character);
        CHECK(!RAW_STRING_FUNCTION(wchar, compare)(WSTRING_METHOD(data)(&formatted_string), reference_string));
        WSTRING_METHOD(destroy_at)(&formatted_string);
    }
    TEST_BLOCK("format os string") {
        OS_CHAR_TYPE const* const filepath = 
            #if defined(_WIN32)
                OS_STRING_LITERAL("C:\\Users\\UserName\\Documents\\my_file.txt")
            #else
                OS_STRING_LITERAL("home/UserName/Documents/my_file.txt")
            #endif
        ;
        OS_CHAR_TYPE const* const reference_string = 
            #if defined(_WIN32)
                OS_STRING_LITERAL("filepath: C:\\Users\\UserName\\Documents\\my_file.txt\n")
            #else
                OS_STRING_LITERAL("filepath: home/UserName/Documents/my_file.txt\n")
            #endif
        ;
        struct OS_STRING_TYPE() formatted_string = NAMESPACE_UTILS(format)(OS_STRING_LITERAL("filepath: %s\n"), filepath);
        CHECK(!RAW_STRING_FUNCTION(OS_CHAR_TYPE, compare)(OS_STRING_METHOD(data)(&formatted_string), reference_string));
        OS_STRING_METHOD(destroy_at)(&formatted_string);
    }
}
