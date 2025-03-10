#pragma once
#include "chore.h"
#include <stddef.h>

typedef struct List {
  struct List *prev;
  struct List *next;
} List;

#define LIST_MEMBER ll
#define ListDeclare List LIST_MEMBER
#define List(T)     List##T

#define container_of(ptr, type, member) \
  ({ \
    typeof(((type *)0)->member) const *mptr = ptr; \
    (type *)((char *)mptr - offsetof(type, member)); \
  })

#define initList(T, v, member) \
  ({ \
    T *result = galloc(T, 1); \
    result->LIST_MEMBER.prev = &result->LIST_MEMBER; \
    result->LIST_MEMBER.next = &result->LIST_MEMBER; \
    result->member = v; \
    result; \
  })
#define foreach_List(rt, elem) \
  for (bool flag##elem = true; flag##elem;) \
    for (auto elem = rt; flag##elem; \
         (flag##elem = elem->LIST_MEMBER.next != &(rt)->LIST_MEMBER) \
         && (elem = container_of(elem->LIST_MEMBER.next, typeof(*(rt)), LIST_MEMBER)))
#define appendList(l, v, member) \
  do { \
    typeof(l) _new = galloc(typeof(*(l)), 1); \
    _new->member = v; \
    _new->LIST_MEMBER.prev = (l)->LIST_MEMBER.prev; \
    (l)->LIST_MEMBER.prev = &_new->LIST_MEMBER; \
    _new->LIST_MEMBER.next = &(l)->LIST_MEMBER; \
    _new->LIST_MEMBER.prev->next = &_new->LIST_MEMBER; \
  } while (0)
#define insert(l, val) pass
#define removeList(l)  pass
#define moveList(l, dir) \
  (l = container_of((l)->LIST_MEMBER.dir, typeof(*(l)), LIST_MEMBER))
#define nextList(l) moveList(l, next)
#define prevList(l) moveList(l, prev)
#define deleteList(l) \
  do { \
    List *cursor = (l)->LIST_MEMBER.next, *next; \
    while (cursor != &(l)->LIST_MEMBER) { \
      next = cursor->next; \
      free(container_of(cursor, typeof(*(l)), LIST_MEMBER)); \
      cursor = next; \
    } \
    free(container_of(cursor, typeof(*(l)), LIST_MEMBER)); \
  } while (0)
