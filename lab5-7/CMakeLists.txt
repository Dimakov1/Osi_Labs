project(ZMQProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(/opt/homebrew/include)
include_directories(${CMAKE_SOURCE_DIR}/include) 
link_directories(/opt/homebrew/lib)

add_executable(client src/client.cpp)
add_executable(worker src/worker.cpp)

target_link_libraries(client zmq)
target_link_libraries(worker zmq)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests
    tests/test_main.cpp
    include/node.h
    include/net_func.h
)

target_link_libraries(tests PRIVATE ${GTEST_LIBRARIES} zmq Threads::Threads)

enable_testing()
add_test(NAME ZMQTests COMMAND tests)

add_custom_target(clean COMMAND ${CMAKE_COMMAND} -E remove -f client worker tests)
