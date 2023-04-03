cmake_minimum_required(VERSION 3.16)
project(unicstm VERSION 0.1.0)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        main.c
)

add_definitions(-DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 17)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wpedantic
        -Wall
        -Werror
        -Wno-unused-function
        -Wno-declaration-after-statement
        -Wno-disabled-macro-expansion
        -fmacro-backtrace-limit=0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -pednatic
        -Wall
        -Werror
        -Wno-unused-function
        -Wno-declaration-after-statement
        -Wno-disabled-macro-expansion
        -fmacro-backtrace-limit=0
        -fsanitize=address
        -g)
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        DEBUG
        ENABLE_TESTS
)

add_subdirectory(src)
