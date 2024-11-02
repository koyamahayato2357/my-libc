#pragma once
#include "ansiesc.h"
#include "gene.h"

enum {
  LOG_LEVEL_TRACE,
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_INFO,
  LOG_LEVEL_WARN,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_CRITICAL,
  LOG_LEVEL_OFF,
};

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_OFF
#endif

#if LOG_LEVEL <= LOG_LEVEL_TRACE
#define LOG_TRACE(...) fprintf(stderr, ESTHN "[TRACE] " ESCLR __VA_ARGS__)
#else
#define LOG_TRACE(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LOG_DEBUG(...) fprintf(stderr, ESTHN "[DEBUG] " ESCLR __VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOG_INFO(...) fprintf(stderr, ESTHN "[INFO] " ESCLR __VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARN
#define LOG_WARN(...) fprintf(stderr, ESTHN "[WARN] " ESCLR __VA_ARGS__)
#else
#define LOG_WARN(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LOG_ERROR(...) fprintf(stderr, ESTHN "[ERROR] " ESCLR __VA_ARGS__)
#else
#define LOG_ERROR(...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_CRITICAL
#define LOG_CRITICAL(...) fprintf(stderr, ESTHN "[CRITICAL] " ESCLR __VA_ARGS__)
#define LOG_PRINTANY(x) printany(x)
#else
#define LOG_CRITICAL(...)
#define LOG_PRINTANY(x)
#endif
