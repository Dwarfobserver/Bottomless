
#include <iostream>
#include <build_info.hpp>

int main() {
    char const* me = build::current_target == build::target::client
        ? "client" : build::current_target == build::target::server
        ? "server" : build::current_target == build::target::tests
        ? "tests"  : "unknown";

    std::cout << "Hello " << me << " !\n";
    std::cout << "In debug ? " << (build::current_mode == build::mode::debug) << "\n";
    std::cout << "Resources path = " << build::resources_path << "\n";
}
