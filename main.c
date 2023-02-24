#include <utils/format_print.h>
#include <utils/format.h>

#include <containers/dynamic/string/string.h>

#include <tests/containers/static/array/array.h>
#include <tests/containers/dynamic/string/string.h>
#include <tests/utils/result/result.h>
#include <tests/fs/file/encoding.h>
#include <tests/network/socket/socket.h>
#include <tests/network/address_info/address_info.h>
#include <tests/network/client/client.h>
#include <tests/network/server/server.h>
#include <tests/network/nb_client/nb_client.h>
#include <tests/network/nb_server/nb_server.h>

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
    EXECUTE_TYPE_TESTS(result);
    EXECUTE_TYPE_TESTS(encoding);
    EXECUTE_TYPE_TESTS(socket);
    EXECUTE_TYPE_TESTS(address_info);
    EXECUTE_TYPE_TESTS(client);
    EXECUTE_TYPE_TESTS(server);
    EXECUTE_TYPE_TESTS(nb_client);
    EXECUTE_TYPE_TESTS(nb_server);
}

void print_formatted_args(int const argc, char const* const argv[]) {
    STRING_TYPE() formatted_string = utils__format("argc: %d\n", argc);
    utils__format_print(STRING_METHOD(data)(&formatted_string));
    STRING_METHOD(destroy_at)(&formatted_string);

    for (int index = 0u; index < argc; ++index) {
        utils__format_print("argv[%d]: %s\n", index, argv[index]);
    }
}
