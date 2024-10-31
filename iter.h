/**
 * first 8 byte are meta data
 *
 * | leading-address                                               |
 * ----------------------------------------------------------------------------
 * | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 1 | 2 | 3
 * ----------------------------------------------------------------------------
 * | (int) length  | (int) index   | pointer to data array         |
 *
 */

#pragma once
#include "def.h"
#include "nullable.h"
#include "vector.h"

#define METADATA_OFFSET 8

#define initIterWithArray(buf)                                                 \
  ({                                                                           \
    typeof(buf) ret[2] = {};                                                   \
    Iter(typeof(buf[0])) iter = (typeof(buf[0]) **)ret;                        \
    IterLen(iter) = sizeof(buf) / sizeof(buf[0]);                              \
    IterId(iter) = 0;                                                          \
    IterBuf(iter) = buf;                                                       \
    iter;                                                                      \
  })
#define initIterWithVector(vec)                                                \
  ({                                                                           \
    typeof(VectorBuf(vec)) ret[2] = {};                                        \
    Iter(typeof(VectorBuf(vec)[0])) iter = (typeof(VectorBuf(vec)[0]) **)ret;  \
    IterLen(iter) = VectorLen(vec);                                            \
    IterId(iter) = 0;                                                          \
    IterBuf(iter) = VectorBuf(vec);                                            \
    iter;                                                                      \
  })

#define Iter(T) T **
#define IterLen(iter) ((int *)iter)[0]
#define IterId(iter) ((int *)iter)[1]
#define IterBuf(iter) (iter)[1]

#define foreach(iter, item)                                                    \
  for (auto item = IterBuf(iter)[IterId(iter)]; IterId(iter) < IterLen(iter);  \
       item = IterBuf(iter)[++IterId(iter)])

#define DEF_ITER(T)                                                            \
  Option(T) next(Iter(T) * iter) overloadable;                                 \
  void iterStart(Iter(T)) overloadable;                                        \
  void iterEnd(Iter(T)) overloadable;

APPLY_PRIMITIVE_TYPES(DEF_ITER)
