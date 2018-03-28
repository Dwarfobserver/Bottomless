
#include <catch.hpp>
#include <visitors.hpp>

TEST_CASE("visitors iterables", "[visitors]") {
    std::vector<int> ints{ 2, 1, 7 };

    int sum = 0;
    visit(ints, [&] (int v) { sum += v; });

    REQUIRE(sum == 10);
}

TEST_CASE("visitors tuples", "[visitors]") {
    auto tuple = std::make_tuple(12ul, 1u, -7);

    int sum = 0;
    visit(tuple, [&] (auto v) { sum += v; });

    REQUIRE(sum == 6);
}
