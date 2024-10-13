cmake_minimum_required(VERSION 3.10)

project(lab1_test_project)

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
    ../lab1/src/child1.c        
    ../lab1/src/child2.c      
    ../lab1/src/utils.c       
)

target_include_directories(lab1_test PRIVATE
    ../lab1/include              
)

target_link_libraries(lab1_test PRIVATE GTest::GTest)

add_test(NAME lab1_test COMMAND lab1_test)
