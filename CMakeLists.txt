cmake_minimum_required(VERSION 3.16)
project(unicstm VERSION 0.1.0)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_library(${PROJECT_NAME})

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
    target_link_options(${PROJECT_NAME} PRIVATE -lasan -lpthread -lm)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -pedantic
        -Wall
        -Werror
        -Wno-unused-function
        -Wno-declaration-after-statement
        -Wno-disabled-macro-expansion
        -fsanitize=address
        -Wno-sequence-point
        )
endif()

add_subdirectory(src)
