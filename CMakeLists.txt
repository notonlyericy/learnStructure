cmake_minimum_required(VERSION 3.23)
project(learn_structure)
add_executable(have_fun main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LEARN_STRUCTURE_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(LEARN_STRUCTURE_BIN_ROOT ${CMAKE_CURRENT_BINARY_DIR})

enable_testing()
add_subdirectory(${LEARN_STRUCTURE_PROJECT_ROOT}/third-part/googletest-1.14.0 googletest)
add_subdirectory(list/unittest/arrayList)
add_subdirectory(stack/unittest/stack)