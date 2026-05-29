/**
 * @file example_print_version.cpp
 * @brief Версия библиотеки CircuitGenGenerator.
 */
#include <CircuitGenGenerator/CircuitGenGenerator.hpp>
#include <iostream>

auto main() -> int {
  std::cout << "CircuitGenGenerator version "
            << CircuitGenGenerator::getVersion() << '\n';
  return 0;
}
