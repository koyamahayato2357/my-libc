#pragma once
#include "errcode.h"
#include "exproriented.h"

#define CAT(a, b) a##b
#define TOSTR(x) #x
#define TO2STR(x) TOSTR(x)
#define HERE __FILE__ ":" TO2STR(__LINE__)
#define overloadable __attribute__((overloadable))

// free when exiting scope
#define drop __attribute__((cleanup(free4drop)))
// call specified function when exiting scope
#define dropf(cf) __attribute__((cleanup(cf)))
// specified length bit integer
#define i(n) _BitInt(n)
// specified length bit unsigned integer
#define u(n) unsigned _BitInt(n)
#define galloc(type, size) /* general allocator */                             \
  ({ malloc(sizeof(type) * size) orelse ppanicx(ERR_ALLOC_FAILED); })
#define lesser(a, b) ((a) > (b) ? (b) : (a))
#define bigger(a, b) ((a) < (b) ? (b) : (a))

typedef char *str;

void free4drop(void *);
