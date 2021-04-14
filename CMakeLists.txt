cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/run_tests.dir)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


set(SOURCES_SOLVER
    main.cpp
    cards.cpp
    cards.hpp
)


add_executable(run ${SOURCES_SOLVER})


set(SOURCES_TESTS
    test.cpp
    cards.hpp
    cards.cpp
)

add_executable(tests ${SOURCES_TESTS})

target_link_libraries(tests ${GTEST_LIBRARIES} pthread)

