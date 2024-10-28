#pragma once
#include "def.h"
#include "exproriented.h"
#include "gene.h"
#include <stdio.h>

#define NULLABLE_H_OPTIONT Option
#define Option(T) CAT(NULLABLE_H_OPTIONT, T)

#define DEF_OPTIONAL(T)                                                        \
  typedef struct {                                                             \
    bool isnull;                                                               \
    T val;                                                                     \
  } Option(T);                                                                 \
  Option(T) Some(T v) overloadable;                                            \
  Option(T) map(Option(T), T (*)(T)) overloadable;                             \
  Option(T) and_then(Option(T), Option(T) (*)(T)) overloadable;                \
  bool isnull(Option(T)) overloadable;                                         \
  T unwrap_unsafe(Option(T)) overloadable;                                     \
  T unwrap(Option(T)) overloadable;

#define Null(T)                                                                \
  (Option(T)) {                                                                \
    true, (T) { 0 }                                                            \
  }
#define unwrap_or(o, default) (ifx(isnull(o)) default elsex unwrap_unsafe(o))

APPLY_TYPE_GEN(DEF_OPTIONAL)
