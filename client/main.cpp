
#include <iostream>
#include <utility.hpp>

int main() {
    std::cout << "Bottomless -- client v" << build::version_string
              << " (" << build::mode_string << ")\n";

    std::cin.get();
}
