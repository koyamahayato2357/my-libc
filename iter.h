#pragma once
#include "def.h"
#include "nullable.h"
#include "vector.h"
#include <stdio.h>

#define foreach(iter, item)                                                    \
  for (auto item = iter.buf[iter.i]; iter.i < iter.len;                        \
       item = iter.buf[++iter.i])

#define initIterWithArray(buf)                                                 \
  _initIterWithArray(buf, sizeof(buf) / sizeof(buf[0]))

#define ITER_H_ITERT Iter
#define Iter(T) CAT(ITER_H_ITERT, T)

#define DEF_ITER(T)                                                            \
  typedef struct {                                                             \
    T *buf;                                                                    \
    size_t len;                                                                \
    size_t i;                                                                  \
  } Iter(T);                                                                   \
  Iter(T) _initIterWithArray(T *buf) __attribute__((overloadable));            \
  Iter(T) initIterWithVector(Vector(T)) __attribute__((overloadable));         \
  Option(T) next(Iter(T) * iter) __attribute__((overloadable));                \
  void iterStart(Iter(T)) __attribute__((overloadable));                       \
  void iterEnd(Iter(T)) __attribute__((overloadable));

DEF_ITER(char);
DEF_ITER(int);
DEF_ITER(size_t);
DEF_ITER(double);
DEF_ITER(str);
