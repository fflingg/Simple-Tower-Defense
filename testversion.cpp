#include <iostream>
#include <SFML/System.hpp>

int main() {
    std::cout << "SFML version: "
              << SFML_VERSION_MAJOR << "."
              << SFML_VERSION_MINOR << "."
              << SFML_VERSION_PATCH << std::endl;
    return 0;
}