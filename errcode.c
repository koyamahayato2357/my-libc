// Add more error codes as needed
#include "errcode.h"
#include <stdio.h>
#include <stdlib.h>

char *codetomsg(int code) {
  switch (code) {
  case ERR_SUCCESS:
    return "success";
  default:
    return "";
  }
}

[[noreturn]] void panic(int e) {
  printf("Panicked at %s:%d; ", __FILE__, __LINE__);
  puts(codetomsg(e));
  exit(e);
}
