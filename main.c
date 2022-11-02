#include <utils/format_print.h>
#include <utils/format.h>

#include <containers/string.h>
#include <containers/string_impl.h>

#include <tests/containers/array.h>
#include <tests/containers/string.h>

int main(const int argc, char const* const argv[]) {
    string_char formatted_string = utils__format("argc: %d\n", argc);
    utils__format_print(string_char_data(&formatted_string));
    string_char_destroy_at(&formatted_string);

    for (int index = 0u; index < argc; ++index) {
        utils__format_print("argv[%d]: %s\n", index, argv[index]);
    }

    EXECUTE_TYPE_TESTS(array);
    EXECUTE_TYPE_TESTS(string);

    return 0;
}
