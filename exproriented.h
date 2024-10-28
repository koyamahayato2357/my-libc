#pragma once
#include "errcode.h"

#define $break $(break)
#define $continue $(continue)
#define $return(a) $(return a)
#define $unreachable                                                           \
  $(longjmp(EXCEPTION_H_jb[EXCEPTION_H_nest - 1], ERR_REACHED_UNREACHABLE))
#define $panic(e) $(panic(e))
#define $throw(e) $(throw(e))

// use in pointer calculation
#define p$break p$(break)
#define p$continue p$(continue)
#define p$return(a) p$(return a)
#define p$unreachable                                                          \
  p$(longjmp(EXCEPTION_H_jb[EXCEPTION_H_nest - 1], ERR_REACHED_UNREACHABLE))
#define p$panic(e) p$(panic(e))
#define p$throw(e) p$(throw(e))

#define ifx(cond) (cond) ?
#define elsex :
#define orelse ?:
#define $(statements)                                                          \
  ({                                                                           \
    statements;                                                                \
    0UL;                                                                       \
  })
#define p$(statements)                                                         \
  ({                                                                           \
    statements;                                                                \
    (void *)0;                                                                 \
  })
