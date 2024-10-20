#pragma once
#include <stdlib.h>

typedef struct LinuxList {
  struct LinuxList *prev;
  struct LinuxList *next;
} LinuxList;

#define LINUXLIST_MEMBER ll
#define enableLinuxList LinuxList LINUXLIST_MEMBER
#define LinuxList(T) LinuxList##T

#define offset_of(type, member) ((size_t) & ((type *)0)->member)
#define container_of(ptr, type, member)                                        \
  ({                                                                           \
    const __typeof__(((type *)0)->member) *mptr = ptr;                         \
    (type *)((char *)mptr - offset_of(type, member));                          \
  })

#define initLinuxList(T)                                                       \
  ({                                                                           \
    T *result = malloc(sizeof(T));                                             \
    result->LINUXLIST_MEMBER.prev = &result->LINUXLIST_MEMBER;                 \
    result->LINUXLIST_MEMBER.next = &result->LINUXLIST_MEMBER;                 \
    result;                                                                    \
  })
#define foreach_LinuxList(rt, elem)                                            \
  for (bool flag##elem = true; flag##elem;)                                    \
    for (auto elem = container_of((rt)->LINUXLIST_MEMBER.next,                 \
                                  __typeof__(*(rt)), LINUXLIST_MEMBER);        \
         flag##elem;                                                           \
         (flag##elem =                                                         \
              elem->LINUXLIST_MEMBER.next != &(rt)->LINUXLIST_MEMBER) &&       \
         (elem = container_of(elem->LINUXLIST_MEMBER.next, __typeof__(*(rt)),  \
                              LINUXLIST_MEMBER)))
#define append(l, v)                                                           \
  do {                                                                         \
    __typeof__(l) new = malloc(sizeof(__typeof__(*(l))));                      \
    new->val = v;                                                              \
    new->LINUXLIST_MEMBER.prev = (l)->LINUXLIST_MEMBER.prev;                   \
    (l)->LINUXLIST_MEMBER.prev = &new->LINUXLIST_MEMBER;                       \
    new->LINUXLIST_MEMBER.next = &(l)->LINUXLIST_MEMBER;                       \
    new->LINUXLIST_MEMBER.prev->next = &new->LINUXLIST_MEMBER;                 \
  } while (0)
#define insert(l, val) pass
#define deleteLinuxList(l)                                                     \
  do {                                                                         \
    LinuxList *cursor = (l)->LINUXLIST_MEMBER.next, *next;                     \
    while (cursor != &(l)->LINUXLIST_MEMBER) {                                 \
      next = cursor->next;                                                     \
      free(container_of(cursor, __typeof__(*(l)), LINUXLIST_MEMBER));          \
      cursor = next;                                                           \
    }                                                                          \
  } while (0)
