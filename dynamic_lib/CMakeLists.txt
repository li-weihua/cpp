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

# remove c++ floag -O3
remove_cxx_flag("-O3")

# c++11
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
