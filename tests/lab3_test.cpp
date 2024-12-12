#include <gtest/gtest.h>
#include <sys/mman.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h> 

extern "C" {
    #include "memory_map.h"
    #include "processes.h"
    #include "error_handling.h"
}

TEST(test_01, basic_test_set) {
    const char* input = "Hello World";
    const char* expected = "hello_world";

    size_t size = 1024;
    char* mem = static_cast<char*>(create_shared_memory(size));
    ASSERT_NE(mem, MAP_FAILED) << "Не удалось создать разделяемую память";
    ASSERT_NE(mem, nullptr) << "Разделяемая память равна nullptr";

    strcpy(mem, input);

    pid_t pid1 = fork();
    ASSERT_GE(pid1, 0) << "Не удалось создать процесс для child1";
    if (pid1 == 0) {
        child1(mem);
        _exit(EXIT_FAILURE);
    }

    int status1;
    waitpid(pid1, &status1, 0);
    ASSERT_TRUE(WIFEXITED(status1)) << "Child1 не завершился корректно";
    ASSERT_EQ(WEXITSTATUS(status1), EXIT_SUCCESS) << "Child1 завершился с ошибкой";
    EXPECT_STREQ(mem, "hello world");

    pid_t pid2 = fork();
    ASSERT_GE(pid2, 0) << "Не удалось создать процесс для child2";
    if (pid2 == 0) {
        child2(mem);
        _exit(EXIT_FAILURE);
    }

    int status2;
    waitpid(pid2, &status2, 0);
    ASSERT_TRUE(WIFEXITED(status2)) << "Child2 не завершился корректно";
    ASSERT_EQ(WEXITSTATUS(status2), EXIT_SUCCESS) << "Child2 завершился с ошибкой";
    EXPECT_STREQ(mem, expected);

    release_shared_memory(mem, size);
}

TEST(test_02, basic_test_set) {
    const char* input = "TestString";
    const char* expected = "teststring";

    size_t size = 1024;
    char* mem = static_cast<char*>(create_shared_memory(size));
    ASSERT_NE(mem, MAP_FAILED) << "Не удалось создать разделяемую память";
    ASSERT_NE(mem, nullptr) << "Разделяемая память равна nullptr";

    strcpy(mem, input);

    pid_t pid1 = fork();
    ASSERT_GE(pid1, 0) << "Не удалось создать процесс для child1";
    if (pid1 == 0) {
        child1(mem);
        _exit(EXIT_FAILURE);
    }

    int status1;
    waitpid(pid1, &status1, 0);
    ASSERT_TRUE(WIFEXITED(status1)) << "Child1 не завершился корректно";
    ASSERT_EQ(WEXITSTATUS(status1), EXIT_SUCCESS) << "Child1 завершился с ошибкой";
    EXPECT_STREQ(mem, "teststring");

    pid_t pid2 = fork();
    ASSERT_GE(pid2, 0) << "Не удалось создать процесс для child2";
    if (pid2 == 0) {
        child2(mem);
        _exit(EXIT_FAILURE);
    }

    int status2;
    waitpid(pid2, &status2, 0);
    ASSERT_TRUE(WIFEXITED(status2)) << "Child2 не завершился корректно";
    ASSERT_EQ(WEXITSTATUS(status2), EXIT_SUCCESS) << "Child2 завершился с ошибкой";
    EXPECT_STREQ(mem, expected);

    release_shared_memory(mem, size);
}

TEST(test_03, basic_test_set) {
    const char* input = "123 Test 456";
    const char* expected = "123_test_456";

    size_t size = 1024;
    char* mem = static_cast<char*>(create_shared_memory(size));
    ASSERT_NE(mem, MAP_FAILED) << "Не удалось создать разделяемую память";
    ASSERT_NE(mem, nullptr) << "Разделяемая память равна nullptr";

    strcpy(mem, input);

    pid_t pid1 = fork();
    ASSERT_GE(pid1, 0) << "Не удалось создать процесс для child1";
    if (pid1 == 0) {
        child1(mem);
        _exit(EXIT_FAILURE);
    }

    int status1;
    waitpid(pid1, &status1, 0);
    ASSERT_TRUE(WIFEXITED(status1)) << "Child1 не завершился корректно";
    ASSERT_EQ(WEXITSTATUS(status1), EXIT_SUCCESS) << "Child1 завершился с ошибкой";
    EXPECT_STREQ(mem, "123 test 456");

    pid_t pid2 = fork();
    ASSERT_GE(pid2, 0) << "Не удалось создать процесс для child2";
    if (pid2 == 0) {
        child2(mem);
        _exit(EXIT_FAILURE);
    }

    int status2;
    waitpid(pid2, &status2, 0);
    ASSERT_TRUE(WIFEXITED(status2)) << "Child2 не завершился корректно";
    ASSERT_EQ(WEXITSTATUS(status2), EXIT_SUCCESS) << "Child2 завершился с ошибкой";
    EXPECT_STREQ(mem, expected);

    release_shared_memory(mem, size);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
