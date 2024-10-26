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
#define pbreakx                                                                \
  ({                                                                           \
    break;                                                                     \
    (void *)0;                                                                 \
  })
#define pcontinuex                                                             \
  ({                                                                           \
    continue;                                                                  \
    (void *)0;                                                                 \
  })
#define preturnx(a)                                                            \
  ({                                                                           \
    return a;                                                                  \
    (void *)0                                                                  \
  })
#define ifx(cond) (cond) ?
#define elsex :
#undef unreachable // builtin macro
#define unreachable                                                            \
  ({                                                                           \
    longjmp(EXCEPTION_H_jb[EXCEPTION_H_nest - 1], ERR_REACHED_UNREACHABLE);    \
    0;                                                                         \
  })
#define panicx(e)                                                              \
  ({                                                                           \
    panic(e);                                                                  \
    0;                                                                         \
  })
#define punreachable                                                           \
  ({                                                                           \
    longjmp(EXCEPTION_H_jb[EXCEPTION_H_nest - 1], ERR_REACHED_UNREACHABLE);    \
    (void *)0;                                                                 \
  })
#define ppanicx(e)                                                             \
  ({                                                                           \
    panic(e);                                                                  \
    (void *)0;                                                                 \
  })
#define orelse ?:
