#include "arena.h"
#include "def.h"
#include "testing.h"

arena arena_new(size_t cap) {
  // sizeof(char) is guaranteed to be 1
  void *new = galloc(char, cap);
  return (arena){new, cap, new};
}

void *arena_alloc(arena *a, size_t cap) {
  if (a->p + a->cap < a->next + cap)
    // should i realloc?
    return nullptr;
  void *ret = a->next;
  a->next += cap;
  return ret;
}

void arena_destroy(arena *a) { free(a->p); }

test(arena) {
  arena a dropf(arena_destroy) = arena_new(100);
  void *p = arena_alloc(&a, 10);
  expecteq(100, a.cap);
  expect(a.p + 10 == a.next);
}

test(boundary_arena) {
  arena a dropf(arena_destroy) = arena_new(10);
  void *p = arena_alloc(&a, 10);
  expect(p != nullptr);
  p = arena_alloc(&a, 1);
  expect(nullptr == p);
}
