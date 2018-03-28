
/// serial::in_base<Serializer> and serial::in_base<Serializer> are CRTP base classes for

#pragma once

#include <visitors.hpp>
#include <serial/decorators.hpp>

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

namespace serial {

    /// This visitor add decorators. Add custom visitors :

    namespace detail {
        /// TODO
    }

    /// in_access and out_access are the types exposing operator& for directly (de)serializable
    /// types.

    namespace detail {
        
        template <class Serializer>
        struct in_access {
            Serializer& span;

            template <class T>
            in_access& operator&(T& data) {
                if constexpr (traits::is_directly_deserializable<Serializer, T>) {
                    span.deserialize(data);
                }
                else if constexpr (traits::is_visitable<T>) {
                    visit(data, [&] (auto& v) {
                        *this & v;
                    });
                }
                else {
                    static_assert(false, "The type T cannot be directly deserialized by "
                                         "the type Serializer, and cannot be visited.");
                }
                return *this;
            }

            template <class T>
            in_access& operator&(decorator<T>& data) {
                return *this;
            }
        };

        template <class Serializer>
        struct out_access {
            Serializer& span;

            template <class T>
            out_access& operator&(T& data) {
                if constexpr (traits::is_directly_serializable<Serializer, T>) {
                    span.serialize(const_cast<T const&>(data));
                }
                else if constexpr (traits::is_visitable<T>) {
                    visit(data, [&] (auto& v) {
                        *this & v;
                    });
                }
                else {
                    static_assert(false, "The type T cannot be directly serialized by "
                                         "the type Serializer, and cannot be visited.");
                }
                return *this;
            }
            
            template <class T, class = std::enable_if_t<
                !traits::is_directly_serializable<Serializer, T>
            >>
            out_access& operator&(decorator<T>& data) {
                return *this;
            }
        };
        
    }

    /// in_base and out_base exposes flux operators (>> and <<).
    /// They delegate the serialize call to access classes above.

    template <class Serializer>
    struct in_base {
        using access = detail::in_access<Serializer>;

        template <class T>
        Serializer& operator>>(T& data) {
            auto& user = static_cast<Serializer&>(*this);
            auto s = access{ user };
            s & data;
            return user;
        }
    };

    template <class Serializer>
    struct out_base {
        using access = detail::out_access<Serializer>;

        template <class T>
        Serializer& operator<<(T const& data) {
            auto& user = static_cast<Serializer&>(*this);
            auto s = access{ user };
            s & const_cast<T&>(data);
            return user;
        }
    };

}
