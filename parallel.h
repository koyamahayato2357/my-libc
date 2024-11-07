#pragma once
#include "errcode.h"
#include <pthread.h>

#define async(fn, arg)                                                         \
  ({                                                                           \
    pthread_t pt;                                                              \
    if (pthread_create(&pt, nullptr, fn, (void *)arg) != 0)                    \
      panic(ERR_THREAD_CREATE);                                                \
    pt;                                                                        \
  })
#define await(pt)                                                              \
  ({                                                                           \
    void *ret;                                                                 \
    if (pthread_join(pt, &ret) != 0)                                           \
      panic(ERR_THREAD_JOIN);                                                  \
    ret;                                                                       \
  })
