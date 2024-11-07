#ifdef TEST_MODE_ALL
#include "parallel.h"
#include "testing.h"
#include <pthread.h>
#include <unistd.h>

void *f1(void *p [[maybe_unused]]) {
  sleep(1);
  puts("f1 ended (expected first)");
  return nullptr;
}

void *f2(void *p [[maybe_unused]]) {
  sleep(2);
  puts("f2 ended (expected second)");
  return nullptr;
}

test(parallel) {
  pthread_t pt2 = async_f(f2);
  pthread_t pt1 = async_f(f1);
  expecteq((void *)nullptr, await(pt2));
  expecteq((void *)nullptr, await(pt1));
}
#endif
