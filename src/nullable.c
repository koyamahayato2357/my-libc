#include "nullable.h"
#include "testing.h"

#define DEF_OPTIONFN(T) \
  overloadable Option(T) Some(T v) { \
    return (Option(T)){false, v}; \
  } \
  overloadable Option(T) map(Option(T) o, T (*f)(T)) { \
    return $if(isnull(o)) Null(T) $else Some(f(unwrap_unsafe(o))); \
  } \
  overloadable Option(T) and_then(Option(T) o, Option(T) (*f)(T)) { \
    return $if(isnull(o)) Null(T) $else f(unwrap_unsafe(o)); \
  } \
  overloadable bool isnull(Option(T) o) { \
    return o.isnull; \
  } \
  overloadable T unwrap_unsafe(Option(T) o) { \
    return o.val; \
  } \
  overloadable T unwrap(Option(T) o) { \
    return unwrap_or(o, (T)$panic(ERR_REACHED_UNREACHABLE)); \
  } \
  overloadable void printany(Option(T) o) { \
    if (isnull(o)) printf("null"); \
    else printany(unwrap_unsafe(o)); \
  } \
  overloadable void printanyln(Option(T) o) { \
    printany(o); \
    putchar('\n'); \
  } \
  overloadable bool eq(Option(T) lhs, Option(T) rhs) { \
    return $if(isnull(lhs) || isnull(rhs)) false $else eq( \
      unwrap_unsafe(lhs), unwrap_unsafe(rhs) \
    ); \
  }

TMAP(DEF_OPTIONFN)

test (Some) {
  Option(size_t) option = Some((size_t)0);
  expect(!isnull(option));
  expecteq(0, unwrap(option));

  Option(char) coption = Some((char)42);
  expect(!isnull(coption));
  expecteq(42, unwrap(coption));
  coption = Some((char)'a');
  expect(!isnull(coption));
  expecteq('a', unwrap(coption));
}

test (Null) {
  Option(double) noption = Null(double);
  expect(isnull(noption));
}

test_table(
  isnull_table, isnull, (bool, Option(int)),
  {
    { true,  Null(int)},
    {false,   Some(10)},
    {false, Some(-100)},
    {false,  Some(334)},
}
)

test (unwrap_or) {
  Option(size_t) o = Null(size_t);
  expecteq(42, unwrap_or(o, 42));
  o = Some((size_t)99);
  expecteq(99, unwrap_or(o, 42));
}

test (unwrap_unsafe) {
  Option(int) o = Some(99);
  expecteq(99, unwrap_unsafe(o));
  // Undefined behaivior; might be false
  // expecteq(Null(T).val, unwrap_unsafe(Null(T)));
  o = Some(334);
  expecteq(334, unwrap_unsafe(o));
}

int square(int x) {
  return x * x;
}

test (map) {
  Option(int) o = Null(int);
  expect(isnull(map(o, square)));
  o = Some(10);
  expecteq(100, unwrap(map(o, square)));
}

Option(int) square_o(int x) {
  return Some(x * x);
}

test (and_then) {
  Option(int) o = Null(int);
  expect(isnull(and_then(o, square_o)));
  o = Some(10);
  expecteq(100, unwrap(and_then(o, square_o)));
}

test (chain) {
  Option(int) o = Some(4);
  expecteq(65'536, unwrap(map(map(map(o, square), square), square)));
}

test (iflet) {
  Option(int) o = Some(334);
  iflet (o) (nonnull) expecteq(334, nonnull);
  else testing_unreachable;
  o = Null(int);
  iflet (o) (null) {
      _ = null;
      testing_unreachable;
    }
  else expect(isnull(o));
}
