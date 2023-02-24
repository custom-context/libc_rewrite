#include "encoding.h"

#include <fs/file/encoding.h>

#include <containers/dynamic/string/string.h>
#include <containers/dynamic/string/string_impl.h>

#if defined(WIN32)
    #include <windows.h>
#else
    #include <unistd.h>
    #include <fcntl.h>
#endif

#define OPTIONAL_ENCODING_TYPE CONCAT3(optional, _, UTF_ENCODING_ENUM())

typedef struct OPTIONAL_ENCODING_TYPE {
    int has_value_;
    UTF_ENCODING_ENUM() encoding_;
} OPTIONAL_ENCODING_TYPE;

static struct OPTIONAL_ENCODING_TYPE get_file_encoding(
    char const* const TYPE_NAME,
    char const* const TEST_BLOCK_NAME,
    size_t* const TEST_BLOCK_COUNTER_PTR,
    //
    char const filename[const]);

static char const* encoding_type_to_filename(UTF_ENCODING_ENUM() encoding);

IMPLEMENT_TYPE_TESTS(encoding) {
    TEST_BLOCK("check files encoding over test files") {
#if defined(_WIN32)
        static char const *const current_directory_path =
          "\\src\\tests\\fs\\file\\";
        static char const *const encoded_files_relative_path = "utf_encoded_files\\";
#elif defined(__unix__) || defined(__APPLE__)
        static char const *const current_directory_path = "/src/tests/fs/file/";
        static char const* const encoded_files_relative_path = "utf_encoded_files/";
#endif
        CHECK(STRINGIFY(PROJECT_SOURCE_DIR));
        STRING_TYPE() directory_path;
#if defined(_WIN32)
        STRING_METHOD(construct_from_c_string_at)
        (&directory_path, STRINGIFY(PROJECT_SOURCE_DIR));
        STRING_METHOD(append_c_string)(&directory_path, current_directory_path);
#elif defined(__unix__) || defined(__APPLE__)
        STRING_METHOD(construct_from_c_string_at)
        (&directory_path, STRINGIFY(PROJECT_SOURCE_DIR));
        STRING_METHOD(append_c_string)(&directory_path, current_directory_path);
#endif
        STRING_METHOD(append_c_string)(&directory_path, encoded_files_relative_path);

        UTF_ENCODING_ENUM() const encodings_to_check[] = {
            // UTF_ENCODING_ENUM_VALUE(UTF32_BE_BOM),
            // UTF_ENCODING_ENUM_VALUE(UTF32_LE_BOM),
            UTF_ENCODING_ENUM_VALUE(UTF16_BE_BOM),
            UTF_ENCODING_ENUM_VALUE(UTF16_LE_BOM),
            UTF_ENCODING_ENUM_VALUE(UTF8_BOM),
            // UTF_ENCODING_ENUM_VALUE(UTF32_BE),
            // UTF_ENCODING_ENUM_VALUE(UTF32_LE),
            // UTF_ENCODING_ENUM_VALUE(UTF16_BE),
            // UTF_ENCODING_ENUM_VALUE(UTF16_LE),
            UTF_ENCODING_ENUM_VALUE(UTF8)
        };

        for (uint index = 0u; index < sizeof(encodings_to_check) / sizeof(UTF_ENCODING_ENUM()); ++index) {
            STRING_TYPE() filepath;
            STRING_METHOD(construct_copy_at)(&filepath, &directory_path);
            STRING_METHOD(append_c_string)(&filepath, encoding_type_to_filename(encodings_to_check[index]));
            
            CHECK(get_file_encoding(TYPE_NAME, TEST_BLOCK_NAME, &TEST_BLOCK_COUNTER, STRING_METHOD(data)(&filepath)).encoding_ == encodings_to_check[index]);

            STRING_METHOD(destroy_at)(&filepath);
        }

        STRING_METHOD(destroy_at)(&directory_path);
    }
}

static struct OPTIONAL_ENCODING_TYPE get_file_encoding(
    char const* const TYPE_NAME,
    char const* const TEST_BLOCK_NAME,
    size_t* const TEST_BLOCK_COUNTER_PTR,
    //
    char const filename[const]) {
    size_t TEST_BLOCK_COUNTER = *TEST_BLOCK_COUNTER_PTR;

#if defined(_WIN32)
    HANDLE file_handler =
        CreateFile(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                   FILE_ATTRIBUTE_NORMAL, NULL);
    CHECK(file_handler != INVALID_HANDLE_VALUE); // file not found
    if (file_handler == INVALID_HANDLE_VALUE) {
        *TEST_BLOCK_COUNTER_PTR = TEST_BLOCK_COUNTER;
        return (OPTIONAL_ENCODING_TYPE){0};
    }

    DWORD count_bytes_read;
    char bytes[4];
    ReadFile(file_handler, bytes, sizeof(bytes), &count_bytes_read, NULL);

    UTF_ENCODING_ENUM() encoding = NAMESPACE_FS_FILE(get_encoding)(count_bytes_read, bytes);
    CloseHandle(file_handler);

    *TEST_BLOCK_COUNTER_PTR = TEST_BLOCK_COUNTER;
    return (OPTIONAL_ENCODING_TYPE){1, encoding};
#elif defined(__unix__) || defined(__APPLE__)
    int file_descriptor = open(filename, O_RDONLY);
    CHECK(file_descriptor != -1); // file not found
    if (file_descriptor == -1) {
        close(file_descriptor);
        *TEST_BLOCK_COUNTER_PTR = TEST_BLOCK_COUNTER;
        return (OPTIONAL_ENCODING_TYPE){0};
    }

    char bytes[4];
    ssize_t count_bytes_read = read(file_descriptor, bytes, sizeof(bytes));

    UTF_ENCODING_ENUM() encoding = NAMESPACE_FS_FILE(get_encoding)(count_bytes_read, bytes);
    close(file_descriptor);

    *TEST_BLOCK_COUNTER_PTR = TEST_BLOCK_COUNTER;
    return (OPTIONAL_ENCODING_TYPE){1, encoding};
#endif
}

static char const* encoding_type_to_filename(UTF_ENCODING_ENUM() encoding) {
    switch (encoding) {
        case UTF_ENCODING_ENUM_VALUE(UTF32_BE_BOM): return "utf32_BE_BOM.txt";
        case UTF_ENCODING_ENUM_VALUE(UTF32_LE_BOM): return "utf32_LE_BOM.txt";
        case UTF_ENCODING_ENUM_VALUE(UTF16_BE_BOM): return "utf16_BE_BOM.txt";
        case UTF_ENCODING_ENUM_VALUE(UTF16_LE_BOM): return "utf16_LE_BOM.txt";
        case UTF_ENCODING_ENUM_VALUE(UTF8_BOM): return "utf8_BOM.txt";

        case UTF_ENCODING_ENUM_VALUE(UTF32_BE): return "utf32_BE.txt";
        case UTF_ENCODING_ENUM_VALUE(UTF32_LE): return "utf32_LE.txt";
        case UTF_ENCODING_ENUM_VALUE(UTF16_BE): return "utf16_BE.txt";
        case UTF_ENCODING_ENUM_VALUE(UTF16_LE): return "utf16_LE.txt";
        case UTF_ENCODING_ENUM_VALUE(UTF8): return "utf8.txt";
    }
    return NULL;
}
