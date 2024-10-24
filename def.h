#pragma once
#include "errcode.h"
#include "exproriented.h"
#include <stdlib.h>

#define CAT(a, b) a##b

// free when exiting scope
#define drop __attribute__((cleanup(free4drop)))
// call specified function when exiting scope
#define dropf(cf) __attribute__((cleanup(cf)))
// specified length bit integer
#define i(n) _BitInt(n)
// specified length bit unsigned integer
#define u(n) unsigned _BitInt(n)
#define galloc(type, size) /* general allocator */                             \
  ({                                                                           \
    void *p = malloc(sizeof(type) * size);                                     \
    if (p == nullptr)                                                          \
      panic(ERR_ALLOC_FAILED);                                                 \
    p;                                                                         \
  })
#define lesser(a, b) ((a) > (b) ? (b) : (a))
#define bigger(a, b) ((a) < (b) ? (b) : (a))

typedef char *str;

void free4drop(void *);
void *rerealloc(size_t curn_byte, void *p, size_t newn_byte);
