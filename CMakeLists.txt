cmake_minimum_required(VERSION 3.14)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(${CMAKE_PROJECT_NAME}_lib src/five.cpp)
add_executable(${CMAKE_PROJECT_NAME}_exe src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)

find_library(GTest gtest)

enable_testing()

add_executable(
  test01
  test/test01.cpp
)
target_link_libraries(
  test01
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test01)