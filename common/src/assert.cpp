
#include <assert.hpp>
#include <compiler_hints.hpp>

assert_error::assert_error(std::string&& msg) :
    std::runtime_error(std::move(msg))
{}

namespace detail {
    NO_INLINE void assert_failed(
        char const* expression,
        char const* file,
        int line,
        std::string const& message)
    {
        using namespace std::string_literals;
        auto msg =  "In file "s + file + "\n"
                    "Line " + std::to_string(line) + " : Assert failed at '"s + expression + "'.\n"
                    "Message : " + message;
        throw assert_error{ std::move(msg) };
    }
}
