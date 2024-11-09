#pragma once
#include "exproriented.h"
#include <stddef.h>
#include <sys/types.h>

#define CAT(a, b) a##b
#define TOSTR(x) #x
#define TO2STR(x) TOSTR(x)
#define HERE __FILE__ ":" TO2STR(__LINE__)
#define overloadable __attribute__((overloadable))

// free when exiting scope
#define drop __attribute__((cleanup(free4drop)))
// call specified function when exiting scope
#define ondrop(cf) __attribute__((cleanup(cf)))
// specified length bit integer
#define i(n) _BitInt(n)
// specified length bit unsigned integer
#define u(n) unsigned _BitInt(n)
#define galloc(type, size) /* general allocator */                             \
  (malloc(sizeof(type) * size) orelse p$panic(ERR_ALLOC))
#define lesser(a, b) ((a) > (b) ? (b) : (a))
#define bigger(a, b) ((a) < (b) ? (b) : (a))
#define orelse ?:
#define swap(a, b)                                                             \
  do {                                                                         \
    typeof(a) temp = a;                                                        \
    a = b;                                                                     \
    b = temp;                                                                  \
  } while (0)
#define likely(cond) if (__builtin_expect(!!(cond), 1))
#define unlikely(cond) if (__builtin_expect(!!(cond), 0))

typedef u_int8_t void8_t;
typedef u_int16_t void16_t;
typedef u_int32_t void32_t;
typedef u_int64_t void64_t;
typedef unsigned long long void128_t;

void free4drop(void *const restrict);
void *grealloc(void *restrict, size_t);
