#pragma once
#include "def.h"
#include "nullable.h"
#include "vector.h"
#include <stdio.h>

#define METADATA_OFFSET 8

#define initIterWithArray(buf)                                                 \
  _initIterWithArray(buf, sizeof(buf) / sizeof(buf[0]))

#define Iter(T) T *
#define IterLen(iter) ((int *)iter)[0]
#define IterId(iter) ((int *)iter)[1]
#define IterBuf(iter) ((iter) + METADATA_OFFSET / sizeof((iter)[0]) + 1)

#define foreach(iter, item)                                                    \
  for (auto item = IterBuf(iter)[IterId(iter)]; IterId(iter) < IterLen(iter);  \
       item = IterBuf(iter)[++IterId(iter)])

#define DEF_ITER(T)                                                            \
  Iter(T) _initIterWithArray(T *buf) overloadable;                             \
  Iter(T) initIterWithVector(Vector(T)) overloadable;                          \
  Option(T) next(Iter(T) * iter) overloadable;                                 \
  void iterStart(Iter(T)) overloadable;                                        \
  void iterEnd(Iter(T)) overloadable;

APPLY_PRIMITIVE_TYPES(DEF_ITER)
