cmake_minimum_required(VERSION 3.20)
project(lab01 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR "Use GNU GCC: configure with -DCMAKE_CXX_COMPILER=g++")
endif()
add_compile_options(-Wall -Wextra -Wpedantic -g -fsanitize=address -fno-omit-frame-pointer)
add_link_options(-fsanitize=address)

find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
    )
    FetchContent_MakeAvailable(googletest)
endif()

add_library(lab01_lib src/str_ops.cpp)
target_include_directories(lab01_lib PUBLIC include)

add_executable(lab01_main src/main.cpp)
target_link_libraries(lab01_main PRIVATE lab01_lib)

add_executable(tests test/str_ops_test.cpp)
target_link_libraries(tests PRIVATE lab01_lib GTest::gtest_main)
enable_testing()
add_test(NAME Lab01Tests COMMAND tests)