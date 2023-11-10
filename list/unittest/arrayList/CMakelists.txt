cmake_minimum_required(VERSION 3.26)
project(arrayList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#add_subdirectory(${LEARN_STRUCTURE_PROJECT_ROOT}/third-part/googletest-1.14.0 googletest)

add_executable(arrayList_unittest arrayList_unittest.cpp)

target_include_directories(arrayList_unittest PUBLIC
        ${LEARN_STRUCTURE_PROJECT_ROOT}/list
        ${LEARN_STRUCTURE_PROJECT_ROOT}/utils)

target_link_libraries(arrayList_unittest PUBLIC GTest::gtest GTest::gtest_main)

add_test(NAME arrayList_unittest COMMAND arrayList_unittest)