#pragma once
#include "def.h"
#include <stdio.h>

#define DEF_GEN(T)                                                             \
  void printany(T) overloadable;                                           \
  bool eq(T, T) overloadable;

DEF_GEN(int)
DEF_GEN(size_t)
DEF_GEN(double)
DEF_GEN(char)
DEF_GEN(char *)
DEF_GEN(void *)
