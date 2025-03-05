#include "macro.h"
#include "testing.h"

test(macro) {
  expecteq("0", TOSTR(BOOL(0)));
  expecteq("1", TOSTR(BOOL(100)));
}
