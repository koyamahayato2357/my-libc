#pragma once
#include "errcode.h"
#include "exproriented.h"
#include <stdlib.h>

#define CAT(a, b) a##b

#define drop __attribute__((cleanup(free4drop)))
#define dropf(cf) __attribute__((cleanup(cf)))
#define i(n) _BitInt(n)
#define u(n) unsigned _BitInt(n)
#define HERE __FILE__ ":" __LINE__
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
