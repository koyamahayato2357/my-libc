#pragma once
#include "ansiesc.h"
#include "gene.h"

#define LOG_LEVEL_TRACE 0
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_WARN 3
#define LOG_LEVEL_ERROR 4
#define LOG_LEVEL_CRITICAL 5
#define LOG_LEVEL_OFF 6

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
