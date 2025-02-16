#include <gtest/gtest.h>
#include <cstring>
#include <string>

extern "C" {
    #include "error_handling.h"
    #include "memory_map.h"
    #include "processes.h"
}

#define BUFFER_SIZE 1024

TEST(Lab3Test, SingleWord) {
    init_child_process(BUFFER_SIZE);
    const char* input = "Hello World";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "hello_world");
}

TEST(Lab3Test, NoSpaces) {
    init_child_process(BUFFER_SIZE);
    const char* input = "TestString";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "teststring");
}

TEST(Lab3Test, EmptyString) {
    init_child_process(BUFFER_SIZE);
    const char* input = "";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "");
}

TEST(Lab3Test, LeadingAndTrailingSpaces) {
    init_child_process(BUFFER_SIZE);
    const char* input = "  Hello World  ";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "__hello_world__");
}

TEST(Lab3Test, SpecialCharacters) {
    init_child_process(BUFFER_SIZE);
    const char* input = "Hello, World!";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "hello,_world!");
}

TEST(Lab3Test, NumericCharacters) {
    init_child_process(BUFFER_SIZE);
    const char* input = "123 Test 456";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "123_test_456");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
