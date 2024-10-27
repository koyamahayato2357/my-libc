// Add more error codes as needed
#include "errcode.h"
#include "def.h"
#include <stdio.h>
#include <stdlib.h>

const char *codetomsg(int code) {
  switch (code) {
  case ERR_SUCCESS:
    return "success";
  default:
    return "";
  }
}

[[noreturn]] void panic(int e) {
  printf("Panicked at " HERE);
  puts(codetomsg(e));
  exit(e);
}
