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
    const char* input = "Hello";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "hello");
}

TEST(Lab3Test, MultipleWords) {
    const char* input = "Hello World";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "hello_world");
}

TEST(Lab3Test, MixedCaseAndSpaces) {
    const char* input = "HeLLo WoRLd Test";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "hello_world_test");
}

TEST(Lab3Test, NoSpaces) {
    const char* input = "HELLOWORLD";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "helloworld");
}

TEST(Lab3Test, EmptyString) {
    const char* input = "";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "");
}

TEST(Lab3Test, LeadingAndTrailingSpaces) {
    const char* input = "  Hello World  ";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "__hello_world__");
}

TEST(Lab3Test, SpecialCharacters) {
    const char* input = "Hello, World!";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "hello,_world!");
}

TEST(Lab3Test, NumericCharacters) {
    const char* input = "Test123 456";
    char output[BUFFER_SIZE];

    int result = process_string(input, output, BUFFER_SIZE);
    EXPECT_EQ(result, 0) << "process_string вернула ошибку";
    EXPECT_STREQ(output, "test123_456");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
