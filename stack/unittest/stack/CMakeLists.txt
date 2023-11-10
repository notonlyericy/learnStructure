cmake_minimum_required(VERSION 3.26)
project(stack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(stack_unittest stack_unittest.cpp)

target_include_directories(stack_unittest PUBLIC
        ${LEARN_STRUCTURE_PROJECT_ROOT}/stack
        ${LEARN_STRUCTURE_PROJECT_ROOT}/list
        ${LEARN_STRUCTURE_PROJECT_ROOT}/utils)

target_link_libraries(stack_unittest PUBLIC GTest::gtest GTest::gtest_main)

add_test(NAME stack_unittest COMMAND stack_unittest)