
/// serial::in_base<Serializer> and serial::in_base<Serializer> are CRTP base classes for

#pragma once

#include <serial/base_traits.hpp>
#include <serial/decorators.hpp>

namespace serial {

    /// in_access and out_access are the types exposing operator& for directly (de)serializable
    /// types.

    namespace detail {
        
        template <class Serializer>
        struct in_access {
            Serializer& span;

            template <class T, class = std::enable_if_t<
                traits::is_directly_deserializable<Serializer, T>
            >>
            in_access& operator&(T& data) {
                span.deserialize(data);
                return *this;
            }
        };

        template <class Serializer>
        struct out_access {
            Serializer& span;

            template <class T, class = std::enable_if_t<
                traits::is_directly_serializable<Serializer, T>
            >>
            out_access& operator&(T& data) {
                span.serialize(const_cast<T const&>(data));
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
