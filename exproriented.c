/*
 * Usage
 * ----------------------------------------------------------------------------
 * if expression         | puts(ifx(lhs == rhs) "equal" elsex "not equal");
 * ----------------------------------------------------------------------------
 * break expression      | p = next() orelse breakx;
 * ----------------------------------------------------------------------------
 * continue expression   | is_validinput(input) orelse continuex;
 * ----------------------------------------------------------------------------
 * return expression     | char *homedir = getenv("HOME") orelse preturnx(-1);
 * ----------------------------------------------------------------------------
 */

#include "exproriented.h"
#include "testing.h"

test(in_expr) {
  int i = 0;
  for (;;) {
    int j [[maybe_unused]] = ifx(i == 1) 1 elsex $break;
    testing_unreachable;
  }
  for (int i = 0; i < 5; i++) {
    int j [[maybe_unused]] = $continue;
    testing_unreachable;
  }
}

test(in_statement) {
  for (;;) {
    $break;
    testing_unreachable;
  }
  for (int i = 0; i < 5; i++) {
    $continue;
    testing_unreachable;
  }
}

test(multi_statement) {
  int a = ifx(true)({
    int i = 1;
    i * 2;
  }) elsex({
    int i = 5;
    (i + 1) * i;
  });
  expecteq(a, 2);
  a = ifx(false)({
    int i = 9;
    i - 1;
  }) elsex({
    int i [[maybe_unused]] = a;
    a;
  });
  expecteq(a, 2);
}

test(dollar_sign) {
  // $ expression returns 0.
  // For now.
  // I want Unit type
  int a = $(int i = 5; expecteq(5, i));
  expecteq(0, a);
}
