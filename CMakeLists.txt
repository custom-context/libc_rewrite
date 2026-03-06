cmake_minimum_required(VERSION 3.16)
project(unicstm VERSION 0.1.0)

include_directories(${PROJECT_SOURCE_DIR}/src)
add_library(${PROJECT_NAME})

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
    target_link_options(${PROJECT_NAME} PRIVATE -lpthread -lm)
else()
    target_link_options(${PROJECT_NAME} PRIVATE -lasan -lpthread -lm)
endif()

set(COMMON_COMPILE_OPTIONS
    -Wall
    -Werror
    -Wno-unused-function
    -Wno-declaration-after-statement
    -Wno-disabled-macro-expansion
    -Wno-switch-enum
)

# not compatible with c standard less than C11
# but `pre-c11-compat` warning not exists for clang version <=18
include(CheckCCompilerFlag)
check_c_compiler_flag(-Wno-pre-c11-compat NO_PRE_C11_COMPATABILITY_FLAG_EXISTS)
if (NO_PRE_C11_COMPATABILITY_FLAG_EXISTS)
    list(APPEND COMMON_COMPILE_OPTIONS
        -Wno-pre-c11-compat
    )
endif()

if(WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wpedantic
        ${COMMON_COMPILE_OPTIONS}
        -Wno-unsafe-buffer-usage # arrays usage is trigger compile error
        -Wno-covered-switch-default # incompatible with `switch-default` warnings
        -Wno-gnu-alignof-expression # confronts with _Alignof usage (that was added in C11)
        -Wno-c++98-compat # project uses aligof
        -fmacro-backtrace-limit=0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -pedantic
        ${COMMON_COMPILE_OPTIONS}
        -fsanitize=address
        -Wno-sequence-point
        )
endif()

add_subdirectory(src)
