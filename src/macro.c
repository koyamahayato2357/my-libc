#include "macro.h"
#include "testing.h"

test (macro) {
  expecteq("0", TOSTR(BOOL(0)));
  expecteq("1", TOSTR(BOOL(100)));
}

test_table(
  if, , (int, int),
  {
    {0, IF(10)(0, 10)},
    {1, IF(1)(IF(1)(1, 5))},
    {1, IF(0)(IF(1)(0, 1), 1)},
}
)
