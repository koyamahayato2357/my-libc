#include "list.h"
#include "testing.h"

typedef struct {
  ListDeclare;
  int val;
} sample;

test(list) {
  sample *root = initList(sample, 1, val);

  appendList(root, 2, val);
  appendList(root, 3, val);

  int i = 0;
  foreach_List(root, elem) expecteq(++i, elem->val);

  deleteList(root);
}

test(nextlist) {
  sample *root = initList(sample, 42, val);
  sample *p = root;

  appendList(root, 84, val);
  appendList(root, 126, val);

  sample *n = p;
  expect(n->val == 42);
  n = nextList(p);
  expect(n->val == 84);
  n = nextList(p);
  expect(n->val == 126);

  deleteList(root);
}
