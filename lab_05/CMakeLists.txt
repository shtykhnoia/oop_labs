cmake_minimum_required(VERSION 3.10)

project("lab_05")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    TLS_VERIFY false
)
FetchContent_MakeAvailable(gtest)

set(${CXX_FLAGS} "${CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic")

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}_exe main.cpp)

set_target_properties(${PROJECT_NAME}_exe PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()
add_executable(tests_lab_05 tests/tests05.cpp)
target_link_libraries(tests_lab_05 gtest gmock)
add_test(NAME Lab05Tests COMMAND tests_lab_05)


set_target_properties(tests_lab_05 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)


