#include "def.h"
#include "errcode.h"
#include "testing.h"
#include <stdlib.h>

// <!DANGER!> Don't call except drop
void free4drop(void *pp) { free(*(void **)pp); }
// <!DANGER!> Don't call except drop

void *rerealloc(size_t curn_byte, void *p, size_t newn_byte) {
  void *ret = realloc(p, newn_byte);
  if (ret != nullptr)
    return ret;
  ret = malloc(newn_byte);
  if (ret == nullptr)
    panic(ERR_ALLOC_FAILED);
  memcpy(ret, p, lesser(curn_byte, newn_byte));
  free(p);
  return ret;
}

test(leak) { drop void *p = malloc(100); }

test(galloc) {
  drop char *p = galloc(char, 100);
  expect(p != nullptr);
  // Terminate with error
  // char *q = galloc(long long, 0xffffffffffffffff);
}
