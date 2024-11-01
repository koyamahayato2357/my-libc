/*
 * first 8 byte are meta data
 *
 * | leading-address
 * ----------------------------------------------------------------------------
 * | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 1 | 2 | 3
 * ----------------------------------------------------------------------------
 * | (int) length  | (int) capa    | data
 *
 */

#pragma once
#include "def.h"
#include "nullable.h"

#define METADATA_OFFSET 8
#define DEFAULT_VECCAP 32
#define Vector(T) T *
#define initVector(T)                                                          \
  ({                                                                           \
    Vector(T) vec = galloc(T, DEFAULT_VECCAP);                                 \
    VectorCap(vec) = DEFAULT_VECCAP;                                           \
    VectorLen(vec) = 0;                                                        \
    vec;                                                                       \
  })
#define VectorLen(vec) ((int *)vec)[0]
#define VectorCap(vec) ((int *)vec)[1]
#define VectorBuf(vec) ((vec) + METADATA_OFFSET / sizeof((vec)[0]))
#define initVectorWithArray(...)                                               \
  _initVectorWithArray(__VA_ARGS__, sizeof(__VA_ARGS__));

#define DEF_VEC(T)                                                             \
  void expand(Vector(T) *) overloadable;                                       \
  void push_unsafe(Vector(T) *, T) overloadable;                               \
  void push(Vector(T) *, T) overloadable;                                      \
  void shrink(Vector(T) *) overloadable;                                       \
  Option(T) pop_raw(Vector(T) *) overloadable;                                 \
  Option(T) pop(Vector(T) *) overloadable;                                     \
  void resize(Vector(T) *, size_t) overloadable;                               \
  Vector(T) _initVectorWithArray(const T *const, size_t) overloadable;         \
  void deinitVector(Vector(T) *) overloadable;

APPLY_PRIMITIVE_TYPES(DEF_VEC)
