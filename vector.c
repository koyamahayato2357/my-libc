#include "vector.h"
#include "testing.h"
#include <stdlib.h>

#define DEF_VECFN(T)                                                           \
  overloadable void expand(Vector(T) * vec) {                                  \
    if (vec->cap >= vec->len + 1)                                              \
      return;                                                                  \
    vec->buf = realloc(vec->buf, vec->cap * 2);                                \
    vec->cap *= 2;                                                             \
  }                                                                            \
  overloadable void push_unsafe(Vector(T) * vec, T v) {                        \
    vec->buf[vec->len++] = v;                                                  \
  }                                                                            \
  overloadable void push(Vector(T) * vec, T v) {                               \
    expand(vec);                                                               \
    push_unsafe(vec, v);                                                       \
  }                                                                            \
  overloadable void shrink(Vector(T) * vec) {                                  \
    if (vec->len * 4 > vec->cap)                                               \
      return;                                                                  \
    vec->buf = realloc(vec->buf, vec->cap / 2);                                \
    vec->cap /= 2;                                                             \
  }                                                                            \
  overloadable Option(T) pop_raw(Vector(T) * vec) {                            \
    if (vec->len == 0)                                                         \
      return Null(T);                                                          \
    return Some(vec->buf[--(vec->len)]);                                       \
  }                                                                            \
  overloadable Option(T) pop(Vector(T) * vec) {                                \
    shrink(vec);                                                               \
    return pop_raw(vec);                                                       \
  }                                                                            \
  overloadable void resize(Vector(T) * vec, size_t n) {                        \
    vec->buf = realloc(vec->buf, n);                                           \
  }                                                                            \
  overloadable Vector(T) _initVectorWithArray(const T *const a, size_t len) {  \
    size_t cap = bigger(len * 1.5, DEFAULT_VECCAP);                            \
    T *buf = galloc(T, cap);                                                   \
    memcpy(buf, a, len);                                                       \
    return (Vector(T)){cap, len, buf};                                         \
  }                                                                            \
  overloadable void deinitVector(Vector(T) * vec) {                            \
    /* for drop */                                                             \
    free(vec->buf);                                                            \
  }

APPLY_PRIMITIVE_TYPES(DEF_VECFN)

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
