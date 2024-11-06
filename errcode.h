// Add more error codes as needed
#pragma once
#include "def.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  ERR_SUCCESS = 0,
  ERR_REACHED_UNREACHABLE = 1,
  ERR_ALLOC_FAILED = 2,
  ERR_THREAD_CREATE = 3,
  ERR_THREAD_JOIN = 4,
  ERR_RETRY = -1,
} errcode_t;

#define panic(e)                                                               \
  do {                                                                         \
    printf("Panicked at " HERE " ");                                           \
    puts(codetomsg(e));                                                        \
    exit(1);                                                                   \
  } while (0)

char const *codetomsg(int);
