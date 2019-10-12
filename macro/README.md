## how to check the OS(platform)
```
Linux and Linux-derived           __linux__
Android                           __ANDROID__ (implies __linux__)
Linux (non-Android)               __linux__ && !__ANDROID__
Darwin (Mac OS X and iOS)         __APPLE__
Windows                           _WIN32
Windows 64 bit                    _WIN64 (implies _WIN32)
Fuschia                           __Fuchsia__
```

## how to check the compiler
```
Visual Studio       _MSC_VER
gcc                 __GNUC__
clang               __clang__ (also defines __GNUC__)
icc                 __ICC (linux, macos)
icc                 __ICL (windows)
nvcc                __CUDACC__
```
note: on linux platform, clang and icc are compatible with gcc. 
while on windows platform, icc is compatible with vc++.

```c
#if defined(__clang__)
	/* Clang/LLVM. ---------------------------------------------- */

#elif defined(__ICC) || defined(__INTEL_COMPILER)
	/* Intel ICC/ICPC. ------------------------------------------ */

#elif defined(__GNUC__) || defined(__GNUG__)
	/* GNU GCC/G++. --------------------------------------------- */

#elif defined(_MSC_VER)
	/* Microsoft Visual Studio. --------------------------------- */

#endif

#if defined(__CUDACC__)
	/* NVCC --------------------------------- */

#endif
```

## how to check the compiler version

- clang/llvm
  - **\_\_clang_major__**, **\_\_clang_minor__**, and **\_\_clang_patchlevel__** contain the major version, minor version, and patch level numbers, e.g. "8", "0", and "1" for version 8.0.1
  - **\_\_clang_version__** contains a version string, eg. "8.0.1 (tags/RELEASE_801/final)"

