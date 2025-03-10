#pragma once
#include "errcode.h"
#include <setjmp.h>

constexpr size_t MAX_NEST_DEPTH = 8;

extern jmp_buf EXCEPTION_H_jb[MAX_NEST_DEPTH];
extern int EXCEPTION_H_errcode;
extern int EXCEPTION_H_nest;

#define EXCEPTION_H_CAT(x, y)     x##y
#define EXCEPTION_H_GENUNIQTOK(x) EXCEPTION_H_CAT(EXCEPTION_H_, x)

void EXCEPTION_H_cl(int *const restrict *const restrict g);

#define EXCEPTION_H_TRY(cnt) \
  for (int *EXCEPTION_H_CAT(EXCEPIOTN_H_g_, cnt) \
         [[gnu::cleanup(EXCEPTION_H_cl)]] \
         = &EXCEPTION_H_nest, \
       EXCEPTION_H_CAT(EXCEPTION_H_FLAG, cnt) = 1; \
       EXCEPTION_H_CAT(EXCEPTION_H_FLAG, cnt); \
       EXCEPTION_H_CAT(EXCEPTION_H_FLAG, cnt) = 0) \
    if ((EXCEPTION_H_errcode = setjmp(EXCEPTION_H_jb[EXCEPTION_H_nest++])) \
          == 0 \
        || EXCEPTION_H_errcode == ERR_RETRY)

#define try          EXCEPTION_H_TRY(__COUNTER__)
#define catch(e)     else if (EXCEPTION_H_errcode == (e))
#define catchor(e)   else if (EXCEPTION_H_errcode & (e))
#define catchany     else
#define capture(cap) for (int cap = EXCEPTION_H_errcode; cap; cap = 0)
#define retry        throw(ERR_RETRY)
#define throw(e)     longjmp(EXCEPTION_H_jb[EXCEPTION_H_nest - 1], e)
#undef unreachable // builtin macro
#define unreachable \
  longjmp(EXCEPTION_H_jb[EXCEPTION_H_nest - 1], ERR_REACHED_UNREACHABLE)
#define ignerr try
