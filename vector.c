#include "vector.h"
#include "testing.h"
#include <stdlib.h>

#define DEF_VECFN(T)                                                           \
  void expand(Vector(T) * vec) overloadable {                                  \
    if (VectorCap(*vec) >= VectorLen(*vec) + 1)                                \
      return;                                                                  \
    VectorCap(*vec) *= 2;                                                      \
    *vec = grealloc(*vec, VectorCap(*vec));                                     \
  }                                                                            \
  void push_unsafe(Vector(T) * vec, T v) overloadable {                        \
    VectorBuf(*vec)[VectorLen(*vec)++] = v;                                    \
  }                                                                            \
  void push(Vector(T) * vec, T v) overloadable {                               \
    expand(vec);                                                               \
    push_unsafe(vec, v);                                                       \
  }                                                                            \
  void shrink(Vector(T) * vec) overloadable {                                  \
    if (VectorLen(*vec) * 4 > VectorCap(*vec))                                 \
      return;                                                                  \
    VectorCap(*vec) /= 2;                                                      \
    *vec = grealloc(*vec, VectorCap(*vec));                                     \
  }                                                                            \
  Option(T) pop_raw(Vector(T) * vec) overloadable {                            \
    if (VectorLen(*vec) == 0)                                                  \
      return Null(T);                                                          \
    return Some(VectorBuf(*vec)[--(VectorLen(*vec))]);                         \
  }                                                                            \
  Option(T) pop(Vector(T) * vec) overloadable {                                \
    shrink(vec);                                                               \
    return pop_raw(vec);                                                       \
  }                                                                            \
  void resize(Vector(T) * vec, size_t n) overloadable {                        \
    *vec = grealloc(VectorBuf(*vec), n + 8);                                    \
  }                                                                            \
  Vector(T) _initVectorWithArray(const T *const a, size_t len) overloadable {  \
    Vector(T) vec = initVector(T);                                             \
    size_t cap = bigger(len * 1.5, DEFAULT_VECCAP + METADATA_OFFSET);          \
    VectorCap(vec) = cap;                                                      \
    VectorLen(vec) = len;                                                      \
    memcpy(VectorBuf(vec), a, len);                                            \
    return vec;                                                                \
  }                                                                            \
  overloadable void deinitVector(Vector(T) * vec) {                            \
    /* for drop */                                                             \
    free(*vec);                                                                \
  }

APPLY_PRIMITIVE_TYPES(DEF_VECFN)

test(push) {
  Vector(char) vec = initVector(char);
  push(&vec, 'a');
  push(&vec, 'b');
  push(&vec, 'c');
  push(&vec, 'd');
  expecteq(VectorBuf(vec)[0], 'a');
  expecteq(VectorBuf(vec)[1], 'b');
  expecteq(VectorBuf(vec)[2], 'c');
  expecteq(VectorBuf(vec)[3], 'd');
  deinitVector(&vec);
}

test(pop) {
  Vector(char) vec = initVectorWithArray("hello world");
  expecteq(VectorLen(vec), strlen("hello world") + 1);

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
  expecteq(VectorCap(vec), 128);
  for (int i = 0; i < 90; i++)
    pop_raw(&vec);
  shrink(&vec);
  expecteq(VectorCap(vec), 64);
  deinitVector(&vec);
}
