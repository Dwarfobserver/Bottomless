
/// Package header including commonly used headers.

#pragma once

#include <build_info.hpp>
#include <assert.hpp>
#include <compiler_hints.hpp>

// defer(f) returns a RAII object which invokes the functor at the end of it's scope.

namespace detail {
    template <class F>
    struct deferred {
        deferred(F&& f)      noexcept(std::is_nothrow_move_constructible_v<F>) :
            f_(std::move(f)) {}
        deferred(F const& f) noexcept(std::is_nothrow_copy_constructible_v<F>) :
            f_(f) {}
        ~deferred()          noexcept(noexcept(std::declval<F>()()))
            { f_(); }
    private:
        F f_;
    };
}

template <class F>
auto defer(F&& defferedFunction) {
    return detail::deferred<F>{ std::forward<F>(defferedFunction) };
}

/// TODO Macro defer (with auto name)
