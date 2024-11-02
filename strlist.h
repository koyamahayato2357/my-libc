#pragma once
#include "list.h"
#include "vector.h"

#define initStringList(a) _initStringList(a, sizeof(a))
#define dropStringList ondrop(deleteStringList)

typedef struct {
  ListDeclare;
  Vector(char) v;
} StringList;

StringList *_initStringList(char const *const restrict, size_t);
void append(StringList *const restrict,
            char const *const restrict) overloadable;
char *toString(StringList const *const);
void deleteStringList(StringList *const restrict *const restrict);
