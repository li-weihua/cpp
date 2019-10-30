#pragma once

// reference:
// Linux: https://gcc.gnu.org/wiki/Visibility
// Windows:
// https://docs.microsoft.com/en-us/cpp/cpp/dllexport-dllimport?view=vs-2017

#ifdef _WIN32 
#if defined(BUILD_SHARED_LIBS)
#define LIBRARY_API  __declspec(dllexport)
#else
#define LIBRARY_API  __declspec(dllimport)
#endif
#else // _WIN32
#if defined(__GNUC__)
#define LIBRARY_API __attribute__((__visibility__("default")))
#else // __GNUC__
#define LIBRARY_API
#endif // __GNUC__
#endif

