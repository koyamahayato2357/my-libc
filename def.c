#include "def.h"
#include "testing.h"
#include <stdlib.h>

// <!DANGER!> Don't call except drop
void free4drop(void *const restrict pp) { free(*(void **)pp); }
// <!DANGER!> Don't call except drop

// greater realloc
void *grealloc(void *restrict old, size_t sz) {
  return realloc(old, sz) orelse p$panic(ERR_ALLOC);
}

test(leak) { drop void *p = malloc(100); }

test(galloc) {
  drop char *p = galloc(char, 100);
  expectneq(nullptr, (void *)p);
  // Terminate with error
  // char *q = galloc(long long, 0xffffffffffffffff);
  p = grealloc(p, 10000);
  expectneq(nullptr, (void *)p);
}
