#include <gtest/gtest.h>
#include <cstring> 
#include "../include/parent.h"

TEST(test_01, basic_test_set) {
    const char* result = ParentRoutine("Hello World");
    EXPECT_EQ(strcmp(result, "hello_world"), 0); 
}

TEST(test_02, basic_test_set) {
    const char* result = ParentRoutine("TestString");
    EXPECT_EQ(strcmp(result, "teststring"), 0); 
}

TEST(test_03, basic_test_set) {
    const char* result = ParentRoutine("123 Test 456");
    EXPECT_EQ(strcmp(result, "123_test_456"), 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
