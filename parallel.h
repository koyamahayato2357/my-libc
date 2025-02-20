#pragma once
#include "errcode.h"
#include <pthread.h>

// Is this correct usage of the word async/await?
#define async(fn, arg)                                                         \
  ({                                                                           \
    pthread_t pt;                                                              \
    if (pthread_create(&pt, nullptr, fn, (void *)arg))                         \
      panic(ERR_THREAD_CREATE);                                                \
    pt;                                                                        \
  })
#define await(pt)                                                              \
  ({                                                                           \
    void *ret;                                                                 \
    if (pthread_join(pt, &ret))                                                \
      panic(ERR_THREAD_JOIN);                                                  \
    ret;                                                                       \
  })
