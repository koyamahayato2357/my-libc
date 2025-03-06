#pragma once
#include "exproriented.h"
#include "def.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

#define HERE         __FILE__ ":" TOSTR(__LINE__)
#define overloadable [[clang::overloadable]]

// call specified function when exiting scope
#define ondrop(cf) [[gnu::cleanup(cf)]]
// free when exiting scope
#define drop     ondrop(free4drop)
#define dropfile ondrop(fclose4drop)

#define bigger(a, b) ((a) > (b) ? (a) : (b))

// specified length bit integer
#define i(n) _BitInt(n)
#define u(n) unsigned _BitInt(n)

#define galloc(type, size) /* general allocator */ \
  ((type *)malloc(sizeof(type) * size) ?: p$panic(ERR_ALLOC))
#define _ auto CAT(_DISCARD_, __COUNTER__) [[maybe_unused]]
#define swap(a, b) \
  do { \
    typeof(a) temp = a; \
    a = b; \
    b = temp; \
  } while (0)

void free4drop(void *restrict const);
void fclose4drop(FILE **restrict const);
void *grealloc(void *restrict, size_t);
