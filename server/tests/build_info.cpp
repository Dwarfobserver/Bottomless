
#include <catch.hpp>
#include <build_info.hpp>


TEST_CASE("build_info", "[environment]") {
    CHECK(build::current_target == build::target::server);
    CHECK(build::has_resources);
}
