cmake_minimum_required(VERSION 3.22)

project(Advent2021 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

# googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

# Entrypoint
add_executable(advent src/main.cc)

# General utilities
add_library(file src/file.c src/file.h)

# Day 1
add_executable(day1-1 src/day1/part1/main.c)
add_library(day1-2_helpers src/day1/part2/helpers.c src/day1/part2/helpers.h)
add_executable(day1-2 src/day1/part2/main.c)
target_link_libraries(day1-2 day1-2_helpers)

# Day 2
add_executable(day2-1 src/day2/part1.c)
add_library(day2_point src/day2/point.c src/day2/point.h)
target_link_libraries(day2-1 file day2_point)
add_executable(day2-2 src/day2/part2.c)
target_link_libraries(day2-2 file day2_point)

# Day 3
add_library(day3-1 src/day3/part1.c src/day3/part1.h)
target_link_libraries(day3-1 file)
add_library(day3-2 src/day3/part2.c src/day3/part2.h)
target_link_libraries(day3-2 file)

# Day 4
add_library(day4-1 src/day4/part1.cc src/day4/part1.h)
target_link_libraries(day4-1 file)
add_library(day4-2 src/day4/part2.cc src/day4/part2.h)
target_link_libraries(day4-2 file)

target_link_libraries(
  advent
  day3-1
  day3-2
  day4-1
  day4-2
)

# Testing
enable_testing()

add_executable(day1-2_test src/day1/part2/helpers_test.cc)
target_link_libraries(day1-2_test gtest_main day1-2_helpers)

add_executable(day2-1_test src/day2/point_test.cc)
target_link_libraries(day2-1_test gtest_main day2_point)

add_executable(day3_test src/day3/test.cc)
target_link_libraries(day3_test gtest_main day3-1 day3-2)

add_executable(day4_test src/day4/test/test.cc)
target_link_libraries(day4_test gtest_main gmock gtest day4-1 file)
configure_file(src/day4/test/test_input.txt test_fixtures/day4/input.txt COPYONLY)

include(GoogleTest)
gtest_discover_tests(day1-2_test)
gtest_discover_tests(day2-1_test)
gtest_discover_tests(day3_test)
gtest_discover_tests(day4_test)
