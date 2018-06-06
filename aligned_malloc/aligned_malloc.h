#ifndef ALIGNED_MALLOC_H_
#define ALIGNED_MALLOC_H_

void *aligned_malloc(size_t memsize, size_t alignment);
void aligned_free(void *p);

#endif

