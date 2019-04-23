todo
----
- [x] function/class in namespace
- [ ] using plugin method open dynamic library

CMakeLists.txt explain
----------------------
1. At beginning, specify the miminum cmake version
```cmake
cmake_minimum_required(VERSION 3.5)

2. When build the release type on linux, cmake will add **-O3** option which should be deleted!
```cmake
macro(remove_cxx_flag flag)
    string(REPLACE "${flag}" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endmacro()

# remove c++ floag -O3
remove_cxx_flag("-O3")
```
3. When set optimization option, -O2 is preferred!
```cmake
# Use -O2 for release builds (-O3 doesn't improve perf, and -Os results in perf regression)
target_compile_options(mathlib PRIVATE "$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:-O2>")
```
