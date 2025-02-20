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
  expecteq(42, n->val);
  n = nextList(p);
  expecteq(84, n->val);
  n = nextList(p);
  expecteq(126, n->val);

  deleteList(root);
}
