#pragma once
#include "def.h"
#include "nullable.h"
#include <stdio.h>

#define VECTOR_H_VECTOR Vector
#define DEFAULT_VECCAP 32
#define Vector(T) VECTOR_H_VECTOR##T
#define initVector(T)                                                          \
  (Vector(T)) { DEFAULT_VECCAP, 0, galloc(T, DEFAULT_VECCAP) }
#define initVectorWithArray(a) _initVectorWithArray(a, sizeof(a));

#define DEF_VEC(T)                                                             \
  typedef struct {                                                             \
    int cap /* unit: bytes */;                                                 \
    int len /* unit: bytes */;                                                 \
    T *buf;                                                                    \
  } Vector(T);                                                                 \
  void expand(Vector(T) *) __attribute__((overloadable));                      \
  void push_unsafe(Vector(T) *, T) __attribute__((overloadable));              \
  void push(Vector(T) *, T) __attribute__((overloadable));                     \
  void shrink(Vector(T) *) __attribute__((overloadable));                      \
  Option(T) pop_raw(Vector(T) *) __attribute__((overloadable));                \
  Option(T) pop(Vector(T) *) __attribute__((overloadable));                    \
  void resize(Vector(T) *, size_t) __attribute__((overloadable));              \
  Vector(T) _initVectorWithArray(T *, size_t) __attribute__((overloadable));   \
  void deinitVector(Vector(T)*) __attribute__((overloadable));

DEF_VEC(int)
DEF_VEC(char)
DEF_VEC(size_t)
DEF_VEC(double)
DEF_VEC(str)
