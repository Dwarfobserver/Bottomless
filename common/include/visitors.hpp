
#pragma once

#include <traits.hpp>
#include <tuple>
#include <optional>

/// Visit optionals. First occurence of visit, to write the trait is_visitable.

template <class F, class T>
void visit(std::optional<T>& opt, F&& f) {
    if (opt) f(*opt);
}

/// Indicates if a type can be visited.

namespace traits {

    namespace detail {
        template <class T, class SFINAE = void>
        struct is_visitable {
            static constexpr bool value = false;
        };
        template <class T>
        struct is_visitable<T, std::void_t<decltype(
            visit(std::declval<T&>(), std::declval<float&&>())
        )>> {
            static constexpr bool value = true;
        };
    }
    template <class T>
    constexpr bool is_visitable = detail::is_visitable<T>::value;
    
}

/// Visit tuples. TODO Add forward references for data & F

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
