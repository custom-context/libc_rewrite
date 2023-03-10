cmake_minimum_required(VERSION 3.16)
project(unicstm VERSION 0.1.0)

set(CMAKE_C_COMPILER_VERSION 17)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
    PRIVATE
        main.c
)

add_definitions(-DPROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
    target_compile_options(${PROJECT_NAME} PRIVATE /std:c17 -Wpedantic -Wall -Werror -Wno-unused-function -Wno-declaration-after-statement -fmacro-backtrace-limit=0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -pednatic -Wall -Werror -Wno-unused-function -Wno-declaration-after-statement -fmacro-backtrace-limit=0 -fsanitize=address -g)
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        DEBUG
        ENABLE_TESTS
)

add_subdirectory(src)
