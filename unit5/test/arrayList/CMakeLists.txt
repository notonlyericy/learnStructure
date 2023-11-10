cmake_minimum_required(VERSION 3.23)
project(arrayList)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(../../../includes)
add_executable(
        arrayList
        main.cpp
)
target_link_libraries(
        arrayList
        GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(arrayList)