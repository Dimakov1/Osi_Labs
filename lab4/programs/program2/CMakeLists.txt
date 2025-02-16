cmake_minimum_required(VERSION 3.10)

project(program2 C)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(program2 main.c)

target_link_libraries(program2 PRIVATE gcf sort dl)

install(TARGETS program2 DESTINATION bin)
