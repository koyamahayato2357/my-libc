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

test (parallel) {
  pthread_t pt2 = spawn(f2, nullptr);
  pthread_t pt1 = spawn(f1, nullptr);
  expecteq((void *)nullptr, join(pt2));
  expecteq((void *)nullptr, join(pt1));
}
#endif
