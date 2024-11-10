#include "gene.h"
#include <string.h>
#include <tgmath.h>

#define EPSILON 1e-5

static bool double_eq(double a, double b) { return fabs(a - b) < EPSILON; }
static bool complex_eq(double complex a, double complex b) {
  return fabs(creal(a - b)) < EPSILON && fabs(cimag(a - b)) < EPSILON;
}

void printany(int x) overloadable { printf("%d", x); }
void printany(size_t x) overloadable { printf("%zu", x); }
void printany(double x) overloadable { printf("%lf", x); }
void printany(char x) overloadable { printf("'%c'", x); }
void printany(bool x) overloadable { printf($if(x) "true" $else "false"); }
void printany(char *x) overloadable { printf("%s", x); }
void printany(void *x) overloadable { printf("%p", x); }

#define DEF_printanyln(T)                                                      \
  void printanyln(T x) overloadable {                                          \
    printany(x);                                                               \
    putchar('\n');                                                             \
  }
APPLY_PRIMITIVE_TYPES(DEF_printanyln)
#define DEF_Pprintanyln(T)                                                     \
  void printanyln(T x) overloadable {                                          \
    printany((void *)x);                                                       \
    putchar('\n');                                                             \
  }
APPLY_POINTER_TYPES(DEF_Pprintanyln)

bool eq(int x, int y) overloadable { return x == y; }
bool eq(size_t x, size_t y) overloadable { return x == y; }
bool eq(double x, double y) overloadable { return double_eq(x, y); }
bool eq(char x, char y) overloadable { return complex_eq(x, y); }
bool eq(bool x, bool y) overloadable { return x == y; }
bool eq(char *x, char *y) overloadable { return !strcmp(x, y); }
bool eq(void *x, void *y) overloadable { return x == y; }
