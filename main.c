#include <utils/format_print.h>
#include <utils/format.h>

#include <containers/string.h>
#include <containers/string_impl.h>

#include <tests/containers/array/array.h>
#include <tests/containers/string/string.h>
#include <fs/file/encoding.h>

void exec_tests();
void print_formatted_args(int const argc, char const* const argv[const]);

void check_file_encoding(char const filename[const]);

int main(int const argc, char const* const argv[]) {
    exec_tests();

    print_formatted_args(argc, argv);

    if (argc < 2) {
        utils__format_print("file name not passed as second parameter");
        return 1;
    }
    check_file_encoding(argv[1]);

    return 0;
}

void exec_tests() {
    EXECUTE_TYPE_TESTS(array);
    EXECUTE_TYPE_TESTS(string);
}

void print_formatted_args(int const argc, char const* const argv[]) {
    string_char formatted_string = utils__format("argc: %d\n", argc);
    utils__format_print(string_char_data(&formatted_string));
    string_char_destroy_at(&formatted_string);

    for (int index = 0u; index < argc; ++index) {
        utils__format_print("argv[%d]: %s\n", index, argv[index]);
    }
}

#include <unistd.h>
#include <fcntl.h>

void check_file_encoding(char const filename[const]) {
    int file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1) {
        utils__format_print("file `%s` not found", filename);
        return;
    }
    char bytes[4];
    ssize_t count_bytes_read = read(file_descriptor, bytes, sizeof(bytes));
    
    UTF_ENCODING_ENUM() encoding = NAMESPACE_FS_FILE(get_encoding)(count_bytes_read, bytes);

    switch (encoding) {
        case UTF_ENCODING_ENUM_VALUE(UTF32_BE): utils__format_print("file `%s` encoding is UTF-32 BE", filename); break;
        case UTF_ENCODING_ENUM_VALUE(UTF32_LE): utils__format_print("file `%s` encoding is UTF-32 LE", filename); break;
        case UTF_ENCODING_ENUM_VALUE(UTF16_BE): utils__format_print("file `%s` encoding is UTF-16 BE", filename); break;
        case UTF_ENCODING_ENUM_VALUE(UTF16_LE): utils__format_print("file `%s` encoding is UTF-16 LE", filename); break;
        case UTF_ENCODING_ENUM_VALUE(UTF8_BOM): utils__format_print("file `%s` encoding is UTF-8 with BOM", filename); break;
        case UTF_ENCODING_ENUM_VALUE(UTF8): utils__format_print("file `%s` encoding is UTF-8", filename); break;
    }

    close(file_descriptor);
}
