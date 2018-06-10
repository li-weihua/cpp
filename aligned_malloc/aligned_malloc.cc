#include <cstdlib>

#include "aligned_malloc.h"

namespace cpp {

void *aligned_malloc(size_t memsize, size_t alignment) {
  void *p1 = NULL;
  void **p2 = NULL;

  size_t offset = (alignment - 1) + sizeof(void *);
  p1 = std::malloc(memsize + offset);
  if (NULL == p1) {
    return NULL;
  }

  p2 = (void **)(((size_t)p1 + offset) &~ (alignment-1));
  p2[-1] = p1;

  return p2;
}

void aligned_free(void *p) {
  free(((void **)p)[-1]);
}

} // namespace cpp

