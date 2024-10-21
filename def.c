#include "def.h"
#include "errcode.h"
#include "testing.h"
#include <stdlib.h>

void free4drop(void **pp) { free(*pp); }

test(leak) { drop void *p = malloc(100); }

test(galloc) {
  char *p = galloc(char, 100);
  expect(p != nullptr);
  // Terminate with error
  // char *q = galloc(long long, 0xffffffffffffffff);
  free(p);
}
