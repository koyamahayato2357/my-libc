#pragma once
#include "def.h"

#define DEF_GEN(T) \
  overloadable void printany(T); \
  overloadable void printanyln(T); \
  overloadable bool eq(T, T);

#define APPLY_PRIMITIVE_TYPES(M) M(int) M(size_t) M(double) M(char) M(bool)
#define APPLY_POINTER_TYPES(M) \
  M(int *) M(size_t *) M(double *) M(char *) M(bool *) M(void *)

APPLY_PRIMITIVE_TYPES(DEF_GEN)
APPLY_POINTER_TYPES(DEF_GEN)
