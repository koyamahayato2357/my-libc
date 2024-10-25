#include "vector.h"
#include "testing.h"
#include <stdlib.h>

#define DEF_VECFN(T)                                                           \
  __attribute__((overloadable)) void expand(Vector(T) * vec) {                 \
    if (vec->cap >= vec->len + 1)                                              \
      return;                                                                  \
    vec->buf = realloc(vec->buf, vec->cap * 2);                                \
    vec->cap *= 2;                                                             \
  }                                                                            \
  __attribute__((overloadable)) void push_unsafe(Vector(T) * vec, T v) {       \
    vec->buf[vec->len++] = v;                                                  \
  }                                                                            \
  __attribute__((overloadable)) void push(Vector(T) * vec, T v) {              \
    expand(vec);                                                               \
    push_unsafe(vec, v);                                                       \
  }                                                                            \
  __attribute__((overloadable)) void shrink(Vector(T) * vec) {                 \
    if (vec->len * 4 > vec->cap)                                               \
      return;                                                                  \
    vec->buf = realloc(vec->buf, vec->cap / 2);                                \
    vec->cap /= 2;                                                             \
  }                                                                            \
  __attribute__((overloadable)) Option(T) pop_raw(Vector(T) * vec) {           \
    if (vec->len == 0)                                                         \
      return Null(T);                                                          \
    return Some(vec->buf[--(vec->len)]);                                       \
  }                                                                            \
  __attribute__((overloadable)) Option(T) pop(Vector(T) * vec) {               \
    shrink(vec);                                                               \
    return pop_raw(vec);                                                       \
  }                                                                            \
  __attribute__((overloadable)) void resize(Vector(T) * vec, size_t n) {       \
    vec->buf = realloc(vec->buf, n);                                           \
  }                                                                            \
  __attribute__((overloadable)) Vector(T)                                      \
      _initVectorWithArray(T *a, size_t len) {                                 \
    size_t blockn = 1;                                                         \
    while (DEFAULT_VECCAP * blockn < len)                                      \
      blockn++;                                                                \
    T *buf = malloc(sizeof(T) * DEFAULT_VECCAP * blockn);                      \
    memcpy(buf, a, len);                                                       \
    return (Vector(T)){DEFAULT_VECCAP * blockn, len, buf};                     \
  }                                                                            \
  __attribute__((overloadable)) void deinitVector(Vector(T) * vec) {           \
    /* for drop */                                                             \
    free(vec->buf);                                                            \
  }

DEF_VECFN(int)
DEF_VECFN(char)
DEF_VECFN(size_t)
DEF_VECFN(double)

test(push) {
  Vector(char) vec = initVector(char);
  push(&vec, 'a');
  push(&vec, 'b');
  push(&vec, 'c');
  push(&vec, 'd');
  expecteq(vec.buf[0], 'a');
  expecteq(vec.buf[1], 'b');
  expecteq(vec.buf[2], 'c');
  expecteq(vec.buf[3], 'd');
  deinitVector(&vec);
}

test(pop) {
  Vector(char) vec = initVectorWithArray("hello world");
  expecteq(vec.len, strlen("hello world") + 1);

  expecteq(unwrap(pop(&vec)), '\0');
  expecteq(unwrap(pop(&vec)), 'd');
  expecteq(unwrap(pop(&vec)), 'l');
  expecteq(unwrap(pop(&vec)), 'r');
  push(&vec, 'a');
  expecteq(unwrap(pop(&vec)), 'a');
  deinitVector(&vec);
}

test(expand_shrink) {
  Vector(char) vec = initVector(char);
  for (int i = 0; i < 100; i++)
    push(&vec, i);
  expecteq(vec.cap, 128);
  for (int i = 0; i < 90; i++)
    pop_raw(&vec);
  shrink(&vec);
  expecteq(vec.cap, 64);
  deinitVector(&vec);
}
