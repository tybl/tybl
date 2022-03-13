#include <cstdlib>
#include <cstdio>

void * operator new(size_t size)
{
  void * p = malloc(size);
  fprintf(stderr, "operator new(%lu) returned %p\n", size, p);
  return p;
}

void operator delete(void * p) noexcept
{
  fprintf(stderr, "operator delete(%p)\n", p);
  free(p);
}

void operator delete(void * p, size_t size) noexcept
{
  fprintf(stderr, "operator delete(%p, %lu)\n", p, size);
  free(p);
}
