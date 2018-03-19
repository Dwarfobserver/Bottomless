
// Defines the ASSERT(predicate, message) macro which evaluates predicate only in debug mode.
// In case of failure, throw an assert_error.

#pragma once

#include <build_info.hpp>
#include <string>

class assert_error : public std::runtime_error {
public:
    explicit assert_error(std::string&& msg);
};

namespace detail {
    void assert_failed(
        char const* expression,
        char const* file,
        int line,
        std::string const& message);
}

#if defined(NDEBUG)
    #if defined(_MSC_VER)
        #define ASSERT(x, msg) __assume(x)
    #else
        #define ASSERT(x, msg) static_cast<void>(0)
    #endif
#else
    #define ASSERT(predicate, message) static_cast<void>( \
                static_cast<bool>(predicate) || \
                (sc::detail::assert_failed(#predicate, __FILE__, static_cast<int>(__LINE__), message), 0))
#endif
