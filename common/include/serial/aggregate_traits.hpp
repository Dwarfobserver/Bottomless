
/// Provides traits to detect and iterate on aggregate types.

#pragma once

#include <traits.hpp>

// Implementation inspired by :
// https://playfulprogramming.blogspot.ca/2016/12/serializing-structs-with-c17-structured.html
// Thanks to his wildcard type.

namespace traits {

    /// Defines the max arity that a type can have.

    constexpr int max_arity = 20;

    /// Detects if a type is brace-constructible from N elements.

    namespace detail {
        template <class SFINAE, class T, class...Args>
        struct is_brace_constructible {
            static constexpr bool value = false;
        };

        template <class T, class...Args>
        struct is_brace_constructible<std::void_t<
            decltype(T{ any<Args>... })
        >, T, types_tag<Args...>> {
            static constexpr bool value = true;
        };
    }

    template <class T, unsigned N>
    constexpr bool is_brace_constructible =
        detail::is_brace_constructible<void, T, make_types_tag<N, void>>::value;

    /// Gives the arity of a type (the number of elements which construct him).
    /// If he isn't an aggregate type, returns -1.
    /// If the maximum arity is reached, stops the compilation.

    namespace detail {
        template <class T, unsigned I>
        constexpr int arity_of_rec() {
            static_assert(I < max_arity, "");
            if constexpr (!traits::is_brace_constructible<T, I + 1>) {
                return I;
            }
            else {
                return arity_of_rec<T, I + 1>();
            }
        }

        template <class T>
        constexpr int arity_of() {
            // MSVC do not implement std::is_aggregate<T>
            if constexpr (!std::is_aggregate_v<T>) {
                return -1;
            }
            else {
                return arity_of_rec<T, 0>();
            }
        }
    }

    template <class T>
    constexpr int arity_of = detail::arity_of<T>();

}
