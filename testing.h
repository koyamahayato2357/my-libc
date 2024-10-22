#pragma once
#include "errcode.h"
#include "exception.h"
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <tgmath.h>

#ifdef TEST_MODE
extern int TESTING_H_success;
extern int TESTING_H_fail;
#define test(name)                                                             \
  void TESTING_H_tester##name(jmp_buf);                                        \
  __attribute__((constructor)) void TESTING_H_testrunner##name() {             \
    int TESTING_H_COL = 3 - (strlen(#name) + 3) / 8;                           \
    jmp_buf jb;                                                                \
    printf("\033[34mTesting\033[0m " #name "...");                             \
    for (int TESTING_H_i = 0; TESTING_H_i < TESTING_H_COL; TESTING_H_i++)      \
      putchar('\t');                                                           \
    printf("\033[2m=> ");                                                      \
    if (setjmp(jb) == 0)                                                       \
      TESTING_H_tester##name(jb);                                              \
    else {                                                                     \
      puts("\033[31m[NG]\033[0m");                                             \
      TESTING_H_fail++;                                                        \
      return;                                                                  \
    }                                                                          \
    puts("\033[32m[OK]\033[0m");                                               \
    TESTING_H_success++;                                                       \
  }                                                                            \
  void TESTING_H_tester##name(jmp_buf jb)

#define main main_
#else
#define test(name) void TESTING_H_dummy##name()
#endif

#define expect(cond)                                                           \
  do                                                                           \
    if (!(cond)) {                                                             \
      printf("Failed at %s:%d %s ", __FILE__, __LINE__, #cond);                \
      longjmp(jb, 1);                                                          \
    }                                                                          \
  while (0)
#define expecteq(lhs, rhs)                                                     \
  do                                                                           \
    if (!_Generic((lhs),                                                       \
        double: double_eq(lhs, rhs),                                           \
        double complex: complex_eq(lhs, rhs),                                  \
        default: (lhs == rhs))) {                                              \
      printf("Expected ");                                                     \
      printany((lhs));                                                         \
      printf(" found ");                                                       \
      printany((rhs));                                                         \
      printf(" at %s:%d", __FILE__, __LINE__);                                 \
      longjmp(jb, 1);                                                          \
    }                                                                          \
  while (0)

#define EPSILON 1e-5
// Helper function to compare doubles with epsilon
bool double_eq(double, double);

bool complex_eq(double complex, double complex);

#define testing_unreachable                                                    \
  ({                                                                           \
    printf("\033[31mReached line %s:%d\033[0m\n", __FILE__, __LINE__);         \
    longjmp(jb, ERR_REACHED_UNREACHABLE);                                      \
    (size_t)0;                                                                 \
  })
#define printany(x)                                                            \
  printf(_Generic((x),                                                         \
         int: "%d",                                                            \
         size_t: "%zu",                                                        \
         double: "%lf",                                                        \
         char: "%c",                                                           \
         char *: "%s",                                                         \
         default: "%p"),                                                       \
         x)
