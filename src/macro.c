#include "macro.h"
#include "testing.h"

test_table(
  bool_macro, , (int, int),
  {
    {0, BOOL(0)},
    {1, BOOL(1)},
    {1, BOOL(8)},
}
)

test_table(
  if_macro, , (int, int),
  {
    {0, IF(10)(0, 10)},
    {1, IF(1)(IF(1)(1, 5))},
    {1, IF(0)(IF(1)(0, 1), 1)},
}
)
