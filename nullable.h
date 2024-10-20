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
  Option(T) Some(T v) __attribute__((overloadable));

#define Null(T)                                                                \
  (Option(T)) { true, (T)0 }
#define isnull(o) (o).isnull
#define unwrap_or(o, default)                                                  \
  ({                                                                           \
    auto temp = o;                                                             \
    temp.isnull ? default : temp.val;                                          \
  })
#define unwrap(o) unwrap_or(o, unreachable)
#define unwrap_unsafe(o) ((o).val)
#define map_option(o, f)                                                       \
  do                                                                           \
    f(unwrap_or((o), breakx));                                                 \
  while (0)
#define and_then(o, f)                                                         \
  ifx(isnull(o)) Null(__typeof__((o).val)) elsex f(unwrap_unsafe(o))

DEF_OPTIONAL(char);
DEF_OPTIONAL(int);
DEF_OPTIONAL(double);
DEF_OPTIONAL(size_t);
DEF_OPTIONAL(str);
