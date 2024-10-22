#include "nullable.h"
#include "def.h"
#include "testing.h"

#define DEF_OPTIONFN(T)                                                        \
  Option(T) Some(T v) __attribute__((overloadable)) {                          \
    return (Option(T)){false, v};                                              \
  }                                                                            \
  Option(T) and_then(Option(T) o, T (*f)(T)) __attribute__((overloadable)) {   \
    return ifx(isnull(o)) Null(T) elsex Some(f(unwrap_unsafe(o)));             \
  }

DEF_OPTIONFN(char)
DEF_OPTIONFN(int)
DEF_OPTIONFN(double)
DEF_OPTIONFN(size_t)
DEF_OPTIONFN(str)

test(Some) {
  Option(size_t) option = Some((size_t)0);
  expect(!isnull(option));
  expecteq(unwrap(option), 0);

  Option(char) coption = Some((char)42);
  expect(!isnull(coption));
  expecteq(unwrap(coption), 42);
  coption = Some((char)'a');
  expect(!isnull(coption));
  expecteq(unwrap(coption), 'a');
}

test(Null) {
  Option(double) noption = Null(double);
  expect(isnull(noption));
}

test(unwrap_or) {
  Option(size_t) o = Null(size_t);
  expecteq(unwrap_or(o, 42), 42);
  o = Some((size_t)99);
  expecteq(unwrap_or(o, 42), 99);
}

test(unwrap_unsafe) {
  Option(int) o = Some(99);
  expecteq(unwrap_unsafe(o), 99);
  o = Null(int);
  expecteq(unwrap_unsafe(o), Null(int).val);
}

int square(int x) { return x * x; }

test(map) {
  Option(int) o = Null(int);
  expect(isnull(and_then(o, square)));
  o = Some(10);
  expecteq(unwrap(and_then(o, square)), 100);
}
