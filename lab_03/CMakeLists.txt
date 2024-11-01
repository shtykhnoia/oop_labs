cmake_minimum_required(VERSION 3.10)
project("Lab 3" VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -Werror=maybe-uninitialized")

include_directories(${PROJECT_SOURCE_DIR}/include)

# Pull and build Google Test
include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    TLS_VERIFY false
)
FetchContent_MakeAvailable(gtest)

# The definition of the Shapes library
add_library(
    figures
    src/figure.cpp
    src/rectangle.cpp
)



# Executables
add_executable(main src/main.cpp)

add_executable(rectangleTest tests/rectangle.cpp)
target_link_libraries(rectangleTest figures gtest)

target_include_directories(figures PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE figures)

# Testing configuration
enable_testing()
add_test(NAME TRIANGLE_SUITE COMMAND rectangleTest)