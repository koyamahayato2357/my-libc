#pragma once
#include "errcode.h"

#define breakx                                                                 \
  ({                                                                           \
    break;                                                                     \
    0UL;                                                                       \
  })
#define continuex                                                              \
  ({                                                                           \
    continue;                                                                  \
    0UL;                                                                       \
  })
#define returnx(a)                                                             \
  ({                                                                           \
    return a;                                                                  \
    0UL                                                                        \
  })
#undef unreachable // builtin macro
#define unreachable                                                            \
  ({                                                                           \
    longjmp(EXCEPTION_H_jb[EXCEPTION_H_nest - 1], ERR_REACHED_UNREACHABLE);    \
    0UL;                                                                       \
  })
#define panicx(e)                                                              \
  ({                                                                           \
    panic(e);                                                                  \
    0UL;                                                                       \
  })
#define throwx(e)                                                              \
  ({                                                                           \
    throw(e);                                                                  \
    0UL;                                                                       \
  })

// use in pointer calculation
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
#define pthrowx(e)                                                             \
  ({                                                                           \
    throw(e);                                                                  \
    (void *)0;                                                                 \
  })

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
    (void *)0                                                                  \
  })
