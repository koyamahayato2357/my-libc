#include "iter.h"
#include "nullable.h"
#include "testing.h"

#define DEF_ITERFN(T)                                                          \
  Iter(T) _initIterWithArray(T *buf, size_t len) overloadable {                \
    Iter(T) ret = galloc(char, sizeof(T *) + METADATA_OFFSET);                 \
    IterId(ret) = 0;                                                           \
    IterLen(ret) = len;                                                        \
    IterBuf(ret) = buf;                                                        \
    return ret;                                                                \
  }                                                                            \
  Iter(T) initIterWithVector(Vector(T) vec) overloadable {                     \
    Iter(T) ret = galloc(T, sizeof(T *) + METADATA_OFFSET);                    \
    IterId(ret) = 0;                                                           \
    IterLen(ret) = VectorLen(vec);                                             \
    IterBuf(ret) = VectorBuf(vec);                                             \
    return ret;                                                                \
  }                                                                            \
  Option(T) next(Iter(T) * iter) overloadable {                                \
    if (IterLen(*iter) <= IterId(*iter))                                       \
      return Null(T);                                                          \
    return Some(IterBuf(*iter)[IterId(*iter)++]);                              \
  }                                                                            \
  void iterStart(Iter(T) iter) overloadable { IterId(iter) = 0; }              \
  void iterEnd(Iter(T) iter) overloadable { IterId(iter) = IterLen(iter); }

APPLY_PRIMITIVE_TYPES(DEF_ITERFN)

test(next) {
  Iter(char) iter = initIterWithArray("hello world!");
  expect(!strcmp("hello world!", IterBuf(iter)));
  expecteq(unwrap(next(&iter)), 'h');
  IterId(iter) = IterLen(iter) - 1;
  expecteq(unwrap(next(&iter)), '\0');
  expect(isnull(next(&iter)));
}

test(foreach) {
  Iter(char) iter =
      initIterWithArray("You don't come to Russia, Russia come to you.");
  size_t i = 0;
  foreach (iter, item)
    expecteq(item, IterBuf(iter)[i++]);
  expecteq(IterId(iter), IterLen(iter));
  expect(isnull(next(&iter)));
}

test(initwith_vector) {
  Vector(char) vec = initVectorWithArray("This is sample text.");
  Iter(char) iter = initIterWithVector(vec);
  int i = 0;
  foreach (iter, item)
    expecteq(item, VectorBuf(vec)[i++]);
  deinitVector(&vec);
}
