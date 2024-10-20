#pragma once

#define CAT(a, b) a##b

#define drop __attribute__((cleanup(free4drop)))
#define dropf(cf) __attribute__((cleanup(cf)))
#define i(n) _BitInt(n)
#define u(n) unsigned _BitInt(n)
#define HERE __FILE__ ":" __LINE__

typedef char *str;

void free4drop(void **);
