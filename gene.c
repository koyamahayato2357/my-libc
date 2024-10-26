#include "gene.h"
#include <string.h>
#include <tgmath.h>

#define EPSILON 1e-5
#define olable __attribute__((overloadable))

static bool double_eq(double a, double b) { return fabs(a - b) < EPSILON; }
static bool complex_eq(double complex a, double complex b) {
  return fabs(creal(a - b)) < EPSILON && fabs(cimag(a - b)) < EPSILON;
}

olable void printany(int x) { printf("%d", x); }
olable void printany(size_t x) { printf("%zu", x); }
olable void printany(double x) { printf("%lf", x); }
olable void printany(char x) { printf("%c", x); }
olable void printany(char *x) { printf("%s", x); }
olable void printany(void *x) { printf("%p", x); }

olable bool eq(int x, int y) { return x == y; }
olable bool eq(size_t x, size_t y) { return x == y; }
olable bool eq(double x, double y) { return double_eq(x, y); }
olable bool eq(char x, char y) { return complex_eq(x, y); }
olable bool eq(char *x, char *y) { return !strcmp(x, y); }
olable bool eq(void *x, void *y) { return x == y; }

#undef olable
