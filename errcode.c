// Add more error codes as needed
#include "errcode.h"

char const *codetomsg(int code) {
  switch (code) {
  case ERR_SUCCESS:
    return "success";
  case ERR_ALLOC_FAILED:
    return "allocation failure";
  case ERR_REACHED_UNREACHABLE:
    return "reached unreachable";
  default:
    return "";
  }
}
