#pragma once

#include <utils/macros.h>

#define DECLARE_TYPE_TESTS(TYPE) extern void FUNCTION_FOR_TYPE(test, TYPE)(const char* TYPE_NAME)
#define IMPLEMENT_TYPE_TESTS(TYPE) void FUNCTION_FOR_TYPE(test, TYPE)(const char* TYPE_NAME)
#define DEFINE_TYPE_TESTS(TYPE) inline static void FUNCTION_FOR_TYPE(test, TYPE)(const char* TYPE_NAME)
#define EXECUTE_TYPE_TESTS_(TYPE) FUNCTION_FOR_TYPE(test, TYPE)(""#TYPE)
#define EXECUTE_TYPE_TESTS(TYPE) EXECUTE_TYPE_TESTS_(TYPE)

#define TEST_BLOCK_(NAME)\
for (char const* TEST_BLOCK_NAME = ""#NAME; TEST_BLOCK_NAME; TEST_BLOCK_NAME = (void*)(0L))\
for (unsigned TEST_BLOCK_COUNTER = 0u; TEST_BLOCK_COUNTER != 1u; TEST_BLOCK_COUNTER = 1u)
#define TEST_BLOCK(NAME) TEST_BLOCK_(NAME)

int errprintf(const char* restrict format, ...);

#define CHECK_(EXPR)\
if (EXPR) {} else {\
    errprintf("[%s][%s][%zu]: at " __FILE__ ":%d: Assertion `" #EXPR "` failed\n", TYPE_NAME, TEST_BLOCK_NAME, TEST_BLOCK_COUNTER++, __LINE__);\
} UNUSED(EXPR)
#define CHECK(EXPR) CHECK_(EXPR)
