#pragma once

// for MS VC, refer: https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros
// for all, refer: http://nadeausoftware.com/articles/2012/02/c_c_tip_how_detect_processor_type_using_compiler_predefined_macros

// MS VC defines _M_IX86
// gcc defines __x86_64 and __x86_64__
#if defined(_M_IX86) || defined(__i386) || defined(__i386__)
#define CPU_X86 1
#endif

// MS VC defines _M_AMD64 and _M_X64
// gcc defines __x86_64 and __x86_64__
#if defined(_M_AMD64) || defined (_M_X64) || defined(__x86_64) || defined(__x86_64__)
#define CPU_X86_64 1
#endif

// arm processor
#if defined(__arm__) || defined(_M_ARM)
  #define CPU_ARM 1
#endif

#if defined(__aarch64__) || defined(_M_ARM64)
  #define CPU_ARM64 1
#endif

