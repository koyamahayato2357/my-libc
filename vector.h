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
  void expand(Vector(T) *) overloadable;                                       \
  void push_unsafe(Vector(T) *, T) overloadable;                               \
  void push(Vector(T) *, T) overloadable;                                      \
  void shrink(Vector(T) *) overloadable;                                       \
  Option(T) pop_raw(Vector(T) *) overloadable;                                 \
  Option(T) pop(Vector(T) *) overloadable;                                     \
  void resize(Vector(T) *, size_t) overloadable;                               \
  Vector(T) _initVectorWithArray(const T *const, size_t) overloadable;         \
  void deinitVector(Vector(T) *) overloadable;

DEF_VEC(int)
DEF_VEC(char)
DEF_VEC(size_t)
DEF_VEC(double)
DEF_VEC(str)
