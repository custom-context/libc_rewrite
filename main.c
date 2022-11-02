#include <utils/format_print.h>
#include <utils/format.h>

#include <containers/string.h>
#include <containers/string_impl.h>

#include <tests/containers/array/array.h>
#include <tests/containers/string/string.h>
#include <tests/fs/file/encoding.h>

void exec_tests();
void print_formatted_args(int const argc, char const* const argv[const]);

void check_file_encoding(char const filename[const]);

int main(int const argc, char const* const argv[]) {
    exec_tests();

    print_formatted_args(argc, argv);

    return 0;
}

void exec_tests() {
    EXECUTE_TYPE_TESTS(array);
    EXECUTE_TYPE_TESTS(string);
    EXECUTE_TYPE_TESTS(encoding);
}

void print_formatted_args(int const argc, char const* const argv[]) {
    string_char formatted_string = utils__format("argc: %d\n", argc);
    utils__format_print(string_char_data(&formatted_string));
    string_char_destroy_at(&formatted_string);

    for (int index = 0u; index < argc; ++index) {
        utils__format_print("argv[%d]: %s\n", index, argv[index]);
    }
}
