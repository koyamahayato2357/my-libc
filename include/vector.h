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
#include "gene.h"
#include "nullable.h"

constexpr size_t METADATA_OFFSET = 8;
constexpr size_t DEFAULT_VECCAP = 32;
#define Vector(T)       T *
#define initVector(T) \
  ({ \
    Vector(T) vec = galloc(T, DEFAULT_VECCAP); \
    VectorCap_OVERWRITE(vec) = DEFAULT_VECCAP; \
    VectorLen_OVERWRITE(vec) = 0; \
    vec; \
  })
#define VectorLen(vec)           ((size_t)((int *)vec)[0])
#define VectorCap(vec)           ((size_t)((int *)vec)[1])
#define VectorLen_OVERWRITE(vec) ((int *)vec)[0]
#define VectorCap_OVERWRITE(vec) ((int *)vec)[1]
#define VectorBuf(vec)           ((vec) + METADATA_OFFSET / sizeof((vec)[0]))
#define initVectorWithArray(...) \
  _initVectorWithArray(__VA_ARGS__, sizeof(__VA_ARGS__));

#define DEF_VEC(T) \
  overloadable void expand(Vector(T) *const restrict); \
  overloadable void push_unsafe(Vector(T) *const restrict, T); \
  overloadable void push(Vector(T) *const restrict, T); \
  overloadable void shrink(Vector(T) *const restrict); \
  overloadable Option(T) pop_raw(Vector(T) *const restrict); \
  overloadable Option(T) pop(Vector(T) *const restrict); \
  overloadable void resize(Vector(T) *const restrict, size_t); \
  overloadable Vector(T) \
    _initVectorWithArray(T const *const restrict, size_t); \
  overloadable void deinitVector(Vector(T) *const restrict);

TMAP(DEF_VEC)
