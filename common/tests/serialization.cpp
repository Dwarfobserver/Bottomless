
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

template <class F>
void visit(Title& title, F&& f) { // TODO Allow rvalue ref binding
    constexpr auto mister = "Mr.";
    constexpr auto miss   = "Ms.";
    f(title == Title::mister ? mister : miss);
}

template <class F>
void visit(Person& p, F&& f) {
    visit(p.title, f);
    f(p.name);
}

TEST_CASE("custom types", "[serialization]") {
    Person person{ Title::mister, "Propre"s };

    std::ostringstream sStream;
    using Serializer = stream_serializer<std::ostringstream>;
    Serializer serializer{ sStream };

    serializer << person;
    CHECK(sStream.str() == "Mr.Propre");
}

namespace {
    struct Currency {
        int value;
    };
    struct Converter {
        std::string brand;
        Currency dollars;
        Currency euros;
    };
}

TEST_CASE("aggregate types", "[serialization]") {
    Converter converter{ "HSBC", { 2 }, { 3 } };

    std::ostringstream sStream;
    using Serializer = stream_serializer<std::ostringstream>;
    Serializer serializer{ sStream };

    serializer << converter;
    CHECK(sStream.str() == "HSBC23");
}
