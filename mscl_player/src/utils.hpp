/**
 * @file mscl_player/utils.hpp
 */

#pragma once

#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cmath>

// ================================================================================================================================

#if !defined(NDEBUG)
    #include <stdio.h>
    
    #define LOG(...) (void)std::fprintf(stderr, __VA_ARGS__)
    #define ASSERT(expr) if (expr) {} else std::abort()
#else
    #define LOG(...) (void)0
    #define ASSERT(expr) if (expr) {} else std::abort()
#endif

// ================================================================================================================================

