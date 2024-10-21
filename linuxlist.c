#include "linuxlist.h"
#include "testing.h"

typedef struct {
  enableLinuxList;
  int val;
} sample;

test(linuxlist) {
  sample *root = initLinuxList(sample);

  appendLinuxList(root, 1);
  appendLinuxList(root, 2);
  appendLinuxList(root, 3);

  int i = 0;
  foreach_LinuxList(root, elem) expecteq(++i, elem->val);

  deleteLinuxList(root);
}

test(nextlist) {
  sample *root = initLinuxList(sample);
  sample *p = root;

  appendLinuxList(root, 42);
  appendLinuxList(root, 84);
  appendLinuxList(root, 126);

  sample *n = nextLinuxList(p);
  expect(n->val == 42);
  n = nextLinuxList(p);
  expect(n->val == 84);
  n = nextLinuxList(p);
  expect(n->val == 126);

  deleteLinuxList(root);
}
