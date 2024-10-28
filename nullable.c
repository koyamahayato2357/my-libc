#include "nullable.h"
#include "def.h"
#include "testing.h"

#define DEF_OPTIONFN(T)                                                        \
  Option(T) Some(T v) overloadable { return (Option(T)){false, v}; }           \
  Option(T) map(Option(T) o, T (*f)(T)) overloadable {                         \
    return ifx(isnull(o)) Null(T) elsex Some(f(unwrap_unsafe(o)));             \
  }                                                                            \
  Option(T) and_then(Option(T) o, Option(T) (*f)(T)) overloadable {            \
    return ifx(isnull(o)) Null(T) elsex f(unwrap_unsafe(o));                   \
  }                                                                            \
  bool isnull(Option(T) o) overloadable { return o.isnull; }                   \
  T unwrap_unsafe(Option(T) o) overloadable { return o.val; }                  \
  T unwrap(Option(T) o) overloadable {                                         \
    return unwrap_or(o, (T)$panic(ERR_REACHED_UNREACHABLE));                   \
  }

APPLY_PRIMITIVE_TYPES(DEF_OPTIONFN)

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
  expecteq(42, unwrap_or(o, 42));
  o = Some((size_t)99);
  expecteq(99, unwrap_or(o, 42));
}

test(unwrap_unsafe) {
  Option(int) o = Some(99);
  expecteq(unwrap_unsafe(o), 99);
  // Undefined behaivior; might be false
  // expecteq(unwrap_unsafe(Null(T)), Null(T).val);
  o = Some(334);
  expecteq(unwrap_unsafe(o), 334);
}

int square(int x) { return x * x; }

test(map) {
  Option(int) o = Null(int);
  expect(isnull(map(o, square)));
  o = Some(10);
  expecteq(100, unwrap(map(o, square)));
}

Option(int) square_o(int x) { return Some(x * x); }

test(and_then) {
  Option(int) o = Null(int);
  expect(isnull(and_then(o, square_o)));
  o = Some(10);
  expecteq(100, unwrap(and_then(o, square_o)));
}

test(chain) {
  Option(int) o = Some(4);
  expecteq(65536, unwrap(map(map(map(o, square), square), square)));
}
