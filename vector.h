#pragma once
#include "nullable.h"
#include <stdio.h>

#define VECTOR_H_VECTOR Vector
#define DEFAULT_VECCAP 32
#define Vector(T) VECTOR_H_VECTOR##T
#define initVector(T)                                                          \
  (Vector(T)) { DEFAULT_VECCAP, 0, malloc(sizeof(T) * DEFAULT_VECCAP) }
#define arraytovec(a) _initVectorWithArray(a, sizeof(a));

#define DEF_VEC(T)                                                             \
  typedef struct {                                                             \
    int cap;                                                                   \
    int len;                                                                   \
    T *buf;                                                                    \
  } Vector(T);                                                                 \
  void push(Vector(T) *, T) __attribute__((overloadable));                     \
  Option(T) pop(Vector(T) *) __attribute__((overloadable));                    \
  Vector(T) _initVectorWithArray(T *, size_t) __attribute__((overloadable));   \
  void deinitVector(Vector(T)) __attribute__((overloadable));

DEF_VEC(int)
DEF_VEC(char)
DEF_VEC(size_t)
DEF_VEC(double)
