
#pragma once

#include <string>
#include <assert.hpp>
#include <serial/io_base.hpp>

/// Copy the bytes representation of the objects serialized.

class binary_serializer :
    public serial::in_base <binary_serializer>,
    public serial::out_base<binary_serializer>
{
    friend serial::in_base <binary_serializer>::access;
    friend serial::out_base<binary_serializer>::access;
public:
    char* bytes;
    binary_serializer(char* bytes = nullptr) : bytes(bytes) {}
private:
    template <class T, class = std::enable_if_t<
        std::is_trivially_copyable_v<T>
    >>
    void serialize(T const& data) {
        ASSERT(bytes, "The buffer pointer must not be null");
        reinterpret_cast<T&>(*bytes) = data;
        bytes += sizeof(T);
    }

    template <class T, class = std::enable_if_t<
        std::is_trivially_copyable_v<T>
    >>
    void deserialize(T& data) {
        ASSERT(bytes, "The buffer pointer must not be null");
        data = reinterpret_cast<T&>(*bytes);
        bytes += sizeof(T);
    }
};

/// Wrap a stream object which can serialize objects. TODO Make serialize functions privates

template <class Stream = std::iostream>
struct stream_serializer :
    public serial::in_base <stream_serializer<Stream>>,
    public serial::out_base<stream_serializer<Stream>>
{
    friend typename serial::in_base <stream_serializer<Stream>>::access;
    friend typename serial::out_base<stream_serializer<Stream>>::access;
public:
    Stream& stream;
    stream_serializer(Stream& stream) : stream(stream) {}
//private:
    template <class T, class = std::void_t<
        decltype(stream << std::declval<T const&>())
    >>
    void serialize(T const& data) {
        stream << data;
    }

    template <class T, class = std::void_t<
        decltype(stream >> std::declval<T&>())
    >>
    void deserialize(T& data) {
        stream >> data;
    }
};

/// Wrap a stream object which can serialize objects as string.
/// Use spaces indentation and decorators.

template <class OStream = std::ostream>
struct pretty_printer :
    public serial::out_base<pretty_printer<OStream>>
{
    friend typename serial::out_base<pretty_printer<OStream>>::access;
public:
    OStream& stream;
    int const indentation;
    pretty_printer(OStream& stream, int indentation) :
        stream(stream),
        indentation(indentation)
    {}
//private:
    std::string spaces;

    template <class T>
    void serialize(T const& val) {
        stream << val;
    }
    
    void serialize(serial::separator)   {
        stream << ",\n";
    }
    void serialize_begin(char c) {
        stream << spaces << c << '\n';
        spaces += std::string(indentation, ' ');
    }
    void serialize_end(char c)   {
        spaces.resize(spaces.size() - indentation);
        stream << '\n' << spaces << c;
    }
    void serialize(serial::begin_struct)     { serialize_begin('{'); }
    void serialize(serial::end_struct)       { serialize_end  ('}'); }
    void serialize(serial::begin_collection) { serialize_begin('['); }
    void serialize(serial::end_collection)   { serialize_end  (']'); }
};
