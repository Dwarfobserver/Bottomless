
#pragma once


namespace serial {

    template <class T>
    class decorator {};

    template <class T>
    constexpr bool is_decorator = false;

    template <class T>
    constexpr bool is_decorator<decorator<T>> = true;

    namespace detail {
        class separator_type {};
        class begin_struct_type {};
        class end_struct_type {};
        class begin_collection_type {};
        class end_collection_type {};
    }

    using separator        = decorator<detail::separator_type>;
    using begin_struct     = decorator<detail::begin_struct_type>;
    using end_struct       = decorator<detail::end_struct_type>;
    using begin_collection = decorator<detail::begin_collection_type>;
    using end_collection   = decorator<detail::end_collection_type>;

}
