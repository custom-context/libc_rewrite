#include <utils/format_print.h>
#include <utils/format.h>

#include <containers/dynamic/string/string.h>

#include <tests/utils/string/raw_string/compare/compare.h>
#include <tests/utils/format/format.h>
#include <tests/containers/reference_counted/reference_counted.h>
#include <tests/concurrent/thread/native_thread.h>
#include <tests/containers/static/array/array.h>
#include <tests/containers/dynamic/array/array.h>
#include <tests/containers/dynamic/string/string.h>
#include <tests/containers/dynamic/tree/rb_tree/set/set.h>
#include <tests/containers/dynamic/tree/rb_tree/map/map.h>
#include <tests/utils/result/result.h>
#include <tests/fs/file/encoding.h>
#include <tests/network/socket/socket.h>
#include <tests/network/address_info/address_info.h>
#include <tests/network/client/client.h>
#include <tests/network/server/server.h>
#include <tests/network/nb_client/nb_client.h>
#include <tests/network/nb_server/nb_server.h>

#if defined(_WIN32)
    #define MAIN _tmain
#else
    #define MAIN main
#endif

void execute_test_by_name(OS_CHAR_TYPE const* test_name);

int MAIN(int const argc, OS_CHAR_TYPE const* const argv[]) {
    UNUSED(argc);
    UNUSED(argv);
    if (argc < 2) {
        NAMESPACE_UTILS(format_print)("Count of arguments less than 2. provided argc: %d", argc);
        return 1;
    }
    execute_test_by_name(OS_STRING_LITERAL("raw_string_compare"));
    for (usize index = 0u; index < (usize)(argc - 1); ++index) {
        execute_test_by_name(argv[index + 1u]);
    }

    return 0;
}

#include "string.h"

#define EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(TEST_NAME_VAR, TEST_NAME)\
if (!RAW_STRING_FUNCTION(OS_CHAR_TYPE, compare)(TEST_NAME_VAR, OS_STRING_LITERAL(#TEST_NAME))) {\
    EXECUTE_TYPE_TESTS(TEST_NAME);\
} else {}\

void execute_test_by_name(OS_CHAR_TYPE const* test_name) {
    #if defined(_WIN32)
    if (!_tcscmp(test_name, OS_STRING_LITERAL("raw_string_compare")))
    #else
    if (!strcmp(test_name, OS_STRING_LITERAL("raw_string_compare")))
    #endif
    {
        EXECUTE_TYPE_TESTS(raw_string_compare);
    }
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, format)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, reference_counted)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, native_thread)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, array)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, dynamic_array)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, rb_tree_set)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, rb_tree_map)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, string)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, result)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, encoding)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, socket)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, address_info)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, client)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, nb_client)
    EXECUTE_TYPE_TESTS_ON_EQUAL_TEST_NAME(test_name, nb_server)
}
