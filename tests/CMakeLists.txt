cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(utest VERSION 0.1.0)

cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH PRIMARY_PROJECT_ROOT_DIR)

include(CTest)
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        main.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PRIMARY_PROJECT_ROOT_DIR}/src
        ..
)

add_definitions(-DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        C_STANDARD 17
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_RULE_MESSAGES OFF)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
elseif(APPLE)
    target_link_options(${PROJECT_NAME} PRIVATE -lpthread -lm -fsanitize=address)
else()
    target_link_options(${PROJECT_NAME} PRIVATE -lasan -lpthread -lm)
endif()

if(WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wpedantic
        -Wall
        -Werror
        -Wno-unused-function
        -Wno-unsafe-buffer-usage # main function's argv array usage is trigger compile error
        -Wno-covered-switch-default # incompatible with `switch-default` warnings
        -Wno-gnu-alignof-expression # confronts with _Alignof usage (that was added in C11)
        -Wno-c++98-compat # project uses aligof
        -Wno-declaration-after-statement
        -Wno-disabled-macro-expansion
        -Wno-switch-enum
        -fmacro-backtrace-limit=0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -pedantic
        -Wall
        -Werror
        -Wno-unused-function
        -Wno-declaration-after-statement
        -Wno-disabled-macro-expansion
        -Wno-switch-enum
        -fsanitize=address
        -O0
        -Wno-sequence-point
        -g)
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        DEBUG
        ENABLE_TESTS
)

add_subdirectory(${PRIMARY_PROJECT_ROOT_DIR}/src primary_project_sources)
add_subdirectory(concurrent)
add_subdirectory(containers)
add_subdirectory(encoding)
add_subdirectory(fs)
add_subdirectory(json)
add_subdirectory(network)
add_subdirectory(utils)

set(TESTS_LIST
    raw_string_compare
    format
    reference_counted
    native_thread
    thread
    optional
    array
    string_view
    dynamic_array_storage
    dynamic_array
    rb_tree_set
    rb_tree_map
    string
    encoding_base64
    result
    json_value
    json_serialize
    json_lexer
    json_parser
    json_deserialize
    socket
    address_info
    client
    nb_client
    nb_server
)

set(FAIL_REGEX "failed")

foreach(TEST ${TESTS_LIST})
add_test(NAME ${TEST}
    COMMAND ${PROJECT_NAME} ${TEST})
set_property(TEST ${TEST}
    PROPERTY
        FAIL_REGULAR_EXPRESSION "${FAIL_REGEX}")
endforeach()
