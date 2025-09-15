cmake_minimum_required(VERSION 3.20)
project(ForwardListFromScratch LANGUAGES CXX)

# ==== Compiler setup ====
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  add_compile_options(-Wall -Wextra -Wpedantic -O2)
endif()

# ==== Header-only library ====
add_library(forward_list_lib INTERFACE)
target_include_directories(forward_list_lib INTERFACE src)

# ==== GoogleTest via FetchContent ====
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ==== Testing ====
include(CTest)
enable_testing()

add_executable(forward_list_test
  test/testing.cpp
)
target_link_libraries(forward_list_test
  PRIVATE forward_list_lib GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(forward_list_test)
