#include <iostream>
#include <string>

#include "instruction_set.h"

inline const char * const BoolString(bool b) {
  return b ? "True" : "False";
}

int main() {

  std::cout << "support SSE: " << BoolString(GetISA()->HasSSE()) << std::endl;
  std::cout << "support SSE2: " << BoolString(GetISA()->HasSSE2()) << std::endl;
  std::cout << "support SSE3: " << BoolString(GetISA()->HasSSE3()) << std::endl;
  std::cout << "support SSSE3: " << BoolString(GetISA()->HasSSSE3()) << std::endl;
  std::cout << "support SSE4.1: " << BoolString(GetISA()->HasSSE4_1()) << std::endl;
  std::cout << "support SSE4.2: " << BoolString(GetISA()->HasSSE4_2()) << std::endl;
  std::cout << "support SSE4a: " << BoolString(GetISA()->HasSSE4A()) << std::endl;
  std::cout << "support AVX: " << BoolString(GetISA()->HasAVX()) << std::endl;
  std::cout << "support F16C: " << BoolString(GetISA()->HasF16C()) << std::endl;
  std::cout << "support FMA3: " << BoolString(GetISA()->HasFMA3()) << std::endl;
  std::cout << "support FMA4: " << BoolString(GetISA()->HasFMA4()) << std::endl;
  std::cout << "support XOP: " << BoolString(GetISA()->HasXOP()) << std::endl;
  std::cout << "support AVX2: " << BoolString(GetISA()->HasAVX2()) << std::endl;
  std::cout << "support AVX512F: "
            <<  BoolString(GetISA()->HasAVX512F()) << std::endl;

  std::cout << "support AVX512CD: "
            <<  BoolString(GetISA()->HasAVX512CD()) << std::endl;

  std::cout << "support AVX512DQ: "
            <<  BoolString(GetISA()->HasAVX512DQ()) << std::endl;

  std::cout << "support AVX512BW: "
            <<  BoolString(GetISA()->HasAVX512BW()) << std::endl;

  std::cout << "support AVX512VL: "
            <<  BoolString(GetISA()->HasAVX512VL()) << std::endl;

  std::cout << "support AVX512PF: "
            <<  BoolString(GetISA()->HasAVX512PF()) << std::endl;

  std::cout << "support AVX512ER: "
            <<  BoolString(GetISA()->HasAVX512ER()) << std::endl;


  return 0;
}
