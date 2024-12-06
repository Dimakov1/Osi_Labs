cmake_minimum_required(VERSION 3.10)

project(lab2 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(lab2
    main.cpp
    src/KMeans.cpp
    src/Timer.cpp
    src/Utils.cpp
)

target_include_directories(lab2 PRIVATE include)

find_package(Threads REQUIRED)

target_link_libraries(lab2 PRIVATE Threads::Threads)
