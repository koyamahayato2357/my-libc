#pragma once
#include "exproriented.h"
#include "gene.h"

#define NULLABLE_H_OPTIONT Option
#define NULLABLE_H_FLAG    PRIMITIVE_CAT(NULLABLE_H_cnt, __COUNTER__)
#define Option(T)          PRIMITIVE_CAT(NULLABLE_H_OPTIONT, T)
#define NULLABLE_H_CAPTURE(capture) \
  for (auto capture = unwrap_unsafe(o); NULLABLE_H_FLAG; \
       NULLABLE_H_FLAG = false) \
    if (!isnull(o))
#define iflet(o) \
  for (bool NULLABLE_H_FLAG = true; NULLABLE_H_FLAG;) NULLABLE_H_CAPTURE

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

TMAP(DEF_OPTIONAL)
