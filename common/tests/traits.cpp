
#include <catch.hpp>
#include <serial/aggregate_traits.hpp>


namespace {
    class priv { priv() {} };
    struct empty {};
    struct person {
        int age;
        const char* name;
    };
}

TEST_CASE("aggregates", "[traits]") {
    static_assert(traits::arity_of<priv>  == -1, "");
    static_assert(traits::arity_of<empty>  == 0, "");
    static_assert(traits::arity_of<person> == 2, "");
}

