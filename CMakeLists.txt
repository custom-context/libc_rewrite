cmake_minimum_required(VERSION 3.16)
project(unicstm VERSION 0.1.0)

set(CMAKE_C_COMPILER_VERSION 17)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        main.c
)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wno-unused-function -fsanitize=address -g)
target_link_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wno-unused-function -fsanitize=address -g)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        DEBUG
        ENABLE_TESTS
)

add_subdirectory(src)
