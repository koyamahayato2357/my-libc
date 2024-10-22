#include "def.h"
#include "errcode.h"
#include "testing.h"
#include <stdlib.h>

// <!DANGER!> Don't call except drop
void free4drop(void *pp) { free(*(void **)pp); }
// <!DANGER!> Don't call except drop

test(leak) { drop void *p = malloc(100); }

test(galloc) {
  drop char *p = galloc(char, 100);
  expect(p != nullptr);
  // Terminate with error
  // char *q = galloc(long long, 0xffffffffffffffff);
}
