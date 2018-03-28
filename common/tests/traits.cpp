
#include <catch.hpp>
#include <aggregates_to_tuples.hpp>

namespace {
    class priv { priv() {} };
    struct empty {};
    struct person {
        const char* name;
        int age;
    };
}

TEST_CASE("traits iterables", "[traits]") {
    static_assert(!traits::is_iterable<float>);
    static_assert( traits::is_iterable<std::vector<float>>);
}

TEST_CASE("traits aggregates", "[traits]") {
    static_assert(traits::arity_of<priv>  == -1, "");
    static_assert(traits::arity_of<empty>  == 0, "");
    static_assert(traits::arity_of<person> == 2, "");
    
    person p{ "Alex", 24 };

    auto tuple_val = to_tuple(p);
    auto tuple_ref = as_tuple(p);

    p.age += 2;
    CHECK(std::get<1>(tuple_val) == 24);
    CHECK(std::get<1>(tuple_ref) == 26);
}
