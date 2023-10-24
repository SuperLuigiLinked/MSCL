/**
 * @file demo/utils.h
 */

#pragma once

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LOG(...) (void)fprintf(stderr, __VA_ARGS__)

#if __has_builtin(__debugbreak) && !defined(NDEBUG)
    #define ASSERT(expr) if (expr) {} else (__debugbreak(), abort())
#else
    #define ASSERT(expr) if (expr) {} else abort()
#endif
