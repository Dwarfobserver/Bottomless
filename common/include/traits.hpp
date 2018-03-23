
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

    template <auto...args>
    struct values_tag {};

    // Used to create a sequence of classes in a tag.

    namespace detail {
        template <int I, class...Ts>
        struct make_types_tag;
        template <int I, class T, class...Ts>
        struct make_types_tag<I, T, Ts...> {
            using type = typename make_types_tag<I - 1, T, T, Ts...>::type;
        };
        template <class T, class...Ts>
        struct make_types_tag<0, T, Ts...> {
            using type = types_tag<Ts...>;
        };
    }

    template <unsigned N, class T>
    using make_types_tag = typename detail::make_types_tag<N, T>::type;

    // Used to create a sequence of values in a tag.

    namespace detail {
        template <int I, auto...args>
        struct make_values_tag;
        template <int I, auto arg, auto...args>
        struct make_values_tag<I, arg, args...> {
            using type = typename make_values_tag<I - 1, arg, arg, args...>::type;
        };
        template <auto arg, auto...args>
        struct make_values_tag<0, arg, args...> {
            using type = values_tag<args...>;
        };
    }

    template <unsigned N, auto arg>
    using make_values_tag = typename detail::make_values_tag<N, arg>::type;

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
