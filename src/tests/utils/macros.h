#pragma once

#include <utils/macros.h>

#ifdef ENABLE_TESTS

#include <stdio.h>

#define DECLARE_TYPE_TESTS(TYPE) extern void FUNCTION_FOR_TYPE(test, TYPE)(const char* TYPE_NAME)
#define IMPLEMENT_TYPE_TESTS(TYPE) void FUNCTION_FOR_TYPE(test, TYPE)(const char* TYPE_NAME)
#define DEFINE_TYPE_TESTS(TYPE) inline static void FUNCTION_FOR_TYPE(test, TYPE)(const char* TYPE_NAME)
#define EXECUTE_TYPE_TESTS_(TYPE) FUNCTION_FOR_TYPE(test, TYPE)(""#TYPE)
#define EXECUTE_TYPE_TESTS(TYPE) EXECUTE_TYPE_TESTS_(TYPE)

#define TEST_BLOCK_(NAME)\
for (char* TEST_BLOCK_NAME = ""#NAME; TEST_BLOCK_NAME != NULL; TEST_BLOCK_NAME = NULL)\
for (size_t TEST_BLOCK_COUNTER = 0; TEST_BLOCK_COUNTER != 1; TEST_BLOCK_COUNTER = 1)
#define TEST_BLOCK(NAME) TEST_BLOCK_(NAME)

#define CHECK_(EXPR)\
if (EXPR) {} else {\
    printf("[%s][%s][%zu]: at " __FILE__ ":%d: Assertion `" #EXPR "` failed\n", TYPE_NAME, TEST_BLOCK_NAME, TEST_BLOCK_COUNTER++, __LINE__);\
} UNUSED(EXPR)
#define CHECK(EXPR) CHECK_(EXPR)

#else

#include <stddef.h>

#define DECLARE_TYPE_TESTS(TYPE) extern void FUNCTION_FOR_TYPE(test, TYPE)(const char* TYPE_NAME)
#define IMPLEMENT_TYPE_TESTS(TYPE) void FUNCTION_FOR_TYPE(test, TYPE)(const char* TYPE_NAME)
#define DEFINE_TYPE_TESTS(TYPE) inline static void FUNCTION_FOR_TYPE(test, TYPE)(const char* TYPE_NAME)
#define EXECUTE_TYPE_TESTS(TYPE)
#define TEST_BLOCK(NAME)\
for (char* TEST_BLOCK_NAME; 0;)\
for (size_t TEST_BLOCK_COUNTER; 0;)

#define CHECK(EXPR) {}

#endif
