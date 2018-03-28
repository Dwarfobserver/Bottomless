
/// Defines cross_compiler macros for clang, gcc and msvc.

#pragma once

#if defined(_DEBUG)
#include <assert.hpp>
#endif

/// Ensures that the compiler is supported (msvc, clang or gcc).

#if !defined(_MSC_VER) && !defined(__clang__) && !defined(__GNUG__)
#error The compiler used is not supported.
#endif

/// FORCE_INLINE and NO_INLINE : Indicates that a function must (not) be inlined.

#if defined(_MSC_VER)
    #define FORCE_INLINE __forceinline
    #define NO_INLINE __declspec(noinline)
#else
    #define FORCE_INLINE inline __attribute__((always_inline))
    #define NO_INLINE __attribute__((noinline))
#endif

/// LIKELY(x) and UNLIKELY(x) : Mark an expression as evaluating to respectively true or false most of the time.

#if defined(_MSC_VER)
    #define LIKELY(x)   (static_cast<bool>(x))
    #define UNLIKELY(x) (static_cast<bool>(x))
#else
    #define LIKELY(x)   (__builtin_expect(static_cast<bool>(x), true))
    #define UNLIKELY(x) (__builtin_expect(static_cast<bool>(x), false))
#endif

/// RESTRICT : Indicates that pointers or references of the same type do not overlap on values.

#if defined(NDEBUG)
    #define RESTRICT __restrict
#else
    #define RESTRICT
#endif

/// UNREACHABLE() : Mark a path as unreachable. In debug, throw an exception.

#if defined(NDEBUG)
    #if defined(_MSC_VER)
        #define UNREACHABLE() __assume(0)
    #else
        #define UNREACHABLE() __builtin_unreachable()
    #endif
#else
    #define UNREACHABLE() ASSERT(false, "UNREACHABLE() macro reached in debug mode")
#endif
