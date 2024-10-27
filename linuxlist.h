#pragma once
#include <stddef.h>
#include <stdlib.h>

typedef struct LinuxList {
  struct LinuxList *prev;
  struct LinuxList *next;
} LinuxList;

#define LINUXLIST_MEMBER ll
#define enableLinuxList LinuxList LINUXLIST_MEMBER
#define LinuxList(T) LinuxList##T

#define container_of(ptr, type, member)                                        \
  ({                                                                           \
    const typeof(((type *)0)->member) *mptr = ptr;                             \
    (type *)((char *)mptr - offsetof(type, member));                           \
  })

#define initLinuxList(T, v, member)                                            \
  ({                                                                           \
    T *result = malloc(sizeof(T));                                             \
    result->LINUXLIST_MEMBER.prev = &result->LINUXLIST_MEMBER;                 \
    result->LINUXLIST_MEMBER.next = &result->LINUXLIST_MEMBER;                 \
    result->member = v;                                                        \
    result;                                                                    \
  })
#define foreach_LinuxList(rt, elem)                                            \
  for (bool flag##elem = true; flag##elem;)                                    \
    for (auto elem = rt; flag##elem;                                           \
         (flag##elem =                                                         \
              elem->LINUXLIST_MEMBER.next != &(rt)->LINUXLIST_MEMBER) &&       \
         (elem = container_of(elem->LINUXLIST_MEMBER.next, typeof(*(rt)),      \
                              LINUXLIST_MEMBER)))
#define appendLinuxList(l, v, member)                                          \
  do {                                                                         \
    typeof(l) _new = malloc(sizeof(typeof(*(l))));                             \
    _new->member = v;                                                          \
    _new->LINUXLIST_MEMBER.prev = (l)->LINUXLIST_MEMBER.prev;                  \
    (l)->LINUXLIST_MEMBER.prev = &_new->LINUXLIST_MEMBER;                      \
    _new->LINUXLIST_MEMBER.next = &(l)->LINUXLIST_MEMBER;                      \
    _new->LINUXLIST_MEMBER.prev->next = &_new->LINUXLIST_MEMBER;               \
  } while (0)
#define insert(l, val) pass
#define removeLinuxList(l) pass
#define moveLinuxList(l, dir)                                                  \
  ({                                                                           \
    l = container_of((l)->LINUXLIST_MEMBER.dir, typeof(*(l)),                  \
                     LINUXLIST_MEMBER);                                        \
  })
#define nextLinuxList(l) moveLinuxList(l, next)
#define prevLinuxList(l) moveLinuxList(l, prev)
#define deleteLinuxList(l)                                                     \
  do {                                                                         \
    LinuxList *cursor = (l)->LINUXLIST_MEMBER.next, *next;                     \
    while (cursor != &(l)->LINUXLIST_MEMBER) {                                 \
      next = cursor->next;                                                     \
      free(container_of(cursor, typeof(*(l)), LINUXLIST_MEMBER));              \
      cursor = next;                                                           \
    }                                                                          \
    free(container_of(cursor, typeof(*(l)), LINUXLIST_MEMBER));                \
  } while (0)
