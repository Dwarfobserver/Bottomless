
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

    template <class T, T arg>
    struct value_tag {
        static constexpr auto value = arg;
    };

    template <class T, T...args>
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
        template <int I, class T, T...args>
        struct make_values_tag;
        template <int I, class T, T arg, T...args>
        struct make_values_tag<I, T, arg, args...> {
            using type = typename make_values_tag<I - 1, T, arg, arg, args...>::type;
        };
        template <class T, T arg, T...args>
        struct make_values_tag<0, T, arg, args...> {
            using type = values_tag<T, args...>;
        };
    }

    template <unsigned N, class T, T arg>
    using make_values_tag = typename detail::make_values_tag<N, T, arg>::type;

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

    /// Detect if a type is iterable (with begin() and end() member functions).
    
    namespace detail {
        template <class T, class SFINAE = void>
        struct is_iterable {
            static constexpr bool value = false;
        };
        template <class T>
        struct is_iterable<T, std::void_t<decltype(
            (std::declval<T&>().begin(), std::declval<T&>().end())
        )>> {
            static constexpr bool value = true;
        };
    }

    template <class T>
    constexpr bool is_iterable = detail::is_iterable<T>::value;

}
