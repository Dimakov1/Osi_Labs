cmake_minimum_required(VERSION 3.10)

project(OSI_LABS_Tests)

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(lab1_test
    lab1_test.cpp           
    ../lab1/src/parent.c      
    ../lab1/src/child.c          
    ../lab1/src/utils.c       
)

target_include_directories(lab1_test PRIVATE
    ../lab1/include              
)

target_link_libraries(lab1_test PRIVATE GTest::GTest)

add_test(NAME lab1_test COMMAND lab1_test)

add_executable(lab2_test
    lab2_test.cpp
    ../lab2/src/KMeans.cpp
    ../lab2/src/Utils.cpp
    ../lab2/src/Timer.cpp
)

target_include_directories(lab2_test PRIVATE
    ../lab2/include
)

find_package(Threads REQUIRED)

target_link_libraries(lab2_test PRIVATE GTest::GTest Threads::Threads)

add_test(
    NAME lab2_single_thread
    COMMAND lab2_test --gtest_filter=Lab2Test.SingleThreadedRun
)

add_test(
    NAME lab2_multi_thread
    COMMAND lab2_test --gtest_filter=Lab2Test.MultiThreadedRun
)
