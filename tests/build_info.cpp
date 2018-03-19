
#include <catch.hpp>
#include <build_info.hpp>

TEST_CASE("build_info", "[build_info]") {
    REQUIRE(build::current_target == build::target::tests);
    REQUIRE(build::has_resources  == false);
    REQUIRE(build::resources_path == nullptr);
}
