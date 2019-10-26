#pragma once

#include <string>

#include "cpu_arch.h"

// cpu vendor
enum class CPUVendor {
  UNKONWN,   // unkown
  X86_INTEL, // intel x86/x64 cpu
  X86_AMD,   // amd
  X86_VIA,   // via

};

// detection instruction set
//
class InstructionSet {
public:

  // do detection
  InstructionSet();


  // x86 isa
  #if defined(CPU_X86) || defined(CPU_X86_64)
  inline CPUVendor GetVendor() const {
    return vendor_;
  }

  inline std::string GetVendorString() const {
    switch (vendor_) {
      case CPUVendor::X86_INTEL: return "INTEL";
      case CPUVendor::X86_AMD:   return "AMD";
      case CPUVendor::X86_VIA:   return "VIA";
      case CPUVendor::UNKONWN: return "UNKONWN";
    }
    return "UNKONWN";
  }

  inline int GetLevel() const {
    return level_;
  }

  inline bool HasSSE() const {
    return sse_;
  }

  inline bool HasSSE2() const {
    return sse2_;
  }

  inline bool HasSSE3() const {
    return sse3_;
  }

  inline bool HasSSSE3() const {
    return ssse3_;
  }

  inline bool HasSSE4_1() const {
    return sse41_;
  }
 
  inline bool HasSSE4_2() const {
    return sse42_;
  }
 
  inline bool HasSSE4A() const {
    return sse4a_;
  }

  inline bool HasAVX() const {
    return avx_;
  }

  inline bool HasF16C() const {
    return f16c_;
  }

  inline bool HasFMA3() const {
    return fma3_;
  }

  inline bool HasFMA4() const {
    return fma4_;
  }

  inline bool HasXOP() const {
    return xop_;
  }

  inline bool HasAVX2() const {
    return avx2_;
  }

  inline bool HasAVX512F() const {
    return avx512f_;
  }

  inline bool HasAVX512CD() const {
    return avx512cd_;
  }
 
  inline bool HasAVX512DQ() const {
    return avx512dq_;
  }

  inline bool HasAVX512BW() const {
    return avx512bw_;
  }

  inline bool HasAVX512VL() const {
    return avx512vl_;
  }

  inline bool HasAVX512PF() const {
    return avx512pf_;
  }

  inline bool HasAVX512ER() const {
    return avx512er_;
  }

  // arm isa
  #elif defined(CPU_ARM) || defined(CPU_ARM64)

  #endif

private:
  // cpu vendor
  CPUVendor vendor_;
    
  // for x86
  int level_;
  bool sse_;
  bool sse2_;
  bool sse3_;
  bool ssse3_;
  bool sse41_;
  bool sse42_;
  bool sse4a_; // only for amd
  bool f16c_;
  bool avx_;
  bool fma3_;
  bool fma4_; // only for amd
  bool xop_;  // only for amd
  bool avx2_;
  bool avx512f_;
  bool avx512cd_;
  bool avx512bw_;
  bool avx512vl_;
  bool avx512dq_;
  bool avx512er_;
  bool avx512pf_;
  bool avx512_ifma_;

  // for arm
};

//
InstructionSet* GetISA();
