#include "def.h"
#include "testing.h"
#include <stdlib.h>

// for drop
void free4drop(void *const restrict pp) { free(*(void **)pp); }

// greater realloc
void *grealloc(void *restrict old, size_t sz) {
  return realloc(old, sz) ?: p$panic(ERR_ALLOC);
}

test(leak) { void *p drop = malloc(100); }

test(galloc) {
  char *p drop = galloc(char, 100);
  expectneq(nullptr, (void *)p);
  // Terminate with error
  // char *q = galloc(long long, 0xffffffffffffffff);
  p = grealloc(p, 10000);
  expectneq(nullptr, (void *)p);
}
