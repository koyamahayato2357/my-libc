// Add more error codes as needed
#pragma once

typedef enum {
  ERR_SUCCESS = 0,
  ERR_REACHED_UNREACHABLE = 1,
  ERR_ALLOC_FAILED = 2,
  ERR_RETRY = -1,
} errcode_t;

const char *codetomsg(int);
void panic(int);
