
#include <sstream>
#include <catch.hpp>
#include <serial/all.hpp>

using namespace std::string_literals;

TEST_CASE("basic types", "[serialization]") {
    std::stringstream stream;
    using Serializer = stream_serializer<std::stringstream>;
    Serializer s{ stream };

    static_assert(traits::is_directly_serializable  <Serializer, int>);
    static_assert(traits::is_directly_deserializable<Serializer, int>);

    static_assert(traits::is_directly_serializable  <Serializer, std::string>);
    static_assert(traits::is_directly_deserializable<Serializer, std::string>);

    int  value = 42;
    std::string hello{ "Hello_stream_!" };
    s << value << hello;

    int  value_copy = 10;
    std::string hello_copy;
    s >> value_copy >> hello_copy;

    REQUIRE(value == value_copy);
    REQUIRE(hello == hello_copy);
}

namespace {
    enum class Title {
        mister,
        miss
    };
    struct Person {
        Title title;
        std::string name;
    };
}

template <class Serializer>
Serializer& operator&(Serializer& s, Title& g) { // TODO Allow rvalue ref binding
    constexpr auto m = "Mr.";
    constexpr auto f = "Ms.";
    return s & (g == Title::mister ? m : f);
}

template <class Serializer>
Serializer& operator&(Serializer& s, Person& p) { // TODO²
    using namespace serial;
    return s & begin_struct_ref()
             & p.title
             & separator_ref()
             & p.name
             & end_struct_ref();
}

TEST_CASE("custom types", "[serialization]") {
    Person person{ Title::mister, "Propre"s };

    std::ostringstream sStream;
    using Serializer = stream_serializer<std::ostringstream>;
    Serializer serializer{ sStream };

    serializer << person;
    CHECK(sStream.str() == "Mr.Propre");

    std::ostringstream pStream;
    using Printer = pretty_printer<std::ostringstream>;
    Printer printer{ pStream, 4 };

    printer << person;
    CHECK(pStream.str() ==
    "{\n"
    "    Mr.,\n"
    "    Propre\n"
    "}");
}

