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

#if !defined(NDEBUG)
    #define LOG(...) (void)fprintf(stderr, __VA_ARGS__)
    #define ASSERT(expr) if (expr) {} else (LOG("ASSERTION FAILED:\n" #expr "\n"), abort())
#else
    #define LOG(...) (void)0
    #define ASSERT(expr) if (expr) {} else abort()
#endif
