#pragma once
#include "def.h"
#include "exproriented.h"
#include "gene.h"

#define NULLABLE_H_OPTIONT Option
#define Option(T)          CAT(NULLABLE_H_OPTIONT, T)

#define DEF_OPTIONAL(T) \
  typedef struct { \
    bool isnull; \
    T val; \
  } Option(T); \
  overloadable Option(T) Some(T v); \
  overloadable Option(T) map(Option(T), T (*)(T)); \
  overloadable Option(T) and_then(Option(T), Option(T) (*)(T)); \
  overloadable bool isnull(Option(T)); \
  overloadable T unwrap_unsafe(Option(T)); \
  overloadable T unwrap(Option(T)); \
  overloadable void printany(Option(T)); \
  overloadable void printanyln(Option(T)); \
  overloadable bool eq(Option(T), Option(T));

#define Null(T) \
  (Option(T)) { \
    true, (T){0} \
  }
#define unwrap_or(o, default) ($if(isnull(o)) default $else unwrap_unsafe(o))

APPLY_PRIMITIVE_TYPES(DEF_OPTIONAL)
