#pragma once
#include "errcode.h"

#define breakx                                                                 \
  ({                                                                           \
    break;                                                                     \
    0;                                                                         \
  })
#define continuex                                                              \
  ({                                                                           \
    continue;                                                                  \
    0;                                                                         \
  })
#define returnx(a)                                                             \
  ({                                                                           \
    return a;                                                                  \
    0                                                                          \
  })
#define ifx(cond) (cond) ?
#define elseifx(cond) : (cond) ?
#define elsex :
#define unreachable                                                            \
  ({                                                                           \
    longjmp(EXCEPTION_H_jb[EXCEPTION_H_nest - 1], 1);                          \
    0;                                                                         \
  })
#define panicx(e)                                                              \
  ({                                                                           \
    panic(e);                                                                  \
    0;                                                                         \
  })
