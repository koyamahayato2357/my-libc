#include "iter.h"
#include "nullable.h"
#include "testing.h"

#define DEF_ITERFN(T)                                                          \
  Iter(T) _initIterWithArray(T *buf, size_t len)                               \
      __attribute__((overloadable)) {                                          \
    return (Iter(T)){buf, len, 0};                                             \
  }                                                                            \
  Option(T) next(Iter(T) * iter) __attribute__((overloadable)) {               \
    if (iter->len <= iter->i)                                                  \
      return Null(T);                                                          \
    return Some(iter->buf[iter->i++]);                                         \
  }                                                                            \
  void iterStart(Iter(T) iter) __attribute__((overloadable)) { iter.i = 0; }   \
  void iterEnd(Iter(T) iter) __attribute__((overloadable)) {                   \
    iter.i = iter.len;                                                         \
  }

DEF_ITERFN(char)
DEF_ITERFN(int)
DEF_ITERFN(size_t)
DEF_ITERFN(double)
DEF_ITERFN(str)

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
