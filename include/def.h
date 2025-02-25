#pragma once
#include "exproriented.h"
#include <stddef.h>
#include <sys/types.h>

#define CAT(a, b) a##b
#define TOSTR(x) #x
#define TO2STR(x) TOSTR(x)
#define HERE __FILE__ ":" TO2STR(__LINE__)
#define overloadable [[clang::overloadable]]

// call specified function when exiting scope
#define ondrop(cf) [[gnu::cleanup(cf)]]
// free when exiting scope
#define drop ondrop(free4drop)
// specified length bit integer
#define i(n) _BitInt(n)
// specified length bit unsigned integer
#define u(n) unsigned _BitInt(n)
#define galloc(type, size) /* general allocator */                             \
  ((type *)malloc(sizeof(type) * size) ?: p$panic(ERR_ALLOC))
#define lesser(a, b) ((a) > (b) ? (b) : (a))
#define bigger(a, b) ((a) < (b) ? (b) : (a))
#define _ auto CAT(_DISCARD_, __COUNTER__) [[maybe_unused]]
#define swap(a, b)                                                             \
  do {                                                                         \
    typeof(a) temp = a;                                                        \
    a = b;                                                                     \
    b = temp;                                                                  \
  } while (0)

void free4drop(void *const restrict);
void *grealloc(void *restrict, size_t);
