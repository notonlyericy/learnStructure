cmake_minimum_required(VERSION 3.26)
project(stack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(arrayStack_unittest unittest.cpp)

target_include_directories(arrayStack_unittest PUBLIC
        ${LEARN_STRUCTURE_PROJECT_ROOT}/stack
        ${LEARN_STRUCTURE_PROJECT_ROOT}/list
        ${LEARN_STRUCTURE_PROJECT_ROOT}/utils)

target_link_libraries(arrayStack_unittest PUBLIC GTest::gtest GTest::gtest_main)

add_test(NAME arrayStack_unittest COMMAND arrayStack_unittest)