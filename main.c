#include <utils/format_print.h>
#include <utils/format.h>

#include <containers/string.h>
#include <containers/string_impl.h>

#include <tests/containers/array.h>

void test_string_construct_at() {
    string_char str;
    string_char_construct_at(&str);
    utils__format_print("stack allocated string: %s\n", string_char_data(&str));
    utils__format_print("stack allocated string size: %d\n", string_char_size(&str));
    utils__format_print("stack allocated string capacity: %d\n", string_char_capacity(&str));
    utils__format_print("stack allocated string max extension: %d\n", *string_char_at(&str, string_char_capacity(&str)));
    utils__format_print("is stack allocated string: %d\n", str.is_stack_allocated_);
}

void test_string_push_back() {
    string_char str;
    string_char_construct_at(&str);
    for (unsigned i = 0; i < string_char_capacity(&str); ++i) {
        char value = 'a' + string_char_size(&str);
        string_char_push_back(&str, &value);
    }
    utils__format_print("stack allocated string: %s\n", string_char_data(&str));
    utils__format_print("stack allocated string size: %d\n", string_char_size(&str));
    utils__format_print("stack allocated string capacity: %d\n", string_char_capacity(&str));
    utils__format_print("stack allocated string max extension: %d\n", *string_char_at(&str, string_char_capacity(&str)));
    utils__format_print("is stack allocated string: %d\n", str.is_stack_allocated_);
    for (unsigned i = 'a' + string_char_size(&str); i <= 'z'; ++i) {
        char value = i;
        string_char_push_back(&str, &value);
    }
    utils__format_print("stack allocated string: %s\n", string_char_data(&str));
    utils__format_print("stack allocated string size: %d\n", string_char_size(&str));
    utils__format_print("stack allocated string capacity: %d\n", string_char_capacity(&str));
    utils__format_print("is stack allocated string: %d\n", str.is_stack_allocated_);
    for (unsigned i = 'A'; i <= 'Z'; ++i) {
        char value = i;
        string_char_push_back(&str, &value);
    }
    utils__format_print("stack allocated string: %s\n", string_char_data(&str));
    utils__format_print("stack allocated string size: %d\n", string_char_size(&str));
    utils__format_print("stack allocated string capacity: %d\n", string_char_capacity(&str));
    utils__format_print("is stack allocated string: %d\n", str.is_stack_allocated_);
    string_char_destroy_at(&str);
}

void test_string_from_c_string() {
    string_char str;
    string_char_construct_from_c_string_at(&str, "str w. len < 16");
    utils__format_print("stack allocated string: %s\n", string_char_data(&str));
    utils__format_print("stack allocated string size: %d\n", string_char_size(&str));
    utils__format_print("stack allocated string capacity: %d\n", string_char_capacity(&str));
    utils__format_print("is stack allocated string: %d\n", str.is_stack_allocated_);
    string_char_destroy_at(&str);

    string_char_construct_from_c_string_at(&str, "str w. more than 16");
    utils__format_print("stack allocated string: %s\n", string_char_data(&str));
    utils__format_print("stack allocated string size: %d\n", string_char_size(&str));
    utils__format_print("stack allocated string capacity: %d\n", string_char_capacity(&str));
    utils__format_print("is stack allocated string: %d\n", str.is_stack_allocated_);
    string_char_destroy_at(&str);
}

int main(const int argc, char const* const argv[]) {
    string_char formatted_string = utils__format("argc: %d\n", argc);
    utils__format_print(string_char_data(&formatted_string));
    string_char_destroy_at(&formatted_string);

    for (int index = 0u; index < argc; ++index) {
        utils__format_print("argv[%d]: %s\n", index, argv[index]);
    }
    test_string_construct_at();
    test_string_push_back();
    test_string_from_c_string();

    EXECUTE_TYPE_TESTS(array);

    return 0;
}
