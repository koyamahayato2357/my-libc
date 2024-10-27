#pragma once
#include "list.h"
#include "vector.h"

#define initStringList(a) _initStringList(a, sizeof(a))
#define dropStringList ondrop(deleteStringList)

typedef struct {
  enableList;
  Vector(char) v;
} StringList;

StringList *_initStringList(char *, size_t);
void append(StringList *, char *) overloadable;
char *toString(const StringList *const);
void deleteStringList(StringList **);
