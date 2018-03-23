
/// Stores common traits

#pragma once

#include <type_traits>


namespace traits {

    /// Used to retrieve classes from an overload or a specialization.

    template <class T>
    struct type_tag {
        using type = T;
    };

    template <class...Ts>
    struct types_tag {};

    /// Same for constexpr values.

    template <auto arg>
    struct value_tag {
        static constexpr auto value = arg;
    };

    // Used to create a sequence of classes in a tag.

    namespace detail {
        template <int I, class...Ts>
        struct make_types_tag;
        template <int I, class T, class...Ts>
        struct make_types_tag<I, T, Ts...> {
            using type = make_types_tag<I - 1, T, T, Ts...>;
        };
        template <class...Ts>
        struct make_types_tag<0, Ts...> {
            using type = types_tag<Ts...>;
        };
    }

    template <class T, unsigned N>
    using make_types_tag = typename detail::make_types_tag<N, T>;

    // Used to create a sequence of values in a tag.

    namespace detail {
        template <int I, auto...args>
        struct make_types_tag;
        template <int I, auto arg, auto...args>
        struct make_types_tag<I, arg, args...> {
            using type = make_types_tag<I - 1, arg, arg, args...>;
        };
        template <auto...args>
        struct make_types_tag<0, args...> {
            using type = types_tag<args...>;
        };
    }

    template <auto arg, unsigned N>
    using make_values_tag = typename detail::make_types_tag<N, T>;

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

}
