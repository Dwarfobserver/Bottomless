
#include <iostream>
#include <utility.hpp>

namespace {
    void check_environment() {
        ASSERT(build::current_target == build::target::client, "Wrong current target");
        ASSERT(build::has_resources, "Has the resources path");
    }
}

int main() {
    auto waitInput = defer([] { std::cin.get(); });
    try {
        check_environment();
        std::cout << "Bottomless client v" << build::version_string
                  << " (" << build::mode_string << ")\n";
    }
    catch(std::exception& e) {
        std::cout << "Error\n" << e.what() << '\n';
        return 1;
    }
}
