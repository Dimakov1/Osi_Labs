cmake_minimum_required(VERSION 3.20)

project(OS_LABS CXX)

enable_testing()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lab1)
add_subdirectory(lab2)
add_subdirectory(tests)
