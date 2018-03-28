

#pragma once

#include <aggregates_to_tuples.hpp>

/// Decay char native as a char pointer.

template <class Serializer, int N>
Serializer& operator&(Serializer& s, char const (& data)[N]) { // TODO string_view of size N ?
    return s & static_cast<char const*>(data);
}

template <class Serializer, class...Ts>
Serializer& operator&(Serializer& s, std::tuple<Ts...>& tuple) {
    
}

