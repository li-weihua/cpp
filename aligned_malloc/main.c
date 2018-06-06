#include <stdio.h>

#include "aligned_malloc.h"

int main() {

  const int alignment = 32; 
  size_t memsize = 10 * sizeof(int);

  int *p = aligned_malloc(memsize, alignment);

  printf("true start address: %p\n", ((void **)p)[-1]);
  printf("aligned start address: %p\n", p);

  aligned_free(p);

  return 0;
}
