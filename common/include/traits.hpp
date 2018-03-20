
/// Stores common traits

#pragma once

#include <type_traits>


namespace traits {

    /// Used to retrieve classes from an overload or a specialization.

    template <class...Args>
    struct types_tag {};

    /// Used to create a sequence of voids in type_tag.

    namespace detail {
        template <int I, class...Vs>
        struct void_tag_rec {
            using type = typename void_tag_rec<I - 1, void, Vs...>::type;
        };

        template <class...Vs>
        struct void_tag_rec<0, Vs...> {
            using type = types_tag<Vs...>;
        };
    }

    template <unsigned N>
    using make_voids_tag = typename detail::void_tag_rec<N>::type;

    /// Used to represent any class.

    struct wildcard {
        template <class T, class = std::enable_if_t<
            !std::is_lvalue_reference<T>::value
        >>
        operator T&&() const;

        template <class T, class = std::enable_if_t<
            std::is_copy_constructible<T>::value
        >>
        operator T&() const;
    };

    /// Wildcard parametred by a class so it can be folded.

    template <class = void>
    static constexpr const wildcard any{};

    /// Detects if an expression is valid.

    namespace detail {
        template <class SFINAE, template <class...> class Expr, class...Ts>
        struct is_valid {
            static constexpr bool value = false;
        };
        template <template <class...> class Expr, class...Ts>
        struct is_valid<std::void_t<
            Expr<Ts...>
        >, Expr, Ts...> {
            static constexpr bool value = true;
        };
    }

    template <template <class...> class Expr, class...Ts>
    constexpr bool is_valid =
        detail::is_valid<void, Expr, Ts...>::value;

}
