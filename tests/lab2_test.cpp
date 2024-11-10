#include <gtest/gtest.h>
#include <cstdlib>

int run_program(const std::string& input_file) {
    std::string command = "./lab2/lab2 < " + input_file;
    #ifdef _WIN32
    #endif
    return system(command.c_str());
}

TEST(Lab2Test, SingleThreadedRun) {
    int ret = run_program("../tests/files_for_lab2/input_single.txt");
    EXPECT_EQ(ret, 0) << "Однопоточный запуск завершился с ошибкой.";
}

TEST(Lab2Test, MultiThreadedRun) {
    int ret = run_program("../tests/files_for_lab2/1_flow.txt");
    EXPECT_EQ(ret, 0) << "Многопоточный запуск завершился с ошибкой.";
}

TEST(Lab2Test, MultiThreadedRun2) {
    int ret = run_program("../tests/files_for_lab2/4_flow.txt");
    EXPECT_EQ(ret, 0) << "Многопоточный запуск завершился с ошибкой.";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
