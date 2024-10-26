#include "linuxlist.h"
#include "testing.h"

typedef struct {
  enableLinuxList;
  int val;
} sample;

test(linuxlist) {
  sample *root = initLinuxList(sample, 1, val);

  appendLinuxList(root, 2, val);
  appendLinuxList(root, 3, val);

  int i = 0;
  foreach_LinuxList(root, elem) expecteq(++i, elem->val);

  deleteLinuxList(root);
}

test(nextlist) {
  sample *root = initLinuxList(sample, 42, val);
  sample *p = root;

  appendLinuxList(root, 84, val);
  appendLinuxList(root, 126, val);

  sample *n = p;
  expect(n->val == 42);
  n = nextLinuxList(p);
  expect(n->val == 84);
  n = nextLinuxList(p);
  expect(n->val == 126);

  deleteLinuxList(root);
}
