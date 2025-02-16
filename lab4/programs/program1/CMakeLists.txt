cmake_minimum_required(VERSION 3.10)

project(program1 C)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(program1 main.c)

target_link_libraries(program1 PRIVATE gcf sort)

install(TARGETS program1 DESTINATION bin)
