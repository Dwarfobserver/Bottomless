
#include <sstream>
#include <catch.hpp>
#include <serial/all.hpp>


TEST_CASE("basic types", "[serialization]") {
    std::stringstream stream;
    using Serializer = stream_serializer<std::stringstream>;
    Serializer s{ stream };

    static_assert(traits::is_serializable  <Serializer, int>);
    static_assert(traits::is_deserializable<Serializer, int>);

    static_assert(traits::is_serializable  <Serializer, std::string>);
    static_assert(traits::is_deserializable<Serializer, std::string>);

    int  value = 42;
    std::string hello{ "Hello_stream_!" };
    s << value << hello;

    int  value_copy = 10;
    std::string hello_copy;
    s >> value_copy >> hello_copy;

    REQUIRE(value == value_copy);
    REQUIRE(hello == hello_copy);
}
