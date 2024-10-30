#include "strlist.h"
#include "testing.h"

StringList *_initStringList(char *buf, size_t len) {
  StringList *ret = initList(StringList, _initVectorWithArray(buf, len), v);
  return ret;
}

overloadable void append(StringList *sl, char *buf) {
  Vector(char) new = initVectorWithArray(buf);
  appendList(sl, new, v);
}

char *toString(const StringList *const sl) {
  size_t len = 0;
  foreach_List(sl, item) len += VectorLen(item->v);
  char *ret = galloc(char, len);
  size_t offset = 0;
  foreach_List(sl, item) {
    memcpy(ret + offset, VectorBuf(item->v), VectorLen(item->v) - 1);
    offset += VectorLen(item->v) - 1;
  }
  return ret;
}

void deleteStringList(StringList **sl) {
  foreach_List(*sl, item) deinitVector(&item->v);
  deleteList(*sl);
}

test(initstrlist) {
  dropStringList StringList *sl = initStringList("hello world!");
  expecteq("hello world!", VectorBuf(sl->v));
  append(sl, "hello");
  StringList *prevsl = container_of(sl->ll.prev, StringList, ll);
  expecteq("hello", VectorBuf(prevsl->v));
}

test(tostring) {
  dropStringList StringList *sl = initStringList("this is sample text");
  append(sl, "hello");
  expecteq(sl->ll.next, sl->ll.prev);
  expecteq(sl->ll.next->next, &sl->ll);
  char *str drop = toString(sl);
  expecteq("this is sample texthello", str);
}
