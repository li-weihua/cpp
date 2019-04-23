# target1: make shared library libmathlib.so on Linux or mathlib.dll on Windows
add_library(mathlib SHARED mathlib.cc)

# add compiler macro
target_compile_definitions(mathlib PRIVATE MATHLIB_BUILD_SHARED_LIBS)

# set optimization option, -O2 is preferred
# Use -O2 for release builds (-O3 doesn't improve perf, and -Os results in perf regression)
target_compile_options(mathlib PRIVATE "$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:-O2>")

# target2: build test example
add_executable(call_test call_test.cc)
target_link_libraries(call_test  mathlib)

