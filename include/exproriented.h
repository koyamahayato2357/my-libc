#pragma once
#include "errcode.h"

#define UNIT 0UL

#define orelse ?:

#define $break       $(break)
#define $continue    $(continue)
#define $return(...) $(return __VA_ARGS__)
#define $unreachable $(unreachable)
#define $panic(e)    $(panic(e))
#define $throw(e)    $(throw(e))

// use in pointer calculation
#define p$break       p$(break)
#define p$continue    p$(continue)
#define p$return(...) p$(return __VA_ARGS__)
#define p$unreachable p$(unreachable)
#define p$panic(e)    p$(panic(e))
#define p$throw(e)    p$(throw(e))

#define $if(cond) (cond) ?
#define $else :
#define $(statements) \
  ({ \
    statements; \
    UNIT; \
  })
#define p$(statements) \
  ({ \
    statements; \
    (void *)UNIT; \
  })
