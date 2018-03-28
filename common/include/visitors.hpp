
#pragma once

#include <traits.hpp>
#include <tuple>
#include <optional>

/// Visit tuples.

namespace detail {
    template <class F, int I, class...Ts>
    void visit_tuple(F&& f, std::tuple<Ts...>& tuple, traits::value_tag<int, I>) {
        if constexpr (I < sizeof...(Ts)) {
            f(std::get<I>(tuple));
            visit_tuple(f, tuple, traits::value_tag<int, I + 1>{});
        }
    }
}

template <class F, class...Ts>
void visit(std::tuple<Ts...>& tuple, F&& f) {
    detail::visit_tuple(f, tuple, traits::value_tag<int, 0>{});
}

/// Visit iterables.

template <class F, class Iterable, class = std::enable_if_t<
    traits::is_iterable<Iterable>
>>
void visit(Iterable& iterable, F&& f) {
    for (auto& val : iterable) f(val);
}

/// Visit optionals.

template <class F, class T>
void visit(std::optional<T>& opt, F&& f) {
    if (opt) f(*opt);
}
