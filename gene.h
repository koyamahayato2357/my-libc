#pragma once
#include "def.h"
#include <stdio.h>

#define DEF_GEN(T)                                                             \
  void printany(T) overloadable;                                               \
  bool eq(T, T) overloadable;

#define APPLY_TYPE_GEN(M) M(int) M(size_t) M(double) M(char) M(bool)
#define APPLY_POINTER_GEN(M)                                                   \
  M(int *) M(size_t *) M(double *) M(char *) M(bool *) M(void *)

APPLY_TYPE_GEN(DEF_GEN)
APPLY_POINTER_GEN(DEF_GEN)
