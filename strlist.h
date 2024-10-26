#pragma once
#include "linuxlist.h"
#include "vector.h"

#define initStringList(a) _initStringList(a, sizeof(a))

typedef struct {
  enableLinuxList;
  Vector(char) v;
} StringList;

StringList *_initStringList(char *, size_t);
void append(StringList *, char *) __attribute__((overloadable));
char *toString(const StringList *const);