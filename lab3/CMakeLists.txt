cmake_minimum_required(VERSION 3.10)

project(InterProcessCommunication C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)

add_executable(lab3
    main.c
    src/error_handling.c
    src/memory_map.c
    src/processes.c
)
