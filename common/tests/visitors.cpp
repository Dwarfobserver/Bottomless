
#include <catch.hpp>
#include <visitors.hpp>

TEST_CASE("visitors iterables", "[visitors]") {
    static_assert(traits::is_visitable<std::vector<int>>);

    std::vector<int> ints{ 2, 1, 7 };

    int sum = 0;
    visit(ints, [&] (int v) { sum += v; });

    REQUIRE(sum == 10);
}

TEST_CASE("visitors tuples", "[visitors]") {
    static_assert(traits::is_visitable<std::tuple<unsigned long, unsigned, signed>>);

    auto tuple = std::make_tuple(12ul, 1u, -7);

    int sum = 0;
    visit(tuple, [&] (auto v) { sum += v; });

    REQUIRE(sum == 6);
}

namespace {
    struct price { int value; };
    struct opaque {};
}

template <class F>
void visit(price& p, F&& f) {
    f(p.value);
}

TEST_CASE("visitors custom types", "[visitors]") {
    static_assert(!traits::is_visitable<opaque>);
    static_assert( traits::is_visitable<price>);

    price p{ 42 };

    int value = 0;
    visit(p, [&] (auto v) { value += v; });

    REQUIRE(value == 42);
}
