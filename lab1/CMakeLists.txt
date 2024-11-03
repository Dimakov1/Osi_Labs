cmake_minimum_required(VERSION 3.10)

project(lab1 C)

set(CMAKE_C_STANDARD 11)

add_executable(lab1
    main.c
    src/parent.c
    src/child.c
    src/utils.c)

target_include_directories(lab1 PRIVATE include)
