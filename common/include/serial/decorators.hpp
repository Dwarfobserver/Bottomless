
/// Decorators can be used to agrement objects serialization.
/// By default, serializers ignore them.

#pragma once


namespace serial {

    /// Decorator types are instances of decorator<T>.

    template <class T>
    class decorator {};

    /// Decorator trait detector.

    template <class T>
    constexpr bool is_decorator = false;

    template <class T>
    constexpr bool is_decorator<decorator<T>> = true;
    template <class T>
    constexpr bool is_decorator<decorator<decorator<T>>> = false;

    /// Decorator tag types.

    namespace detail {
        class separator_type {};
        class begin_struct_type {};
        class end_struct_type {};
        class begin_collection_type {};
        class end_collection_type {};
    }

    /// Decorator concrete types.

    using separator        = decorator<detail::separator_type>;
    using begin_struct     = decorator<detail::begin_struct_type>;
    using end_struct       = decorator<detail::end_struct_type>;
    using begin_collection = decorator<detail::begin_collection_type>;
    using end_collection   = decorator<detail::end_collection_type>;

    /// helper functions to return a mutable reference to a decorator.

    namespace detail {
        template <class Decorator>
        Decorator& decorator_ref() { return *static_cast<Decorator*>(nullptr); }
    }

    constexpr auto separator_ref        = detail::decorator_ref<separator>;
    constexpr auto begin_struct_ref     = detail::decorator_ref<begin_struct>;
    constexpr auto end_struct_ref       = detail::decorator_ref<end_struct>;
    constexpr auto begin_collection_ref = detail::decorator_ref<begin_collection>;
    constexpr auto end_collection_ref   = detail::decorator_ref<end_collection>;
}
