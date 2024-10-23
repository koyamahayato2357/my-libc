#pragma once
#include "def.h"
#include "exproriented.h"
#include <stdio.h>

#define NULLABLE_H_OPTIONT Option
#define Option(T) CAT(NULLABLE_H_OPTIONT, T)

#define DEF_OPTIONAL(T)                                                        \
  typedef struct {                                                             \
    bool isnull;                                                               \
    T val;                                                                     \
  } Option(T);                                                                 \
  Option(T) Some(T v) __attribute__((overloadable));                           \
  Option(T) and_then(Option(T), T (*)(T)) __attribute__((overloadable));

#define Null(T)                                                                \
  (Option(T)) { true }
#define isnull(o) (o).isnull
#define unwrap_or(o, default)                                                  \
  ({                                                                           \
    auto temp = o;                                                             \
    temp.isnull ? default : temp.val;                                          \
  })
#define unwrap(o) unwrap_or(o, unreachable)
#define unwrap_unsafe(o) ((o).val)

DEF_OPTIONAL(char);
DEF_OPTIONAL(int);
DEF_OPTIONAL(double);
DEF_OPTIONAL(size_t);
DEF_OPTIONAL(str);
