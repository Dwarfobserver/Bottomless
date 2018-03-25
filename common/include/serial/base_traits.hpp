
#pragma once


namespace traits {

    /// Detect if, for a given serializer, a class is (de) serializable.

    template <class Serializer, class T, class SFINAE = void>
    constexpr bool is_directly_deserializable = false;

    template <class Serializer, class T>
    constexpr bool is_directly_deserializable<Serializer, T, std::void_t<
        decltype(std::declval<Serializer&>().deserialize(std::declval<T&>()))
    >> = true;


    template <class Serializer, class T, class SFINAE = void>
    constexpr bool is_directly_serializable = false;

    template <class Serializer, class T>
    constexpr bool is_directly_serializable<Serializer, T, std::void_t<
        decltype(std::declval<Serializer&>().serialize(std::declval<T const&>()))
    >> = true;

}
