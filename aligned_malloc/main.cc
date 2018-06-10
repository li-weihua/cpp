#include <cstdio>

#include "aligned_malloc.h"

int main() {

  const int alignment = 32; 
  size_t memsize = 10 * sizeof(int);

  int *p = static_cast<int *>(cpp::aligned_malloc(memsize, alignment));

  std::printf("true start address: %p\n", ((void **)p)[-1]);
  std::printf("aligned start address: %p\n", p);

  cpp::aligned_free(p);

  return 0;
}
