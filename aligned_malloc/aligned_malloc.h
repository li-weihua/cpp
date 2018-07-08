#ifndef CPP_ALIGNED_MALLOC_H_
#define CPP_ALIGNED_MALLOC_H_

#include <cstddef>

namespace cpp {

void *aligned_malloc(size_t memsize, size_t alignment);
void aligned_free(void *p);

} // namespace cpp

#endif // CPP_ALIGNED_MALLOC_H

