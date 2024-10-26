#pragma once
#include <stdio.h>

#define DEF_GEN(T)                                                             \
  void printany(T) __attribute__((overloadable));                              \
  bool eq(T, T) __attribute__((overloadable));

DEF_GEN(int)
DEF_GEN(size_t)
DEF_GEN(double)
DEF_GEN(char)
DEF_GEN(char *)
DEF_GEN(void *)
