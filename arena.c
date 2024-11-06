#include "arena.h"
#include "def.h"
#include "testing.h"
#include <stdlib.h>

arena arena_new(size_t cap) {
  // sizeof(char) is guaranteed to be 1
  void *new = galloc(char, cap);
  return (arena){new, cap, new};
}

void *arena_alloc(arena *restrict a, size_t cap) {
  if (a->p + a->cap < a->next + cap)
    // TODO realloc or list structuring
    return nullptr;
  void *ret = a->next;
  a->next += cap;
  return ret;
}

void arena_destroy(arena *restrict a) { free(a->p); }

test(arena) {
  arena a ondrop(arena_destroy) = arena_new(100);
  void *p = arena_alloc(&a, 10);
  expectneq(nullptr, p);
  expecteq(100, a.cap);
  expecteq(a.p + 10, a.next);
}

test(boundary_arena) {
  arena a ondrop(arena_destroy) = arena_new(10);
  void *p = arena_alloc(&a, 10);
  expectneq(nullptr, p);
  p = arena_alloc(&a, 1);
  expecteq((void *)nullptr, p);
}
