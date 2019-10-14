#pragma once

#include "cpu_arch.h"

#if !defined(CPU_X86) && !defined(CPU_X86_64)
#error "not x86 cpu"
#endif

#if defined(_MSC_VER)
  #include <intrin.h>
#endif

#include <cstdint>

struct cpuid_regs {
  int32_t eax;
  int32_t ebx;
  int32_t ecx;
  int32_t edx;
};

//
namespace {

cpuid_regs cpuid(int32_t eax) {
  struct cpuid_regs r;
  #if defined(__GNUC__)
  //__cpuid(eax, r.eax, r.ebx, r.ecx, r.edx);
  __asm__ ("cpuid\n\t"
           : "=a" (r.eax), "=b" (r.ebx), "=c" (r.ecx), "=d" (r.edx)
           : "0" (eax));
  #else // windows
  int32_t regs[4];
  __cpuid(regs, eax);
  r.eax = regs[0];
  r.ebx = regs[1];
  r.ecx = regs[2];
  r.edx = regs[3];
  #endif

  return r;
}

cpuid_regs cpuidex(int32_t eax, int32_t ecx) {
  struct cpuid_regs r;
  #if defined(__GNUC__)
  //__cpuid_count(eax, ecx, r.eax, r.ebx, r.ecx, r.edx);
  __asm__ ("cpuid\n\t"
           : "=a" (r.eax), "=b" (r.ebx), "=c" (r.ecx), "=d" (r.edx)
           : "0" (eax), "2" (ecx));
  #else // windows
  int32_t regs[4];
  __cpuidex(regs, eax, ecx);
  r.eax = regs[0];
  r.ebx = regs[1];
  r.ecx = regs[2];
  r.edx = regs[3];
  #endif

  return r;
}

// The following code is copied from Agner's vector class library!
//
// Define interface to xgetbv instruction
//
uint64_t xgetbv(int32_t ctr) {	
#if (defined (_MSC_FULL_VER) && _MSC_FULL_VER >= 160040000) || (defined (__INTEL_COMPILER) && __INTEL_COMPILER >= 1200) 
    // Microsoft or Intel compiler supporting _xgetbv intrinsic

    return uint64_t(_xgetbv(ctr));                    // intrinsic function for XGETBV

#elif defined(__GNUC__)                               // use inline assembly, Gnu/AT&T syntax

   uint32_t a, d;
   __asm("xgetbv" : "=a"(a),"=d"(d) : "c"(ctr) : );
   return a | (uint64_t(d) << 32);

#else  // #elif defined (_WIN32)                      // other compiler. try inline assembly with masm/intel/MS syntax
   uint32_t a, d;
    __asm {
        mov ecx, ctr
        _emit 0x0f
        _emit 0x01
        _emit 0xd0 ; // xgetbv
        mov a, eax
        mov d, edx
    }
   return a | (uint64_t(d) << 32);

#endif
}

} // namespace

