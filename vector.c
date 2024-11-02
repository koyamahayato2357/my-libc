#include "vector.h"
#include "testing.h"
#include <stdbit.h>
#include <stdlib.h>

#define DEF_VECFN(T)                                                           \
  void expand(Vector(T) *const restrict vec) overloadable {                    \
    if (VectorCap(*vec) >                                                      \
        VectorLen(*vec) + METADATA_OFFSET / (int)sizeof(**vec))                \
      return;                                                                  \
    VectorCap(*vec) = stdc_bit_ceil(VectorLen(*vec));                          \
    *vec = grealloc(*vec, VectorCap(*vec));                                    \
  }                                                                            \
  void push_unsafe(Vector(T) *const restrict vec, T v) overloadable {          \
    VectorBuf(*vec)[VectorLen(*vec)++] = v;                                    \
  }                                                                            \
  void push(Vector(T) *const restrict vec, T v) overloadable {                 \
    expand(vec);                                                               \
    push_unsafe(vec, v);                                                       \
  }                                                                            \
  void shrink(Vector(T) *const restrict vec) overloadable {                    \
    if (VectorLen(*vec) * 4 > VectorCap(*vec))                                 \
      return;                                                                  \
    VectorCap(*vec) = stdc_bit_ceil(VectorLen(*vec));                          \
    *vec = grealloc(*vec, VectorCap(*vec));                                    \
  }                                                                            \
  Option(T) pop_raw(Vector(T) *const restrict vec) overloadable {              \
    return $if(VectorLen(*vec) == 0) Null(T)                                   \
        $else Some(VectorBuf(*vec)[--(VectorLen(*vec))]);                      \
  }                                                                            \
  Option(T) pop(Vector(T) *const restrict vec) overloadable {                  \
    shrink(vec);                                                               \
    return pop_raw(vec);                                                       \
  }                                                                            \
  void resize(Vector(T) *const restrict v, size_t len) overloadable {          \
    *v = grealloc(VectorBuf(*v), len + METADATA_OFFSET / (int)sizeof(**v));    \
  }                                                                            \
  Vector(T) _initVectorWithArray(T const *const restrict a, size_t len)        \
      overloadable {                                                           \
    Vector(T) vec = initVector(T);                                             \
    size_t cap = bigger(len + len / 2, DEFAULT_VECCAP + METADATA_OFFSET);      \
    VectorCap(vec) = cap;                                                      \
    VectorLen(vec) = len;                                                      \
    memcpy(VectorBuf(vec), a, len);                                            \
    return vec;                                                                \
  }                                                                            \
  void deinitVector(Vector(T) *const restrict vec) overloadable {              \
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
  expecteq('a', VectorBuf(vec)[0]);
  expecteq('b', VectorBuf(vec)[1]);
  expecteq('c', VectorBuf(vec)[2]);
  expecteq('d', VectorBuf(vec)[3]);
  deinitVector(&vec);
}

test(pop) {
  Vector(char) vec = initVectorWithArray("hello world");
  expecteq(strlen("hello world") + 1, VectorLen(vec));

  expecteq('\0', unwrap(pop(&vec)));
  expecteq('d', unwrap(pop(&vec)));
  expecteq('l', unwrap(pop(&vec)));
  expecteq('r', unwrap(pop(&vec)));
  push(&vec, 'a');
  expecteq('a', unwrap(pop(&vec)));
  deinitVector(&vec);
}

test(expand_shrink) {
  Vector(char) vec = initVector(char);
  for (int i = 0; i < 100; i++)
    push(&vec, i);
  expecteq(128, VectorCap(vec));
  for (int i = 0; i < 90; i++)
    pop_raw(&vec);
  shrink(&vec);
  expecteq(16, VectorCap(vec));
  deinitVector(&vec);
}
