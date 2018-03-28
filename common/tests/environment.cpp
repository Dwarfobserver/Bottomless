
#include <catch.hpp>
#include <build_info.hpp>
#include <string>


TEST_CASE("build_info", "[environment]") {
    using namespace std::string_literals;

    if (build::current_mode == build::mode::debug) {
        CHECK(build::mode_string == "debug"s);
    }
    else {
        CHECK(build::current_mode == build::mode::release);
        CHECK(build::mode_string == "release"s);
    }

    CHECK(build::current_target == build::target::common);
    CHECK(build::target_string  == "common"s);

    CHECK(build::has_resources == false);

    CHECK(build::version_major + build::version_minor > 0);

    auto vMajor = std::to_string(build::version_major);
    auto vMinor = std::to_string(build::version_minor);
    CHECK(build::version_string == vMajor + "." + vMinor);
}
