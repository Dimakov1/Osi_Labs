cmake_minimum_required(VERSION 3.10)

project(OSI_LABS_Tests)

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
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

add_executable(lab3_test
    lab3_test.cpp
    ../lab3/src/error_handling.c
    ../lab3/src/memory_map.c
    ../lab3/src/processes.c
)

target_include_directories(lab3_test PRIVATE
    ../lab3/include
)

target_link_libraries(lab3_test PRIVATE GTest::GTest)

add_test(NAME lab3_test COMMAND lab3_test)

add_executable(lab4_gcf_test
    gcf_test.cpp
    ../lab4/src/gcf_euclidean.c
    ../lab4/src/gcf_naive.c
    ../lab4/src/gcf_wrapper.c
)

target_include_directories(lab4_gcf_test PRIVATE
    ../lab4/include
)

target_link_libraries(lab4_gcf_test PRIVATE GTest::GTest)

add_test(NAME lab4_gcf_test COMMAND lab4_gcf_test)

add_executable(lab4_sort_test
    sort_test.cpp
    ../lab4/src/sort_bubble.c
    ../lab4/src/sort_quick.c
    ../lab4/src/sort_wrapper.c
)

target_include_directories(lab4_sort_test PRIVATE
    ../lab4/include
)

target_link_libraries(lab4_sort_test PRIVATE GTest::GTest)

add_test(NAME lab4_sort_test COMMAND lab4_sort_test)
