# set minimum cmake version!
cmake_minimum_required(VERSION 3.5)

project(DynamicLib CXX)

# if not set build type, set Release
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

macro(remove_cxx_flag flag)
    string(REPLACE "${flag}" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endmacro()


# target1: make shared library libmathlib.so on Linux or mathlib.dll on Windows
add_library(mathlib SHARED mathlib.cc)

# add compiler macro
target_compile_definitions(mathlib PRIVATE MATHLIB_BUILD_SHARED_LIBS)

# remove c++ floag -O3
remove_cxx_flag("-O3")

# set optimization option, -O2 is preferred
# Use -O2 for release builds (-O3 doesn't improve perf, and -Os results in perf regression)
target_compile_options(mathlib PRIVATE "$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:-O2>")

# target2: build test example
add_executable(call_test call_test.cc)
target_link_libraries(call_test  mathlib)

