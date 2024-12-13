cmake_minimum_required(VERSION 3.10)

project(lab4 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(include)

add_library(gcf SHARED
    src/gcf_euclidean.c
    src/gcf_naive.c
    src/gcf_wrapper.c
)

set_target_properties(gcf PROPERTIES
    PUBLIC_HEADER include/gcf.h
)

add_library(sort SHARED
    src/sort_bubble.c
    src/sort_quick.c
    src/sort_wrapper.c
)

set_target_properties(sort PROPERTIES
    PUBLIC_HEADER include/sort.h
)

install(TARGETS gcf sort
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)
