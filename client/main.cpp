
#include <iostream>
#include <utility.hpp>

namespace {
    void check_environment() {
        ASSERT(build::current_target == build::target::client, "Wrong current target");
        ASSERT(build::has_resources, "Has the resources path");
    }
}

int main() {
    std::cout << "Bottomless -- client v" << build::version_string
              << " (" << build::mode_string << ")\n";

    auto waitInput = defer([] { std::cin.get(); });
    try {
        check_environment();
    }
    catch(std::exception& e) {
        std::cout << "Exception caught :\n" << e.what() << '\n';
        return 1;
    }
}
