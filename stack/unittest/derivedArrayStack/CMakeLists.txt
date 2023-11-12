cmake_minimum_required(VERSION 3.26)
project(stack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(derivedArrayStack_unittest unittest.cpp)

target_include_directories(derivedArrayStack_unittest PUBLIC
        ${LEARN_STRUCTURE_PROJECT_ROOT}/stack
        ${LEARN_STRUCTURE_PROJECT_ROOT}/list
        ${LEARN_STRUCTURE_PROJECT_ROOT}/utils)

target_link_libraries(derivedArrayStack_unittest PUBLIC GTest::gtest GTest::gtest_main)

add_test(NAME derivedArrayStack_unittest COMMAND derivedArrayStack_unittest)