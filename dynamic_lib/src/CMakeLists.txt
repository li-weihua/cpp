cmake_minimum_required(VERSION 3.12)

project(call_test)
add_library(mathlib SHARED mathlib.cc)
add_compile_definitions(MATHLIB_BUILD_SHARED_LIBS)

add_executable(call_test call_test.cc)
target_link_libraries(call_test  mathlib)

