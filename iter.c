#include "iter.h"
#include "nullable.h"
#include "testing.h"

#define DEF_ITERFN(T)                                                          \
  Iter(T) _initIterWithArray(T *buf, size_t len) overloadable {                \
    return (Iter(T)){buf, len, 0};                                             \
  }                                                                            \
  Iter(T) initIterWithVector(Vector(T) vec) overloadable {                     \
    return (Iter(T)){vec.buf, vec.len, 0};                                     \
  }                                                                            \
  Option(T) next(Iter(T) * iter) overloadable {                                \
    if (iter->len <= iter->i)                                                  \
      return Null(T);                                                          \
    return Some(iter->buf[iter->i++]);                                         \
  }                                                                            \
  void iterStart(Iter(T) iter) overloadable { iter.i = 0; }                    \
  void iterEnd(Iter(T) iter) overloadable { iter.i = iter.len; }

APPLY_TYPE_GEN(DEF_ITERFN)

test(next) {
  Iter(char) iter = initIterWithArray("hello world!");
  expect(!strcmp("hello world!", iter.buf));
  expecteq(unwrap(next(&iter)), 'h');
  iter.i = iter.len - 1;
  expecteq(unwrap(next(&iter)), '\0');
  expect(isnull(next(&iter)));
}

test(foreach) {
  Iter(char) iter =
      initIterWithArray("You don't come to Russia, Russia come to you.");
  size_t i = 0;
  foreach (iter, item)
    expecteq(item, iter.buf[i++]);
  expecteq(iter.i, iter.len);
  expect(isnull(next(&iter)));
}

test(initwith_vector) {
  Vector(char) vec = initVectorWithArray("This is sample text.");
  Iter(char) iter = initIterWithVector(vec);
  int i = 0;
  foreach (iter, item)
    expecteq(item, vec.buf[i++]);
  deinitVector(&vec);
}
