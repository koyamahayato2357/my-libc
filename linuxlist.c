#include "linuxlist.h"
#include "testing.h"

typedef struct {
  enableLinuxList;
  int val;
} sample;

test(linuxlist) {
  sample *root = initLinuxList(sample);

  append(root, 1);
  append(root, 2);
  append(root, 3);

  int i = 0;
  foreach_LinuxList(root, elem) expecteq(++i, elem->val);

  deleteLinuxList(root);
}
