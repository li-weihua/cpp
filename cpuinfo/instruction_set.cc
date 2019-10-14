#include "instruction_set.h"

// x86
#if defined(CPU_X86) || defined(CPU_X86_64)
#include "cpuid_x86.h"
// arm 
#elif defined(_M_AMD64) || defined(CPU_X86_64)
#include "cpuid_arm.h"
#endif

InstructionSet::InstructionSet(): 
  level_(0),
  sse_(false),
  sse2_(false),
  sse3_(false),
  ssse3_(false),
  sse41_(false),
  sse42_(false),
  sse4a_(false),
  f16c_(false),
  avx_(false),
  fma3_(false),
  fma4_(false),
  xop_(false),
  avx2_(false),
  avx512f_(false),
  avx512cd_(false),
  avx512bw_(false),
  avx512vl_(false),
  avx512dq_(false),
  avx512er_(false),
  avx512pf_(false), 
  avx512_ifma_(false) {

  cpuid_regs regs = cpuid(1);

  // check SSE
  if (regs.edx & (1<<25)) sse_   = true;
  if (regs.edx & (1<<26)) sse2_  = true;
  if (regs.ecx & (1<<0))  sse3_  = true;
  if (regs.ecx & (1<<9))  ssse3_ = true;
  if (regs.ecx & (1<<19)) sse41_ = true;
  if (regs.ecx & (1<<20)) sse42_ = true;
  if (regs.ecx & (1<<6)) sse4a_ = true;

  // check AVX
  // first check the hardware support OSXSAVE and AVX
  // then check the operating system also support XMM and YMM state
  bool osxsave = regs.ecx & (1<<27);
  bool b_avx = regs.ecx & (1<<28);
  bool os_support = (xgetbv(0) & 6 == 6);

  if (osxsave && b_avx && os_support) avx_ = true;

  // check F16C
  if (avx_ && (regs.ecx & (1<<29))) f16c_ = true;

  // check FMA3
  if (avx_ && (regs.ecx & (1<<12))) fma3_ = true;

  // check FMA4 and XOP
  regs = cpuid(0x80000001);
  if (avx_ && (regs.ecx & (1<<16))) fma4_ = true;
  if (avx_ && (regs.ecx & (1<<11))) xop_ = true;

  // check AVX2
  regs = cpuidex(7, 0);
  if (avx_ && (regs.ebx & (1<<5))) avx2_ = true;

  // check AVX512
  bool b_avx512f = (regs.ebx & (1<<16));
  // intel document convetion bit 0-31, so xcr0[7:5] means 6,7,8
  // execute xgetbv and verify xcr0[7:5] = '111b' (1110,0000)
  // opmask, upper 256-bit zmm, and zmm
  os_support = os_support && (xgetbv(0) & 0xC0 == 0xC0);
  if (osxsave && b_avx512f && os_support) avx512f_ = true;

  // check AVX512DQ
  if (avx512f_ && (regs.ebx & (1<<17))) avx512dq_ = true;

  // check AVX512_IFMA
  if (avx512f_ && (regs.ebx & (1<<21))) avx512_ifma_ = true;

  // check AVX512PF
  if (avx512f_ && (regs.ebx & (1<<26))) avx512pf_ = true;

  // check AVX512ER
  if (avx512f_ && (regs.ebx & (1<<27))) avx512er_ = true;

  // check AVX512CD
  if (avx512f_ && (regs.ebx & (1<<28))) avx512cd_ = true;

  // check AVX512BW
  if (avx512f_ && (regs.ebx & (1<<30))) avx512bw_ = true;

  // check AVX512VL
  if (avx512f_ && (regs.ebx & (1<<31))) avx512vl_ = true;

}


static InstructionSet g_InstructionSet;

InstructionSet* GetISA() {
  return &g_InstructionSet;
}


