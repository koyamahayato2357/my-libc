// Add more error codes as needed
#pragma once

typedef enum {
  ERR_SUCCESS = 0,
  ERR_REACHED_UNREACHABLE = 1,
  ERR_RETRY = -1,
} errcode_t;

char *codetomsg(int);
void panic(int);
