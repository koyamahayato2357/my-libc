#pragma once
#include <stddef.h>

typedef struct {
  void *p;
  size_t cap;
  void *next;
} arena;

arena arena_new(size_t);
void *arena_alloc(arena *, size_t);
void arena_destroy(arena *);
